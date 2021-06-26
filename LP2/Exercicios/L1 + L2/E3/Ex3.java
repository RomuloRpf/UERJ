import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;


public class Ex3
{
	public static void main(String[] args) throws IOException
	{
		int num;
		ArrayList pessoas = new ArrayList();
		BufferedReader inData = new BufferedReader(new InputStreamReader(System.in));
		String opcao;
		MinhaListaOrdenavel lista = new MinhaListaOrdenavel();
		lista.add(new Homem("Joao","10/10/1990",65.9,1.77));
		lista.add(new Mulher("Maria","25/11/1980",60,1.62));
		lista.add(new Homem("Pedro","10/10/1990",88.7,1.85));
		lista.add(new Mulher("Marta","25/08/1980",65.9,1.77));
		lista.add(new Homem("Marcos","02/05/1993",55.7,1.90));
		lista.add(new Mulher("Carla","12/10/1965",70.9,1.68));
		lista.add(new Homem("Zezinho","15/10/1987",100.5,1.96));
		lista.add(new Mulher("Ana","30/06/1980",59.8,1.58));
		lista.add(new Homem("Carlos","10/10/1990",80,1.70));
		lista.add(new Mulher("Carol","25/1/1980",62.6,1.87));
		while(true)
		{
			try
			{
				System.out.println("1.Imprimir Lista");
				System.out.println("2.Sair");
				System.out.print("Digite sua opcao: ");
				opcao = inData.readLine();	
				if(opcao.compareTo("1")==0)
				{
					System.out.println("Escolha seu modo de ordenacao");
					System.out.println("1.Alfabetica (A-Z)");
					System.out.println("2.Alfabetica (Z-A)");
					System.out.println("3.Menor Peso");
					System.out.println("4.Maior Peso");
					System.out.println("5.Maior Altura");
					System.out.println("6.Menor IMC");
					System.out.print("Digite sua opcao: ");
					opcao = inData.readLine();
					System.out.println("");
					num = Integer.parseInt(opcao);
					pessoas = lista.ordena(num);
					for(int i=0; i< pessoas.size(); i++)
					{
						System.out.println(pessoas.get(i));
					}
				}
				else if(opcao.compareTo("2")==0)
				{
					break;
				}
				else
				{
					System.out.println("----Opcao Invalida!!!");
				}
			}
			catch(NumberFormatException e)
			{
				System.out.println("----Digite um numero inteiro!!!");
			}
			catch(IllegalArgumentException invalido)
			{
				System.out.println("----Opcao Invalida");
			}
			catch(IOException e)
			{
				System.out.println(e);
			}
			catch(Exception e)
			{
				System.out.println(e);
			}
		}
	}
}