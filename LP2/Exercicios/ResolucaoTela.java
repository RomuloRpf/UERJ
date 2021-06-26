import java.awt.Toolkit;
import java.awt.Dimension;

public class ResolucaoTela{
 public static void main(String[] args){
  Toolkit tk = Toolkit.getDefaultToolkit();
  Dimension tela = tk.getScreenSize();
  System.out.println("A resolucao do sistema e: "+ tela.width +" X "+ tela.height);
  }
}