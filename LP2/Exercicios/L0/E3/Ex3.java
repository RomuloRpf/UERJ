import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Ex2
{
	public static void main(String[] args)
	{
		BufferedReader inData = null;
		String entrada = "";
		double angGraus = 0;
		for(int i=0; i < numdeargs;i++)
		{
			try
			{
				System.out.println("Digite uma medida em graus do angulo: ");
				inData = new BufferedReader(new InputStreamReader(System.in));
				entrada = inData.readLine();
				}
			}
			catch(NumberFormatException e)
			{
				System.out.println("O argumento, '"+ entrada +"', nao e numero\n");
			}
			catch(IOException e)
			{
				System.out.println("Nao foi possivel ler o dado passado\n");
			}
			catch(ArithmeticException divisao_por_zero)
			{
				System.out.println("Nao e possivel dividir um numero por zero\n");
			}
		}
	}
}