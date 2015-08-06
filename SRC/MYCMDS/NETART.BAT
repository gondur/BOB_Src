@echo off
goto A_%1
:A_
set src=s:\projects\bob\artsrc\finish
call %0 FULLSCR stills
for %i in (2) call %0 WATER %i
for %i in (std user) call %0 NOSEART %i
call %0 LOADERART
echo ACTIVEX ARTWORK
set dst=..\game\artwork\axart
set dst2=..\game\artwork\axart2

copy /qu %src%\tempmig\*.bmp %dst
copy /qu %src%\tempmig\i_ready1.bmp %dst2


copy /qu %src%\icons\tooltop.bmp %dst
copy /qu %src%\icons\puck*.bmp %dst
copy /qu %src%\icons\scrl*.bmp %dst
copy /qu %src%\icons\lwtltop.bmp %dst2
copy /qu %src%\icons\siderule.bmp %dst2
copy /qu %src%\icons\toprule.bmp %dst2


copy /qu %src%\icons\titlebar.bmp %dst\titleb.bmp

copy /qu %src%\icons\iconbw.bmp %dst2\iconset1.bmp
copy /qu %src%\icons\iconlwbw.bmp %dst2\iconslw1.bmp
copy /qu %src%\icons\*.h h\*.g

copy /qu %src%\icons\teleback.bmp %dst2


echo MAP ART
copy /tu s:\projects\bob\artsrc\frmap64p\map?_??.bmp ..\game\map_64p\
copy /tu s:\projects\bob\artsrc\frmap64p\maptable.bmp ..\game\map_64p\

goto end
:A_FULLSCR
set trg=..\game\artwork\dial1024
echo FRONT END SCREENS %2

copy /qu %src%\stills\quikshts.bmp %trg 
copy /qu %src%\stills\sideslct.bmp %trg 
copy /qu %src%\stills\phases.bmp %trg 
copy /qu %src%\stills\endday.bmp %trg 
copy /qu %src%\stills\gameslct.bmp %trg 
copy /qu %src%\stills\radio.bmp %trg 
copy /qu %src%\stills\visitors.bmp %trg 
copy /qu %src%\stills\lwfrag.bmp %trg 
copy /qu %src%\stills\raffrag.bmp %trg 
copy /qu %src%\stills\ready.bmp %trg 
copy /qu %src%\stills\locker.bmp %trg 
copy /qu %src%\stills\multiply.bmp %trg 
copy /qu %src%\stills\phases.bmp %trg 
copy /qu %src%\stills\quikdbrf.bmp %trg 
copy /qu %src%\stills\diary.bmp %trg 
copy /qu %src%\stills\incident.bmp %trg 
copy /qu %src%\stills\replay.bmp %trg 
copy /qu %src%\stills\sideslct.bmp %trg 
copy /qu %src%\stills\mc_3d.bmp %trg 
copy /qu %src%\stills\mc_3dii.bmp %trg 
copy /qu %src%\stills\mc_2d.bmp %trg 
copy /qu %src%\stills\mc_cntrl.bmp %trg 
copy /qu %src%\stills\mc_sound.bmp %trg 
copy /qu %src%\stills\sm_flt.bmp %trg 
copy /qu %src%\stills\sm_game.bmp %trg 
copy /qu %src%\stills\sm_miss.bmp %trg 
copy /qu %src%\stills\sm_views.bmp %trg 
copy /qu %src%\stills\loadsave.bmp %trg 
copy /qu %src%\stills\loading.bmp %trg 

::language specific title screens
copy /qu %src%\stills\title.bmp ..\game\english\text\title.bmp
copy /qu %src%\stills\ftitle.bmp ..\game\french\text\title.bmp
copy /qu %src%\stills\gtitle.bmp ..\game\german\text\title.bmp
copy /qu %src%\stills\ititle.bmp ..\game\italian\text\title.bmp
copy /qu %src%\stills\stitle.bmp ..\game\spanish\text\title.bmp

::copy english if not got language specific title screen
copy /qu %src%\stills\title.bmp ..\game\russian\text\title.bmp


goto end
:A_WATER
set trg=..\game\artwork\water%2
echo MAP DIALOGUE ART %2

