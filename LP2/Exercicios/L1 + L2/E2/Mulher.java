public class Mulher extends PessoaIMC
{
	public Mulher(String nome,String datanascimento,double peso,double altura)
	{
		super(nome,datanascimento,peso,altura);
	}
	public String resultIMC()
	{
		double imc = calculaIMC(getPeso(),getAltura());
		if(imc < 19.0)
		{
			return "Abaixo do peso ideal\n";
		}
		else if(imc <= 25.8 && imc >= 19.0)
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