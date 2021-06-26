import java.math.*;

public class Ex1{
	public static void main(String[]args){
		String tipo;
		int i=0;
		if(args.length==0){
			System.out.println("Numero de argumentos insuficiente");
		}
		else
		{
			if(args.length>3)
			{
				System.out.println("Numero de argumentos excessivo");
			}
			else
			{
				float lados[] = new float[args.length];
				for(i=0; i<args.length;i++)
				{
					try
					{
						lados[i] = Float.parseFloat(args[i]);
						if(lados[i]<=0)
						{
							throw new IllegalArgumentException("erro");
						}
						if(args.length==1)
						{
							System.out.println("A area do circulo e: "+ calcula(lados[0])  +" unidades de area.");
						}
						if(args.length==2 && i==1)
						{
							System.out.println("A area do retangulo e: "+ calcula(lados[0],lados[1])  +" unidades de area.");
						}
						if(args.length==3 && i==2)
						{
							tipo = verifica(lados[0],lados[1],lados[2]);
							if(tipo=="nao forma triangulo")
							{
								System.out.println("Os argumentos passados "+ lados[0]+ " " + lados[1] + " " + lados[2] +" nao formam um triangulo.");
							}
							else
							{
								System.out.println("A area do triangulo e: "+ calcula(lados[0],lados[1],lados[2])  +" unidades de area.");
								if(tipo=="equilatero")
								{
									System.out.println("O triangulo e equilatero.");
								}
								if(tipo=="isosceles")
								{
									System.out.println("O triangulo e isosceles.");
								}
								if(tipo=="escaleno")
								{
									System.out.println("O triangulo e escaleno.");
								}
							}
						}
					}
					catch(NumberFormatException e)
					{
						System.out.println((i+1)+"o argumento, '"+ args[i] +"', nao e numero");
					}
					catch(IllegalArgumentException erro)
					{
						System.out.println((i+1)+"o argumento, '"+ args[i] +"', nao e valido");
					}
				}
			}
		}
	}
	private static float calcula(float r){
		return (float)(Math.PI*(r*r));
	}
	private static float calcula(float b, float a){
		return a*b;
	}
	private static float calcula(float l1, float l2, float l3){
		float p = (l1 +l2 + l3)/2;
		return (float)(Math.sqrt(p*(p - l1)*(p - l2)*(p - l3)));
	}
	private static String verifica(float l1,float l2, float l3)
	{
		if((Math.abs(l2 - l3) < l1) && (l1 < l2 + l3))
		{
			if((Math.abs(l1 - l3) < l2) && (l2 < l1 + l3))
			{
				if((Math.abs(l1 - l2) < l3) && (l3 < l1 + l2))
				{
					if((l1==l2) && (l1==l3) && (l2==l3))
					{
						return "equilatero";
					}
					else
					{
						if((l1==l2) || (l1==l3) || (l2==l3))
						{
							return "isosceles";
						}
						else
						{
							return "escaleno";
						}
					}
				}
				else
				{
					return "nao forma triangulo";
				}
			}
			else
			{
				return "nao forma triangulo";
			}
		}
		else
		{
			return "nao forma triangulo";
		}
	}
}