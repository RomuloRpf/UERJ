import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;

public class Ex1
{
	int numeroEmpregados;
	
	public Ex1(int numero_de_empregados)
	{
		numeroEmpregados = numero_de_empregados;
	}
	public boolean verificaNome(String validarnome)
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
	public void calculaSalarios() throws IOException
	{
		ArrayList<FuncionarioContratado> funcionarios = new ArrayList<>();
		String nome="",codigo;
		double salario;
		int numeroDependentes;
		FuncionarioContratado empregado;
		System.out.println("\n- - - Cadastro de Funcionarios - - -\n");
		BufferedReader inData = new BufferedReader(new InputStreamReader(System.in));
		String folhasalarial="";
		
		for(int i=0;i<numeroEmpregados;i++)
		{
			System.out.print("Nome do empregado: ");
			nome = inData.readLine();
			if(verificaNome(nome)==false)
			{
				throw new IllegalArgumentException("nome_invalido");
			}
			System.out.print("Codigo do empregado: ");
			codigo = inData.readLine();
			System.out.print("Salario-base: ");
			salario = Float.parseFloat(inData.readLine());
			System.out.print("Numero de dependentes: ");
			numeroDependentes = Integer.parseInt(inData.readLine());
			empregado = new FuncionarioContratado(nome,codigo,salario,numeroDependentes);
			funcionarios.add(empregado);
			empregado.calculaSalario(numeroDependentes);
			folhasalarial +=empregado.toString();
			System.out.println("");
		}
		System.out.println("- - - Folha Salarial - - -");
		System.out.println(folhasalarial);
	}
	public static void main(String[] args) throws IOException, NenhumArgumento, ArgumentosExcessivos
	{
		try
		{
			System.out.print("Digite o numero de funcionarios a serem cadastrados: ");
			BufferedReader inData = new BufferedReader(new InputStreamReader(System.in));
			String numero = inData.readLine();
			for(int i=0;i<numero.length();i++)
			{
				if(numero.charAt(i) == ' ')
				{
					throw new ArgumentosExcessivos();
				}
			}
			if(numero.compareTo("") == 0)
			{
				throw new NenhumArgumento();
			}
			int numerodeempregados = Integer.parseInt(numero);
			if(numerodeempregados <=0)
			{
				System.out.println("O numero passado e menor ou igual a zero");
			}
			else
			{
				Ex1 cadastroFucionarios = new Ex1(numerodeempregados);
				cadastroFucionarios.calculaSalarios();
			}
		}
		catch(NenhumArgumento nenhumargumento)
		{
			System.out.println("O numero de funcionarios nao foi informado");
		}
		catch(ArgumentosExcessivos muitosargumentos)
		{
			System.out.println("Mais de um numero foi passado");
		}
		catch(IOException e)
		{
			System.out.println(e);
		}
		catch(NumberFormatException e)
		{
			System.out.println("O argumento nao e um numero");
		}
		catch(IllegalArgumentException nome_invalido)
		{
			System.out.println("O nome passado possui numeros - nome invalido ");
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
}