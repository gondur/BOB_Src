//------------------------------------------------------------------------------
//Filename       uiicons.h
//System         
//Author         R. Hyde 
//Date           Mon 1 Nov 1999
//Description    
//BOOL BitBlt( int x, int y, int nWidth, int nHeight, CDC* pSrcDC, int xSrc, int ySrc, DWORD dwRop );
//------------------------------------------------------------------------------
#ifndef	UIICONS_Included
#define	UIICONS_Included

#define	DEFAULT_UIICONS 0

enum	{BIGGEST_ICON_RADIUS=33};


enum	IconsUI
{
	ICON_NO_ICON=0,
	ICON_MAXICONPAGES=1,
	ICON_PAGE_MASK  =0x00ff0000,
	ICON_PAGE_SHIFT=16,
	ICON_ENTRY_MASK =0x0000ffff,
	ICON_SELECT_MASK=0xff000000,
	ICON_SELECT_SHIFT=24,
	ICON_PAGE_BASE=0x10000,
	ICON_PAGE_1=0x10000,
	ICON_PAGE_1_BEFORE=ICON_PAGE_1-1,
	#include "iconnum.g"
	#include "iconnum2.g"
	ICON_PAGE_1_LAST,


	ICON_PAGE_END=0x20000,
								//0 is up
	ICON_SELECT_1=0x1000000,	//down
	ICON_SELECT_2=0x2000000,	//pressed up
	ICON_SELECT_3=0x3000000,	//pressed down
	ICON_SELECT_4=0x4000000,	//disabled up
	ICON_SELECT_5=0x5000000,	//disabled down
	ICON_SELECT_6=0x6000000,
	ICON_SELECT_7=0x7000000,
};
enum	IconModes
{	IM_UPUNSEL,IM_UPSEL,
	IM_DOWNUNSEL,IM_DOWNSEL,
	IM_DISUNSEL,IM_DISSEL
};

class	CDC;
class	CPoint;

struct	IconPlace
{
	enum	{MAX_DIRECTIONS=8,PIXELSPERUNIT=8,PIXELSPERROW=128};
	UWord	X,
			Y,
			W,
			H;
	UByte	modes[MAX_DIRECTIONS];
};
class	IconDescUI;
enum	FileNum;
class	IconDescUI
{  
	friend class	CMIGApp;
	enum	Alignment	{MINIMUM,CENTRE,MAXIMUM};
	CDC*	imagemap;
	static	CDC	imagemapinstances[];
	static	IconPlace*	iconplaces[];
	static	IconPlace	icontable1[];
	IconsUI		selectedicon;
	IconModes	selectedmode;
	IconPlace*	iconplace;

public:
//basic setup functions:
	static void	LoadInstances(HDC,FileNum);
	IconDescUI& Set(IconsUI icon,IconModes mode=IM_UPUNSEL);
	IconDescUI& Set(IconModes mode=IM_UPUNSEL);
	CON IconDescUI();

//alternate setup function syntax:
	CON IconDescUI(IconsUI icon,IconModes mode=IM_UPUNSEL);
	IconDescUI& operator=(IconsUI icon);
	IconDescUI& operator=(IconModes mode);
	IconDescUI& operator[](IconModes mode) {return operator=(mode);}

//inspect functions:
	operator IconsUI() {return selectedicon;}
	operator IconModes()	{return selectedmode;}
	operator bool()			{return selectedicon!=ICON_NO_ICON;}
	CPoint WH() const;

//draw functions:
	virtual bool	SolidIcon(CDC* target,CPoint& p,Alignment x=MINIMUM,Alignment y=MINIMUM);
	virtual bool	MaskIcon(CDC* target,CPoint& p,Alignment x=MINIMUM,Alignment y=MINIMUM);
	virtual bool	OrIcon(CDC* target,CPoint& p,Alignment x=MINIMUM,Alignment y=MINIMUM);
	virtual bool	AndIcon(CDC* target,CPoint& p,Alignment x=MINIMUM,Alignment y=MINIMUM);
};
#endif
