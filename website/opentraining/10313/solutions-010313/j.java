/**
 *  j:    Civilization
 *  Author:  Evgeniy Chetvertakov
 *  Verdict: OK
 *  Max flow solution with proper capacities on cities and "do not shoot" end vertices.
 */

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.TreeSet;


public class j {

	abstract class GraphNode implements Comparable<GraphNode>{
		public boolean equals(Object o) { return compareTo((GraphNode)o) == 0; }
		public int compareTo(GraphNode o) { 
			//return this.toString().compareTo(o.toString());
			int ta,tb;
			
			if(this instanceof Point3D) ta=1;
			else if(this instanceof Point) ta=2;
			else if(this instanceof GraphNodeImpl) ta=3;
			else throw new Error("something wrong. HBWYGSBV");
			
			if(o instanceof Point3D) tb=1;
			else if(o instanceof Point) tb=2;
			else if(o instanceof GraphNodeImpl) tb=3;
			else throw new Error("something wrong. RGTBEAVT");
			
			if(ta != tb ) return Integer.compare(ta, tb);
			if(ta == 1) return ((Point3D)this).compareTo((Point3D)o);
			if(ta == 2) return ((Point)this).compareTo((Point)o);
			if(ta == 3) return ((GraphNodeImpl)this).compareTo((GraphNodeImpl)o);
			throw new Error("EBRHERY%B");
			
		}
		public int hashCode() { throw new Error("hashCode is not implemented here"); }
	};
	
	class GraphNodeImpl extends GraphNode {
		private String name;
		public GraphNodeImpl(String name) {this.name = name;}
		public String toString() { return name; }
		public int hashCode() { return name.hashCode(); }
		public int compareTo(GraphNodeImpl o) { return name.compareTo(o.name); }
	};
	
	class Point extends GraphNode{
		public int x,y; //immutable
		private String strrepr=null;
		public Point(int x,int y) { this.x = x; this.y=y; }
		public Point(Point p) { this.x = p.x; this.y=p.y; }
		public Point add(Point p) { return new Point(this.x+p.x,this.y+p.y); }
		public String toString() {
			if(strrepr==null) strrepr=String.format("(%d,%d)", x,y);
			return strrepr;
		}
		public int hashCode() { return (x<<10)^(y<<5)^y^x; }
		public int compareTo(Point o) { 
			if( this.x == o.x )  return Integer.compare(this.y, o.y);
			return Integer.compare(this.x, o.x);
		}
	}
	
	class Point3D extends Point {
		private int z;
		private String strrepr=null;
		public Point3D(Point p,int z) { super(p); this.z=z;}
		public String toString() {
			if(strrepr==null) strrepr=String.format("(%d,%d,%d)", x,y,z);
			return strrepr;
		}
		public int hashCode() { return (x<<10)^(y<<6)^(z<<3)^y^x^z; }
		public int compareTo(Point3D o) {
			if( this.z == o.z )
			{
				if( this.x == o.x )  return Integer.compare(this.y, o.y);
				return Integer.compare(this.x, o.x);
			}
			return Integer.compare(this.z, o.z);
		}

	}
	
	
	class UnpassableCell extends Point { protected UnpassableCell(int x,int y) { super(x,y); } };
	
	class City extends UnpassableCell {
		public int n,health;
		public City(int x,int y,int n,int health) { super(x, y); this.n=n; this.health=health; }
	}
	
	class Mountain extends UnpassableCell {
		public int n,health;
		public Mountain(int x,int y) { super(x, y); }
	}
	
	class Catapult extends Point {
		public int n,movesCount;
		public Catapult(int x,int y,int n,int movesCount) { super(x, y); this.n=n; this.movesCount=movesCount; }
	}
	
	
	// arcs
	abstract class Arc implements Comparable<Arc>{
		abstract public GraphNode getFrom();
		abstract public GraphNode getTo();
		abstract public int getVolume();
		abstract public int getWeight();
		abstract public Arc getBackArc();
		abstract public void addWeight(int d);
		public String toString() { return getFrom().toString() + " -> " + getTo().toString(); }
		public int compareTo(Arc o) { 
			//return this.toString().compareTo(o.toString());
			int a = this.getFrom().compareTo(o.getFrom());
			if( a != 0 ) return a; 
			return this.getTo().compareTo(o.getTo());
		}
	}
	
