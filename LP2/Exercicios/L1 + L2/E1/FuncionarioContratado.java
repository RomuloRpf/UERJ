public class FuncionarioContratado extends Funcionario
{
	private int numeroDependentes;
	private double salarioFamilia;
	final double valorPorDep = 9.58;
	final double aliquotaIR = 0.15;
	
	public FuncionarioContratado(String nome, String codigo,double salario,int numeroDependentes)
	{
		super(nome,codigo,salario);
		this.numeroDependentes = numeroDependentes;
	}
	public void calculaSalario()
	{
		super.calculaSalario(aliquotaIR);
	}
	public void calculaSalario(int numeroDependentes)
	{
		double aux;
		salarioFamilia = (numeroDependentes * valorPorDep);
		aux = getSalario() + salarioFamilia;
		super.setSalario(aux);
		calculaSalario();
	}
	public int getNumeroDependentes()
	{
		return numeroDependentes;
	}
	public double getSalarioFamilia()
	{
		return salarioFamilia;
	}
	public String getNome()
	{
		return super.getNome();
	}
	public String getCodigo()
	{
		return super.getCodigo();
	}
	public double getSalario()
	{
		return super.getSalario();
	}
	public double getSalarioLiquido()
	{
		return super.getSalarioLiquido();
	}
	
	@Override
	public String toString()
	{
		return "\n" + super.toString() + "Salario-Liquido: " + String.format("%.2f", getSalarioLiquido()) + "\n";
	}
}