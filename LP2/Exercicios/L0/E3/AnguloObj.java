import java.math.*;


public class AnguloObj
{
	private double arcoRad;
	
	public void AnguloObj(double ang)
	{
		arcoRad = Math.toRadians(ang);
	}
	public double converteAngulo()
	{
		return arcoRad;
	}
	public double funcaoSeno ()
	{
		double seno = Math.sin(arcoRad);
		BigDecimal seno_arredondado = BigDecimal.valueOf(seno).setScale(4, RoundingMode.HALF_EVEN);
		return seno_arredondado.doubleValue();
	}
	public double funcaoCoseno ()
	{
		double coseno = Math.cos(arcoRad);
		BigDecimal coseno_arredondado = BigDecimal.valueOf(coseno).setScale(4, RoundingMode.HALF_EVEN);
		return coseno_arredondado.doubleValue();
	}
	public double funcaoTangente()
	{
		double tangente = Math.tan(arcoRad);
		BigDecimal tangente_arredondado = BigDecimal.valueOf(tangente).setScale(4, RoundingMode.HALF_EVEN);
		return tangente_arredondado.doubleValue();
	}
	public double funcaoCotangente() 
	{
		double tangente = Math.tan(arcoRad);
		BigDecimal tangente_arredondado = BigDecimal.valueOf(tangente).setScale(4, RoundingMode.HALF_EVEN);
		if(tangente_arredondado.doubleValue()==0)
		{
			throw new ArithmeticException("divisao_por_zero");
		}
		else
		{
			double cotangente = (1/tangente_arredondado.doubleValue());
			BigDecimal cotangente_arredondado = BigDecimal.valueOf(cotangente).setScale(4, RoundingMode.HALF_EVEN);
			return cotangente_arredondado.doubleValue();
		}
	}
	
	@Override
	public String toString()
	{
		return "Arco: " + converteAngulo() + "\n" + "Seno: "+ funcaoSeno() + "\n" +"Coseno: "+ funcaoCoseno() + "\n" + "Tangente: "+ funcaoTangente() + "\n" + "Cotangente: " + funcaoCotangente();
	}
}