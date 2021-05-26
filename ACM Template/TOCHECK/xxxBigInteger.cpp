struct BigInteger{
	static const int MAXLEN=205,base=1e8; //base^2*MAXLEN<=1e18
	ll len,num[MAXLEN];
	void print()const{
		printf("%lld",num[len]);
		for (int i=len-1;i>0;--i) printf("%08lld",num[i]);
	}
	void clear(){ len=1; memset(num,0,sizeof(num)); }
	BigInteger(){}
	BigInteger(ll x){
		if (x==0) num[len=1]=0;
		else for (len=0;x;x/=base) num[++len]=x%base;
	}
	BigInteger operator +(const BigInteger &B)const{
		if (B.len>len) return B+(*this);
		BigInteger C; C.clear(); C.len=len;
		for (int i=1;i<=B.len;++i) {
			C.num[i]+=num[i]+B.num[i];
			if (C.num[i]>=base) C.num[i+1]=C.num[i]/base,C.num[i]%=base;
		}
		for (int i=B.len+1;i<=C.len;++i) {
			C.num[i]+=num[i];
			if (C.num[i]>=base) C.num[i+1]=C.num[i]/base,C.num[i]%=base;
		}
		if (C.num[C.len+1]) C.len++;
		return C;
	}
	BigInteger operator -(const BigInteger &B)const{ //*this>=B
		BigInteger C=(*this);
		for (int i=1;i<=B.len;++i) {
			C.num[i]-=B.num[i];
			if (C.num[i]<0) C.num[i+1]--,C.num[i]+=base;
		}
		for (int i=B.len+1;i<=C.len;++i)
		if (C.num[i]<0) C.num[i+1]--,C.num[i]+=base; else break;
		while (C.len>1&&C.num[C.len]==0) C.len--;
		return C;
	}
	BigInteger operator *(const BigInteger &B)const{
        BigInteger C; C.clear(); C.len=len+B.len-1;
		for (int i=1;i<=len;++i) {
			for (int j=1;j<=B.len;++j) {
				int k=i+j-1;
				C.num[k]+=num[i]*B.num[j];
				if (C.num[k]>=base) C.num[k+1]+=C.num[k]/base,C.num[k]%=base;
			}
		}
		if (C.num[C.len+1]>0) C.len++;
        return C;
    }
	BigInteger operator /(const ll &b)const{
		BigInteger C=(*this);
		ll rem=0;
		for (int i=C.len;i>0;--i) {
			rem=rem*base+C.num[i];
			C.num[i]=rem/b,rem%=b;
		}
		while (C.len>1&&C.num[C.len]==0) C.len--;
		return C;
	}
	bool operator <(const BigInteger &B)const{
		if (len<B.len) return 1; else if (len>B.len) return 0;
		for (int i=len;i;--i)
		if (num[i]<B.num[i]) return 1; else if (num[i]>B.num[i]) return 0;
		return 0;
	}
}A;
typedef BigInteger BI;const int MAXLEN=205,base=1e8; //base^2*MAXLEN<=1e18
struct BigInteger{
	ll len,num[MAXLEN];
	void print()const{
		printf("%lld",num[len]);
		for (int i=len-1;i>0;--i) printf("%08lld",num[i]);
	}
	void clear(){ len=1; memset(num,0,sizeof(num)); }
	BigInteger(){}
	BigInteger(ll x){
		if (x==0) num[len=1]=0;
		else for (len=0;x;x/=base) num[++len]=x%base;
	}
	BigInteger operator +(const BigInteger &B)const{
		if (B.len>len) return B+(*this);
		BigInteger C; C.clear(); C.len=len;
		for (int i=1;i<=B.len;++i) {
			C.num[i]+=num[i]+B.num[i];
			if (C.num[i]>=base) C.num[i+1]=C.num[i]/base,C.num[i]%=base;
		}
		for (int i=B.len+1;i<=C.len;++i) {
			C.num[i]+=num[i];
			if (C.num[i]>=base) C.num[i+1]=C.num[i]/base,C.num[i]%=base;
		}
		if (C.num[C.len+1]) C.len++;
		return C;
	}
	BigInteger operator -(const BigInteger &B)const{ //*this>=B
		BigInteger C=(*this);
		for (int i=1;i<=C.len;++i) {
			C.num[i]-=B.num[i];
			if (C.num[i]<0) C.num[i+1]--,C.num[i]+=base;
		}
		while (C.len>1&&!C.num[C.len]) C.len--;
		return C;
	}
	BigInteger operator *(const BigInteger &B)const{
		if (B.len>len) return B*(*this);
		if (B.len==1&&B.num[1]==0) return B;
		if (len==1) return BigInteger(num[1]*B.num[1]);
		int mid=len/2;
		BigInteger a1,a2,b1,b2;
		a1.len=len-mid; a2.len=mid;
		for (int i=1;i<=mid;++i) a2.num[i]=num[i];
		for (int i=mid+1;i<=len;++i) a1.num[i-mid]=num[i];
		if (B.len>mid) {
			b1.len=B.len-mid; b2.len=mid;
			for (int i=1;i<=mid;++i) b2.num[i]=B.num[i];
			for (int i=mid+1;i<=B.len;++i) b1.num[i-mid]=B.num[i];
		}
		else {
			b1.num[b1.len=1]=0; b2.len=B.len;
			for (int i=1;i<=B.len;++i) b2.num[i]=B.num[i];
		}
		BigInteger C,z1,z2,z3; C.clear();
		z1=a1*b1; z3=a2*b2; z2=(a1+a2)*(b1+b2)-z1-z3;
		for (int i=1;i<=z1.len;++i) C.num[mid*2+i]+=z1.num[i];
		for (int i=1;i<=z2.len;++i) C.num[mid+i]+=z2.num[i];
		for (int i=1;i<=z3.len;++i) C.num[i]+=z3.num[i];
		C.len=z1.len+mid*2;
		for (int i=1;i<=C.len;++i) C.num[i+1]+=C.num[i]/base,C.num[i]%=base;
		while (C.num[C.len+1]) {
			C.len++;
			C.num[C.len+1]=C.num[C.len]/base;
			C.num[C.len]%=base;
		}
		while (C.len>1&&C.num[C.len]==0) C.len--;
		return C;
	}
	BigInteger operator /(const ll &b)const{
		BigInteger C=(*this);
		ll rem=0;
		for (int i=C.len;i>0;--i) {
			rem=rem*base+C.num[i];
			C.num[i]=rem/b,rem%=b;
		}
		while (C.len>1&&C.num[C.len]==0) C.len--;
		return C;
	}
	bool operator <(const BigInteger &B)const{
		if (len<B.len) return 1; else if (len>B.len) return 0;
		for (int i=len;i;--i)
		if (num[i]<B.num[i]) return 1; else if (num[i]>B.num[i]) return 0;
		return 0;
	}
}A;
typedef BigInteger BI;
