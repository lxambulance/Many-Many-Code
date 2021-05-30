inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int BUFFER_MAX_SIZE=100000;
struct Quick_In{
	char buf[BUFFER_MAX_SIZE],*ps=buf,*pe=buf+1;
	inline void InNext(){
		if (++ps==pe) pe=(ps=buf)+fread(buf,sizeof(char),sizeof(buf)/sizeof(char),stdin);
	}
	//支持double类型
	template<class T>
	inline bool operator ()(T &number){
		T f=1;
		number=0;
		if (ps==pe) return false; //EOF
		do{
			InNext();
			if ((*ps)=='-') f=-1;
		}while (ps!=pe&&!isdigit(*ps));
		if (ps==pe) return false; //EOF
		bool vis_point=0;
		do{
			if ((*ps)=='.') vis_point=1;
			else{
				number=number*10+(*ps)-48;
				if (vis_point) f*=0.1;
			}
			InNext();
		}while (ps!=pe&&(isdigit(*ps)||(*ps)=='.'));
		number*=f;
		return true;
	}
}In;
struct Quick_Out{
	char buf[BUFFER_MAX_SIZE],*ps=buf,*pe=buf+BUFFER_MAX_SIZE;
	char tmp[51]; //整数暂存数组
	double dx[15]={5e-1,5e-2,5e-3,5e-4,5e-5,5e-6,5e-7,5e-8,5e-9,5e-10,5e-11,5e-12,5e-13,5e-14,5e-15};
	inline void write(){
		fwrite(buf, sizeof(char), ps - buf, stdout);
		ps = buf;
	}
	inline void oc(char c){
		*(ps++)=c;
		if (ps==pe) write();
	}
	inline void os(char *s){
		for (int i=0;s[i];++i) oc(s[i]);
	}
	//输出默认带回车
	template<class T>
	inline void oi(T x,char bc='\n'){
		if (x<0) oc('-'),x=-x;
		int len=0;
		if (!x) tmp[len++]='0';
		while (x) tmp[len++]=x%10+'0',x/=10;
		while (len) oc(tmp[--len]);
		oc(bc);
	}
	void of(double x,int fix=8,char bc='\n'){
		x+=dx[fix];
		if (x<0) oc('-'),x=-x;
		oi((ll)x,'.');
		x-=(ll)x;
		while (fix--) {
			x*=10;
			oc('0'+(int)x);
			x-=(int)x;
		}
		oc(bc);
	}
	~Quick_Out() {
		write();
	}
}Out;
