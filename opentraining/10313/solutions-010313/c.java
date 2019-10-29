/**
 * Correct solution (must be OK).
 * Author: stgatilov
 * Optimized version of direct rewrite of sol_sg_ok.cpp.
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Comparator;
import java.util.Collections;

public class c {
	static private final int SIZE = 100<<10;
	static private final int MAXN = 3 * SIZE;
	static private final long INF = 1000000000000000000L;

	class pii {
		public int first;
		public int second;
		pii(int a, int b) { first = a; second = b; }
	};

	class ConstComparator implements Comparator<pii> {
		public int compare(pii a, pii b) {
			return Integer.compare(a.first, b.first);
		}
	};

	class Edge {
		int a, b;
		int wgt;

		Edge() {}
		Edge(int _a, int _b, int _w) {
			a = _a;
			b = _b;
			wgt = _w;
		}
		Edge reversed() {
			return new Edge(b, a, wgt);
		}
	};

	int n, m, v;
	HashMap<Integer, Integer> constMap = new HashMap<Integer, Integer>(2 * SIZE);
	ArrayList<pii> constList = new ArrayList<pii>(2 * SIZE);
	ArrayList<ArrayList<Edge>> nbrDir = new ArrayList<ArrayList<Edge>>(MAXN);
	ArrayList<ArrayList<Edge>> nbrRev = new ArrayList<ArrayList<Edge>>(MAXN);

	boolean used[] = new boolean[MAXN];

	ArrayList<Integer> outOrder = new ArrayList<Integer>(MAXN);
	void DFS_topsort(int v) {
		used[v] = true;
		for (Edge e : nbrDir.get(v))
			if (!used[e.b])
				DFS_topsort(e.b);
		outOrder.add(v);
	}

	int[] biconnColor = new int[MAXN];
	int biconnCount;
	void DFS_biconn(int v) {
		used[v] = true;
		biconnColor[v] = biconnCount;
		for (Edge e : nbrRev.get(v))
			if (!used[e.b])
				DFS_biconn(e.b);
	}

	int z;
	ArrayList<ArrayList<Edge>> nbrZip = new ArrayList<ArrayList<Edge>>(MAXN);
	HashMap<pii, Integer> zipEdgeByEnds = new HashMap<pii, Integer>(MAXN);

	void AddZippedEdge(int ca, int cb, int w) {
		Edge e = new Edge(ca, cb, w);
		pii ends = new pii(ca, cb);
		if (zipEdgeByEnds.containsKey(ends)) {
			Integer old = zipEdgeByEnds.get(ends);
			if (old > e.wgt)
				old = e.wgt;
		}
		else
			zipEdgeByEnds.put(ends, e.wgt);
	}

	long[] dist = new long[MAXN];

	int[] sol = new int[MAXN];






	private BufferedReader inp;
	private PrintWriter out;
	
	c() throws Throwable {
		inp = new BufferedReader(new FileReader(new File("input.txt")));
		out = new PrintWriter(new File("output.txt"));
	}

	
	void readAll() throws Throwable {
		final StringTokenizer st = new StringTokenizer(inp.readLine());
		m = Integer.parseInt(st.nextToken());
		n = Integer.parseInt(st.nextToken());

		for (int i = 0; i < 2*m+n; i++) {
			nbrDir.add(new ArrayList<Edge>());
			nbrRev.add(new ArrayList<Edge>());
		}

		int[] vIdx = new int[2];
		for (int i = 0; i < m; i++) {
			final StringTokenizer inst = new StringTokenizer(inp.readLine());
			int op = Integer.parseInt(inst.nextToken());

			for (int e = 0; e < 2; e++) {
				int t = Integer.parseInt(inst.nextToken());
				int val = Integer.parseInt(inst.nextToken());

				if (t == 1) {
					if (!constMap.containsKey(val)) {
						vIdx[e] = n + constMap.size();
						constMap.put(val, vIdx[e]);
					}
					else
						vIdx[e] = constMap.get(val);
				}
				else
					vIdx[e] = val - 1;
			}

			Edge e = new Edge();
			e.a = vIdx[1];
			e.b = vIdx[0];
			e.wgt = -op;
			nbrDir.get(e.a).add(e);
			nbrRev.get(e.b).add(e.reversed());
		}

	}
	
	boolean solve() throws Throwable {
		v = n + constMap.size();
		for (Map.Entry<Integer, Integer> entry : constMap.entrySet())
			constList.add(new pii(entry.getKey(), entry.getValue()));
		constMap = null;	//no longer used
		
		Collections.sort(constList, new ConstComparator());

		for (int i = 0; i+1 < constList.size(); i++) {
			Edge e = new Edge();
			e.a = constList.get(i+1).second;
			e.b = constList.get(i).second;
			e.wgt = constList.get(i).first - constList.get(i+1).first;
			nbrDir.get(e.a).add(e);
			nbrRev.get(e.b).add(e.reversed());
		}

		Arrays.fill(used, false);
		for (int i = 0; i < v; i++) if (!used[i])
			DFS_topsort(i);

/*		System.err.println("Top sort: ");
		for (int i = 0; i < v; i++) {
			System.err.print(" ");
			System.err.print(outOrder.get(i));
		}
		System.err.println("");*/

		Arrays.fill(used, false);
		for (int i = v-1; i>=0; i--) {
			int s = outOrder.get(i);
			if (used[s]) continue;
			DFS_biconn(s);
			biconnCount++;
		}
		nbrRev = null;	//no longer used

