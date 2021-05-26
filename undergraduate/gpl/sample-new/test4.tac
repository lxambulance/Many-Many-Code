var i
i = 1000007
label main
begin
var j
j = 2
label L4
var t0
t0 = (j < i)
ifz t0 goto L5
var t1
t1 = i / j
var t2
t2 = t1 * j
var t3
t3 = (i == t2)
ifz t3 goto L3
actual L1
call PRINTS
actual j
call PRINTN
actual L2
call PRINTS
label L3
var t4
t4 = j + 1
j = t4
goto L4
label L5
j = 2
label L8
var t5
t5 = (j < i)
ifz t5 goto L9
var t7
t7 = i / j
var t8
t8 = t7 * j
var t9
t9 = (i == t8)
ifz t9 goto L7
actual L6
call PRINTS
actual j
call PRINTN
actual L2
call PRINTS
label L7
var t6
t6 = j + 1
j = t6
goto L8
label L9
end
