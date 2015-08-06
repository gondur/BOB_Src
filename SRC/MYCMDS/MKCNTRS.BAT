:::@echo off
cd S:\projects\bob\artsrc\
cd
copy s:landscap\daypal.pal ..\game\landmaps\
copy s:artsrc\land.pal ..\game\landmaps\

iff "%1"=="newpal" then
	make45 -f makefile\makland.mke
:::	call mlm.bat NewPal
:::	make45 -s -f makefile\makecntr.mke
:::else 
:::	make45 -s -f makefile\makecntr.mke %&
endiff
:::call mlm.bat
make45 -s -f makefile\makecntr.mke %&
make45 -f makefile\makland.mke %&
