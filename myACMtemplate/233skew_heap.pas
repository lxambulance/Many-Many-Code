type
	Node=^HeapNode;
	HeapNode=record
		key,dis:int64;
		l,r:Node;
	end;
	Edge=record
		l:longint;
		ed,nt,lt:array[0..100005]of longint;
	end;
var 
	E:Edge;
	Null:Node;
	ans:int64;
	i,k,n,m,root:longint;
	H:array[0..100005]of Node;
	salary,lead,num,sum:array[0..100005]of int64;
	
	function Newnode(k:longint):Node; var tmp:Node;
	begin new(tmp); tmp^.l:=Null; tmp^.r:=Null; tmp^.key:=k; tmp^.dis:=1; exit(tmp); end;
	function Merge(x,y:Node):Node;
	var tmp:Node;
	begin
		if (x=Null) then exit(y);
		if (y=Null) then exit(x);
		if (x^.key<y^.key) then begin tmp:=x; x:=y; y:=tmp; end;
		x^.r:=Merge(x^.r,y);
		if (x^.r^.dis>x^.l^.dis) then begin tmp:=x^.r; x^.r:=x^.l; x^.l:=tmp; end;
		x^.dis:=x^.r^.dis+1; exit(x);
	end;
	procedure dfs(t:longint);
	var i,j:longint;
	begin
		num[t]:=1; sum[t]:=salary[t]; H[t]:=Newnode(salary[t]); i:=E.lt[t];
		while (i>0) do begin
			j:=E.ed[i]; dfs(j); 
			num[t]:=num[t]+num[j]; sum[t]:=sum[t]+sum[j]; H[t]:=Merge(H[t],H[j]); 
			i:=E.nt[i];
		end;
		while (sum[t]>m) do 
			begin dec(num[t]); dec(sum[t],H[t]^.key); H[t]:=Merge(H[t]^.l,H[t]^.r); end;
		if (ans<num[t]*lead[t]) then ans:=num[t]*lead[t];
	end;
	procedure add(x,y:longint);
	begin inc(E.l); E.ed[E.l]:=y; E.nt[E.l]:=E.lt[x]; E.lt[x]:=E.l; end;
	
begin
	readln(n,m);
	fillchar(E.lt,sizeof(E.lt),0); E.l:=0;
	for i:=1 to n do begin
		readln(k,salary[i],lead[i]); 
		if (k=0) then root:=i else add(k,i);
	end;
	new(Null); Null^.key:=0; Null^.dis:=0; Null^.l:=Null; Null^.r:=Null;
	ans:=0; dfs(root); writeln(ans);
end.

5 4
0 3 3
1 3 5
2 2 2
1 2 4
2 3 1
