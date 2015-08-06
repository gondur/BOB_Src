:@echo off
iff "%Lang" == "" .AND. "%1" == "" then
echo You must provide a Language for MergeTxt
else
if not "%1"=="" set Lang=%1
Echo MergeTxt using %Lang using file-list %2
copy mfc\bob.rc ..\MFC%2_bob.rc
copy mfc\resource.h ..\MFC%2_bob_resource.h
copy %Lang%\bob.rc ..\%1%2_bob.rc
set projpath=T:
if "%2"=="#" mergelst # mfc\resource.h # %1\bob.rc # # # h\noradtxt.g # #
if not "%2"=="#" mergelst @%lang%\mergelst.lst
endiff

