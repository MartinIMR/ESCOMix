import java.net.Socket;
import java.net.ServerSocket;
import java.lang.Thread;
import java.io.IOException;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.nio.ByteBuffer;


class MulMat
{	
   
   public static void main(String [] args) throws Exception
   {
	    int N = 4;
	    double [][] A = new double[N][N];
		double [][] B = new double[N][N];
		double [][] C = new double[N][N];
		
		/* Inicializar matrices */
        inicializarMatrices(A,B, N);
		/* Trasponer B */
		transponerMatriz(B, N);
		
		System.out.println("Matriz A creada es:");
		imprimirMatriz(A,N,N);
		System.out.println("Matriz B creada es:");
		imprimirMatriz(B,N,N);
		
		double [][] C1 = multiplica_matrices(copia_matriz(A,0,N), copia_matriz(B,0,N), N);
		double [][] C2 = multiplica_matrices(copia_matriz(A,0,N), copia_matriz(B,N/2,N), N);
		double [][] C3 = multiplica_matrices(copia_matriz(A,N/2,N), copia_matriz(B,0,N), N);
		double [][] C4 = multiplica_matrices(copia_matriz(A,N/2,N), copia_matriz(B,N/2,N), N);
		acomoda(C,C1,0,0,N);
		acomoda(C,C2,0,N/2,N);
		acomoda(C,C3,N/2,0,N);
		acomoda(C,C4,N/2,N/2,N);
		
		imprimirMatriz(C,N,N);
		hacerChecksum(C, N, N);
	 
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
   
   public static void transponerMatriz(double [][] matriz,int N)
   {
	   double aux;
	   for (int i = 0; i < (N-1); i++)
		{
			for (int j = (i+1); j < N; j++)
			{
				aux = matriz[i][j];
				matriz[i][j] = matriz[j][i];
				matriz[j][i] = aux;
			}
		}
   }
   
   public static void inicializarMatrices(double [][] A,double [][] B, int N)
   {
      	for(int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++)
			{
				A[i][j] = 2 * i + j;
				B[i][j] = 2 * i - j;
			}
	    }
   }
   
  public static double[][] copia_matriz(double[][] A,int inicio, int N)
	{
 	 	double[][] M = new double[N/2][N];
 	 	for (int i = 0; i < N/2; i++)
   		   for (int j = 0; j < N; j++)
     		  M[i][j] = A[i + inicio][j];
 		return M;
	}
	
  public static void acomoda(double[][] C,double[][] A,int renglon,int columna, int N)
  {
    for (int i = 0; i < N/2; i++)
      for (int j = 0; j < N/2; j++)
        C[i + renglon][j + columna] = A[i][j];
  }

  public static double[][] multiplica_matrices(double[][] A,double[][] B, int N)
  {
    double[][] C = new double[N/2][N/2];
    for (int i = 0; i < N/2; i++)
      for (int j = 0; j < N/2; j++)
        for (int k = 0; k < N; k++)
          C[i][j] += A[i][k] * B[j][k];
    return C;
  }
   
}
