/*
Jeremy Lafond
jalafond
pa3
Matrix.java ADT(uses list)
*/
public class Matrix
{
	private List[] rows;
	private int matrixSize;
	private int NNZEntries;

	private class Entry
   	{
      	// Fields
   		int column;
 		double value;
		// Constructor for node
		Entry(int column, double value) 
		{	 
			this.value = value;
			this.column = column;
      	}
		public String toString()
      	{
			return ( "(" + String.valueOf(column) + ", " + String.valueOf(value) + ")" );
		}
		public boolean equals(Object x)
		{
			if(x instanceof Entry)
			{
				Entry eq = (Entry)x;
				return(this.column == eq.column && this.value == eq.value);
			}
			else
			{
				return false;
			}
		}
	}
	// Constructor
	// Makes a new n x n zero Matrix. pre: n>=1
	Matrix(int n)
	{
		if(n < 1)
		{
			throw new RuntimeException("Matrix error: n is not a valid input");
		}
		else
		{
			matrixSize = n;
			rows = new List[matrixSize + 1];
			for(int j = 0; j < matrixSize + 1; j++)
			{
				rows[j] = new List();
			}
			NNZEntries = 0;
		}
	}
	// Access functions
	// Returns n, the number of rows and columns of this Matrix
	int getSize()
	{
		return matrixSize;
	}
	// Returns the number of non-zero entries in this Matrix
	int getNNZ()
	{
		return NNZEntries;
	}
	// Overrides Object's equals() method
	public boolean equals(Object x)
	{
		if(x instanceof Matrix)
		{
			Matrix M = (Matrix)x;
			if(M.getSize() == this.getSize() && M.getNNZ() == this.getNNZ())
			{
				for(int i = 1; i <= getSize(); i++)
				{
					if(!(this.rows[i].equals(M.rows[i])) )
					{
						return false;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	// Manipulation procedures
	// Sets this Matrix to the zero state
	void makeZero()
	{
		for(int j = 0; j < rows.length; j++)
		{
			rows[j].clear();
		}
		NNZEntries = 0;
	}
	// Returns a new Matrix having the same entries as this Matrix
	Matrix copy()
	{
		Matrix agentSmith = new Matrix(this.matrixSize);
		agentSmith.matrixSize = this.matrixSize;
		for(int j = 0; j <= matrixSize; j++)
		{
			List curr = rows[j];
			for(curr.moveFront(); curr.index() >= 0; curr.moveNext())
			{
				Entry listEntry = (Entry)curr.get();
				agentSmith.changeEntry(j, listEntry.column, listEntry.value);
			}
		}
		agentSmith.NNZEntries = this.NNZEntries;
		return agentSmith;
	}
	// Changes ith row, jth column of this Matrix to x
	// Pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x)
	{
		if(i < 1 || i > getSize() || j < 1 || j > getSize())
		{
			throw new RuntimeException("Matrix error: invalid input values for i and j");
		}
		Entry newEntry = new Entry(j, x);
		if(rows[i].length() == 0 && x != 0)
		{
			rows[i].append(newEntry);
			NNZEntries++;
			return;
		}
		if(rows[i].length() == 0 && x == 0)
		{
			return;	
		}
		rows[i].moveFront();
		Entry rowEntry = (Entry)rows[i].get();
		Entry front = (Entry)rows[i].front();
		Entry back = (Entry)rows[i].back();
		if(x == 0)
		{
			while(rows[i].index() >= 0)
			{
				rowEntry = (Entry)rows[i].get();
				if(rowEntry.column == j)
				{
					rows[i].delete();
					NNZEntries--;
				}
				else 
				{
					rows[i].moveNext();
				}
			}
			return;
		}
		else
		{
			if(back.column < j)
			{
				rows[i].append(newEntry);
				NNZEntries++;
				return;
			}
			if(front.column > j)
			{
				rows[i].prepend(newEntry);
				NNZEntries++;
				return;
			}
			while(rows[i].index() >= 0)
			{
				rowEntry = (Entry) rows[i].get();
				if(rowEntry.column == j)
				{
					rowEntry.value = x;
					return;							
				}
				else if(rowEntry.column > j)
				{
					rows[i].insertBefore(newEntry);
					NNZEntries++;
					return;
				}
				rows[i].moveNext();	
			}
		}	
	}
	// Returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x)
	{
		Matrix neo = new Matrix(matrixSize);
		for(int j = 1; j <= matrixSize; j++)
		{
			if(rows[j].length() > 0)
			{
				for(rows[j].moveFront(); rows[j].index() > -1; rows[j].moveNext())
				{
					Entry stuff = (Entry)rows[j].get();
					double multi = x * stuff.value;
					neo.changeEntry(j, stuff.column, multi);
				}
			}
		}
		return neo;
	}
	// Returns a new Matrix that is the sum of this Matrix with M
	// Pre: getSize()==M.getSize()
	Matrix add(Matrix M)
	{
		if(matrixSize != M.matrixSize)
		{
			throw new RuntimeException("Matrix error: Matrices are not of equal size.");
		}
		if(this.equals(M))
		{
			return(this.scalarMult(2));
		}
		Matrix neo = new Matrix(matrixSize);
		Matrix temp = M.copy();
		double val1 = 0;
		double val2 = 0;
		double newVal = 0;
		int colNum1 = 0;
		int colNum2 = 0;
		for(int j = 1; j <= matrixSize; j++) 
		{
			if(rows[j].length != 0)
			{
				rows[j].moveFront();
			}
			if(temp.rows[j].length != 0)
			{
				temp.rows[j].moveFront();
			}
			while(rows[j].index() != -1 || temp.rows[j].index() != -1)
			{
				newVal = 0;
				if(rows[j].index() != -1)
				{
					Entry entry = (Entry)rows[j].get();
					val1 = entry.value;
					colNum1 = entry.column;
				} 
				else
				{
					val1 = 0;
				}
				if(temp.rows[j].index() != -1)
				{
					Entry entry = (Entry)temp.rows[j].get();
					val2 = entry.value;
					colNum2 = entry.column;
				} 
				else
				{
					val2 = 0;
				}
				if(colNum1 == colNum2)
				{
					newVal = val1 + val2;
					neo.changeEntry(j, colNum1, newVal);
					rows[j].moveNext();
					temp.rows[j].moveNext();
				}
				else if(colNum1 < colNum2)
				{
					if(rows[j].index() == -1)
					{
					    neo.changeEntry(j, colNum2, val2);
					    temp.rows[j].moveNext();
					}
					else
					{
					    newVal += val1;
					    neo.changeEntry(j, colNum1, newVal);
					    rows[j].moveNext();
					}
				}
				else if(colNum1 > colNum2)
				{
					if(temp.rows[j].index() == -1)
					{
					    neo.changeEntry(j, colNum1, val1);
					    rows[j].moveNext();
					}
					else
					{
						newVal += val2;
						neo.changeEntry(j, colNum2, newVal);
						temp.rows[j].moveNext();
					}
				}
			}
		}
		return neo;
	}
	// Returns a new Matrix that is the difference of this Matrix with M
	// Pre: getSize()==M.getSize()
	Matrix sub(Matrix M)
	{
		if(matrixSize != M.matrixSize)
		{
			throw new RuntimeException("Matrix error: Matrices are not of equal size.");
		}
		Matrix neo = new Matrix(matrixSize);
		Matrix temp = M.copy();
		double val1 = 0.0;
		double val2 = 0.0;
		double newVal = 0.0;
		int colNum1 = 0;
		int colNum2 = 0;
		for(int j = 1; j <= matrixSize; j++) 
		{
			if(rows[j].length != 0)
			{
				rows[j].moveFront();
			}
			if(temp.rows[j].length != 0)
			{
				temp.rows[j].moveFront();
			}
			while(rows[j].index() != -1 || temp.rows[j].index() != -1)
			{
				newVal = 0;
				if(rows[j].index() != -1)
				{
					Entry entry = (Entry)rows[j].get();
					val1 = entry.value;
					colNum1 = entry.column;
				}
				else
				{
					val1 = 0;
				}
				if(temp.rows[j].index() != -1)
				{
					Entry entry = (Entry)temp.rows[j].get();
					val2 = entry.value;
					colNum2 = entry.column;
				}
				else
				{
					val2 = 0;
				}
				if(colNum1 == colNum2)
				{
					newVal = val1 - val2;
					neo.changeEntry(j, colNum1, newVal);
					rows[j].moveNext();
					temp.rows[j].moveNext();
				}
				else if(colNum1 < colNum2)
				{
					if(rows[j].index() == -1)
					{
						newVal = -1 * val2;
					    neo.changeEntry(j, colNum2, newVal);
					    temp.rows[j].moveNext();
					}
					else
					{
					    neo.changeEntry(j, colNum1, val1);
					    rows[j].moveNext();
					}
				}
				else if(colNum1 > colNum2)
				{
					if(temp.rows[j].index() == -1)
					{
					    neo.changeEntry(j, colNum1, val1);
					    rows[j].moveNext();
					}
					else
					{
						newVal -= val2;
						neo.changeEntry(j, colNum2, newVal);
						temp.rows[j].moveNext();
					}
				}
			}
		}
		return neo;
	}
	// Returns a new Matrix that is the transpose of this Matrix
	Matrix transpose()
	{
		Matrix neo1 = new Matrix(matrixSize);
		for(int j = 0; j <= matrixSize; j++)
		{
			List curr = this.rows[j];
			for(curr.moveFront(); curr.index() != -1; curr.moveNext())
			{
				Entry pill = (Entry)curr.get();
				neo1.changeEntry(pill.column, j, pill.value);
			}
		}
		return neo1;
	}
	// Returns a new Matrix that is the product of this Matrix with M
	// Pre: getSize()==M.getSize()
	Matrix mult(Matrix M)
	{
		if(getSize() != M.getSize())
		{
			throw new RuntimeException("Matrix error: Both arrays are not the same size.");
		}
		Matrix neo = new Matrix(matrixSize);
		Matrix agentSmith = M.copy();
		agentSmith = agentSmith.transpose();
		for(int i = 1; i <= matrixSize; i++)
		{
			for(int j = 1; j <= matrixSize; j++)
			{
				double val = dot(rows[i], agentSmith.rows[j]);
				neo.changeEntry(i, j, val);
			}
		}
		return neo;
	}
	// Other functions
	//helper function for mult
	private static double dot(List P, List Q)
	{
		double valP = 0.0;
		double valQ = 0.0;
		int colP = -1;
		int colQ = -2;
		double sum = 0.0;
		if(P.length() != 0)
		{
			P.moveFront();
		}
		if(Q.length() != 0)
		{
			Q.moveFront();
		}
		while(P.index() != -1 && Q.index() != -1)
		{
			if(P.index() == -1)
			{
				valP = 0.0;
			}
			else
			{
				Entry stuff1 = (Entry)P.get();
				valP = stuff1.value;
				colP = stuff1.column;
			}
			if(Q.index() == -1)
			{
				valQ = 0.0;
			}
			else
			{
				Entry stuff2 = (Entry)Q.get();
				valQ = stuff2.value;
				colQ = stuff2.column;
			}
			if(colP == colQ)
			{
				sum += valP * valQ;
				P.moveNext();
				Q.moveNext();
			}
			else if(colP > colQ)
			{
				Q.moveNext();	
			}
			else if(colQ > colP)
			{
				P.moveNext();
			}
		}
		return sum;
	}
	// Overrides Object's toString() method
	public String toString()
	{
		String matrix = "";
		for(int j = 0; j < matrixSize + 1; j++)
		{
			if(rows[j].length() == 0)
			{
				continue;
			}
			matrix = matrix + (j)+": "+rows[j].toString()+"\n";
		}
		return matrix;
	}
}