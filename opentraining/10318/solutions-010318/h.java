import java.io.*;
import java.lang.*;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.MathContext;
import java.util.*;

public class h
{

    static class Poly {
        double[] data;

        Poly(int deg) {
           data = new double[deg + 1];
        }

        static Poly Linear(int x, double xval, int y, double yval) {
            Poly res = new Poly(1);
            res.data[1] = (yval-xval)/(y - x);
            res.data[0] = xval - res.data[1]*x;
            return res;
        }

        Poly multiply(Poly r) {
            Poly res = new Poly(data.length + r.data.length - 2);
            for (int i = 0; i < data.length; i++)
                for (int j = 0; j < r.data.length; j++) {
                    res.data[i+j] += data[i] * r.data[j];
                }
            return res;
        }
        Poly add(Poly r) {
            Poly res = new Poly(Math.max(data.length - 1, r.data.length - 1));
            for (int i = 0; i < res.data.length; i++)
                res.data[i] = (i < data.length ? data[i] : 0) + (i < r.data.length ? r.data[i] : 0);
            return res;
        }
        Poly integrate() {
            Poly res = new Poly(data.length);
            res.data[0] = 0;
            for (int i = 0; i < data.length; i++)
                res.data[i+1] = data[i] / (i + 1);
            return res;
        }
        double integrate(double l, double r) {
            Poly up = this.integrate();
            return up.eval(r) - up.eval(l);
        }

        double eval(double r) {
            double res = 0;
            for (int i = data.length - 1; i >= 0; i--) {
                res = res * r + data[i];
            }
            return res;
        }

        Poly derivative() {
            Poly res = new Poly(data.length - 2);
            for (int i = 1; i < data.length; i++)
                res.data[i - 1] = data[i] * i;
            return res;
        }

        public String toString() {
            StringBuilder s = new StringBuilder();
            for (int i = 0; i < data.length; i++) {
                s.append(data[i]);
                if (i != 0) {
                    s.append("*x");
                    if (i != 1) {
                        s.append("^").append(i);
                    }
                }
            }
            return s.toString();
        }
    }

    void solve() throws IOException{
        int n = nextInt();
        int[] l = new int[n];
        int[] r = new int[n];
        int[] all = new int[2*n];
        for (int i = 0; i < n; i++) {
            all[2*i] = l[i] = nextInt();
            all[2*i+1] = r[i] = nextInt();
        };
        Arrays.sort(all);

        double res = 0;

        for (int i = 1; i < all.length; i++) {
            if (all[i-1] != all[i]) {
                res = res + solveOne(l, r, all[i - 1], all[i]);
            }
        }

        out.println(String.format("%.18f", res));
    }

    private double solveOne(int[] ls, int[] rs, int l, int r) {
        Poly poly = new Poly(0);
        poly.data[0] = 0;

        for (int i = 0; i <= ls.length; i++) {
            Poly summand = new Poly(0);
            summand.data[0] = 1;
            for (int j = 0; j < ls.length; j++) {
                double leftVal = calcProb(ls[j], rs[j], l);
                double rightVal = calcProb(ls[j], rs[j], r);
                if (i == j) {
                    leftVal = 1 - leftVal;
                    rightVal = 1 - rightVal;
                }
                Poly lin = Poly.Linear(l, leftVal, r, rightVal);
                //System.err.println("i = " + i + " j = " + j + " : " + lin);
                summand = summand.multiply(lin);
            }
            //System.err.println("  " + summand);
            poly = poly.add(summand);
        }
        //poly is distribution function now
        //System.err.println(poly);
        poly = poly.derivative();
        poly = poly.multiply(Poly.Linear(0, 0, 1, 1));
        return poly.integrate(l, r);
    }

    private double calcProb(int l, int r, int x) {
        if (x <= l) return 0;
        if (x >= r) return 1;
        return (x - l)*1.0/( r - l);
    }

    public static void main(String[] args) throws IOException{
        new h().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException
    {
        try {
            Locale.setDefault(Locale.US);
            Reader reader = new FileReader("secondmax.in");
            Writer writer = new FileWriter("secondmax.out");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            in.close();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }       
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(in.readLine());
        }
        return tokenizer.nextToken();
    }

}                                    
