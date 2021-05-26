/**
 * Correct solution (must be OK).
 * Author: Mike Gorodilov
 * Fast solution without binsearch.
 * stgatilov: replaced input with fast scanner.
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Comparator;
import java.util.StringTokenizer;

public class d {
	
	public static class Wire implements Comparable<Wire>{
		long p;
		long sigma;
		long S;
		long maxWeight;
		long dencity;
		long index;
		
		public int compareTo(Wire b)
		{
			long delta = (sigma * S - b.sigma * b.S);
			if (delta == 0)
			{
				return (int)Math.signum((double)sigma / p - (double)b.sigma / b.p);
			}
			return (int)Math.signum(delta);
		}
		
		public double getMaxWeight()
		{
			return S * sigma;
		}
		
		public double getRelativeDencity()
		{
			return S * p;
		}
	}

	public static void main(String[] args) throws Throwable {
		BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        PrintWriter pw = new PrintWriter(new File("output.txt"));

		final StringTokenizer st = new StringTokenizer(br.readLine());
		int d = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());

        Wire wires[] = new Wire[(n + 1)];
        
        for (int index = 0; index < n; index++)
        {
			final StringTokenizer ist = new StringTokenizer(br.readLine());
        	wires[index] = new Wire();
        	wires[index].S = Integer.parseInt(ist.nextToken());
        	wires[index].p = Integer.parseInt(ist.nextToken());
        	wires[index].sigma = Integer.parseInt(ist.nextToken());
        	wires[index].maxWeight = wires[index].S * wires[index].sigma;
        	wires[index].dencity = wires[index].S * wires[index].p;
        	wires[index].index = index + 1;
        }
        wires[n] = new Wire();
        wires[n].S = 0;
        wires[n].p = 1;
        wires[n].sigma = 1;        

        Arrays.sort(wires);

        double deep = d;
        Wire current = wires[(int)n];
        for (int index = (int) n - 1; index >= 0; index--)
        {        	
        	Wire next = wires[index];
        	if (current.getRelativeDencity() < next.getRelativeDencity())
        		continue;
        	double deepCurrent = (current.getMaxWeight() - next.getMaxWeight()) / current.getRelativeDencity();        	
        	if (deepCurrent >= deep)
        	{
        		deepCurrent = deep;
        		double result = current.getMaxWeight() - deepCurrent * current.getRelativeDencity();
        		pw.println(String.format("%.10f",result));
        		
                br.close();
                pw.close();
                
        		return;
        	}
        	deep -= deepCurrent;
        	//pw.println(String.format("%d %d %d %.5f %.5f",current.maxWeight, current.dencity, current.index, deep, deepCurrent));        	
        	current = next;
        }
        
        pw.println(0);
        
        br.close();
        pw.close();
	}

}