	class DirectArc extends Arc {
		private GraphNode from,to;
		private int volume,weight;
		private BackArc back = null;
		public DirectArc(GraphNode from,GraphNode to, int volume, int weight)
		{
			this.from = from;
			this.to = to;
			this.volume = volume;
			this.weight = weight;
		}
		public Arc getBackArc()
		{
			if( back == null ) back = new BackArc(this);
			return back;
		}
		
		public GraphNode getFrom() { return from; }
		public GraphNode getTo() { return to; }
		public int getVolume() { return volume;	}
		public int getWeight() { return weight;	}
		public void addWeight(int d) { weight+=d; }
	}
	class BackArc extends Arc {
		private DirectArc directArc;
		public BackArc(DirectArc arc) { directArc = arc; }
		public GraphNode getFrom() { return directArc.getTo(); }
		public GraphNode getTo() { return directArc.getFrom(); }
		public int getVolume() { return directArc.getVolume();	}
		public int getWeight() { return directArc.getVolume() - directArc.getWeight(); }
		public void addWeight(int d) { directArc.addWeight(-d); }
		public Arc getBackArc() {	return directArc; }
	}
	
	public class Tuple<A, B> { 
		  public final A first; 
		  public final B second; 
		  public Tuple(A first, B second) { 
		    this.first = first; 
		    this.second = second; 
		  } 
		}
	
	class Graph
	{
		public TreeSet<Arc> arcs;
		public TreeMap<GraphNode,ArrayList<Arc> > nodesFrom;
		public Graph(TreeSet<Arc> arcs) {
			this.arcs = arcs;
			
			nodesFrom = new TreeMap<GraphNode,ArrayList<Arc> >();
			for(Arc arc : arcs) { 
				if( !nodesFrom.containsKey(arc.getFrom()) ) nodesFrom.put(arc.getFrom(), new ArrayList<Arc>());
				nodesFrom.get(arc.getFrom()).add(arc);
			}				
			for(Arc arc : arcs) { 
				Arc ba = arc.getBackArc();
				if( !nodesFrom.containsKey(ba.getFrom()) ) nodesFrom.put(ba.getFrom(), new ArrayList<Arc>());
				nodesFrom.get(ba.getFrom()).add(ba);
			}
		}
		
		public TreeSet<Arc> getDirectEmpties(GraphNode node) {
			TreeSet<Arc> res = new TreeSet<Arc>();
			for( Arc a : nodesFrom.get(node) )
			{
				if( (a instanceof DirectArc) && a.getWeight() == 0 )
					res.add(a);
			}
			return res;
		}
		
		public Arc getDirectEmpty(GraphNode node) {
			for( Arc a : nodesFrom.get(node) )
				if( (a instanceof DirectArc) && a.getWeight() == 0 )
					return a;
			return null;
		}
		
		
		public TreeSet<Arc> findPath(GraphNode from,GraphNode to)
		{
			HashMap<GraphNode,Arc> visited = new HashMap<>(nodesFrom.size()*2,0.5f);
			visited.put(from, null);
			Queue<GraphNode> queue = new LinkedList<>();
			queue.add(from);
			
			while(!queue.isEmpty())
			{
				GraphNode node = queue.remove();
				for( Arc arc : nodesFrom.get(node) )
				{
					if( visited.containsKey(arc.getTo())) continue;
					if( arc.getWeight() < 1) continue;
					visited.put(arc.getTo(),arc);
					if(arc.getTo().equals(to)) { queue.clear(); break;}
					queue.add(arc.getTo());
				}
			}
			
			if(! visited.containsKey(to)) return null;
			
			TreeSet<Arc> res = new TreeSet<>();
			GraphNode node = to;
			do {
				Arc a = visited.get(node);
				res.add(a);
				node = a.getFrom();
			} while( !node.equals(from));
			
			return res;
		}
	}
	
	interface Field {
		boolean checkCell(Point p);
	};
	

