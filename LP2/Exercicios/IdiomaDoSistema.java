import java.util.Locale;

public class IdiomaDoSistema{
  public static void main(String[] args){
   Locale local = Locale.getDefault();
   System.out.println("O idioma do sistema e: " + local.getDisplayLanguage());
   }
}