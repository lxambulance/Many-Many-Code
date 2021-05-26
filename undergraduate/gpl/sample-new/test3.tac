var n
n = 0
var m
m = 0
label main
begin
var x
x = 1381
var y
y = 1482
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
var t5
actual x
actual y
t5 = call gcd
x = t5
actual x
call PRINTN
end
label gcd
begin
formal y
formal x
var z
var t6
t6 = (x == 0)
ifz t6 goto L7
return y
label L7
var t7
t7 = (y == 0)
ifz t7 goto L8
return x
label L8
var t8
t8 = (x > y)
ifz t8 goto L9
var t9
t9 = x - y
var t10
actual t9
actual y
t10 = call gcd
z = t10
return z
label L9
var t11
t11 = y - x
var t12
actual x
actual t11
t12 = call gcd
z = t12
return z
end