	// distances from the given point to neighborhood cells
	ArrayList<Point> moves = new ArrayList<Point>(); 
	{
		moves.add(new Point(0,1));
		moves.add(new Point(1,0));
		moves.add(new Point(1,-1));
		moves.add(new Point(0,-1));
		moves.add(new Point(-1,0));
		moves.add(new Point(-1,1));
	}
			
			
	TreeMap<Integer, TreeSet<Point> > walk(int depth, Point startFrom, Field f )
	{
		if( depth == 0 ) {
			TreeMap<Integer, TreeSet<Point> > res = new TreeMap<Integer, TreeSet<Point> >();
			TreeSet<Point> setp = new TreeSet<Point>();
			setp.add(startFrom);
			res.put(0,setp);
			return res;
		}
		
		TreeMap<Integer, TreeSet<Point> > distances = walk(depth-1,startFrom,f);
		TreeSet<Point> d1 = distances.get(depth-1);
		TreeSet<Point> d2 = distances.containsKey(depth-2)?distances.get(depth-1):new TreeSet<Point>();
			
		TreeSet<Point> w =  new TreeSet<Point>();
		for(Point p : d1) 
			for(Point move : moves)
			{
				Point n = p.add(move);
				if( !d1.contains(n) || !d2.contains(n)) w.add(n);
			}
		
		TreeSet<Point> res =  new TreeSet<Point>();
		for(Point p : w) 
			if( f.checkCell(p)) res.add(p);
		
		distances.put(depth, res);
		return distances;
	}
	
	TreeMap<Catapult , Tuple<Point,City> > calc(Field moves_field, Field firing_field, ArrayList<City> cities, ArrayList<Catapult> cats)
	{
		GraphNode source = new GraphNodeImpl("source");
		GraphNode sink = new GraphNodeImpl("sink");
		
		TreeMap<City, TreeSet<Point> > city_area = new TreeMap<>();
		for(City city : cities)
		{
			TreeMap<Integer, TreeSet<Point> > areas = walk(2,city,firing_field);
			TreeSet<Point> area = new TreeSet<>();
			for( TreeSet<Point> area_p : areas.values()) {
				area.addAll(area_p);
			}
			city_area.put(city, area);
		}
		
		
		TreeMap<Catapult, TreeSet<Point> > cat_area = new TreeMap<>();
		for(Catapult cat : cats)
		{
			TreeMap<Integer, TreeSet<Point> > areas = walk(cat.movesCount-1,cat,moves_field);
			TreeSet<Point> area = new TreeSet<>();
			for( TreeSet<Point> area_p : areas.values()) {
				area.addAll(area_p);
			}
			cat_area.put(cat, area);
		}
		
		TreeSet<Arc> arcs = new TreeSet<>();
		
		TreeMap<Catapult , Tuple<Point,City> > res = new TreeMap<>();
		int unused_catpower = cats.size();
		for(City city : cities)
			unused_catpower -= city.health;
		if( unused_catpower < 0) return res;
		cities = new ArrayList<>(cities);
		cities.add( new City(-1,-1,0,unused_catpower) );
		
		for(Catapult cat : cats)
			arcs.add(new DirectArc(source,cat,1,1));
		
		for(Catapult cat : cats)
		{
			TreeSet<Point> cat_set = cat_area.get(cat);
			for(City city : cities)
			{
				TreeSet<Point> intersection = new TreeSet<Point>();
				if( city.n > 0)
				{
					for(Point p : city_area.get(city))
						if(cat_set.contains(p)) intersection.add(p);
				}else{
					intersection.add(cat);
				}
				
				for(Point p : intersection)
				{
					Point cell1 = new Point3D(p,1);
					Point cell2 = new Point3D(p,2);
					
					arcs.add(new DirectArc(cat,cell1,1,1));
					arcs.add(new DirectArc(cell1,cell2,1,1));
					arcs.add(new DirectArc(cell2,city,1,1));
					
				}
			}
		}

		
		for(City city : cities)
			arcs.add(new DirectArc(city,sink,city.health,city.health));

		Graph g = new Graph(arcs);
		
		while(true) {
			TreeSet<Arc> path = g.findPath(source,sink);
			if( path == null) break;
			for(Arc a : path) a.addWeight(-1);
		}
		
		boolean flag = true;
		for(Arc arc : g.nodesFrom.get(sink) )
			if(arc.getBackArc().getWeight() != 0) 
				flag=false;


		if(!flag) return res; // no solution for this set of cities
		
		for(Arc catarc : g.getDirectEmpties(source)) {//g.nodesFrom.get(source)) {
			 //if( catarc.getWeight() != 0) continue;
			 Catapult cat = (Catapult)catarc.getTo();
			 
			 Arc cell1arc = g.getDirectEmpty(cat);
			 Point cell1 = (Point)cell1arc.getTo(); 
			 Arc cell2arc = g.getDirectEmpty(cell1);
			 Arc cityarc = g.getDirectEmpty(cell2arc.getTo());
			 City city = (City)cityarc.getTo();
			 
			 res.put(cat, new Tuple<Point,City>(cell1,city));
		}
		return res;
		
	}
	
