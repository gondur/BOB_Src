@echo off
iff "%Lang" == "" .AND. "%1" == "" then
echo You must provide a Language for SplitChat
else
if not "%1"=="" set Lang=%1
Echo SplitChat using %Lang

set projpath=T:

copy %projpath\radio\%Lang.txt %projpath\radio\%Lang\radmast.res
t %projpath\radio\%Lang\radmast.res

chatbat %projpath\radio\%Lang\radmast.res master.fil


