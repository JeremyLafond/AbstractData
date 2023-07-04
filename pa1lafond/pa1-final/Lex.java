/*
Jeremy Lafond
jalafond
pa1
*/

import java.util.Scanner;
import java.io.*;

class Lex
{
	/*
	Main takes string array arguments and 
	scans lines in based on lex sort.
	also utilizes moveTo helper function.
	*/

	public static void main (String[] args) throws IOException
	{
		if(args.length != 2)
		{
			System.err.println("Usage: Lex infile outfile");
			System.exit(1);
		}
	
		PrintWriter out = new PrintWriter(args[1]);
		Scanner line = new Scanner(new File(args[0]));
		Scanner in = new Scanner(new File(args[0]));
		
		int lineCount = 0;

		while(in.hasNextLine())
		{
			lineCount++;
			in.nextLine();
		}

		String[] newLines= new String[lineCount];

		for (int i = 0; i < lineCount; i++)
		{
			newLines[i] = line.nextLine();
		}

		List linesList = new List();

		/*lex sort
		sorts via compareTo and
		prints into file accordingly.
		*/

		for(int k = 1; k < lineCount; k++)
		{
			String t = newLines[k]; //temp
			int j = k - 1;
			

			while(j >= 0 && t.compareTo(newLines[j]) < 0)
			{
				newLines[j+1] = newLines[j];
				j--;
			}
			newLines[j + 1] = t;
		}

		for(int i = 0; i < lineCount; i++)
		{
			linesList.append(i);
		}

		//prints our new list into file
		for(int m=0; m < lineCount; m++)
		{
			linesList.move(m);
			out.println(newLines[linesList.get()]);
		}

		in.close();
		line.close();
		out.close();

	}
}