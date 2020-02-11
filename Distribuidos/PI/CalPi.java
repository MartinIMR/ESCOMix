import java.net.Socket;
import java.net.ServerSocket;
import java.lang.Thread;
import java.io.IOException;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.nio.ByteBuffer;


class CalPi
{
   protected static int n = 0;
   protected static Object lock = new Object(); 
   protected static double pi = 0;
   
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
				double sp = entrada.readDouble();
				synchronized(lock)
				{
					pi += sp;
					n++;
				}
				entrada.close();
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
		System.out.println("Introduce el número de nodo");
		System.exit(-1);
     }
	 int nodo;
	 nodo = Integer.valueOf(args[0]);
	 double sp = 0;
	 switch(nodo)
	 {
		case 0:
		try
		{
			ServerSocket servidor = new ServerSocket(50000);
			for(byte i = 0; i < 3; i++)
			{
				Socket conexion = servidor.accept();
				Worker worker = new Worker(conexion);
				worker.start();
			}
			double denominador = 0;
			for(int i = 0; i < 10000000; i++ )
			{
				denominador = (8 * i) + 1 ;
				sp += ( 1 / denominador ); 
			}
			synchronized(lock)
			{	
				pi += sp;
				n++;
			}
			while( n != 4)
			{
				Thread.sleep(1000);
			}
		}catch(IOException ioe)
		{
			ioe.printStackTrace();
		}catch(InterruptedException ie)
		{
			ie.printStackTrace();
		}finally{
			pi = pi * 4;
			System.out.println("El valor de pi es:");
			System.out.println(pi);
		}
		break;
		
		case 1:
		try
		{
			Socket conexion = new Socket("localhost",50000);
			DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
			double denominador = 0;
			for(int i = 0; i < 10000000; i++ )
			{
				denominador =  (8 * i) + 3;
				sp -= (1 / denominador); 
			}
			salida.writeDouble(sp);
			salida.flush();
			salida.close();
			conexion.close();
		}catch(IOException ioe)
		{
			ioe.printStackTrace();
		}
		break;
		case 2:
		try
		{
			Socket conexion = new Socket("localhost",50000);
			DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
			double denominador = 0;
			for(int i = 0; i < 10000000; i++ )
			{
				denominador = (8 * i) + 5;
				sp += ( 1 / denominador ); 
			}
			salida.writeDouble(sp);
			salida.flush();
			salida.close();
			conexion.close();
		}catch(IOException ioe)
		{
			ioe.printStackTrace();
		}
		break;
		case 3:
		try
		{
			Socket conexion = new Socket("localhost",50000);
			DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
			double denominador = 0;
			for(int i = 0; i < 10000000; i++ )
			{
				denominador = (8 * i) + 7;
				sp -= ( 1 / denominador ); 
			}
			salida.writeDouble(sp);
			salida.flush();
			salida.close();
			conexion.close();
		}catch(IOException ioe)
		{
			ioe.printStackTrace();
		}
		break;
		default:
		System.out.println("Nodo ingresado no valido...");
		System.exit(-1);
		break;
	 }
	 
   }

}