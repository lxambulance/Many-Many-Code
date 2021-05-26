var i
i = 4118415
label main
begin
var j
j = 2
label L8
var t0
t0 = j * j
var t1
t1 = (t0 < i)
ifz t1 goto L9
var t3
t3 = i / j
var t4
t4 = t3 * j
var t5
t5 = (i == t4)
ifz t5 goto L7
actual L1
call PRINTS
actual j
call PRINTN
actual L2
call PRINTS
actual j
call PRINTN
actual L3
call PRINTS
var t6
actual j
t6 = call func
actual t6
call PRINTN
actual L4
call PRINTS
label L5
var t7
t7 = i / j
var t8
t8 = t7 * j
var t9
t9 = (i == t8)
ifz t9 goto L6
var t10
t10 = i / j
i = t10
goto L5
label L6
label L7
var t2
t2 = j + 1
j = t2
goto L8
label L9
var t11
t11 = (i > 1)
ifz t11 goto L10
actual L1
call PRINTS
actual i
call PRINTN
actual L2
call PRINTS
actual i
call PRINTN
actual L3
call PRINTS
var t12
actual i
t12 = call func
actual t12
call PRINTN
actual L4
call PRINTS
label L10
end
label func
begin
formal x
var i
i = 1
var ret
ret = 0
label L11
var t13
t13 = (i <= x)
ifz t13 goto L12
var t14
t14 = ret + i
ret = t14
var t15
t15 = i + 1
i = t15
goto L11
label L12
return ret
end
