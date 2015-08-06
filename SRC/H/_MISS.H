#define STRICT
//DEADCODE DAW 27/05/99 #ifdef _DEBUGpe
//DEADCODE DAW 27/05/99 operator new(size_t nSize, char* lpszFileName, int nLine);
//DEADCODE DAW 27/05/99 #define THIS_FILE "MM:" __FILE__
//DEADCODE DAW 27/05/99 #define DEBUG_NEW new(THIS_FILE, __LINE__)
//DEADCODE DAW 27/05/99 
//DEADCODE DAW 27/05/99 #endif
#include "dosdefs.h"
//#include <afx.h>
#define F_SOUNDS
#include "files.g"
#include "myerror.h"
#include "worldinc.h"
#include "node.h"
#include	"UniqueID.h"
#include	"movement.h"
#include	"flyinit.h"
#include	"ranges.h"

class CString;
#include "CString.h"
#include "batnode.h"
#include "package.h"
#include "savegame.h"
#include "bfnumber.h"

//DEADCODE DAW 29/01/00 #include <stdlib.h>
//DEADCODE DAW 29/01/00 #include <windows.h>



//#include <winbase.h>
//#include <winnt.h>
//#include <winuser.h>

