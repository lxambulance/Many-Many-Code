/**
 * Correct solution (must be OK).
 * Author: Dmitry Babiy
 */
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;


public class k {
	
	public static class Flower {		
		public int type, cost;
		public Flower() {}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader	reader = new BufferedReader(new FileReader("input.txt"));
		//BufferedReader	reader = new BufferedReader(new InputStreamReader(System.in));
		int n, s;
		StringTokenizer	st = new StringTokenizer(reader.readLine());
		n = Integer.parseInt(st.nextToken());
		s = Integer.parseInt(st.nextToken());
		Flower[]	fls = new Flower[n];
		
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(reader.readLine());
			fls[i] = new Flower();
			fls[i].type = Integer.parseInt(st.nextToken());
			fls[i].cost = Integer.parseInt(st.nextToken());
		}
		reader.close();
		
		Arrays.sort(fls, new Comparator<Flower>() {
			public int compare(Flower arg0, Flower arg1) {
				if (arg0.cost<arg1.cost) return -1; 
				else if (arg0.cost>arg1.cost) return 1;
				else return 0;
			}			
		});
		
		Set<Integer> types = new HashSet<Integer>();
		
		int curs = 0;
		for (int i = 0; i < n; ++i) {
			if (fls[i].cost + curs > s) break;
			if (types.contains(fls[i].type) == false) {
				types.add(fls[i].type);
				curs += fls[i].cost; 
			}
		}
		
		//PrintWriter writer = new PrintWriter(System.out);
		PrintWriter writer = new PrintWriter(new FileWriter("output.txt"));
		writer.println(types.size());
		writer.close();
	}

}
