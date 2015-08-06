if "%1"=="" %0 ENGLISH FRENCH GERMAN SPANISH
::if "%1"=="" %0 ENGLISH FRENCH GERMAN ITALIAN SPANISH
:loop
if not "%@label[]"=="VERCONTROL" goto dontcompile
cd ..\bobhelp\%1
"c:\program files\html help workshop\hhc.exe" bobhelp
cd ..\..\src\
:dontcompile
copy t:\bobhelp\%1\bobhelp.chm %1\
copy t:\bobhelp\%1\bobhelp.chm ..\game\%1\text\bob.chm
shift
if not "%1"=="" goto loop
