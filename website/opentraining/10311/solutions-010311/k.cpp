#include <cstdio>

#pragma warning ( disable : 4996 ) 
//#define AVOID_MULS_IN_COST_FROM_TILL

const int MAXN = 5000;
const int MAXM = 3000;
const int INFTY = 0x7FFF7FFF;

int freq[MAXN];
int cost_from_till_incl[MAXN][MAXN+1];
int DP[MAXM][MAXN];
int prev[MAXM+1][MAXN];
int N, M;

template<class T> inline T min(T x, T y) {return (x <= y) ? x : y;};



int main(int argc, char* argv[])
{
//	FILE *fin = fopen("input.txt", "rt");
//	FILE *fout = fopen("output.txt", "wt");
	FILE *fin = stdin;
	FILE *fout = stdout;
	fscanf(fin, "%d %d", &N, &M);
	for(int i=0; i<N; i++)
		fscanf(fin, "%d", freq+i);
#ifdef AVOID_MULS_IN_COST_FROM_TILL
	static int sum_freq_before[MAXN+1];
	sum_freq_before[0] = 0;
	for(int i=0; i<N; i++) {
		sum_freq_before[i+1] = sum_freq_before[i] + freq[i];
	}
	for(int j=0; j<N; j++) {
		cost_from_till_incl[j][j] = freq[j];
		for(int i=j-1; i>=0; i--) {
			cost_from_till_incl[i][j] = cost_from_till_incl[i+1][j] + (sum_freq_before[j+1] - sum_freq_before[i]);
		}
	}
#else
	for(int i=0; i<N; i++)
	{
		cost_from_till_incl[i][i] = freq[i];
		for(int j=i+1; j<N; j++)
			cost_from_till_incl[i][j] = cost_from_till_incl[i][j-1] + (j-i+1)*freq[j];
	}
#endif
	for(int j=0; j<N; j++)
	{
		DP[0][j] = cost_from_till_incl[0][j];
		prev[0][j] = -1;
	}
	for(int i=1; i<M; i++)
	{
		DP[i][i] = DP[i-1][i-1] + cost_from_till_incl[i][i];
		prev[i][i] = i-1;
	}

	for(int j=2; j<N; j++)
	{
		prev[M][j] = j-1;
		for(int i=min(M-1,j-1); i>0; i--)
		{
			DP[i][j] = INFTY;
			for(int k=prev[i+1][j]; k>=prev[i][j-1]; k--)
			{
//				if(cost_from_till_incl[k+1][j] > DP[i][j] && i!=M-1)
//				{
////					fprintf(stderr, "my heuristic is _NOT_ fully dominated by Knuth's %d %d %d\n", i, j, k);
//					break;
//				}
				int curr = DP[i-1][k] + cost_from_till_incl[k+1][j];
				if(curr < DP[i][j])
				{
					DP[i][j] = curr;
					prev[i][j] = k;
				}
			}
//			if(j==N-1 && i==M-1)
//				break;
		}
	}


	fprintf(fout, "%d\n", DP[M-1][N-1]);
	fclose(fout);
	fclose(fin);
	return 0;
}

