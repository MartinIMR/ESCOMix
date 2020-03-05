import java.rmi.Naming;

public class Cliente_rmi
{
  public static void main(String args[]) throws Exception
  {
    String url = "rmi://localhost/prueba";
    
    String url1 = "rmi://localhost/nodo1";
    String url2 = "rmi://localhost/nodo2";
    String url3 = "rmi://localhost/nodo3";

    // Returns a reference, a stub, for the remote object associated with the specified name
    Nodo n1 = (Nodo)Naming.lookup(url1);
	Nodo n2 = (Nodo)Naming.lookup(url2);
	Nodo n3 = (Nodo)Naming.lookup(url3);
	
    System.out.println(r.mayusculas("hola"));
    System.out.println("suma=" + r.suma(10,20));

    int[][] m = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    System.out.println("checksum=" + r.checksum(m));
  }
}
