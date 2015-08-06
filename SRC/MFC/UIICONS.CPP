/*
	 Battle of Britain
	 Copyright (C) 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at bob@rowansoftware.com a
better place to ask is http://www.simhq.com/ or even :-
http://www.simhq.com/cgi-bin/boards/cgi-bin/forumdisplay.cgi?action=topics&forum=Battle+of+Britain&number=40&DaysPrune=20&LastLogin=
*/

//------------------------------------------------------------------------------
//Filename       uiicons.cpp
//System         
//Author         R. Hyde 
//Date           Mon 1 Nov 1999
//Description    User interface icon drawing code.
//------------------------------------------------------------------------------

#include "dosdefs.h"
#define F_COMMON
#include "fileman.h"

#include <afxwin.h>         // MFC core and standard components
#include "uiicons.h"


CDC			IconDescUI::imagemapinstances[ICON_MAXICONPAGES];
IconPlace*	IconDescUI::iconplaces[ICON_MAXICONPAGES]={NULL};

#define	MODE2(x,y)	(x*16+y)
#define MODES(a,b,c,d,e,f)	{MODE2 a,MODE2 b,MODE2 c,MODE2 d,MODE2 e,MODE2 f} 
IconPlace	IconDescUI::icontable1[]=
{
	#include "iconlist.g"
	#include "iconlst2.g"
	{0}	//end of list...
};


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadInstances
//Author		R. Hyde 
//Date			Mon 1 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void IconDescUI::LoadInstances(HDC hdc,FileNum f)
{
	if (!iconplaces[0])
	{
		iconplaces[0]=icontable1;
		imagemapinstances[0].CreateCompatibleDC(NULL);
		for (IconPlace* ip=icontable1;ip->W+ip->H;ip++)
			for (int m=7,m0=ip->modes[0];m>0 && ip->modes[m]!=0;m--)
				ip->modes[m]=m0;
	}
	{
		fileblock fb1(f);
		UByteP	pData=(UByteP)getdata(fb1);
		BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
		BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
		BITMAPINFOHEADER* pInfoH=(BITMAPINFOHEADER*)(pData+sizeof(BITMAPFILEHEADER));
		pData+=pFile->bfOffBits;
		HBITMAP map=CreateDIBitmap(hdc,pInfoH,CBM_INIT,pData,pInfo,DIB_RGB_COLORS);
		CBitmap* old=imagemapinstances[0].SelectObject(CBitmap::FromHandle(map));
		if (old)	
			old->DeleteObject();
	}
	fileblocklink::deletedirchain(f); //discard all icons.
}
CON	IconDescUI::IconDescUI()
{
	selectedicon=ICON_NO_ICON;
	selectedmode=IM_UPUNSEL;
	iconplace=NULL;
	imagemap=NULL;
}

CON	IconDescUI::IconDescUI(IconsUI icon,IconModes mode)
{
	this->Set(icon,mode);
}

IconDescUI&	IconDescUI::Set(IconsUI icon,IconModes mode)
{
	ASSERT((icon&ICON_PAGE_MASK)<ICON_PAGE_END);
	int page=(icon&ICON_PAGE_MASK)>>ICON_PAGE_SHIFT;
	int	entry=(icon&ICON_ENTRY_MASK);
	selectedicon=icon;
	iconplace=&iconplaces[page-1][entry];
	imagemap=imagemapinstances+page-1;
	if (icon&ICON_SELECT_MASK)
		return Set(IconModes((icon&ICON_SELECT_MASK)>>ICON_SELECT_SHIFT));
	else
		return Set(mode);
}

IconDescUI&	IconDescUI::Set(IconModes mode)
{
	ASSERT(selectedicon!=ICON_NO_ICON);
	selectedmode=mode;
	return *this;
}

IconDescUI&	IconDescUI::operator=(IconsUI icon)
{
	return Set(icon);
}
IconDescUI&	IconDescUI::operator=(IconModes mode)
{
	return Set(mode);
}
CPoint	IconDescUI::WH()  const
{
	assert(selectedicon!=ICON_NO_ICON);
	return CPoint(iconplace->W*IconPlace::PIXELSPERUNIT,iconplace->H*IconPlace::PIXELSPERUNIT);
}
bool	IconDescUI::SolidIcon(CDC* target,CPoint& p,Alignment ax,Alignment ay)
{
	int	sx=iconplace->X*IconPlace::PIXELSPERUNIT,
		y=iconplace->Y*IconPlace::PIXELSPERUNIT,
		w=iconplace->W*IconPlace::PIXELSPERUNIT,
		h=iconplace->H*IconPlace::PIXELSPERUNIT;
	UByte	moderows=iconplace->modes[selectedmode];
	int	syor=y+IconPlace::PIXELSPERROW*(moderows>>4);
//	int	syand=y+IconPlace::PIXELSPERROW*(moderows&15);
	target->BitBlt(p.x,p.y, w,h, imagemap, sx,syor, SRCCOPY );
	return true;
}

bool	IconDescUI::MaskIcon(CDC* target,CPoint& p,Alignment ax,Alignment ay)
{
	int	sx=iconplace->X*IconPlace::PIXELSPERUNIT,
		y=iconplace->Y*IconPlace::PIXELSPERUNIT,
		w=iconplace->W*IconPlace::PIXELSPERUNIT,
		h=iconplace->H*IconPlace::PIXELSPERUNIT;
	UByte	moderows=iconplace->modes[selectedmode];
	int	syor=y+IconPlace::PIXELSPERROW*(moderows>>4);
	int	syand=y+IconPlace::PIXELSPERROW*(moderows&15);
	target->BitBlt(p.x,p.y, w,h, imagemap, sx,syand, SRCAND );
	target->BitBlt(p.x,p.y, w,h, imagemap, sx,syor, SRCPAINT );
	return true;
}

bool	IconDescUI::OrIcon(CDC* target,CPoint& p,Alignment ax,Alignment ay)
{
	int	sx=iconplace->X*IconPlace::PIXELSPERUNIT,
		y=iconplace->Y*IconPlace::PIXELSPERUNIT,
		w=iconplace->W*IconPlace::PIXELSPERUNIT,
		h=iconplace->H*IconPlace::PIXELSPERUNIT;
	UByte	moderows=iconplace->modes[selectedmode];
	int	syor=y+IconPlace::PIXELSPERROW*(moderows>>4);
//	int	syand=y+IconPlace::PIXELSPERROW*(moderows&15);
	target->BitBlt(p.x,p.y, w,h, imagemap, sx,syor, SRCPAINT );
	return true;
}

bool	IconDescUI::AndIcon(CDC* target,CPoint& p,Alignment ax,Alignment ay)
{
	int	sx=iconplace->X*IconPlace::PIXELSPERUNIT,
		y=iconplace->Y*IconPlace::PIXELSPERUNIT,
		w=iconplace->W*IconPlace::PIXELSPERUNIT,
		h=iconplace->H*IconPlace::PIXELSPERUNIT;
	UByte	moderows=iconplace->modes[selectedmode];
//	int	syor=y+IconPlace::PIXELSPERROW*(moderows>>4);
	int	syand=y+IconPlace::PIXELSPERROW*(moderows&15);
	target->BitBlt(p.x,p.y, w,h, imagemap, sx,syand, SRCAND );
	return true;
}

