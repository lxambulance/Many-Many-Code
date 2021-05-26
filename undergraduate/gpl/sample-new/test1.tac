var n
n = 0
var m
m = 0
label main
begin
n = 1
label L2
var t0
t0 = (n < 10)
ifz t0 goto L3
actual n
call PRINTN
actual L1
call PRINTS
var t1
t1 = n + 1
n = t1
goto L2
label L3
end
