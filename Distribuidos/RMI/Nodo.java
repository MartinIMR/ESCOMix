import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;

public class Nodo extends UnicastRemoteObject implements InterM
{
  // el constructor default requiere reportar que puede producirse RemoteException
  public Nodo throws RemoteException
  {
    super();
  }
  
  public double[][] multiplica_matrices(double[][] A, double[][] B, int N) throws RemoteException
  {
    double[][] C = new double[N/2][N/2];
    for (int i = 0; i < N/2; i++)
      for (int j = 0; j < N/2; j++)
        for (int k = 0; k < N; k++)
          C[i][j] += A[i][k] * B[j][k];
    return C;
  }
  
}
