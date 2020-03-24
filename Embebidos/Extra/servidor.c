#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include "defs.h"


void inicializar_demonio(void);
void isr(int);
void establecer_servidor(void);

int socket_fd;
struct sockaddr_in direccion_servidor; /* Estructura de la familia AF_INET, que almacena direccion */

int 
main(int argc, char **argv)
{

    inicializar_demonio();
    int cliente_sockfd;
    char fdarg[12],fname[] = "/usr/local/bin/serial";
    pid_t pid;
    establecer_servidor();
    while(TRUE)
    {
   	if( (cliente_sockfd = accept(socket_fd, NULL, NULL)) < 0 )
	{
		perror("Ocurrio algun problema al atender a un cliente");
		exit(1);
   	}
        sprintf(fdarg,"%d",cliente_sockfd);
        char * args[3] = {fname,fdarg,NULL};
        pid = fork();
        if(!pid)
        {
          printf("PID hijo:%d\n",getpid());
          execvp(fname,args);
          _exit(0); 
        }
        close(cliente_sockfd);
    }
    close(socket_fd);
    return 0;
}


void 
establecer_servidor(void)
{
  /* Llenar la estructura de dirección con ceros */
  memset(&direccion_servidor, 0, sizeof (direccion_servidor));

  /* Asignacion de parametros de la estructura */
  direccion_servidor.sin_family = AF_INET; /* IPv4 */
  direccion_servidor.sin_port = htons(PUERTO); /* htons - El ordenamiento de bytes en la red es siempre big-endian, arquitecturas little-endian revertir bytes */
  direccion_servidor.sin_addr.s_addr = INADDR_ANY; /* La dirección del host puede ser cualquiera */

  /* Creación del socket del servidor, regresa un file descriptor de este mismo */
  printf("Creando Socket ....\n");
  if( (socket_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
  {
     perror("Ocurrio un problema en la creacion del socket");
     exit(1);
  }

  /* Asociar el fd del socket con una direccion de red */ 
  printf("Configurando socket ...\n");
  if( bind(socket_fd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0 )
  {
     perror ("Ocurrio un problema al configurar el socket");
     exit(1);
  }

  /* El socket estará en espera de solicitudes, esto es, sera pasivo y creara una cola para solicitudes */
  printf ("Estableciendo la aceptacion de clientes...\n");
  if( listen(socket_fd, COLA_CLIENTES) < 0 )	
  {
     perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
     exit(1);
  }
  
  /* Asignacion de la señal */
  if(signal(SIGCLD,isr) == SIG_ERR)
  {
     perror("Error al signar la señal");
     exit(-1);
  }

  /* Version señal usuario  
  if(signal(SIGUSR1,isr) == SIG_ERR)
  {
     perror("Error al asignar la senial\n");
     exit(EXIT_FAILURE);
  }
  */

  

}

void 
inicializar_demonio(void)
{
   FILE *apArch;
    pid_t pid = 0;
    pid_t sid = 0;
    int cont = 0;
// Se crea el proceso hijo
    pid = fork();
    if( pid == -1 )
    {
		perror("Error al crear el primer proceso hijo\n");
		exit(EXIT_FAILURE);
    }
/*
 * Se termina Proceso padre.
 * Al finalizar el proceso padre el proceso hijo es adoptado por init. 
 * El resultado es que la shell piensa que el comando terminó con éxito, 
 * permitiendo que el proceso hijo se ejecute de manera independiente en segundo plano.
 */
    if( pid )
    {
		printf("Se termina proceso padre, PID del proceso hijo %d \n", pid);
		exit(0);
    }
/* Se restablece el modo de archivo
 * Todos los procesos tiene una máscara que indica que permisos no deben establecerse al crear nuevos archivos. 
 * Así cuando se utilizan llamadas al sistema como open() los permisos especificados se comparan con esta máscara, 
 * desactivando de manera efectiva los que en ella se indiquen.
 * La máscara —denominada umask()— es heredada de padres a hijos por los procesos, por lo que su valor por defecto 
 * será el mismo que el que tenía configurada la shell que lanzó el demonio. Esto significa que el demonio no sabe 
 * que permisos acabarán tenido los archivos que intente crear. Para evitarlo simplemente podemos autorizar todos 
 * los permisos 
 */
    umask(0);
/*
 * se inicia una nueva sesion
 * Cada proceso es miembro de un grupo y estos a su vez se reúnen en sesiones. En cada una de estas hay un proceso 
 * que hace las veces de líder, de tal forma que si muere todos los procesos de la sesión reciben una señal SIGHUP.
 * La idea es que el líder muere cuando se quiere dar la sesión por terminada, por lo que mediante SIGHUP se 
 * notifica al resto de procesos esta circunstancia para que puedan terminar ordenadamente.
 * Obviamente no estamos interesados en que el demonio termine cuando la sesión desde la que fue creado finalice, 
 * por lo que necesitamos crear nuestra propia sesión de la que dicho demonio será el líder.
 */
    sid = setsid();
    if( sid < 0 )
    {
		perror("Error al iniciar sesion");
		exit(EXIT_FAILURE);
    }
// Se realiza un segundo fork para separarnos completamente de la sesion del padre
    pid = fork( );
    if( pid == -1 )
    {
		perror("Error al crear el segundo proceso hijo\n");
		exit(EXIT_FAILURE);
    }
    if( pid )
    {
		printf("PID del segundo proceso hijo %d \n", pid);
		apArch = fopen("/var/run/demonio.pid", "w");
		fprintf(apArch, "%d", pid);
		fclose(apArch);

		exit(0);
    }
/* 
 * Se cambia el directorio actual por root.
 * Hasta el momento el directorio de trabajo del proceso es el mismo que el de la shell en el momento en el
 * que se ejecutó el comando. Este podría estar dentro de un punto de montaje cualquiera del sistema, por lo
 * que no tenemos garantías de que vaya a seguir estando disponible durante la ejecución del proceso.
 * Por eso es probable que prefiramos cambiar el directorio de trabajo al directorio raíz, ya que podemos
 * estar seguros de que siempre existirá
 */
    chdir("/");
/*
 * Se cierran los flujos de entrada y salida: stdin, stdout, stderr
 * Puesto que un demonio se ejecuta en segundo plano no debe estar conectado a ninguna terminal. 
 * Sin embargo esto plantea la cuestión de cómo indicar condiciones de error, advertencias u otro 
 * tipo de sucesos del programa. Algunos demonios almacenan estos mensajes en archivos específicos 
 * o en su propia base de datos de sucesos. Sin embargo en muchos sistemas existe un servicio especifico 
 * para registrar estos eventos. En lo sistemas basados en UNIX este servicio lo ofrece el demonio Syslog, 
 * al que otros procesos pueden enviar mensajes a través de la función syslog()
 */
    close( STDIN_FILENO  );
    close( STDOUT_FILENO );
    close( STDERR_FILENO );


}



void 
isr(int sig)
{
   int estado;
   pid_t pid;
   if(sig == SIGCLD)
   {
      pid = wait(&estado);
      printf("señal SIGCLD detectada en proceso hijo: %d\n",pid);
   }
}

/* Version señal del usuario 
void 
isr(int sig)
{
  int estado;
  pid_t pid;
  if(sig == SIGUSR1)
  {
     pid = wait(&estado);
     printf("Senial USR1 detectada en proceso hijo: %d\n", pid);
  }
}
*/
