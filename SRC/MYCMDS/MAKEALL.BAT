@echo off
echo Making english - can do french german italian spanish
echo MAKEALL %user @ %_date %_time>>mycmds\thisver.log
Set Lang=English
if NOT "%1" == "" if not "%1"=="goto" set Lang=%1
goto S_%2
:S_

echo Making all directories nd dir.dir files
md ..\debug
md ..\release
md ..\shapes
del ..\shapes\shapenum.eol
del ..\shapes\shapenum.old
del ..\game\samples\volumes.txt
del ..\game\samples\volumes.bin
del ..\game\english\text\radscrpt.bin
del ..\game\german\text\radscrpt.bin
del ..\game\italian\text\radscrpt.bin
del ..\game\french\text\radscrpt.bin
del ..\game\spanish\text\radscrpt.bin
del rchatter.fil

mkdir ..\game\artwork
mkdir ..\game\abfields
mkdir ..\game\english
mkdir ..\game\french
mkdir ..\game\german
mkdir ..\game\italian
mkdir ..\game\spanish
mkdir ..\game\english\StdProf
mkdir ..\game\french\StdProf
mkdir ..\game\german\StdProf
mkdir ..\game\italian\StdProf
mkdir ..\game\spanish\StdProf
copy ..\game\english\dir.dir /s ..\game\german
copy ..\game\english\dir.dir /s ..\game\french
copy ..\game\english\dir.dir /s ..\game\italian
copy ..\game\english\dir.dir /s ..\game\spanish
fmake2

echo Making all chatter and music
call mycmds\makechat.bat
call mycmds\mksample.bat
rem call mycmds\makexmi2.bat
rem call mycmds\makemile.bat

echo Making all imagemap bases
call mkcntrs.bat
echo Making all shapes
call makeshps.bat

echo Making all static artwork
call netart.bat

call mergetxt
for %i in (FRENCH ITALIAN SPANISH GERMAN RUSSIAN) if exist ..\game\%i\text del ..\game\%i\text
for %i in (FRENCH ITALIAN SPANISH GERMAN RUSSIAN) if not exist ..\game\%i\text\dir.dir md ..\game\%i\text\
for %i in (FRENCH ITALIAN SPANISH GERMAN RUSSIAN) copy ..\game\ENGLISH\text\DIR.DIR ..\game\%i\text\
for %i in (FRENCH ITALIAN SPANISH GERMAN) call makechat %i
for %i in (FRENCH ITALIAN SPANISH GERMAN) call mergetxt %i
::languages include: (FRENCH ITALIAN SPANISH GERMAN PORT GREEK RUSSIAN JAP)
call makehelp
for %i in (ITALIAN RUSIAN)	copy ..\game\english\text\bob.chm ..\game\%i\text\

call mkcntrs.bat
call makeshps.bat

rem call uimap down

::copy grids down
copy /u t:\landscape\griddata\*.grd ..\game\griddata\

::some more dodgy jim bits
if "%@label[]"=="VERCONTROL" goto nothere
start \\vercontrol\bob_central\rubbish
for %i in (map_16a map_16b map_16c map_16d map_32 map_32a map_64p) if not exist ..\game\%i\ md ..\game\%i\
for %i in (map_16a map_16b map_16c map_16d map_32 map_32a map_64p) copy /qu \\vercontrol\bob\bob\game\%i\*.bmp ..\game\%i\
copy t:\game\avi\*.avi /u ..\game\avi
del ..\game\smacker /sy
del ..\game\artwork\dial1024\title.bmp
:nothere
:DeadCode JIM 16Oct100 copy t:bobhelp\bobhelp.chm ..\game\english\text\bob.chm

call fonts

call landup safe
:s_delete
if not exist ..\backup\history.lst md ..\backup
if not exist ..\backup\prev\history.lst md ..\backup\prev
if exist ..\backup\prev\history.lst del /y ..\backup\prev\*.* 
if exist ..\backup\history.lst move ..\backup\*.* ..\backup\prev\
echo.>..\backup\history.lst


echo Deleting stuff to force rebuild [last thing to do]
del bfields*.fil
for %i in (debug release demodeb demorel) (del ..\%i /qsy^md ..\%i\^md ..\%i\exe)
del ..\game\savegame\*.* /qsy
del ..\game\stdprof\*.* /qsy
copy mycmds\rowanx.dsm mycmds\rowanu.dsm
echo	Function myname():myname="%initials%":End Function     >>mycmds\rowanu.dsm
echo	Function myusername():myusername="%user%":End Function >>mycmds\rowanu.dsm
echo MAKEALL @ %_date %_time>>s:\projects\bob\admin\%user%.log
rd ..\game\stdprof
beep 1000 5 200 5 800 5 10000 10
