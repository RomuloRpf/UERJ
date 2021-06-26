import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Vector;

public class Ex2
{
	public static void main(String[] args) throws IOException, NomeInvalido, PesoInvalido, AlturaInvalida, SexoInvalido
	{
		Vector<Pessoa> pessoas = new Vector<Pessoa>();
		int numerodepessoas=0, aux=1;	
		String sexo="", nome="",datadenascimento="";
		String straux="";
		double peso=0, altura=0;
		Homem h;
		Mulher m;
		boolean parada = false;
		
		BufferedReader inData = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Digite o numero de pessoas:");
		while (parada == false)
		{
			try
			{
				straux = inData.readLine();
				if(straux.equals("")==true)
				{
					throw new IllegalArgumentException("inteiro_nao_positivo");
				}
				numerodepessoas = Integer.parseInt(straux);
				if(numerodepessoas<=0)
				{
					throw new IllegalArgumentException("inteiro_nao_positivo");
				}
				parada = true;
			}
			catch(NumberFormatException e)
			{
				System.out.println("--- Digite um numero inteiro!!!");
			}
			catch(IllegalArgumentException inteiro_nao_positivo)
			{
				System.out.println("--- Digite um numero inteiro maior que zero!!!");
			}
		}
		parada = false;
		for(int i=0; i<numerodepessoas; i++)
		{
			while (parada == false)
			{
				try
				{
					switch(aux)
					{
						case 1:
							System.out.println("Inserir homem (h) ou mulher(m)?");
							straux = inData.readLine();
							sexo = straux.toLowerCase();
							if((sexo.compareTo("h")==0) || (sexo.compareTo("m")==0))
							{
								aux ++;
							}
							else
							{
								throw new SexoInvalido();
							}
						case 2:
							System.out.println("Digite o nome:");
							nome = inData.readLine();
							if(verificaNome(nome) == false)
							{
								throw new NomeInvalido(); 
							}
							aux ++;
						case 3:
							System.out.println("Digite a data de nascimento:");
							datadenascimento = inData.readLine();
							aux ++;
						case 4:
							System.out.println("Digite o peso:");
							straux = inData.readLine();
							if(verificaPeso(straux) == false)
							{
								throw new PesoInvalido();
							}
							peso = Double.parseDouble(straux);
							if(peso==0)
							{
								throw new PesoInvalido();
							}
							aux ++;
						case 5:
							System.out.println("Digite a altura (em metros):");
							straux = inData.readLine();
							if(verificaAltura(straux) == false)
							{
								throw new AlturaInvalida();
							}
							altura = Double.parseDouble(straux);
							if(altura==0)
							{
								throw new AlturaInvalida();
							}
					}
					if(sexo.compareTo("h")== 0)
					{
						h = new Homem(nome,datadenascimento,peso,altura);
						pessoas.add(h);
					}
					else if(sexo.compareTo("m")== 0)
					{
						m = new Mulher(nome,datadenascimento,peso,altura);
						pessoas.add(m);
					}
					parada = true;
				}
				catch(SexoInvalido sexo_invalido)
				{
					System.out.println("--- Opcao Invalida!!!");
				}
				catch(NomeInvalido nome_invalido)
				{
					System.out.println("--- O nome nao pode conter numeros!!!");
				}
				catch(PesoInvalido peso_invalido)
				{
					System.out.println("--- O peso deve ser um numero real maior que zero!!!");
				}
				catch(AlturaInvalida altura_invalida)
				{
					System.out.println("--- A altura deve ser um numero real maior que zero!!!");
				}
			}
		}
		System.out.println("-------------");
		System.out.println("-------------");
		
		for(int j=0; j<numerodepessoas; j++)
		{
			System.out.println(pessoas.elementAt(j));
		}
	}
	public static boolean verificaNome(String validarnome)
	{
		for(int i=0;i<validarnome.length();i++)
		{
			if(Character.isDigit(validarnome.charAt(i))== true)
			{
				return false;
			}
		}
		return true;
	}
	public static boolean verificaPeso(String validarpeso)
	{
		for(int i=0;i<validarpeso.length();i++)
		{
			if(Character.isDigit(validarpeso.charAt(i))== false)
			{
				if(validarpeso.charAt(i) != '.')
				{
					return false;
				}
			}
		}
		return true;
	}
	public static boolean verificaAltura(String validaraltura)
	{
		for(int i=0;i<validaraltura.length();i++)
		{
			if(Character.isDigit(validaraltura.charAt(i))== false)
			{
				if(validaraltura.charAt(i)!= '.')
				{
					return false;
				}
			}
		}
		return true;
	}
}