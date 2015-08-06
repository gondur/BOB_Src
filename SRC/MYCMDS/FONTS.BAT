if exist c:\windows\fonts.old\CON	wipe c:\windows\fonts.old
if not exist c:\windows\fonts\fusion_b.ttf copy t:\fonts\fusion_b\fusion_b.ttf c:\windows\fonts
if not exist c:\windows\fonts\g101016_.ttf copy t:\fonts\fontco__\g101016_.ttf c:\windows\fonts
if %@fileage[t:\fonts\fusion_b\fusion_b.ttf] GT %@fileage[c:\windows\fonts\fusion_b.ttf] goto doupdatefont
if %@fileage[t:\fonts\fontco__\g101016_.ttf] GT %@fileage[c:\windows\fonts\g101016_.ttf] goto doupdatefont
echo Fonts are up to date...
goto end

:doupdatefont

echo Fonts are not up to date!
echo Please remove "fusion bold" and "FC-Glamour-Bold" before continuing...
start c:\windows\fonts
pause
if not exist c:\windows\fonts\fusion_b.ttf copy t:\fonts\fusion_b\fusion_b.ttf c:\windows\fonts
if not exist c:\windows\fonts\g101016_.ttf copy t:\fonts\fontco__\g101016_.ttf c:\windows\fonts
:DeadCode JIM 26Sep00 md c:\windows\fonts.new
:DeadCode JIM 26Sep00 copy /q c:\windows\fonts\*.* c:\windows\fonts.new
:DeadCode JIM 26Sep00 copy t:\fonts\fusion_b\fusion_b.ttf c:\windows\fonts.new
:DeadCode JIM 26Sep00 copy t:\fonts\fontco__\g101016_.ttf c:\windows\fonts.new
:DeadCode JIM 26Sep00 ren /A: c:\windows\fonts c:\windows\fonts.old
:DeadCode JIM 26Sep00 ren /A: c:\windows\fonts.new c:\windows\fonts
:DeadCode JIM 26Sep00 attrib /D +h c:\windows\fonts


:end
