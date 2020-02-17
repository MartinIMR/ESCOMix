import java.net.Socket;
import java.net.ServerSocket;
import java.lang.Thread;
import java.io.IOException;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.nio.ByteBuffer;


class MulMat
{
   protected static int N = 120;
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
				//Reservar espacio para matriz A
				int espacio = (N/2) * (N);
				ByteBuffer bb = ByteBuffer.allocate(espacio * (Double.BYTES));
				int iniA = 0,iniB = 0,finA = 0,finB = 0;
				switch(nodo)
				{
					case 1:
					// Cuadrante superior derecho (A1 y B2)
					iniA = 0;
					finA = iniB = N/2;
					finB = N;
					break;
					case 2:
					// Cuadrante inferior izquierdo (A2 y B1) 
					iniA = finB = N/2;
					finA = N;
					iniB = 0;
					break;
					case 3:
					// Cuadrante inferior derecho (A2 y B2) 
					iniA = iniB = N/2;
					finA = finB = N;
					break;
				}
				double checksum = 0;
				for(int i = iniA; i < finA; i++ )
				{
					for(int j = 0; j < N; j++)
					{
						checksum += A[i][j];
						bb.putDouble(A[i][j]);
					}
				}
				if( N > 9 )
				{
				  	System.out.println("Nodo "+nodo+".Checksum de matriz A a enviar:"+checksum);
				}
				// Escribir y enviar matriz A 
				byte[] bytes = bb.array();
				salida.write(bytes);
				salida.flush();
				//Reservar espacio para matriz B
				bb = ByteBuffer.allocate(espacio * (Double.BYTES));
				checksum = 0;
				for(int i = iniB; i < finB; i++ )
				{
					for(int j = 0; j < N; j++)
					{
						checksum += B[i][j];
						bb.putDouble(B[i][j]);
					}
				}
				if( N > 9 )
				{
				  	System.out.println("Nodo "+nodo+".Checksum de matriz B a enviar:"+checksum);
				}
				// Escribir y enviar matriz B
				bytes = bb.array();
				salida.write(bytes);
				salida.flush();
				
				
				// Recibir matriz calculada 
				espacio = (N/2) * (N/2);
				bytes = new byte[espacio*(Double.BYTES)];
				entrada.read(bytes,0, espacio * (Double.BYTES)); 
				bb = ByteBuffer.wrap(bytes);
				checksum = 0;
				for (int i = iniA; i < finA; i++)
				{	
					for(int j = iniB; j < finB; j++)
					{
						C[i][j] = bb.getDouble();
						checksum += C[i][j];
					}
				}
				if( N > 9 )
				{
				  	System.out.println("Nodo "+nodo+".Checksum de matriz C recibida:"+checksum);
				}
				// Indicar termino 
				synchronized(lock){  nt++; }
				System.out.println("Matriz de nodo "+nodo+" recibida");
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
	 System.err.println("Matrices de dimensiones "+N+"x"+N);
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
		System.out.println("Matriz A creada es:");
		imprimirMatriz(A,N,N);
		System.out.println("Matriz B creada es:");
		imprimirMatriz(B,N,N);
		transponerMatriz(B);
		/* Esperar la conexion de los tres nodos */
		ServerSocket servidor = new ServerSocket(50000);
		for(byte i = 0; i < 3; i++)
		{
				Socket conexion = servidor.accept();
				Worker worker = new Worker(conexion);
				worker.start();
		}
		// Calculo de cuadrante superior izquierdo 
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
		imprimirMatriz(C,N,N);
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
			
			double checksum = 0;
            for (int i = 0; i < (N/2); i++)
			{	
				for(int j = 0; j < N; j++)
				{
					A[i][j] = bb.getDouble();
					checksum += A[i][j];
				}
			}
			if( N > 9 )
			{
				  	System.out.println("Checksum de matriz A recibida:"+checksum);
			}
			checksum = 0;
			//Leer la segunda matriz
			entrada.read(bytes,0, espacio * (Double.BYTES)); 
            bb = ByteBuffer.wrap(bytes);
			for (int i = 0; i < (N/2); i++)
			{	
				for(int j = 0; j < N; j++)
				{
					B[i][j] = bb.getDouble();
					checksum += B[i][j];
				}
			}
			if( N > 9 )
			{
				  	System.out.println("Checksum de matriz B recibida:"+checksum);
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
			System.out.println("Enviando cuadrante calculado...");
			// Enviar matriz calculada 
			espacio = (N/2) * (N/2);
			bb = ByteBuffer.allocate(espacio * (Double.BYTES));
			checksum = 0;
			for(int i = 0; i < N/2; i++ )
			{
				for(int j = 0; j < N/2; j++)
				{
					bb.putDouble(C[i][j]);
					checksum += C[i][j];
				}
			}
			if( N > 9 )
			{
				  	System.out.println("Checksum de matriz C calculada:"+checksum);
			}			
			bytes = bb.array();
			salida.write(bytes);
			salida.flush();
			System.out.println("Enviado!");
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
   
    public static void imprimirMatriz(double [][] matriz, int filas, int columnas)
   {
	   if( filas < 9 || columnas < 9)
	   {
		 for(int i = 0; i < filas; i++) 
		 { 
			for (int j = 0; j < columnas; j++)
			{
				System.out.print(matriz[i][j]);
				System.out.print(" ");
			}
			System.out.println("");
	     }
		 System.out.println(" ");   
	   }else
	   {
		 hacerChecksum(matriz,filas,columnas);  
	   }
   }
   
    public static void hacerChecksum(double [][] matriz, int filas, int columnas)
    {
	   double suma = 0;
	   for(int i = 0; i < filas; i++) 
		{
			for (int j = 0; j < columnas; j++)
			{
				suma += matriz[i][j];
			}
	    }
		System.out.println("El checksum de la matriz es:"+suma);
		System.out.println(" ");
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