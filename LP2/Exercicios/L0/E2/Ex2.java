import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Ex2
{
	public static void main(String[] args) 
	{
		BufferedReader inData = null;
		String entrada = "";
		boolean parada = false, argumentoldc = false;
		double angRad = 0, angGraus = 0;
		while (parada==false)
		{
			if(args.length>1)
			{
				System.out.println("Numero de argumentos excessivo.");
			}
			else
			{
				try
				{
					if(args.length==1 && argumentoldc==false)
					{
						argumentoldc = true;
						entrada = args[0];
					}
					else
					{
						System.out.println("Digite uma medida em graus do angulo: ");
						inData = new BufferedReader(new InputStreamReader(System.in));
						entrada = inData.readLine();
					}
					if(entrada.compareTo("") == 0)
					{
						parada = true;
					}
					else
					{
						angGraus = Double.parseDouble(entrada);
						angRad = Angulo.converteAngulo(angGraus);
						System.out.println("Seno: "+ Angulo.funcaoSeno(angRad));
						System.out.println("Coseno: "+ Angulo.funcaoCoseno(angRad));
						System.out.println("Tangente: "+ Angulo.funcaoTangente(angRad));
						System.out.println("Cotangente: "+ Angulo.funcaoCotangente(angRad)+"\n");
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
				catch(TangenteEx tangente_nao_existe)
				{
					System.out.println("Tangente: Nao Existe");
					System.out.println("Cotangente: Nao Existe\n");
				}
				catch(CotangenteEx cotangente_nao_existe)
				{
					System.out.println("Cotangente: Nao Existe\n");
				}
			}
		}
	}
}
