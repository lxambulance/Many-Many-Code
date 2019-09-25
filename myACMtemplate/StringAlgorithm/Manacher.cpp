//使用前字符串需要插入‘#’，长度变为n×2+1，答案长度为对应f值减一
void Manacher(char s[],int f[]){
	int len=strlen(s+1);
	for (int i=1,mx=0,id=0;i<=len;++i) {
		if (mx>i) f[i]=min(f[id*2-i],mx-i); else f[i]=1;
		while (i-f[i]>0&&i+f[i]<=len&&s[i-f[i]]==s[i+f[i]]) ++f[i];
		if (i+f[i]>mx) mx=i+f[i],id=i;
	}
	//FOR(i,1,len) printf("%d%c",f[i]," \n"[i==len]);
}
