@echo off
del shperrs.err				

iff "%user"=="ROBERT" .OR. "%user"=="VLADDRAK" .OR. "%user"=="RICHARD" then
 	iff "%user"=="ROBERT" then
		sm091100 -a -w -o 3 -c -ps -p ..\shapes\
 	else
		sm091100 -a -w -o 3 -ps -p s:\projects\bob\shapes\
	endiff
else
	iff "%user"=="LOBO" then
		sm091100 -a -w -o 3 -p s:\projects\bob\shapes\
	else
		sm091100 -a -o 3 -p t:\shapes\
	endiff
endiff
	
