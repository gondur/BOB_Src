@echo off
goto l_%1
:l_
echo Parameter 1 should be 1 of:
echo 	NEW		newest landscape
echo 	CURR		newest landscape (same)
echo 	PREV		previous newest landscape
echo 	SAFE		safest landscape
echo 	FROM who	steal off another machine

goto end
:l_demomini
start \\tim\share_d\crap.exe>NUL
copy  \\tim\share_d\bobwork\demomini\*.* \bob\game\landscap\*.*
goto end
/////////////////////
:l_NEW
:l_CURR
start \\tim\share_d\crap.exe>NUL
copy  \\tim\share_d\bobwork\newest\*.* \bob\game\landscap\*.*
goto end
/////////////////////
:l_PREV
start \\tim\share_d\crap.exe>NUL
copy  \\tim\share_d\bobwork\last\*.* \bob\game\landscap\*.*
goto end
/////////////////////
:l_SAFE
start \\tim\share_d\crap.exe>NUL
copy  \\tim\share_d\bobwork\safe\*.* \bob\game\landscap\*.*
goto end
:l_from
/////////////////////
start \\%2\crap\whatever.exe>NUL
start \\%2\c\windows\net.exe ver
if exist \\%2\share_c\bob\game\landscap\*.dat copy \\%2\share_c\bob\game\landscap\*.* \bob\game\landscap\*.*
if exist \\%2\c\bob\game\landscap\*.dat copy \\%2\c\bob\game\landscap\*.* \bob\game\landscap\*.*
if exist \\%2\share_d\bob\game\landscap\*.dat copy \\%2\share_d\bob\game\landscap\*.* \bob\game\landscap\*.*
goto end




:end
