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
				System.out.println("Nodo recibido es:"+nodo);
				//Reservar espacio para matriz A y B 
				int espacio = (N/2) * (N);
				ByteBuffer bf = ByteBuffer.allocate( 2 * espacio * (Double.BYTES));
				int iniA = 0,iniB = 0,finA = 0,finB = 0;
				switch(nodo)
				{
					case 1:
					// Enviar A1 y B2
					iniA = 0;
					finA = (N/2) - 1;
					iniB = N/2;
					finB = N;
					break;
					case 2:
					// Enviar A2 y B1 
					iniA = N/2;
					finA = N;
					iniB = 0;
					finB = (N/2) - 1;
					break;
					case 3:
					// Enviar A2 y B2 
					iniA = N/2;
					finA = N;
					iniB = N/2;
					finB = N;
					break;
				}
				// Poner matriz A
				for(; iniA < finA; iniA++ )
				{
					for(int j = 0; j < N; j++)
					{
						bf.putDouble(A[iniA][j]);
					}
				}
				// Poner matriz B
				for(; iniB < finB; iniB++ )
				{
					for(int j = 0; j < N; j++)
					{
						bf.putDouble(A[iniB][j]);
					}
				}
				// Escribir y enviar 
				byte[] bArr = bf.array();
				salida.write(bArr);
				salida.flush();
				// Recibir matriz 
				
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
		synchronized(lock){  nt++; }	// Indicar termino de calculo 
 		while( nt != 4 ){  Thread.sleep(1000);  } // Esperar finalizacion de todos los nodos
		/* Calculo de cuadrante superior izquierdo */
		// A1 * B1
		/*
		int limite = (N/2) - 1 ;
		for(int i = 0; i < limite; i++ ) //Filas de A
		{
			for(int j = 0; j < limite; j++) //Filas de B
			{
				 double suma = 0;
				 for(int k = 0; k < N ; k++) //Columnas
				 {
					suma += A[i][k] + B[j][k]; 
				 }
				 C[i][j] = suma;
 			}
		}
		synchronized(lock){  nt++; }	// Indicar termino de calculo 
 		while( nt != 4 ){  Thread.sleep(1000);  } // Esperar finalizacion de todos los nodos
		// Calcular checksum de la matriz C 
		*/
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
			// Recibir matrices
			int espacio = (N/2) * N;
            byte[] arrA = new byte[espacio*(Double.BYTES)];
			byte[] arrB = new byte[espacio*(Double.BYTES)];
            entrada.read(arrA,0,espacio * (Double.BYTES)); //Leer la primera matriz
			entrada.read(arrB,espacio, espacio * (Double.BYTES)); //Leer la segunda matriz
            ByteBuffer bA = ByteBuffer.wrap(arrA);
			ByteBuffer bB = ByteBuffer.wrap(arrB);
            for (int i = 0; i < (N/2); i++)
			{	
				for(int j = 0; j < N; j++)
				{
					A[i][j] = bA.getDouble();
					B[i][j] = bB.getDouble();
				}
			}
			System.out.println("Nodo numero:"+nodo);
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
			entrada.close();
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