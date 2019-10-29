/*
        All Siberian Olympiad in Informatics, 2015
        Internet round
        Problem: Path
        Author of Solution: Mikhail Diakov
        Verdict: OK
        Solution: O(K * N^2) = (K/2) * Naive Dijkstra
        Note: this solution may be twice faster than the trivial one.
*/

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Locale;
import java.util.StringTokenizer;

public final class e {
	private static final String INPUT = "input.txt";
	private static final String OUTPUT = "output.txt";
	
	private static final int START_AND_FINISH_POINTS_NUM = 2;
	private static final int START_POINT_INDEX = 0;
	private static final int FINISH_POINT_INDEX_SHIFT = 1;
	
	private static final double INFINITE_TIME = 30000.0;
	
	private int n = 0;
	private int m = 0;
	private int k = 0;
	private int vr = 0;
	private int vf = 0;
	
	private int[] x;
	private int[] y;
	
	private double[][] dist;
	
	private int[] a;
	
	private double[] d;
	private boolean[] u;
	private int[] prev;
	private final ArrayList<Integer> subpath = new ArrayList<Integer>();
	
	private double length = 0.0;
	private final ArrayList<Integer> path = new ArrayList<Integer>();
	
	public void solve() throws IOException {
		input();
		path();
		output();
	}
	
	private void input() throws IOException {
		final BufferedReader inp = new BufferedReader(new FileReader(INPUT));
		
		final StringTokenizer st = new StringTokenizer(inp.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		k = Integer.parseInt(st.nextToken());
		vr = Integer.parseInt(st.nextToken());
		vf = Integer.parseInt(st.nextToken());
		
		x = new int[n];
		y = new int[n];
		dist = new double[n][];
		for (int i = 0; i < n; ++i) {
			dist[i] = new double[n];
			final StringTokenizer nst = new StringTokenizer(inp.readLine());
			x[i] = Integer.parseInt(nst.nextToken());
			y[i] = Integer.parseInt(nst.nextToken());
		}
		
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				dist[i][j] = dist[j][i] = distance(i, j) / vf;
			}
		}
		
		for (int i = 0; i < m; ++i) {
			final StringTokenizer mst = new StringTokenizer(inp.readLine());
			final int u = Integer.parseInt(mst.nextToken()) - 1;
			final int v = Integer.parseInt(mst.nextToken()) - 1;
			dist[u][v] = dist[v][u] = distance(u, v) / vr;
		}
		
		a = new int[k + START_AND_FINISH_POINTS_NUM];
		a[START_POINT_INDEX] = 0;
		a[k + FINISH_POINT_INDEX_SHIFT] = n - 1; 
		final StringTokenizer kst = new StringTokenizer(inp.readLine());
		for (int i = 1; i <= k; ++i) {
			a[i] = Integer.parseInt(kst.nextToken()) - 1;
		}
		k += START_AND_FINISH_POINTS_NUM;
		
		inp.close();
	}
	
	private double distance(final int u, final int v) {
		final double dx = x[u] - x[v];
		final double dy = y[u] - y[v];
		return Math.sqrt(dx * dx + dy * dy);
	}
	
	private void path() {
		d = new double[n];
		u = new boolean[n];
		prev = new int[n];
		
		path.add(0);
		for (int i = 1; i < k; i += 2) {
			length += dijkstra(a[i], a[i - 1], ((i + 1) < k) ? a[i + 1] : a[i - 1]);
		}
	}
	
	private double dijkstra(final int s, final int t0, final int t1) {
		Arrays.fill(d, INFINITE_TIME);
		Arrays.fill(u, false);
		
		d[s] = 0;
		for (int i = 0; i < n; ++i) {
			int v = -1;
			for (int j = 0; j < n; ++j) {
				if ( (false == u[j]) && ((-1 == v) || (d[j] < d[v])) ) {
					v = j;
				}
			}
			u[v] = true;
			
			if (u[t0] && u[t1]) {
				break;
			}
			
			for (int to = 0; to < n; ++to) {
				final double relaxedDist = d[v] + dist[v][to];
				if (relaxedDist < d[to]) {
					d[to] = relaxedDist;
					prev[to] = v;
				}
			}
		}
		
		for (int v = prev[t0]; v != s; v = prev[v]) {
			path.add(v);
		}
		path.add(s);
		
		if (t0 != t1) {
			subpath.clear();
			for (int v = t1; v != s; v = prev[v]) {
				subpath.add(v);
			}
			
			final int subsize = subpath.size();
			for (int i = subsize - 1; 0 <= i; --i) {
				path.add(subpath.get(i));
			}
		}
		
		return (t0 == t1) ? d[t0] : (d[t0] + d[t1]);
	}
	
	private void output() throws IOException {
		final PrintWriter out = new PrintWriter(new File(OUTPUT));
		
		out.format(Locale.US, "%.15f\n", length);
		final int pathsize = path.size();
		for (int i = 0; i < pathsize; ++i) {
			out.print(path.get(i) + 1);
			out.print(' ');
		}
		out.println();
		
		out.close();
	}
	
	public static void main(String[] args) throws IOException {
		new e().solve();
	}
}
