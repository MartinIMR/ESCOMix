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
				//Reservar espacio para matriz A y B 
				int espacio = (N/2) * (N);
				ByteBuffer bb = ByteBuffer.allocate(2 * espacio * (Double.BYTES));
				int iniA = 0,iniB = 0,finA = 0,finB = 0;
				switch(nodo)
				{
					case 1:
					// Enviar A1 y B2
					iniA = 0;
					finA = N/2;
					
					iniB = N/2;
					finB = N;
					break;
					case 2:
					// Enviar A2 y B1 
					iniA = N/2;
					finA = N;
					
					iniB = 0;
					finB = N/2;
					break;
					case 3:
					// Enviar A2 y B2 
					iniA = N/2;
					finA = N;
					
					iniB = N/2;
					finB = N;
					break;
				}
				for(; iniA < finA; iniA++ )
				{
					for(int j = 0; j < N; j++)
					{
						bb.putDouble(A[iniA][j]);
					}
				}
				for(; iniB < finB; iniB++ )
				{
					for(int j = 0; j < N; j++)
					{
						bb.putDouble(B[iniB][j]);
					}
				}

				// Escribir y enviar 
				byte[] bytes = bb.array();
				salida.write(bytes);
				salida.flush();
				
				// Recibir matriz calculada 
				espacio = (N/2) * (N/2);
				bytes = new byte[espacio*(Double.BYTES)];
				entrada.read(bytes,0, espacio * (Double.BYTES)); 
				bb = ByteBuffer.wrap(bytes);
				//Usaremos iniA e iniB como donde iniciar en filas y columnas
				//Usaremos finA y fibB como donde terminar en filas y columnas
				switch(nodo)
				{
					case 1:
					// Recibir cuadrante superior derecho
					iniA = 0;
					finA = N/2;
					iniB = N/2;
					finB = N;
					break;
					case 2:
					// Recibir cuadrante inferior izquierdo
					iniA = N/2;
					finA = N;
					iniB = 0;
					finB = N/2;
					break;
					case 3:
					// Recibir cuadrante inferior derecho
					iniA = N/2;
					finA = N;
					iniB = N/2;
					finB = N;
					break;
				}
				for (int i = iniA; i < finA; i++)
				{	
					for(int j = iniB; j < finB; j++)
					{
						C[i][j] = bb.getDouble();
					}
				}
				// Indicar termino 
				synchronized(lock){  nt++; }
				salida.close();	
				entrada.close();
				conexion.close();
			}catch(IOException ioe)
			{
				ioe.printStackTrace();
			}
		}
		
   }
   
   public static void main(String [] args) throws Exception
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
		System.out.println("Matriz A creada es:");
		imprimirMatriz(A);
		System.out.println("Matriz B creada es:");
		imprimirMatriz(B);
		/* Esperar la conexion de los tres nodos */
		ServerSocket servidor = new ServerSocket(50000);
		for(byte i = 0; i < 3; i++)
		{
				Socket conexion = servidor.accept();
				Worker worker = new Worker(conexion);
				worker.start();
		}
		/* Calculo de cuadrante superior izquierdo */
		// A1 * B1
		for(int i = 0; i < N/2; i++ ) //Filas de A
		{
			for(int j = 0; j < N/2; j++) //Filas de B
			{
				 double suma = 0;
				 for(int k = 0; k < N ; k++) //Columnas
				 {
					suma += A[i][k] * B[j][k]; 
				 }
				 C[i][j] = suma;
 			}
		}
		synchronized(lock){  nt++; }	// Indicar termino de calculo 
 		while( nt != 4 ){  Thread.sleep(1000);  } // Esperar finalizacion de todos los nodos
		System.out.println("Matriz C calculada es:");
		imprimirMatriz(C);
		// Calcular checksum de la matriz C 
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
			salida.flush();
			System.out.println("Nodo "+nodo);
			// Recibir matrices
			int espacio = (N/2) * N;
            byte[] bytes = new byte[espacio*(Double.BYTES)];
			System.out.println("Recibiendo matrices...");
			//Leer la primera matriz
            entrada.read(bytes,0, espacio * (Double.BYTES)); 
            ByteBuffer bb = ByteBuffer.wrap(bytes);
            for (int i = 0; i < (N/2); i++)
			{	
				for(int j = 0; j < N; j++)
				{
					A[i][j] = bb.getDouble();
				}
			}
			//Leer la segunda matriz
			entrada.read(bytes,0, espacio * (Double.BYTES)); 
            bb = ByteBuffer.wrap(bytes);
			for (int i = 0; i < (N/2); i++)
			{	
				for(int j = 0; j < N; j++)
				{
					B[i][j] = bb.getDouble();
				}
			}
			System.out.println("Matrices recibidas!");
			//Multiplicar Matrices 
			for(int i = 0; i < N/2; i++ ) //Filas de A
		    {
			    for(int j = 0; j < N/2; j++) //Filas de B
			    {
				   double suma = 0;
				   for(int k = 0; k < N ; k++) //Columnas
				   {
					 suma += A[i][k] * B[j][k]; 
				   }
				   C[i][j] = suma;
 			    }
		    }
			System.out.println("Se calculo el siguiente cuadrante:");
			for(int i = 0; i < (N/2); i++){
				for(int j = 0; j < (N/2); j++){
					System.out.print(C[i][j]);
				    System.out.print(" ");
				}
				System.out.println("");
			}
			System.out.println("Enviando...");
			// Enviar matriz calculada 
			espacio = (N/2) * (N/2);
			bb = ByteBuffer.allocate(espacio * (Double.BYTES));
			for(int i = 0; i < N/2; i++ )
			{
				for(int j = 0; j < N/2; j++)
				{
					bb.putDouble(C[i][j]);
				}
			} 
			bytes = bb.array();
			salida.write(bytes);
			salida.flush();
			System.out.println("Enviado!");
			/*
			System.out.println("Matriz A recibida es:");
			for(int i = 0; i < (N/2); i++){
				for(int j = 0; j < N; j++){
					System.out.print(A[i][j]);
				    System.out.print(" ");
				}
				System.out.println("");
			}	
			System.out.println("Matriz B recibida es:");
			for(int i = 0; i < (N/2); i++){
				for(int j = 0; j < N; j++){
					System.out.print(B[i][j]);
				    System.out.print(" ");
				}
				System.out.println("");
			}	
			*/
			entrada.close();
			salida.close();
			conexion.close();
			System.out.println("Fin de nodo "+nodo);
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