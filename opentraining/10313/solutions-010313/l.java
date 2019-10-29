/*
        All Siberian Olympiad in Informatics, 2015
        Internet round
        Problem: Scrabble
        Verdict: OK
        Author of Solution: Mikhail Diakov
        Solution: Simple simulation
*/

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public final class l {
	private static final String INPUT = "input.txt";
	private static final String OUTPUT = "output.txt";
	
	private static final char HORIZONTAL_ORIENTATION = 'h';
	
	private static final int[][] COEFFICIENTS = {
		{1, 1},
		{1, 1},
		{2, 1},
		{3, 1},
		{1, 2},
		{1, 3}
	};
	
	private static final int[][] BOARD = {
		{5,0,0,2,0,0,0,5,0,0,0,2,0,0,5},
		{0,4,0,0,0,3,0,0,0,3,0,0,0,4,0},
		{0,0,4,0,0,0,2,0,2,0,0,0,4,0,0},
		{2,0,0,4,0,0,0,2,0,0,0,4,0,0,2},
		{0,0,0,0,4,0,0,0,0,0,4,0,0,0,0},
		{0,3,0,0,0,0,0,0,0,0,0,0,0,3,0},
		{0,0,2,0,0,0,2,0,2,0,0,0,2,0,0},
		{5,0,0,2,0,0,0,1,0,0,0,2,0,0,5},
		{0,0,2,0,0,0,2,0,2,0,0,0,2,0,0},
		{0,3,0,0,0,0,0,0,0,0,0,0,0,3,0},
		{0,0,0,0,4,0,0,0,0,0,4,0,0,0,0},
		{2,0,0,4,0,0,0,2,0,0,0,4,0,0,2},
		{0,0,4,0,0,0,2,0,2,0,0,0,4,0,0},
		{0,4,0,0,0,3,0,0,0,3,0,0,0,4,0},
		{5,0,0,2,0,0,0,5,0,0,0,2,0,0,5}
	};
	
	private static final int[] SYMBOLS = { -1000000,
		1,3,2,3,2,1,5,5,1,2,2,2,2,1,1,2,2,2,2,3,10,5,10,5,10,10,10,5,5,10,10,3
	};
	
	private static final int PIECES_PER_PLAYER = 7;
	private static final int ALL_PIECES_BONUS = 15;
	
	private int n = 0;
	private int m = 0;
	
	private final boolean[][] used = new boolean[BOARD.length][BOARD.length];
	
	private int[] scores; 
	
	private void solve() throws IOException {
		scrabble();
		output();
	}
	
	private void scrabble() throws IOException {
		final BufferedReader inp = new BufferedReader(new FileReader(INPUT));
		
		final StringTokenizer st = new StringTokenizer(inp.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		
		scores = new int[n];
		for (int i = 0; i < m; ++i) {
			final StringTokenizer wst = new StringTokenizer(inp.readLine());
			
			final int w = Integer.parseInt(wst.nextToken());
			int playerScore = 0;
			int piecesUsedByPlayer = 0;
			for (int j = 0; j < w; ++j) {
				int wordScore = 0;
				
				final StringTokenizer movest = new StringTokenizer(inp.readLine());
				final int l = Integer.parseInt(movest.nextToken());
				final int dx = (HORIZONTAL_ORIENTATION == movest.nextToken().charAt(0)) ? 1 : 0;
				final int dy = 1 - dx;
				int x = Integer.parseInt(movest.nextToken()) - 1;
				int y = Integer.parseInt(movest.nextToken()) - 1;
				
				int wordCoeff = 1;
				for (int k = 0; k < l; ++k) {
					final int ch = Integer.parseInt(movest.nextToken());
					
					final int colorIndex = BOARD[x][y];
					wordScore += COEFFICIENTS[colorIndex][0] * SYMBOLS[ch];
					wordCoeff *= COEFFICIENTS[colorIndex][1];
					
					if (false == used[x][y]) {
						used[x][y] = true;
						++piecesUsedByPlayer;
					}
					
					x += dx;
					y += dy;
				}
				
				playerScore += wordScore * wordCoeff;
			}
			
			scores[i % n] += playerScore + ( (PIECES_PER_PLAYER == piecesUsedByPlayer) ? ALL_PIECES_BONUS : 0 );
		}
		
		inp.close();
	}
	
	private void output() throws IOException {
		final PrintWriter out = new PrintWriter(new File(OUTPUT));
		
		for (int i = 0; i < n; ++i) {
			out.println(scores[i]);
		}
		
		out.close();
	}
	
	public static void main(String[] args) throws IOException {
		new l().solve();
	}
}
