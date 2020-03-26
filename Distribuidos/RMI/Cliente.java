import java.rmi.Naming;

public class Cliente_rmi
{
  public static void main(String args[]) throws Exception
  {
	  
	if(args.length < 1)
    {
		System.err.println("Introduce el número de nodo");
		System.exit(-1);
    }  
	System.out.println("Matrices de dimensiones "+N+"x"+N);
	  
    String url1 = "rmi://localhost/nodo1";
    String url2 = "rmi://localhost/nodo2";
    String url3 = "rmi://localhost/nodo3";

    // Returns a reference, a stub, for the remote object associated with the specified name
	Nodo n0 = (Nodo)Naming.lookup(url0);
    Nodo n1 = (Nodo)Naming.lookup(url1);
	Nodo n2 = (Nodo)Naming.lookup(url2);
	Nodo n3 = (Nodo)Naming.lookup(url3);
	
  }
  
}