/*		System.err.println("Biconn components: ");
		for (int i = 0; i < v; i++) {
			System.err.print(" ");
			System.err.print(biconnColor[i]);
		}
		System.err.println("");*/

		z = biconnCount;
		for (int i = 0; i < v; i++) {
			for (Edge e : nbrDir.get(i)) {
				int ca = biconnColor[e.a];
				int cb = biconnColor[e.b];
				if (ca == cb) {
					if (e.wgt < 0) {
//						System.err.println(String.format("Bad edge %d -> %d (%d)", e.a, e.b, ca));
						return false;
					}
				}
				else
					AddZippedEdge(ca, cb, e.wgt);
			}
		}

		for (int i = 0; i < z; i++)
			nbrZip.add(new ArrayList<Edge>());
		for (Map.Entry<pii, Integer> elem : zipEdgeByEnds.entrySet())
			nbrZip.get(elem.getKey().first).add(new Edge(elem.getKey().first, elem.getKey().second, elem.getValue()));
		nbrDir = null;	//no longer used
		
	
        Arrays.fill(dist, 3 * INF);
		if (constList.size() > 0) {
			pii x = constList.get(constList.size() - 1);
			int cmp = biconnColor[x.second];
			dist[cmp] = 0;
		}

		Arrays.fill(used, false);
		for (int i = v-1; i >= 0; i--) {
			int cur = biconnColor[outOrder.get(i)];
			if (used[cur]) continue;
			used[cur] = true;
			if (dist[cur] >= INF) continue;

			for (Edge e : nbrZip.get(cur)) {
				long newDist = dist[e.a] + e.wgt;
				if (dist[e.b] > newDist)
					dist[e.b] = newDist;
			}
		}

		for (int i = 0; i < constList.size(); i++) {
			pii pa = constList.get(i);
			pii pm = constList.get(constList.size() - 1);
			int ca = biconnColor[pa.second];
			int cm = biconnColor[pm.second];
			if (dist[cm] - dist[ca] > pm.first - pa.first)
				return false;
		}

		Arrays.fill(used, false);
		for (int i = 0; i < v; i++) {
			int cur = biconnColor[outOrder.get(i)];
			if (used[cur]) continue;
			used[cur] = true;
			if (dist[cur] < INF) continue;

			long tres = -INF;
			for (Edge e : nbrZip.get(cur)) {
				if (dist[e.b] >= INF) continue;
				long newDist = dist[e.b] - e.wgt;
				if (tres < newDist)
					tres = newDist;
			}
			if (tres > -INF)
				dist[cur] = tres;
		}

	
		Arrays.fill(used, false);
		for (int i = v-1; i >= 0; i--) {
			int cur = biconnColor[outOrder.get(i)];
			if (used[cur]) continue;
			used[cur] = true;
			if (dist[cur] > INF) dist[cur] = 0;

			for (Edge e : nbrZip.get(cur)) {
				long newDist = dist[e.a] + e.wgt;
				if (dist[e.b] > newDist)
					dist[e.b] = newDist;
			}
		}

		long delta = 0;
		if (constList.size() > 0)
			delta = constList.get(0).first - dist[biconnColor[constList.get(0).second]];
		for (int i = 0; i < v; i++) {
			long tsol = dist[biconnColor[i]] + delta;
			assert(tsol >= -2000000000 && tsol <= 2000000000);
			sol[i] = (int)tsol;
		}

		for (pii pCI : constList)
			assert (sol[pCI.second] == pCI.first);

		return true;
	}

	void writeSol(boolean hasSolution) throws Throwable {
		if (!hasSolution) {
			out.println("NO");
			return;
		}

		out.println("YES");
		for (int i = 0; i < n; i++)
			out.println(sol[i]);
	}
	
	void doall() throws Throwable {
		readAll();

		boolean hasSolution = solve();

		writeSol(hasSolution);
		
		inp.close();
		out.close();
	}
	
	public static void main(String[] args) throws Throwable {
		new c().doall();
	}
}
