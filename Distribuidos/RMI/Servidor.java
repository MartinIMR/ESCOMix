import java.rmi.Naming;

public class Servidor
{
  
  public static void main(String[] args) throws Exception
  {
	    
    String url1 = "rmi://localhost/nodo1";
    String url2 = "rmi://localhost/nodo2";
    String url3 = "rmi://localhost/nodo3";
	
    Nodo nodo1 = new Nodo();
    Nodo nodo2 = new Nodo();
    Nodo nodo3 = new Nodo();
    
    // Rebinds the specified name to a new remote object
    Naming.rebind(url1,nodo1);
    Naming.rebind(url2,nodo2);
    Naming.rebind(url3,nodo3);
    
  }
  
}
