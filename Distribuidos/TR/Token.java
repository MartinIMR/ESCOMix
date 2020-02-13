import java.net.Socket;
import java.net.ServerSocket;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.lang.Thread;
import java.nio.ByteBuffer;

class Token
{
  static int nodo;
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
	    int puerto = ((nodo + 1)%4) + 50000;
	    Socket cliente = null;
	    while(true)
	    {
		  try{
	      cliente = new Socket("localhost",puerto);
		  break;
		  }catch(Exception e)
		  {
			Thread.sleep(1000);
		  }
	    }
	    DataOutputStream salida = new DataOutputStream(cliente.getOutputStream());
      
	  }catch(Exception e)
	  {
	
		 e.printStackTrace();
	  }
	  
	}
	
  }
  
  
  public static void main(String[] args) throws Exception
  {
	 if(args.length < 1) 
     {
		System.err.println("Introduce el número de nodo");
		System.exit(-1);
     }
     nodo = Integer.valueOf(args[0]);
     ServerSocket servidor = new ServerSocket(50000 + nodo); //El socket que escucha
     for (;;)
     {
      Socket conexion = servidor.accept();
      Worker worker = new Worker(conexion);
      worker.start();
     }
  }
  
}
