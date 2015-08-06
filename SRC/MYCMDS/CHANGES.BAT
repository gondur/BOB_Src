@echo off
pushd
set cwd=%_cwd
call FIXDATE.bat
echo y|y:\map delete n:
subst /d n:
subst n: .
n:
set /r s:\projects\bob\admin\version\%user%.ver
del *.pch *.cfg *.flg *.err /s >&>nul
del mfc\bobold.rc
del m:subpoo\*.* /y
del model\*.fil;*.txt /y
dir /sb /a-h /a-d /[d%DateForUp@%TimeForUp] >m:poo
for %i in (\.grd \.sym \.map \.exe bf.+\.fil \.pif %2 %3 %4)  (grep -i -o- -v %i m:poo >m:poo2^copy /q m:poo2 m:poo)
grep -i- -o- -v "File " m:poo2>m:poo
if not %@filedate[m:poo]==%@filedate[s:\transfer\updates\bob\%user.zip] mv s:\transfer\updates\bob\%user.zip s:\transfer\updates\bob\lastver\%user.zip
type m:poo
echo %@lines[m:poo] FILES!
%1&
if %@lines[m:poo] lt 150 goto inrange
md m:subpoo
dir /sb /a-h /ad *.* >m:poo
for %i in (@m:poo) dir %i\*.* /f /a-h /a-d /[d%DateForUp@%TimeForUp] >m:subpoo\%@filename[%i]
del m:subpoo\*.* /[s0,0] /y
except (*.sym *.map *.exe bob.* ) dir /b /a-h /a-d /[d%DateForUp@%TimeForUp] >m:subpoo\src

echo %@files[m:subpoo\*.*] Directories
del m:poo
:inrange
%1&
echo %@files[m:subpoo\*.*] Directories and  %@lines[m:poo] FILES!
del m:%user.zip
if exist m:poo pkzip -exrP m:%user @m:poo
if not exist m:poo for %i in (m:subpoo\*.*) pkzip -exrP m:%user @%i
copy m:%user.zip s:\transfer\updates\bob\
%cwd\
set cwd=
popd
subst /d n:
