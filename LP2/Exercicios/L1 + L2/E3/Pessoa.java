public class Pessoa extends Object
{
	private String nome;
	private String dataNascimento;
	
	public Pessoa(String nome,String datadenascimento)
	{
		this.nome = nome;
		dataNascimento = datadenascimento;
	}
	public String getNome()
	{
		return nome;
	}
	
	@Override
	public String toString()
	{
		return "Nome: " + nome + "\n" + "Data de Nascimento: " + dataNascimento + "\n";
	}
}