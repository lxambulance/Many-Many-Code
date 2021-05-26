import java.util.Scanner;

// igloos_luka_int.java

public class i {
	private static int r[][];
	private static int a, b, c;
	private static int norm;
	private static int ref_x, ref_y;
	private static int dy, dx;

	static void InitPravac(int x1, int y1, int x2, int y2) {
		a = (y2 - y1);
		b = (x1 - x2);
		norm = a * a + b * b;
		c = -(a * x1 + b * y1);
		ref_x = x1;
		ref_y = y1;
		dy = y1 < y2 ? y2 - y1 : y1 - y2;
		dx = x2 - x1;
	}

	static int FloorY(int x) {
		return ref_y - (dy * (x - ref_x) + dx - 1) / dx;
	}

	static int CeilY(int x) {
		return ref_y + (dy * (x - ref_x) + dx - 1) / dx;
	}

	static boolean Intersects(int x, int y, int r_times_10) {
		int up_times_10 = 10 * (a * x + b * y + c);
		return up_times_10 * up_times_10 <= r_times_10 * r_times_10 * norm;
	}

	static int Count(int x, int y1, int y2) {
		int ret = 0;
		for (int y = y1; y <= y2; ++y) {
			if (r[x][y] != 0 && Intersects(x, y, r[x][y]))
				ret += 1;
		}
		return ret;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);  
		r = new int[1000][1000];
		int n = sc.nextInt();
		for (int i = 0; i < n; ++i) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			int radius = (int) (sc.nextDouble()*10+0.001);
			r[x][y] = radius;
		}
		int q = sc.nextInt();
		for (int i = 0; i < q; ++i) {
			int x1 = sc.nextInt();
			int y1 = sc.nextInt();
			int x2 = sc.nextInt();
			int y2 = sc.nextInt();
			if (x1 > x2 || x1 == x2 && y1 > y2) {
				int temp = x1; x1 = x2; x2 = temp;
				temp = y1; y1 = y2; y2 = temp;
			}
			int ret = 0;
			if (x1 == x2) {
				for (int y = y1; y <= y2; ++y) {
					if (r[x1][y] > 0.0)	
						ret += 1;
				}	
			} else if (y1 == y2) {
				for (int x = x1; x <= x2; ++x) {
					if (r[x][y1] > 0.0)
						ret += 1;
				}
			} else {
				InitPravac(x1, y1, x2, y2);
				if (y2 > y1) {
					int prev_y = y1;
					int next_y = CeilY(x1 + 1);
					ret += Count(x1, prev_y, next_y);
					for (int x = x1 + 1; x < x2; ++x) {
						int curr_y = next_y;
						next_y = CeilY(x + 1);
						ret += Count(x, prev_y, next_y);
						prev_y = curr_y - 1;
					}
					ret += Count(x2, prev_y, next_y);
				} else {
					int prev_y = y1;
					int next_y = FloorY(x1 + 1);
					ret += Count(x1, next_y, prev_y);
					for (int x = x1 + 1; x < x2; ++x) {
						int curr_y = next_y;
						next_y = FloorY(x + 1);
						ret += Count(x, next_y, prev_y);
						prev_y = curr_y + 1;
					}
					ret += Count(x2, next_y, prev_y);
				}
			}
			System.out.println(ret);
		}
	}

}
