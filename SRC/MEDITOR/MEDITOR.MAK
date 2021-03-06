# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = Meditor.exe
OBJFILES = Meditor.obj About.obj AcItem.obj Static.obj MissText.obj \
   afselect.obj missobj.obj SelTarg.obj GrndGrp.obj currshp.obj info.obj \
   Confirm.obj Precomp.obj itemcnt.obj bfform.obj \bob\src\BFIELDS\Meglobal.obj \
   \bob\src\BFIELDS\Persons6.obj \bob\src\BFIELDS\Persons5.obj \
   \bob\src\BFIELDS\Persons2.obj Sgroups.obj gamestub.obj Memain.obj Memain2.obj \
   Loadsave.obj waypoint.obj \bob\src\FILES\Fileman.obj mapload.obj Memain3.obj \
   Eventtxt.obj eventsel.obj Eventspn.obj \bob\src\BFIELDS\Persons4.obj \
   \bob\src\BFIELDS\persons7.obj NameList.obj TPaintWl.obj SGSelect.obj
RESFILES = Meditor.res
RESDEPEN = $(RESFILES) About.dfm AcItem.dfm Static.dfm MissText.dfm \
   afselect.dfm missobj.dfm SelTarg.dfm GrndGrp.dfm currshp.dfm info.dfm \
   Confirm.dfm Precomp.dfm itemcnt.dfm bfform.dfm Sgroups.dfm Memain.dfm \
   Loadsave.dfm waypoint.dfm Eventtxt.dfm eventsel.dfm Eventspn.dfm NameList.dfm \
   SGSelect.dfm
LIBFILES = 
DEFFILE = 
# ---------------------------------------------------------------------------
CFLAG1 = -Od -w -k -r- -y -v -vi- -c -a4 -b- -w-par -w-inl -Vx -Ve -x -g255 \
   -j100
CFLAG2 = -Ic:\bob\src\bfields;c:\bob\src\files;$(BCB)\bin;$(BCB)\examples\controls\source;$(BCB)\images\buttons;.\icons;$(BCB)\projects;$(BCB)\examples\controls;c:\;$(BCB)\images;.\wav;$(BCB)\include;$(BCB)\include\vcl;..\h; 
PFLAGS = -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE \
   -Uc:\bob\src\bfields;c:\bob\src\files;$(BCB)\bin;$(BCB)\examples\controls\source;.\icons;$(BCB)\examples\controls;.\wav;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib \
   -Ic:\bob\src\bfields;c:\bob\src\files;$(BCB)\bin;$(BCB)\examples\controls\source;$(BCB)\images\buttons;.\icons;$(BCB)\projects;$(BCB)\examples\controls;c:\;$(BCB)\images;.\wav;$(BCB)\include;$(BCB)\include\vcl;..\h; \
   -v -$Y -$W -$O- -JPHNV -M     
RFLAGS = -ic:\bob\src\bfields;c:\bob\src\files;$(BCB)\bin;$(BCB)\examples\controls\source;$(BCB)\images\buttons;.\icons;$(BCB)\projects;$(BCB)\examples\controls;c:\;$(BCB)\images;.\wav;$(BCB)\include;$(BCB)\include\vcl;..\h; 
LFLAGS = -Lc:\bob\src\bfields;c:\bob\src\files;$(BCB)\bin;$(BCB)\examples\controls\source;.\icons;$(BCB)\examples\controls;.\wav;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib \
   -Sc:0x80000 -aa -Tpe -x -v -V4.0 
IFLAGS = -g 
LINKER = tlink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) vcl.lib import32.lib cp32mt.lib 
# ---------------------------------------------------------------------------
.autodepend

$(PROJECT): $(OBJFILES) $(RESDEPEN) $(DEFFILE)
	$(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES) 
!

.pas.hpp:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.pas.obj:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.cpp.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $* 

.c.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $**

.rc.res:
    $(BCB)\BIN\brcc32 $(RFLAGS) $<
#-----------------------------------------------------------------------------
