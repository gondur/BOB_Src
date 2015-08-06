@echo off
set src=s:\projects\bob
set shpsrc=s:\projects\bob
:set shpsrc=T:\
md ..\shapes >&>nul
copy /qu %shpsrc%\shapes\*.* ..\shapes
md ..\shapes\shpsrc >&>nul
md ..\shapes\shpdat >&>nul
md ..\shapes\shpani >&>nul
:DeadCode RJS 28Jan00 del h\shapenum.g

iff "%user"=="ROBERT" then
 	copy /qu %src%\shapes\shpsrc\*.asc;*.grp ..\shapes\shpsrc
 	copy /qu %src%\shapes\shpdat\*.dat ..\shapes\shpdat
 	copy /qu %src%\shapes\shpani\*.vue ..\shapes\shpani
 	copy /qu %src%\shapes\shpani\*.vmx ..\shapes\shpani
endiff

imgres3 -m -d master.fil -f imagemap.grp -s %src%\artsrc


copy /q ..\shapes\shapenum.eol ..\shapes\shapenum.old
shpres3 ..\shapes\shapes.res

iff %?==10 then
	echo Naughty additions in the 'shapes.res' file...
	echo    Press 'CTRL & C'... then 'A' to keep these changes
	echo	    ... you will have to rebuild the game ...
	echo OR...
	echo	Press any other key to continue (you will get this message again)
	echo
	echo (If this message really pisses you off, press 'CTRL & C',
	echo           exit, and type 'CLEARSHP'!

	pause
	copy ..\shapes\shapenum.old ..\shapes\shapenum.eol
 else
 	call fmake2 %&
 	call makemaps %&
 	call mshp %&

:DeadCode RJS 28Jan00 	echo Faking BoB shape numbers...
:DeadCode RJS 28Jan00 	ECHO #ifndef SHAPENAM_INCLUDED>>h\shapenum.g
:DeadCode RJS 28Jan00 	ECHO #define SHAPENAM_INCLUDED>>h\shapenum.g
:DeadCode RJS 28Jan00 	ECHO #include "SHAPENAM.h">>h\shapenum.g
:DeadCode RJS 28Jan00 	ECHO #endif	ndef SAHAPENAM_INCLUDED>>h\shapenum.g
:DeadCode MS 29Nov99 	copy /q h\shapenum.g h\temp.g
:DeadCode MS 29Nov99 	copy /q h\temp.g+h\shapenam.h h\shapenum.g
:DeadCode MS 29Nov99 	del /q h\temp.g	echo Faking BoB shape numbers...
 endiff
