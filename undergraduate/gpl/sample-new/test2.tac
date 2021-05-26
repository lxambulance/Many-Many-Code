var n
n = 0
var m
m = 0
label main
begin
n = 1
label L3
var t0
t0 = (n < 10)
ifz t0 goto L4
actual n
call PRINTN
actual L1
call PRINTS
actual L2
call PRINTS
var t1
t1 = n + 1
n = t1
goto L3
label L4
label L5
var t2
t2 = (m < 5)
ifz t2 goto L6
var t3
t3 = m + 1
m = t3
var t4
t4 = m * m
m = t4
goto L5
label L6
actual m
call PRINTN
end
