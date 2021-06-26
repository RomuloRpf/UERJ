public class Funcionario
{
	private String nome;
	private String codigo;
	private double salario;
	private double salarioLiquido;
	
	public Funcionario(String nome,String codigo,double salario)
	{
		this.nome = nome;
		this.codigo = codigo;
		this.salario = salario;
		salarioLiquido = salario;
	}
	public double calculaSalario(double desconto)
	{
		return salarioLiquido = salario - (salario * desconto);
	}
	public String getNome()
	{
		return nome;
	}
	public String getCodigo()
	{
		return codigo;
	}
	public double getSalario()
	{
		return salario;
	}
	public double getSalarioLiquido()
	{
		return salarioLiquido;
	}
	public void setSalario(double salario)
	{
		this.salario = salario;
	}
	
	@Override
	public String toString()
	{
		return "Nome do Empregado: " + nome + "\n" + "Codigo: " + codigo + "\n" + "Salario-Base: " + salario + "\n";
	}
}