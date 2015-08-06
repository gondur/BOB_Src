@echo off
iff "%Lang" == "" .AND. "%1" == "" then
echo You must provide a Language for TestChat
else
if not "%1"=="" set Lang=%1
Echo TestChat using %Lang

set projpath=T:

copy %projpath\radio\%Lang.txt \bob\fakechat\radmast.res
copy %projpath\radio\rchatter.grp \bob\fakechat\
copy %projpath\radio\places.res \bob\fakechat\
chatbat \bob\fakechat\radmast.res master.fil
rchat2 rchatter.grp places.res -x -a -d11000 -n -p -i \bob\fakechat -o ..\game\
copy mfc\bob.rc ..\mfcbob.rc
copy mfc\resource.h ..\mfcbob.h
copy %Lang\bob.rc ..\%Lang\bob.rc
mergelst @%Lang\roblst.lst








































