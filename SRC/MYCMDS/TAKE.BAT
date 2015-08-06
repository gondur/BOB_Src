if not "%4"=="" goto startunpack
@echo off
if "%1"=="" dir s:\projects\bob\versions/od
if "%1"=="" echo TYPE "%0 user" to install that users version and remove one oldsrc
if "%1"=="" echo TYPE "%0 user zip" to zip the oldsrc
if "%1"=="" echo TYPE "%0 user zip 2" to zip two oldsrcs
if "%1"=="" echo TYPE "%0 user keep" to keep all oldsrcs
if "%1"=="" goto end
if not exist s:\projects\bob\versions\%1.zip echo %1 is not a valid username
if not exist s:\projects\bob\versions\%1.zip dir s:\projects\bob\versions/od
if not exist s:\projects\bob\versions\%1.zip  echo TYPE "%0 user" to install that users version...
if not exist s:\projects\bob\versions\%1.zip goto end
cd ..
if "%2"=="keep" goto nooldbackup
set oldbackup=
for %i in (9 8 7 6 5 4 3 2 1 0) for %j in (9 8 7 6 5 4 3 2 1 0) if exist oldsrc.%i%j\CON set oldbackup=%i%j
if "%oldbackup"=="" echo could not find old backups...
if "%oldbackup"=="" goto nooldbackup
if "%2"=="zip" if not exist oldsrc.zip\CON md oldsrc.zip
if "%2"=="zip" pkzip -exrp oldsrc.zip\oldsrc%oldbackup oldsrc.%oldbackup\*.*
echo deleting oldest backup: oldsrc.%oldbackup
del /sxz oldsrc.%oldbackup

if not "%2"=="zip" goto nooldbackup
if not "%3"=="2" goto nooldbackup
set oldbackup=
for %i in (9 8 7 6 5 4 3 2 1 0) for %j in (9 8 7 6 5 4 3 2 1 0) if exist oldsrc.%i%j\CON set oldbackup=%i%j
if "%oldbackup"=="" echo could not find old backups...
if "%oldbackup"=="" goto nooldbackup
if not exist oldsrc.zip\CON md oldsrc.zip
pkzip -exrp oldsrc.zip\oldsrc%oldbackup oldsrc.%oldbackup\*.*
echo deleting oldest backup: oldsrc.%oldbackup
del /sxz oldsrc.%oldbackup

:nooldbackup

copy src\mycmds\take.bat .
take %1 xxx xxx xxx xxx

:startunpack

set backup=
set x=if
for %i in (9 8 7 6 5 4 3 2 1 0) for %j in (9 8 7 6 5 4 3 2 1 0) (%x exist oldsrc.%i%j\CON set x=rem^%x not exist oldsrc.%i%j\CON set backup=%i%j)
ren src oldsrc.%backup
if "%backup"="" echo couldn't allocate a number for new backup!
if "%backup"="" pause
echo old src backed up to  oldsrc.%backup
echo taking %1 version
pkunzip -d s:\projects\bob\versions\%1
cd src
makeall

goto end

























:end
