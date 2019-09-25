struct BigInteger{
	static const int MAXLEN=205,base=1e8;
	ll l,x[MAXLEN];
	inline void print(){
		printf("%lld",x[l]);
		for (int i=l-1;i;--i) printf("%08lld",x[i]);
	}
	inline void clear(){ l=1; memset(x,0,sizeof(x)); }
	BigInteger(){ clear(); }
	BigInteger(ll a){
		clear();
		if (a) for (l=0;a;a/=base) x[++l]=a%base;
	}
	BigInteger operator +(const BigInteger &B)const{
		BigInteger C; C.l=(B.l>l?B.l:l);
		for (int i=1;i<=C.l;++i) {
			C.x[i]+=x[i]+B.x[i];
			if (C.x[i]>=base) C.x[i+1]+=C.x[i]/base,C.x[i]%=base;
		}
		if (C.x[C.l+1]) C.l++;
		return C;
	}
	BigInteger operator -(const BigInteger &B)const{
		BigInteger C=(*this);
		for (int i=1;i<=C.l;++i) {
			C.x[i]-=B.x[i];
			if (C.x[i]<0) C.x[i+1]--,C.x[i]+=base;
		}
		while (C.l>1&&!C.x[C.l]) C.l--;
		return C;
	}
	BigInteger operator *(const BigInteger &B)const{
		BigInteger C; C.l=l+B.l-1;
		for (int i=1;i<=l;++i)
			for (int j=1;j<=B.l;++j) {
				int k=i+j-1;
				C.x[k]+=x[i]*B.x[j];
				if (C.x[k]>=base) C.x[k+1]+=C.x[k]/base,C.x[k]%=base;
			}
		if (C.x[C.l+1]>0) C.l++;
		return C;
	}
	BigInteger operator /(const ll &b)const{
		BigInteger C=(*this); ll j=0;
		for (int i=C.l;i>0;--i) {
			j=j*base+C.x[i];
			C.x[i]=j/b,j%=b;
		}
		while (C.l>1&&C.x[C.l]==0) C.l--;
		return C;
	}
	bool operator <(const BigInteger &B)const{
		if (l<B.l) return 1; else if (l>B.l) return 0;
		for (int i=l;i;--i) if (x[i]<B.x[i]) return 1; else if (x[i]>B.x[i]) return 0;
		return 0;
	}
}A;
typedef BigInteger BI;