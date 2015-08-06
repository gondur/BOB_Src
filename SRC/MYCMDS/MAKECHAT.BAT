@echo off
iff "%Lang" == "" .AND. "%1" == "" then
echo You must provide a Language for MakeChat
else
if not "%1"=="" set Lang=%1
Echo MakeChat using %Lang
delete chaterrs.err
set projpath=T:
rem if not exist %projpath\game\player\*.wav set projpath=u:\mig
rem if not exist %projpath\game\player\*.wav set projpath=\\migalley\migalley\mig
rem if not exist %projpath\game\player\*.wav start %projpath\dgfvuyergv>NUL
rem if not exist %projpath\game\player\*.wav echo STILL CANT FIND PROJPATH=%projpath\game\player\*.wav
echo Copying .WAV files...
copy /qu %projpath\game\player\*.wav ..\game\player\
copy /qu %projpath\game\plyext\*.wav ..\game\plyext\
copy /qu %projpath\game\lwplayer\*.wav ..\game\lwplayer\
copy /qu %projpath\game\lwplyext\*.wav ..\game\lwplyext\
copy /qu %projpath\game\other\*.wav ..\game\other\
copy /qu %projpath\game\othext\*.wav ..\game\othext\
copy /qu %projpath\game\lwother\*.wav ..\game\lwother\
copy /qu %projpath\game\lwothext\*.wav ..\game\lwothext\
copy /qu %projpath\game\ground\*.wav ..\game\ground\
copy /qu %projpath\game\ground2\*.wav ..\game\ground2\
copy /qu %projpath\game\female\*.wav ..\game\female\
copy /qu %projpath\game\tower0\*.wav ..\game\tower0\
copy /qu %projpath\game\tower1\*.wav ..\game\tower1\
copy /qu %projpath\game\tower2\*.wav ..\game\tower2\
copy /qu %projpath\game\lwvoice2\*.wav ..\game\lwvoice2\

echo Copying Radmast.res...
copy /u %projpath\radio\%Lang%\radmast.res %Lang%\

echo RCHAT2...
echo rchat2 rchatter.grp places.res -x -d11000 -n -p -i %projpath\radio\%Lang% -o ..\game\
rchat2 rchatter.grp places.res -x -d11000 -n -p -i %projpath\radio\%Lang% -o ..\game\
rem rchat2 rchatter.grp places.res -d11000 -t 25 -n -p -i %projpath\radio\%Lang% -o ..\game\
fmake2
