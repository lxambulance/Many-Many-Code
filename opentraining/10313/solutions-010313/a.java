/**
 * Correct solution (must be OK).
 * Author: Dmitry Babiy
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.StringTokenizer;


public class a {
	
	public static class Coo {		
		public double x, y;
		public Coo() {}
	}


	public static void main(String[] args) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
		int n, m;
		StringTokenizer	st = new StringTokenizer(reader.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());		
		Coo[]	pts = new Coo[n];		
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(reader.readLine());
			pts[i] = new Coo();
			pts[i].x = Integer.parseInt(st.nextToken());
			pts[i].y = Integer.parseInt(st.nextToken());
		}
		for (int i = 0; i < m; ++i) {
			st = new StringTokenizer(reader.readLine());
			Coo p = new Coo();
			Coo q = new Coo();
			p.x = Integer.parseInt(st.nextToken());
			p.y = Integer.parseInt(st.nextToken());
			q.x = Integer.parseInt(st.nextToken());
			q.y = Integer.parseInt(st.nextToken());
			double a, b, c;
			a = p.y-q.y;
			b = q.x-p.x;
			c = -a*p.x-b*p.y;
			for (int j = 0; j < n; ++j) 
				if (a*pts[j].x + b*pts[j].y + c <= 0) applyFlip(pts[j],a,b,c);
		}
		reader.close();
		
		PrintWriter writer = new PrintWriter("output.txt");		
		for (int i = 0; i < n; ++i) writer.println(""+pts[i].x+" "+pts[i].y);
		writer.close();
	}


	private static void applyFlip(Coo coo, double a1, double b1, double c1) {		
		double a2 = -b1, b2 = a1;
		double c2 = -a2*coo.x - b2*coo.y;
		double intx = (-c1*b2+c2*b1)/(a1*b2-a2*b1);
		double inty = (-a1*c2+a2*c1)/(a1*b2-a2*b1);
		coo.x = 2*(intx-coo.x) + coo.x;
		coo.y = 2*(inty-coo.y) + coo.y;
	}

}
