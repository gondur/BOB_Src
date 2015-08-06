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
//Filename       monotxt.cpp
//System         
//Author         Paul.   
//Date           Wed 16 Oct 1996
//Description    
//------------------------------------------------------------------------------
//DeadCode DAW 23Feb98 #include	"dosdefs.h"


//TempCode JIM 14Nov00 #undef NDEBUG

#define NO_AFX_AUTO
//DEADCODE JIM 08/06/00 typedef union _LARGE_INTEGER {
//DEADCODE JIM 08/06/00     __int64 QuadPart;
//DEADCODE JIM 08/06/00 } LARGE_INTEGER;
//#include	"stdafx.h"
#include	"dosdefs.h"
#include	"monotxt.h"
#include	"Mytime.h"
#ifdef	NDEBUG
#pragma message (__HERE__ "Mono debugs disabled")
#else
#pragma message (__HERE__ "Mono debugs enabled!!!!")
#endif
const	SLong	MonoScreenWidth = 80;
const	SLong	MonoScreenHeight= 25;
const	SLong	MonoStartAddr = 0x0B0000;

class MonoText Mono_Text;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MonoText
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::ClsMono()
{
#ifndef NDEBUG													//DAW 13Nov96
	UWord	temp;

	UWord* scradr = (UWord* )MonoStartAddr;

	cx = cy = 0;

	for (int row = 0;row<MonoScreenWidth;row++)
	{
		for (int column = 0;column<MonoScreenHeight;column++)
		{
			temp = *scradr;

			temp = (temp & 0xFF00) + ' ';

			*scradr++ = temp;
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCursor
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::SetCursor(SLong rx,SLong ry)
{
#ifndef NDEBUG													//DAW 13Nov96
	cx = rx; cy = ry;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Print
//Author		Paul.   
//Date			Thu 24 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::Print(UByte* text,SLong length)
{
#ifndef NDEBUG													//DAW 13Nov96
	UWord  temp;

	UByte  chr;

	UWord* scradr = (UWord* )MonoStartAddr;

	scradr += (cy * MonoScreenWidth) + cx;

	while (length--)
	{
		chr = *text++;

		temp = 0xFF00 & *scradr;

		temp += 0x00FF & (UWord )chr;

		*scradr++ = temp;

		cx++;

		if (cx>=MonoScreenWidth) break;
	}

	cx = 0;

	cy++;

	if (cy>=MonoScreenHeight)
		cy = 0;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TextOutMono
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::TextOutMono(UByte* string)
{
#ifndef NDEBUG													//DAW 13Nov96
	UWord  temp;

	UByte  chr;

	UWord* scradr = (UWord* )MonoStartAddr;

	scradr += (cy * MonoScreenWidth) + cx;

	while (*string)
	{
		chr = *string++;

		if (chr=='\n')	//newline
		{
			cx = 0;
			cy++;

			if (cy>=MonoScreenHeight)	ClsMono();

			scradr = (UWord* )MonoStartAddr + (cy * MonoScreenWidth) + cx;
		}
		else
		{
			temp = 0xFF00 & *scradr;

			temp += 0x00FF & (UWord )chr;

			*scradr++ = temp;

			cx++;

			if (cx>=MonoScreenWidth)
			{
				cx = 0;
				cy++;
				if (cy>=MonoScreenHeight)
				{
					ClsMono();

					scradr = (UWord* )MonoStartAddr;
				}
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BinToASCII
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::BinToASCII(SLong value,UByte* strval)
{
#ifndef NDEBUG													//DAW 13Nov96
	SLong	ival;

	strval += 9;

	for (int counter=0;counter<10;counter++)
	{
		ival = value % 10;

		value = (value - ival)/10;

		*strval = '0' + (UByte )ival;

		strval--;
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartTimer
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::StartTimer(SLong& timevar)
{
#ifndef NDEBUG													//DAW 13Nov96
//TempCode PD 22Oct96 	timevar = Timer_Code.tus;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopTimer
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::StopTimer(SLong& timevar)
{
#ifndef NDEBUG													//DAW 13Nov96
//	SLong	stoptime;

//TempCode PD 22Oct96 	stoptime = Timer_Code.tus;

//	stoptime -= timevar;

//	timevar = stoptime;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopTimer
//Author		Paul.   
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MonoText::StopTimer(SLong& timevar,UByte* string)
{
#ifndef NDEBUG													//DAW 13Nov96
//	SLong	stoptime;

//	UByte	ltstring[] = "1234567890 \n";

//	UByte*	tstring = ltstring;

//TempCode PD 22Oct96 	stoptime = Timer_Code.tus;

//	stoptime -= timevar;

//	TextOutMono(string);

//	BinToASCII(stoptime,tstring);

//	TextOutMono(tstring);
#endif
}

void	MonoText::BinToHEX(SLong v,UByte* c)
{
#ifndef NDEBUG													//DAW 13Nov96
	int p=7;
	while (p>=0)
	{
		int i=v&0xf;
		v>>=4;
		if (i>9)
			c[p]='A'-10+i;
		else
			c[p]='0'+i;
		p--;
	}
	c[8]=0;

#endif
}

//TempCode CSB 13Jul00 ProbeTime::ProbeTime(int x,char* s)	//="%5i")		
//TempCode CSB 13Jul00 {	
//TempCode CSB 13Jul00 	col=x;str=s;
//TempCode CSB 13Jul00 	LARGE_INTEGER t;
//TempCode CSB 13Jul00 	QueryPerformanceCounter(&t);
//TempCode CSB 13Jul00 	ticker=t.QuadPart;
//TempCode CSB 13Jul00 	Mono_Text.Print(UByteP(" <"));
//TempCode CSB 13Jul00 }
//TempCode CSB 13Jul00 
//TempCode CSB 13Jul00 ProbeTime::~ProbeTime()
//TempCode CSB 13Jul00 {
//TempCode CSB 13Jul00 //DEADCODE JIM 08/06/00 	if (Key_Tests.KeyPress3d(RESURRECTKEY))
//TempCode CSB 13Jul00 //DEADCODE JIM 08/06/00 	{
//TempCode CSB 13Jul00 //DEADCODE JIM 08/06/00 		timergo=!timergo;
//TempCode CSB 13Jul00 //DEADCODE JIM 08/06/00 		for (int i=0;i<80;i++)
//TempCode CSB 13Jul00 //DEADCODE JIM 08/06/00 			coltimes[i]=colinsts[i]=0;
//TempCode CSB 13Jul00 //DEADCODE JIM 08/06/00 	}
//TempCode CSB 13Jul00 	LARGE_INTEGER	ticker2;
//TempCode CSB 13Jul00 	QueryPerformanceCounter(&ticker2);
//TempCode CSB 13Jul00 	ticker2.QuadPart-=ticker;
//TempCode CSB 13Jul00 	long	result=ticker2.QuadPart/divfactor;
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 		if (result>coltimes[col]+1000)
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 			Mono_Text.Print(UByteP(str));
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 		if (result<50000)
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 		{
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 			coltimes[col]=(coltimes[col]*colinsts[col]+result)/(colinsts[col]+1);
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 			colinsts[col]+=1;
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 		}
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 		Mono_Text.Print(UByteP(">"));
//TempCode CSB 13Jul00 	int row=colcounts[col];
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 		if (timergo)
//TempCode CSB 13Jul00 	{  
//TempCode CSB 13Jul00 		Mono_Text.Print(UByteP(">   "));
//TempCode CSB 13Jul00 		Mono_Text.PrintAt(col+15,row,UByteP(" "));
//TempCode CSB 13Jul00 		Mono_Text.PrintAt(col,row,result,UByteP(str));
//TempCode CSB 13Jul00 	}
//TempCode CSB 13Jul00 	row++;if (row>20) row=0;
//TempCode CSB 13Jul00 //TEMPCODE DAW 07/06/2000 		if (timergo)
//TempCode CSB 13Jul00 	{
//TempCode CSB 13Jul00 //			Mono_Text.PrintAt(col,row,UByteP(">"));
//TempCode CSB 13Jul00 		Mono_Text.PrintAt(col+15,row,UByteP(">"));
//TempCode CSB 13Jul00 	}
//TempCode CSB 13Jul00 	colcounts[col]=row;
//TempCode CSB 13Jul00 
//TempCode CSB 13Jul00 }
//TempCode CSB 13Jul00 int	QPFMS()	{LARGE_INTEGER v;QueryPerformanceFrequency(&v);return v.QuadPart/10000;}
//TempCode CSB 13Jul00 
//TempCode CSB 13Jul00 int		ProbeTime::colcounts[80]={0};
//TempCode CSB 13Jul00 float	ProbeTime::coltimes[80]={0};
//TempCode CSB 13Jul00 int		ProbeTime::colinsts[80]={0};
//TempCode CSB 13Jul00 int		ProbeTime::divfactor=QPFMS();
//TempCode CSB 13Jul00 bool	ProbeTime::timergo=true;
//TempCode CSB 13Jul00 
