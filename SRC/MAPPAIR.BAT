goto m_%1
:m_
@echo off
:: This batch file pairs up tiles that are actually identical
dir /fb ..\game\map_16a\*.bmp>maplist.txt
dir /fb ..\game\map_16b\*.bmp>>maplist.txt
dir /fb ..\game\map_16c\*.bmp>>maplist.txt
dir /fb ..\game\map_16d\*.bmp>>maplist.txt
dir /fb ..\game\map_32a\*.bmp>>maplist.txt
dir /fb ..\game\map_64p\*.bmp>>maplist.txt
:m_all
cd.>maplist2.txt
cd.>pairlist.txt
cd.>remove.txt
set x=0
for %i in (@maplist.txt) (set x=%@eval[%x+1]^call %0 against %i %x)
goto m_end
:::::::::::::::::::::::::::
:m_against
set y=0
for %j in (@maplist2.txt) (set y=%@eval[%y+1]^call %0 pair %2 %3 %j %y)
echo %2>maplist2.txt
goto m_end
:::::::::::::::::::::::::::
:m_pair
echo comparing %2 %4
if %3 GE %5 goto m_end
echo really comparing %2 %4
::wfcq %2 %4
::if errorlevel 1 goto m_end
::echo %2 %4>>pairlist.txt
:::::::::::::::::::::::::::

:::::::::::::::::::::::::::
:m_end
