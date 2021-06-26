import java.util.*;

public class MinhaListaOrdenavel
{
	ArrayList lista;
	public MinhaListaOrdenavel()
	{
		lista = new ArrayList();
	}
	public void add(PessoaIMC p)
	{
		lista.add(p);
	}
	public PessoaIMC get (int index)
	{
		return (PessoaIMC)lista.get(index);
	}
	
	public Comparator nomeC = new Comparator () 
	{
		public int compare (Object p1, Object p2)
		{
			String pf1, pf2;
			PessoaIMC tmp1 = (PessoaIMC) p1;
			PessoaIMC tmp2 = (PessoaIMC) p2;
			pf2 = tmp2.getNome();
			pf1 = tmp1.getNome();
			return (int)Math.round(pf1.compareTo(pf2));
		}
	};
	public Comparator alturaC = new Comparator () 
	{
		public int compare (Object p1, Object p2)
		{
			double pf1, pf2;
			PessoaIMC tmp1 = (PessoaIMC) p1;
			PessoaIMC tmp2 = (PessoaIMC) p2;
			pf2 = tmp2.getAltura();
			pf1 = tmp1.getAltura();
			return (int)Math.floor(pf2 - pf1);
		}
	};
	public Comparator imcC = new Comparator () 
	{
		public int compare (Object p1, Object p2)
		{
			double pf1, pf2;
			PessoaIMC tmp1 = (PessoaIMC) p1;
			PessoaIMC tmp2 = (PessoaIMC) p2;
			pf2 = tmp2.calculaIMC(tmp2.getPeso(),tmp2.getAltura());
			pf1 = tmp1.calculaIMC(tmp1.getPeso(),tmp1.getAltura());
			return (int)Math.round (pf2 - pf1);
		}
	};
	public Comparator pesoC = new Comparator () 
	{
		public int compare (Object p1, Object p2)
		{
			double pf1, pf2;
			PessoaIMC tmp1 = (PessoaIMC) p1;
			PessoaIMC tmp2 = (PessoaIMC) p2;
			pf2 = tmp2.getPeso();
			pf1 = tmp1.getPeso();
			return (int)Math.round (pf2 - pf1);
		}
	};
	
	public ArrayList ordena (int criterio) 
	{
		switch(criterio)
		{
			case 1:
				Collections.sort(this.lista, nomeC);
				break;
			case 2:
				Collections.sort(this.lista, nomeC.reversed());
				break;
			case 3:
				Collections.sort(this.lista, pesoC.reversed());
				break;
			case 4:
				Collections.sort(this.lista, pesoC);
				break;
			case 5:
				Collections.sort(this.lista, alturaC);
				break;
			case 6:
				Collections.sort(this.lista, imcC.reversed());
				break;
			default:
				throw new IllegalArgumentException("invalido");
		}
		return this.lista;
	}
}