	public void j(String inputfile,String outputfile)
	{
		try{
			Scanner inp = new Scanner( new FileInputStream(inputfile) );
			
			final int W = inp.nextInt();			
			final int H = inp.nextInt();
			
			int N = inp.nextInt();
			ArrayList<City> cities = new ArrayList<City>();
			for(int i=1;i<=N;i++)
				cities.add( new City(inp.nextInt(),inp.nextInt(),i,inp.nextInt()) );

			int C = inp.nextInt();
			ArrayList<Catapult> cats = new ArrayList<Catapult>();
			for(int i=1;i<=C;i++)
				cats.add( new Catapult(inp.nextInt(),inp.nextInt(),i,inp.nextInt()) );
			
			int M = inp.nextInt();
			ArrayList<Mountain> mountains = new ArrayList<Mountain>();
			for(int i=1;i<=M;i++)
				mountains.add( new Mountain(inp.nextInt(),inp.nextInt()) );
			
			inp.close();
			
			// subsets of cities
			ArrayList< ArrayList<City> > aac = new ArrayList< ArrayList<City> >();
			for(int i=(1<<N)-1;i>0;i--)
			{
				ArrayList<City> a = new ArrayList<City>(cities);
				for(int j=N-1;j>=0;j--)
					if( (i & (1<<j)) == 0) a.remove(j);
				aac.add(a);
			}
			
			Collections.sort(aac,
			//aac.sort(
					new Comparator< ArrayList<City> >() {
				public int compare(ArrayList<City> a, ArrayList<City> b) {
					return b.size() - a.size();
				}
			});
			
			// field's configuration
			final TreeSet<UnpassableCell> unpassables = new TreeSet<UnpassableCell>();
			for(City c : cities) unpassables.add(c);
			for(Mountain m : mountains) unpassables.add(m);
			
			Field moves_field = new Field() {
				public boolean checkCell(Point p) {
					return p.x>=0 && p.x<W && p.y>=0 && p.y<H && !unpassables.contains(p);
				}
			};
			Field firing_field = new Field() {
				public boolean checkCell(Point p) {
					return p.x>=0 && p.x<W && p.y>=0 && p.y<H;
				}
			};
			
			
			TreeMap<Catapult , Tuple<Point,City> > sol=null;
			int cityres=0;
			for(ArrayList<City> cities_subset : aac)
			{
				sol = calc(moves_field,firing_field,cities_subset,cats);
				if( ! sol.isEmpty() ) { cityres=cities_subset.size(); break;}
			}
			
			PrintWriter outp = new PrintWriter(outputfile);
			outp.println(cityres);
			for(Catapult cat : cats) {
				if( sol.containsKey(cat) ) {
					Tuple<Point,City> t = sol.get(cat);
					outp.println(String.format("%d %d %d", t.first.x, t.first.y, t.second.n));
				}else{
					outp.println(String.format("%d %d %d", cat.x, cat.y, 0));
				}
			}
			outp.close();

			
			
		}catch(FileNotFoundException e) {
			;
		}
		
	}

	public static void main(String[] args) {
		j t = new j();
		t.j("input.txt","output.txt");
		
		long start = System.currentTimeMillis();
		
/*		for(int i=2;i<=48;i++)
		{
			long s = System.currentTimeMillis();
			t.j(String.format("tests/%d.in", i), String.format("tests/%d.res.txt", i));
			s = System.currentTimeMillis() - s;
			
			System.out.println(String.format("test: %d , time: %d ms", i,s));
		}
		System.out.println(String.format("Total time: %d ms", System.currentTimeMillis() - start));*/
		
	}
}
