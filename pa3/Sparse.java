/*
Jeremy Lafond
jalafond
pa3
*/
//-----------------------------------------------------------------------------
//  Sparse.java
//  A test client for the Matrix ADT. Tests Matrix module. 
//-----------------------------------------------------------------------------
import java.io.*;
import java.util.Scanner;

public class Sparse
{
	public static void main(String[] args) throws IOException
	{
		if(args.length != 2) 
		{
            System.err.println("Usage error: Invalid number of arguements");
            System.exit(1);
        }
		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		int matrixSize = Integer.parseInt(in.next());
		Matrix A = new Matrix(matrixSize);
		Matrix B = new Matrix(matrixSize);
		int lines1 = Integer.parseInt(in.next());
		int lines2 = Integer.parseInt(in.next());
		in.nextLine();
		for(int j = 0; j < lines1; j++)
		{
			int row = Integer.parseInt(in.next());
			int col = Integer.parseInt(in.next());
			double value = Double.parseDouble(in.next());
			A.changeEntry(row, col, value);
		}
		in.nextLine();
		for(int j = 0; j < lines2; j++)
		{
			int row = Integer.parseInt(in.next());
			int col = Integer.parseInt(in.next());
			double value = Double.parseDouble(in.next());
			B.changeEntry(row, col, value);
		}
		//A and B
		out.println("A has " + A.getNNZ() + " non-zero entries:");
		out.println(A.toString());
		out.println("B has " + B.getNNZ() + " non-zero entries:");
		out.println(B.toString());
		//scalar A
		out.println("(1.5)*A =");
		Matrix scal = A.scalarMult(1.5);
		out.println(scal.toString());
		//A+B
		out.println("A+B =");
		Matrix addit = A.add(B);
		out.println(addit.toString());
		//A+A
		out.println("A+A =");
		Matrix additSelf = A.add(A);
		out.println(additSelf.toString());
		//B-A
		out.println("B-A =");
		Matrix diff = B.sub(A);
		out.println(diff.toString());
		//A-A
		out.println("A-A =");
		Matrix diffSelf = A.sub(A);
		out.println(diffSelf.toString());
		//A transposed
		out.println("Transpose(A) =");
		Matrix transM = A.transpose();
		out.println(transM.toString());
		//A * B
		out.println("A*B =");
		Matrix multi = A.mult(B);
		out.println(multi.toString());
		//B * B
		out.println("B*B =");
		Matrix multiSelf = B.mult(B);
		out.println(multiSelf.toString());
		//all done
		in.close();
		out.close();
	}
}