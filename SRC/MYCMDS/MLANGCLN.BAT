cd
rem if exist resource.h	del	resource.h
if exist resource.h move resource.h ..\mfc\
for %i in (res\*.*)	(del %i)
for %i in (*.cur)	(del %i)
@echo.>cleaned.flg