copy /qu %src%\tempmig\resource.bmp	%trg 
copy /qu %src%\dialogs\contr2.bmp	%trg
copy /qu %src%\dialogs\alloc.bmp	%trg
copy /qu %src%\dialogs\coms.bmp		%trg
copy /qu %src%\dialogs\squad.bmp	%trg
copy /qu %src%\dialogs\gruppe.bmp	%trg
copy /qu %src%\dialogs\bases.bmp	%trg
copy /qu %src%\dialogs\lufdir.bmp	%trg
copy /qu %src%\dialogs\rafdir.bmp	%trg
copy /qu %src%\dialogs\group10.bmp	%trg
copy /qu %src%\dialogs\group11.bmp	%trg
copy /qu %src%\dialogs\group12.bmp	%trg
copy /qu %src%\dialogs\group13.bmp	%trg
copy /qu %src%\dialogs\jagges.bmp	%trg
copy /qu %src%\dialogs\zeroges.bmp	%trg
copy /qu %src%\dialogs\kmapfges.bmp	%trg
copy /qu %src%\dialogs\stukages.bmp	%trg
copy /qu %src%\dialogs\filter.bmp	%trg
copy /qu %src%\dialogs\damage.bmp	%trg
copy /qu %src%\dialogs\airfield.bmp	%trg
copy /qu %src%\dialogs\docks.bmp	%trg
copy /qu %src%\dialogs\convoys.bmp	%trg
copy /qu %src%\dialogs\factory.bmp	%trg
copy /qu %src%\dialogs\radar.bmp	%trg
copy /qu %src%\dialogs\london.bmp	%trg
copy /qu %src%\dialogs\lairfld.bmp	%trg
copy /qu %src%\dialogs\ldocks.bmp	%trg
copy /qu %src%\dialogs\lconvy.bmp	%trg
copy /qu %src%\dialogs\lfactory.bmp	%trg
copy /qu %src%\dialogs\lradar.bmp	%trg
copy /qu %src%\dialogs\llondon.bmp	%trg
copy /qu %src%\dialogs\hostile.bmp	%trg
copy /qu %src%\dialogs\loadsave.bmp	%trg
copy /qu %src%\dialogs\lufmissn.bmp	%trg
copy /qu %src%\dialogs\rafmissn.bmp	%trg
copy /qu %src%\dialogs\raflog.bmp	%trg
copy /qu %src%\dialogs\luflog.bmp	%trg
copy /qu %src%\dialogs\rafcmbt.bmp	%trg
copy /qu %src%\dialogs\lufcmbt.bmp	%trg
copy /qu %src%\dialogs\route.bmp	%trg
copy /qu %src%\dialogs\waypoint.bmp	%trg
copy /qu %src%\dialogs\cntl.bmp		%trg
copy /qu %src%\dialogs\cntlaccl.bmp	%trg
copy /qu %src%\dialogs\cntlfly.bmp	%trg
copy /qu %src%\dialogs\intrcept.bmp	%trg
copy /qu %src%\dialogs\weather.bmp	%trg
copy /qu %src%\dialogs\review1.bmp	%trg
copy /qu %src%\dialogs\review2.bmp	%trg
copy /qu %src%\dialogs\review3.bmp	%trg
copy /qu %src%\dialogs\intell.bmp	%trg
copy /qu %src%\dialogs\raftask1.bmp	%trg
copy /qu %src%\dialogs\raftask2.bmp	%trg
copy /qu %src%\dialogs\raftask3.bmp	%trg
copy /qu %src%\dialogs\luftask1.bmp	%trg
copy /qu %src%\dialogs\luftask2.bmp	%trg
copy /qu %src%\dialogs\luftask3.bmp	%trg
copy /qu %src%\dialogs\luftask4.bmp	%trg
copy /qu %src%\dialogs\luftask5.bmp	%trg
copy /qu %src%\dialogs\unit.bmp		%trg
copy /qu %src%\dialogs\blank.bmp	%trg
copy /qu %src%\dialogs\blank2.bmp	%trg
copy /qu %src%\dialogs\squadlst.bmp	%trg
copy /qu %src%\dialogs\tote.bmp		%trg
copy /qu %src%\dialogs\logsquad.bmp	%trg
copy /qu %src%\dialogs\loggrupn.bmp	%trg
copy /qu %src%\dialogs\clock.bmp	%trg
copy /qu %src%\dialogs\gswdrlst.bmp	%trg
copy /qu %src%\dialogs\lufalloc.bmp	%trg
copy /qu %src%\dialogs\headon.bmp	%trg	
copy /qu %src%\dialogs\rafpac.bmp	%trg
copy /qu %src%\dialogs\rconvoy.bmp	%trg
copy /qu %src%\dialogs\spitshrt.bmp	%trg
copy /qu %src%\dialogs\hurishrt.bmp	%trg
copy /qu %src%\dialogs\rdfholes.bmp	%trg
copy /qu %src%\dialogs\winston.bmp	%trg
copy /qu %src%\dialogs\royal.bmp	%trg
copy /qu %src%\dialogs\cannon.bmp	%trg
copy /qu %src%\dialogs\rafmsc1.bmp	%trg
copy /qu %src%\dialogs\rafmsc2.bmp	%trg
copy /qu %src%\dialogs\rafmsc3.bmp	%trg
copy /qu %src%\dialogs\rafmsc4.bmp	%trg
copy /qu %src%\dialogs\rafmsc5.bmp	%trg
copy /qu %src%\dialogs\rafmsc6.bmp	%trg
copy /qu %src%\dialogs\rafmsc7.bmp	%trg
copy /qu %src%\dialogs\rafmsc8.bmp	%trg
copy /qu %src%\dialogs\rafmsc9.bmp  %trg	
copy /qu %src%\dialogs\Radionet.bmp	%trg
copy /qu %src%\dialogs\lufpac.bmp	%trg
copy /qu %src%\dialogs\lufmsc1.bmp	%trg
copy /qu %src%\dialogs\lufmsc2.bmp	%trg
copy /qu %src%\dialogs\lufmsc3.bmp	%trg
copy /qu %src%\dialogs\lufmsc4.bmp	%trg
copy /qu %src%\dialogs\lufmsc5.bmp	%trg
copy /qu %src%\dialogs\lufmsc6.bmp	%trg
copy /qu %src%\dialogs\lufmsc7.bmp	%trg
copy /qu %src%\dialogs\lufmsc8.bmp	%trg
copy /qu %src%\dialogs\lufmsc9.bmp	%trg
copy /qu %src%\dialogs\kills.bmp	%trg
copy /qu %src%\dialogs\losses.bmp	%trg
copy /qu %src%\dialogs\kills1.bmp	%trg

goto end							

:A_NOSEART
rem for %i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16) copy /qu u:\artsrc\stills\nose\%2%%i.bmp ..\game\artwork\nose%2\nose%i.bmp
goto end

:A_LOADERART
set trg=..\game\artwork
echo LOADERART
rem copy /q %src%\stills\loadb.bmp %trg\water2\contr2.bmp

:end


