public class Homem extends PessoaIMC
{
	public Homem(String nome,String datanascimento,double peso,double altura)
	{
		super(nome,datanascimento,peso,altura);
	}
	public String resultIMC()
	{
		double imc = calculaIMC(getPeso(),getAltura());
		if(imc < 20.7)
		{
			return "Abaixo do peso ideal\n";
		}
		else if(imc <= 26.4 && imc >= 20.7)
		{
			return "Peso ideal\n";
		}
		else
		{
			return "Acima do peso ideal\n";
		}
	}
	
	@Override
	public String toString()
	{
		return super.toString() + " " + resultIMC();
	}
}