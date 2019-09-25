#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(b);i>=(a);--i)
typedef long long ll;
inline int read(){
    int x=0,f=1; char ch=getchar();
    while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
    while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}

const int MAXN=400005,INF=2147483647;
int root,top,pool[MAXN];
struct SBT{ int k,s,ch[2]; }T[MAXN];
void clr(){
    root=0,top=MAXN-1;
    FOR(i,1,MAXN-1) pool[top+1-i]=i;
}
void rotate(int &x,int k){//0为右旋，1为左旋
    int y=T[x].ch[k]; T[x].ch[k]=T[y].ch[k^1]; T[y].ch[k^1]=x;
    T[y].s=T[x].s; T[x].s=T[T[x].ch[0]].s+T[T[x].ch[1]].s+1; x=y;
}
void maintain(int &x,bool flag){
    if (!flag) {
        if (T[T[T[x].ch[0]].ch[0]].s>T[T[x].ch[1]].s)//左孩子的左子树大于右孩子
            rotate(x,0);
        else if (T[T[T[x].ch[0]].ch[1]].s>T[T[x].ch[1]].s) {
            rotate(T[x].ch[0],1);
            rotate(x,0);
        }
        else return;
    }
    else {
        if (T[T[T[x].ch[1]].ch[1]].s>T[T[x].ch[0]].s)
            rotate(x,1);
        else if (T[T[T[x].ch[1]].ch[0]].s>T[T[x].ch[0]].s) {
            rotate(T[x].ch[1],0);
            rotate(x,1);
        }
        else return;
    }
    maintain(T[x].ch[0],false);
    maintain(T[x].ch[1],true);
    maintain(x,true);
    maintain(x,false);
}
void ins(int &x,int k){
    if (x==0) {
        x=pool[top--];
        T[x].ch[0]=T[x].ch[1]=0,T[x].s=1,T[x].k=k;
    }
    else {
        T[x].s++;
        if (k<T[x].k) ins(T[x].ch[0],k); else ins(T[x].ch[1],k);
        maintain(x,k>=T[x].k);
    }
}
int del(int &x,int k){
    int ret;
    T[x].s--;
    if ((k==T[x].k)||(k<T[x].k&&T[x].ch[0]==0)||(k>T[x].k&&T[x].ch[1]==0)) {
        ret=T[x].k;
        if (T[x].ch[0]&&T[x].ch[1]) T[x].k=del(T[x].ch[0],T[x].k+1);
        else pool[++top]=x,x=T[x].ch[0]+T[x].ch[1];
    }
    else if (k>T[x].k) ret=del(T[x].ch[1],k);
    else ret=del(T[x].ch[0],k);
    return ret;
}
int findKth(int &x,int k){
    int r=T[T[x].ch[0]].s+1;
    if (r==k) return T[x].k;
    else if (r<k) return findKth(T[x].ch[1],k-r);
    else return findKth(T[x].ch[0],k);
}
int findRank(int &x,int k){
    if (!x) return INF/2;
    if (k<T[x].k) return findRank(T[x].ch[0],k);
    else if (k>T[x].k) return findRank(T[x].ch[1],k)+T[T[x].ch[0]].s+1;
    return min(findRank(T[x].ch[0],k),T[T[x].ch[0]].s+1);
}
int pred(int &x,int y,int k){
    if (x==0) return T[y].k;
    if (T[x].k<k) return pred(T[x].ch[1],x,k);
    else return pred(T[x].ch[0],y,k);
}
int succ(int &x,int y,int k){
    if (x==0) return T[y].k;
    if (T[x].k>k) return succ(T[x].ch[0],x,k);
    else return succ(T[x].ch[1],y,k);
}
void inorder(int &x){
    if (x==0) return;
    else {
        inorder(T[x].ch[0]);
        cerr<<"("<<x<<":"<<T[x].k<<";s=";
        cerr<<T[x].s<<"l="<<T[x].ch[0]<<"r="<<T[x].ch[1]<<")";
        inorder(T[x].ch[1]);
    }
}
int main(){
    clr();
    int q=read();
    while (q--) {
        int op=read(),x=read();
        if (op==1) ins(root,x);
        if (op==2) del(root,x);
        if (op==3) printf("%d\n",findRank(root,x));
        if (op==4) printf("%d\n",findKth(root,x));
        if (op==5) printf("%d\n",pred(root,0,x));
        if (op==6) printf("%d\n",succ(root,0,x));
        //inorder(root); cerr<<endl;
    }
    return 0;
}

/*
20
1 2
1 4
1 3
1 3
1 5
1 4
1 5
1 5
1 3
1 4
3 2
4 5
3 3
4 7
4 5
3 5
4 7
4 10
4 4
3 4

 */

