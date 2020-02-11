import java.net.Socket;
import java.net.ServerSocket;
import java.lang.Thread;
import java.io.IOException;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.nio.ByteBuffer;


class MulMat
{
   protected static int N = 4;
   protected static int nt = 0;
   protected static double [][] A;
   protected static double [][] B;
   protected static double [][] C;
   protected static Object lock = new Object(); 
   
   static class Worker extends Thread
   {
	    Socket conexion;
        Worker(Socket conexion)
        {
            this.conexion = conexion;
        }
		
		public void run()
		{
			try
			{
				DataInputStream entrada = new DataInputStream(conexion.getInputStream());
				DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
				int nodo =  entrada.readInt();
				switch(nodo)
				{
					case 1:
					break;
					case 2:
					break;
					case 3:
					break;
				}
				// Enviar 5 numeros de punto flotante
				ByteBuffer b = ByteBuffer.allocate(5*8);
				b.putDouble(1.1);
				b.putDouble(1.2);
				b.putDouble(1.3);
				b.putDouble(1.4);
				b.putDouble(1.5);
				byte[] a = b.array();
				salida.write(a);
				salida.flush();
				synchronized(lock){  nt++; }
				entrada.close();
				salida.close();	
				conexion.close();
			}catch(IOException ioe)
			{
				ioe.printStackTrace();
			}
		}
		
   }
   
   public static void main(String [] args)
   {
     if(args.length < 1)
     {
		System.err.println("Introduce el número de nodo");
		System.exit(-1);
     }
	 int nodo;
	 nodo = Integer.valueOf(args[0]);
	 
	 if( nodo == 0)
	 {
	    A = new double[N][N];
		B = new double[N][N];
		C = new double[N][N];
		System.out.println("Matrices creadas");
		/* Inicializar matrices */
		for(int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++)
			{
				A[i][j] = 2 * i + j;
				B[i][j] = 2 * i - j;
			}
	    }
		/* Trasponer B */
		transponerMatriz(B);
		/* Esperar la conexion de los tres nodos */
		ServerSocket servidor = new ServerSocket(50000);
		for(byte i = 0; i < 3; i++)
		{
				Socket conexion = servidor.accept();
				Worker worker = new Worker(conexion);
				worker.start();
		}
		/* Calculo de cuadrante superior izquierdo */
		int limite = (N/2) - 1 ;
		for(int i = 0; i < limite; i++ )
		{
			for(int j = 0; j < limite; j++)
			{
				C[i][j] = A[i][j] * B[i][j]; 
 			}
		}
		synchronized(lock){  nt++; }	/* Indicar termino de calculo */
 		while( nt != 4 ){  Thread.sleep(1000);  } /* Esperar finalizacion de todos los nodos */ 
		/* Calcular checksum de la matriz C */
	 }else
     {
		A = new double[N/2][N];
		B = new double[N/2][N];
		C = new double[N/2][N/2];
		try
		{
			Socket conexion = new Socket("localhost",50000);
			DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
			DataInputStream entrada = new DataInputStream(conexion.getInputStream());
			salida.writeInt(nodo); //Enviar numero de nodo
			// recibe 5 n�meros punto flotante
            byte[] a = new byte[5*8];
            entrada.read(a,0,5*8);
            ByteBuffer b = ByteBuffer.wrap(a);
            for (int i = 0; i < 5; i++)
			{	
              System.out.println(b.getDouble());    
			}
			salida.flush();
			salida.close();
			conexion.close();
		}catch(IOException ioe)
		{
			ioe.printStackTrace();
		}
	 }
	 
   }
   
    public static void imprimirMatriz(double [][] matriz)
   {
	   for(int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++)
			{
				System.out.print(matriz[i][j]);
				System.out.print(" ");
			}
			System.out.println("");
	    }
   }
   
   public static void transponerMatriz(double [][] matriz)
   {
	   double aux;
	   for (int i = 0; i < (N-1); i++)
		{
			for (int j = (i+1); j < N; j++)
			{
				aux = B[i][j];
				B[i][j] = B[j][i];
				B[j][i] = aux;
			}
		}
   }
   

}