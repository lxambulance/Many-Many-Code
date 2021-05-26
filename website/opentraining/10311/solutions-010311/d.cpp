#include <cstdio>
#include <vector>

int main()
{
    int N,K;
    int t,d;
    bool answer;
    scanf("%d%d",&N,&K);
    std::vector<int> X(N+1),P(N+1,0);
    for(int i=0;i<=N;++i) scanf("%d",&(X[i]));
    d=X[N]/K;
    answer=false;
    for(int i=0,j=0;j<=N;)
    {
        t=X[j]-X[i];
        if(t==d)
        {
            P[j]=P[i]+1;
            answer|=(P[j]==K-1);
        }
        if(t<=d) ++j;
        if(t>=d) ++i;
    }
    printf("%d",(int)answer);
    return 0;
}
