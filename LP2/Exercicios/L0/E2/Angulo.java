import java.math.*;


public class Angulo
{
	public static double converteAngulo(double ang)throws TangenteEx, CotangenteEx
	{
		return Math.toRadians(ang);
	}
	public static double funcaoSeno (double angrad)
	{
		BigDecimal seno_arredondado = BigDecimal.valueOf(Math.sin(angrad)).setScale(4, RoundingMode.HALF_EVEN);
		return seno_arredondado.doubleValue();
	}
	public static double funcaoCoseno (double angrad)
	{
		BigDecimal coseno_arredondado = BigDecimal.valueOf(Math.cos(angrad)).setScale(4, RoundingMode.HALF_EVEN);
		return coseno_arredondado.doubleValue();
	}
	public static double funcaoTangente(double angrad)
	{
	    if((converteAngulo(90)==angrad) || (converteAngulo(270)==angrad))
		{
		    throw new TangenteEx();
		}
		if((angrad%converteAngulo(90)==0) && (angrad%converteAngulo(180)!=0))
		{
			throw new TangenteEx();
		}
		BigDecimal tangente_arredondado = BigDecimal.valueOf(Math.tan(angrad)).setScale(4, RoundingMode.HALF_EVEN);
		return tangente_arredondado.doubleValue();
	}
	public static double funcaoCotangente(double angrad) 
	{
		BigDecimal tangente_arredondado = BigDecimal.valueOf(Math.tan(angrad)).setScale(4, RoundingMode.HALF_EVEN);
		if((tangente_arredondado.doubleValue()==0) || (angrad % converteAngulo(180) == 0))
		{
		    throw new CotangenteEx();
		}
		double cotangente = (1/tangente_arredondado.doubleValue());
		BigDecimal cotangente_arredondado = BigDecimal.valueOf(cotangente).setScale(4, RoundingMode.HALF_EVEN);
		return cotangente_arredondado.doubleValue();
	}
}
