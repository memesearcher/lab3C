public class Vector : MathObj, IComparable 
{
	public static bool AngleInRads;
	private int dim;
	private float[] elements;
	public int Dim
	{
		get{return dim;}
		set {if(value<=dim)
		{
			float[] vals = new float(value);
			for (int i = 0; i < value; i++)
			vals[i] = elements [i];
			elements = vals;
			dim = value;
		}
		if (value > dim)
		{throw new DimSetExp();}
		}
	}

}

public float this [int i]{
	get {if(i < 0 || i > dim) throw new ArgRangeExp();
	elements[i] = value;
	}
}

public Vectro (float[] vals){
	if(vals == null) throw new ArgNullExp();
	elements = (float[])vals.CopyTo();
	dim = vals.GetLength(0);
}

Public static Mult(VectorA, VectorB){
	if(VectorA == null || VectorB == null)
	throw new ArgNullExp();
	var sum = 0;
	for(int i = 0; i < A.Dim; i++)
	sum += A[i]*B[i];
	return sum;
}

public int CompareTo(VectorA){
	if(A == null)
	throw new ArgNullExp();
	return this.Length() - B.Length();
}