const LL MAXN=1005,base=10000;
struct BigNum{
	LL l,x[MAXN];
	inline void clear() { l=1; memset(x,0,sizeof(x)); }
	BigNum() { clear(); }
	BigNum(LL a) { for (l=0;a;a/=base) x[++l]=a%base; }
	BigNum operator +(const BigNum &B) const {
		BigNum C; C.l=(B.l>l?B.l:l);
		for (LL i=1;i<=C.l;++i) {
			C.x[i]+=x[i]+B.x[i];
			if (C.x[i]>=base) {
				C.x[i+1]+=C.x[i]/base;
				C.x[i]%=base;
			}
		}
		if (C.x[C.l+1]) C.l++;
		return C;
	}
	BigNum operator -(const BigNum &B) const {
		BigNum C=(*this);
		for (LL i=1;i<=C.l;++i) {
			C.x[i]-=B.x[i];
			if (C.x[i]<0) { C.x[i+1]--; C.x[i]+=base; }
		}
		while (C.l>1&&!C.x[C.l]) C.l--;
		return C;
	}
	BigNum operator *(const BigNum &B) const {
		BigNum C; C.l=l+B.l-1;
		for (LL i=1;i<=l;++i)
			for (LL j=1;j<=B.l;++j) {
				LL k=i+j-1;
				C.x[k]+=x[i]*B.x[j];
				if (C.x[k]>=base) {
					C.x[k+1]+=C.x[k]/base;
					C.x[k]%=base;
				}
			}
		while (C.x[C.l+1]>0) {
			C.l++;
			if (C.x[C.l]>base) {
				C.x[C.l+1]=C.x[C.l]/base;
				C.x[C.l]%=base;
			}
		}
		return C;
	}
	BigNum operator /(const LL &b) const {
		BigNum C=(*this);
		for (LL i=C.l,j=0;i>0;--i) {
			j=j*base+C.x[i];
			C.x[i]=j/b;
			j%=b;
		}
		while (C.l>1&&C.x[C.l]==0) C.l--;
		return C;
	}
}A;
typedef BigNum NB;
void write(NB &A) {
	printf("%lld",A.x[A.l]);
	for (LL i=A.l-1;i>0;--i) {
		if (A.x[i]<10) printf("000%lld",A.x[i]);
		else if (A.x[i]<100) printf("00%lld",A.x[i]);
		else if (A.x[i]<1000) printf("0%lld",A.x[i]);
		else printf("%lld",A.x[i]);
	}
	printf("\n");
}

