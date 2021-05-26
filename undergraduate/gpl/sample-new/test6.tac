var i
var j
j = 4
var k
k = 3
var l
l = 2
var m
m = 1
label main
begin
formal i
var t0
t0 = (i != j)
actual t0
call PRINTN
var t1
t1 = (i <= j)
actual t1
call PRINTN
actual i
call PRINTN
actual L1
call PRINTS
var t2
t2 = 4 * i
var t3
t3 = t2 - -3
k = t3
var t4
t4 = (i <= 10)
l = t4
var t5
t5 = i / 2
m = t5
actual L2
call PRINTS
actual i
call PRINTN
actual L1
call PRINTS
actual L3
call PRINTS
actual j
call PRINTN
actual L1
call PRINTS
actual L4
call PRINTS
actual k
call PRINTN
actual L1
call PRINTS
actual L5
call PRINTS
actual l
call PRINTN
actual L1
call PRINTS
actual L6
call PRINTS
actual m
call PRINTN
actual L1
call PRINTS
actual L7
call PRINTS
var t6
actual 15
actual 50
t6 = call func
actual t6
call PRINTN
actual L1
call PRINTS
end
label func
begin
formal y
formal x
var ret
ret = 0
var t7
t7 = ret + 1
ret = t7
label L8
var t8
t8 = x * y
var t9
t9 = (ret < t8)
ifz t9 goto L9
var t11
t11 = ret + y
ret = t11
var t10
t10 = ret - 1
ret = t10
goto L8
label L9
return ret
end
