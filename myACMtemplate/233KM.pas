const 
	lx_is_not_a_genuis=false;
var 
	i,k,n,m,x,y,e,ans:longint;
	flag,lx,ly,slack:array[1..501]of longint;
	vy,vx:array[1..501]of boolean;
	w:array[1..501,1..501]of longint;

	function max(i,j:longint):longint; begin if (i<j) then max:=j else max:=i; end;
	function min(i,j:longint):longint; begin if (i<j) then min:=i else min:=j; end;
	function find(x:longint):boolean;
	var i:longint;
	begin
		vx[x]:=true;
		for i:=1 to n do 
		if ((not vy[i])and(w[x,i]=lx[x]+ly[i])) then begin
			vy[i]:=true;
			if ((flag[i]=0)or(find(flag[i]))) then begin flag[i]:=x; exit(true); end;
		end else 
		if (w[x][i]<lx[x]+ly[i]) then slack[x]:=min(slack[x],lx[x]+ly[i]-w[x][i]);
		exit(false);
	end;
	procedure KM();
	var k,i,d:longint;
	begin
		fillchar(flag,sizeof(flag),0);
		for k:=1 to n do 
		repeat
			fillchar(vx,sizeof(vx),false);
			fillchar(vy,sizeof(vy),false);
			for i:=1 to n do slack[i]:=maxlongint;
			if (find(k)) then break;
			d:=maxlongint;
			for i:=1 to n do d:=min(d,slack[i]);
			for i:=1 to n do begin
				if (vx[i]) then dec(lx[i],d);
				if (vy[i]) then inc(ly[i],d);
			end;
		until lx_is_not_a_genuis;
		ans:=0;
		for k:=1 to n do inc(ans,w[flag[k],k]);   
	end;
	
begin
	read(n,m,e);
	fillchar(lx,sizeof(lx),0);
	fillchar(ly,sizeof(ly),0);
	fillchar(w,sizeof(w),0);
	for i:=1 to e do 
		begin read(x,y,k); w[x][y]:=max(w[x][y],k); lx[x]:=max(lx[x],k); end;
	n:=max(n,m); KM(); writeln(ans);
end.
