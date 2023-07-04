/*
Jeremy Lafond
jalafond
pa3
MatrixTest.java test for Matrix in isolation
*/
public class MatrixTest
{
	public static void main(String[] args)
	{
		int i, j, n=100000;
		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);

		A.changeEntry(1,1,1); B.changeEntry(1,1,1);
		A.changeEntry(1,2,2); B.changeEntry(1,2,0);
		A.changeEntry(1,3,3); B.changeEntry(1,3,1);
		A.changeEntry(2,1,4); B.changeEntry(2,1,0);
		A.changeEntry(2,2,5); B.changeEntry(2,2,1);
		A.changeEntry(2,3,6); B.changeEntry(2,3,0);
		A.changeEntry(3,1,7); B.changeEntry(3,1,1);
		A.changeEntry(3,2,8); B.changeEntry(3,2,1);
		A.changeEntry(3,3,9); B.changeEntry(3,3,1);

		System.out.println(A.getNNZ());
		System.out.println(A.getSize());
		System.out.println(A);

		System.out.println(B.getNNZ());
		System.out.println(B.getSize());
		System.out.println(B.toString());

		Matrix C = A.scalarMult(1.5);
		System.out.println(C.getNNZ());
		System.out.println(C.getSize());
		System.out.println(C.toString());

		Matrix D = A.add(A);
		System.out.println(D.getNNZ());
		System.out.println(D.getSize());
		System.out.println(D.toString());

		Matrix E = A.sub(A);
		System.out.println(E.getNNZ());
		System.out.println(E.getSize());
		System.out.println(E.toString());

		Matrix F = B.transpose();
		System.out.println(F.getNNZ());
		System.out.println(F.getSize());
		System.out.println(F.toString());

		Matrix G = B.mult(B);
		System.out.println(G.getNNZ());
		System.out.println(F.getSize());
		System.out.println(G.toString());

		Matrix H = A.copy();
		System.out.println(H.getNNZ());
		System.out.println(H.toString());
		System.out.println(H.getSize());
		System.out.println(A.equals(H));
		System.out.println(A.equals(B));
		System.out.println(A.equals(A));

		A.makeZero();
		System.out.println(A.getNNZ());
		System.out.println(A.getSize());
		System.out.println(A.toString());
	}
}
/*
Correct output:
9
100000
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
100000
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
100000
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
100000
1: (1, 2.0) (2, 4.0) (3, 6.0)
2: (1, 8.0) (2, 10.0) (3, 12.0)
3: (1, 14.0) (2, 16.0) (3, 18.0)

0
100000

6
100000
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
100000
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
100000
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
100000
*/