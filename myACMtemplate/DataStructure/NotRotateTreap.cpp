mt19937 rng((unsigned long long) new char);
struct Treap{
    int val,key; //分别表示值和堆值
	int sz; //子树大小
    int ch[2]; //0是左二子，1是右儿子
}T[MAXN];
int root,tot;
void make_data(int &now,int value){
    T[++tot].val=value;
	T[tot].key=(int)rng();
    T[tot].sz=1;
    T[tot].ch[0]=T[tot].ch[1]=0;
    now=tot;
}
void update(int now){
    T[now].sz=T[T[now].ch[0]].sz+T[T[now].ch[1]].sz+1;
}
void merge(int &now,int s,int b){
    if(!s||!b){
        now=s+b; return;
    }
    if(T[s].key<T[b].key)
        now=s,merge(T[now].ch[1],T[s].ch[1],b);
    else
        now=b,merge(T[now].ch[0],s,T[b].ch[0]);
    update(now);
}
void split(int now,int &ltr,int &rtr,int value){
    if(!now){
        ltr=rtr=0;
        return;
    }
    if(T[now].val<=value)
        ltr=now,split(T[now].ch[1],T[ltr].ch[1],rtr,value);
    else
        rtr=now,split(T[now].ch[0],ltr,T[rtr].ch[0],value);
    update(now);
}
void ins(int value){
    int x=0,y=0,z=0;
    make_data(z,value);
    split(root,x,y,value);
    merge(x,x,z);
    merge(root,x,y);
}
void del(int value){
    int x=0,y=0,z=0;
    split(root,x,y,value);
    split(x,x,z,value-1);
    merge(z,T[z].ch[0],T[z].ch[1]);
    merge(x,x,z);merge(root,x,y);
}
void getrank(int value){
    int x=0,y=0;
    split(root,x,y,value-1);
    printf("%d\n",T[x].sz+1);
    merge(root,x,y);
}
void findKth(int now,int x){
    while (T[T[now].ch[0]].sz+1!=x) {
        if (T[T[now].ch[0]].sz>=x)
            now=T[now].ch[0];
        else
            x-=(T[T[now].ch[0]].sz+1),now=T[now].ch[1];
    }
    printf("%d\n",T[now].val);
}
void las(int value){
    int x=0,y=0;
    split(root,x,y,value-1);
    findKth(x,T[x].sz);
    merge(root,x,y);
}
void nex(int value){
    int x=0,y=0;
    split(root,x,y,value);
    findKth(y,1);
    merge(root,x,y);
}