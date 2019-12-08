var 
	n,m,k,i,ans:longint;
    x,y,flag,f:array[0..1005] of longint;
	exist:array[0..1005] of boolean;

	function path(x:longint):boolean;
	var i,v:longint;
	begin
		for i:=f[x] to f[x+1]-1 do
		if not(exist[y[i]]) then begin
			v:=y[i]; exist[v]:=true;
			if ((flag[v]=0)or path(flag[v])) then 
				begin flag[v]:=x; exit(true); end;
		end;
		exit(false);
	end;
	procedure hungary();
	var i:longint;
	begin
		fillchar(flag,sizeof(flag),0);
		for i:=1 to m do begin
			fillchar(exist,sizeof(exist),false);
			if (path(i)) then inc(ans);
		end;
	end;
	procedure qsort(l,r:longint);
	var i,j,k,xx,yy:longint;
	begin
		i:=l; j:=r; xx:=x[(i+j)>>1]; yy:=y[(i+j)>>1];
		repeat
			while (x[j]>xx) do dec(j);
			while (xx>x[i]) do inc(i);
			if (i<=j) then begin
				k:=x[i]; x[i]:=x[j]; x[j]:=k;
				k:=y[i]; y[i]:=y[j]; y[j]:=k;
				inc(i); dec(j);
			end;
		until (i>j);
		if (j>l) then qsort(l,j);
		if (i<r) then qsort(i,r);
	end;
	procedure star();
	begin
		qsort(1,k);
		for i:=1 to k do if (f[x[i]]=0) then f[x[i]]:=i;
		f[m+1]:=k+1;
		for i:=m downto 1 do if (f[i]=0) then f[i]:=f[i+1];
	end;
	
begin
	read(m,n,k); ans:=0; 
	for i:=1 to k do read(x[i],y[i]);
	star(); hungary(); writeln(ans);
end.
