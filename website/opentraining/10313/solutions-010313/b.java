/**
 * Correct solution (must be OK).
 * Author: Mike Gorodilov
 * stgatilov: using fast scanner to accelerate input.
 */
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.StringTokenizer;

public class b {

	public static class Team {
		
		public Team(int index) {
			super();
			this.left = index;
			this.right = index;
			this.index = index;
		}
		
		public int left;
		public int right; 
		public int index;
	}
	
	public static final String winToken = "Win";
	public static final String loseToken = "Lose";
	public static final String unknownToken = "Unknown";
	
	public static void main(String[] args) throws Throwable {
		BufferedReader inp = new BufferedReader(new FileReader("input.txt"));
        PrintWriter pw = new PrintWriter(new File("output.txt"));

		final StringTokenizer nst = new StringTokenizer(inp.readLine());
		int n = Integer.parseInt(nst.nextToken());

        HashMap<String, Team> teams = new HashMap<>();
        Team[] table = new Team[1 << n];
        
        for (int index = 0; index < (1 << n); index++)
        {
        	String teamName = inp.readLine();
        	Team team = new Team(index);
        	table[index] = team;
        	teams.put(teamName, team);
        }        
        
        String results = inp.readLine();
        
        int currentMatchIndex = 0;
        for (int round = n; round > 0; round--)
        {
        	for (int index = 0; index < (1 << (round - 1)); index++)
        	{
        		char currentResult = results.charAt(currentMatchIndex);
        		currentMatchIndex++;
        		Team winnerTeam = null;
        		switch (currentResult) {
				case 'W':
					winnerTeam = table[index * 2];
					break;
				case 'L':
					winnerTeam = table[index * 2 + 1];
					break;
				}
        		winnerTeam.left = table[index * 2].left;
        		winnerTeam.right = table[index * 2 + 1].right;
        		table[index] = winnerTeam;        		
        	}
        }
        
		final StringTokenizer rqst = new StringTokenizer(inp.readLine());
        int requestsCount = Integer.parseInt(rqst.nextToken());
        
        for (int i = 0; i < requestsCount; i++)
        {
			final StringTokenizer st = new StringTokenizer(inp.readLine());
        	Team teamA = teams.get(st.nextToken());
        	Team teamB = teams.get(st.nextToken());
        	if (teamA.left <= teamB.index && teamB.index <= teamA.right)
        	{
        		pw.println(winToken);
        	} 
        	else if (teamB.left <= teamA.index && teamA.index <= teamB.right)
        	{
        		pw.println(loseToken);
        	}
        	else 
        	{
        		pw.println(unknownToken);
        	}
        }
        
        inp.close();
        pw.close();
	}

}
