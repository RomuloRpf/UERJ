abstract class PessoaIMC extends Pessoa 
{
	private double peso;
	private double altura;
	
	public PessoaIMC(String nome,String datanascimento,double peso,double altura)
	{
		super(nome,datanascimento);
		this.peso = peso;
		this.altura = altura;
	}
	public double getPeso()
	{
		return peso;
	}
	public double getAltura()
	{
		return altura;
	}
	public double calculaIMC(double peso,double altura)
	{
		double imc = peso/(altura * altura);
		return imc;
	}
	
	abstract String resultIMC();
	
	@Override
	public String toString()
	{
		return super.toString() + "Peso: " + peso + "\n" + "Altura: " + altura + "\n" + "IMC: " + calculaIMC(peso,altura);
	}
}