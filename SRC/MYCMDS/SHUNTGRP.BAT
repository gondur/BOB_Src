:
: Shunts a group by a fixed delta  X and Z
: The deltas can be expressions, but the expressions must not contain spaces
: Param 1 is filename to shunt
: Param 2 is X delta
: Param 3 is Z delta
:
goto L_%4
:L_
@echo off
::::::::::::::::::::::::::::::::::::::::::::
if not "%@eval[%2] %@eval[%3]"=="%2 %3" %0 %1 %@eval[%2] %@eval[%3]
echo applying deltas X=%2 Z=%3 to %1 
del m:temp.dat
for %i in (@%1) call %0 m:temp.dat %2 %3 LINE "%i" %i
echo About to write the changes back unless you press Break NOW!
pause
copy m:temp.dat %1
goto end
::::::::::::::::::::::::::::::::::::::::::::
:L_LINE
if "%6"=="" echo.>>%1
if "%6"=="" goto end
if not "%6"==";GROUP" 	echo (unchanged) %@strip[",%5]
if not "%6"==";GROUP" 	echo %@strip[",%5] >>%1
if "%6"==";GROUP"		echo (corrected) %6 %7	%@eval[%8-%2],%9,%@eval[%10-%2]	%11	%12	%13	%14
if "%6"==";GROUP"		echo %6 %7	%@eval[%8-%2],%9,%@eval[%10-%2]	%11&>>%1
::::::::::::::::::::::::::::::::::::::::::::
:end
