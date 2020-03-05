import java.rmi.Remote;
import java.rmi.RemoteException;

public interface InterM extends Remote
{
  public double[][] multiplica_matrices(double[][] A,double[][] B)throws RemoteException;
}

