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

////////////////////////////////////////////////////////////////////////
//
// Source File:	Placenam.cpp
//
// Original Author:	JIM
// Documented Date:	20/06/01
//
// History:
//		
//		
// Description:	Stand-alone program which creates the list of place names 
//				which is used to give position information in the radio chatter.
//				This is doen by scanning the output of the battlefield system for
//				certain types of object.
////////////////////////////////////////////////////////////////////////		
// PLACENAM.cpp : Defines the entry point for the console application.
//

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	"dosdefs.h"
#include	"bfenum.h"
#include	"readenum.h"



typedef	char	MyString[256];

struct	UidStuff
{
	char*	name;
	char*	text;
};

struct	UIDBands
{
	int			uidstart;
	int			uidcnt;
	char		bandname[256];
	int			uidbandno;
	UidStuff	uidentries[256];

	UIDBands()
	{
		uidstart = 0;
		uidcnt = 0;
		bandname[0]=0;
		uidbandno = 0;
	}
};

int	GetBandNames(MyString* names, char* filename)
{
	FILE*	fp;
	char	buffer[256];
	char	tmpstring[256];
	int		nobands = 0;
	
	fp = fopen(filename,"rt");
	if (fp)
	{
		buffer[0]=0;
		while (fgets(buffer,255,fp))
		{
			tmpstring[0]=0;
			sscanf(buffer,"%s",tmpstring);
			if (tmpstring[0])
				strcpy(names[nobands++],buffer);
		}

		fclose(fp);
	}
	else
		fprintf(stdout,"ERROR:   %s does not exist!\n\n",filename);

	return nobands;
}

void	PullBandInfo(MyString* bands, int bandcnt, UIDBands* bandtable)
{
	IEnumStuff.readenums();
	char	bandname[256];
	char	filename[256];
	char	voicename[256];

	for (int i=0; i < bandcnt; i++)
	{
		sscanf(bands[i],"%s %s %s",voicename,filename,bandname);

		strcpy(bandtable[i].bandname,bands[i]);
		bandtable[i].uidbandno = GetList(ENUM_UIDBand).Translate(bandname);
		for (int j=0; j < 256; j++)
		{
			bandtable[i].uidentries[j].name = GetList(ENUM_UniqueID).Translate(bandtable[i].uidbandno+j+1);
			bandtable[i].uidentries[j].text = GetList(ENUM_UIDtitle).Translate(bandtable[i].uidbandno+j+1);
			if (bandtable[i].uidentries[j].text)
			{
				if (bandtable[i].uidstart == 0)
					bandtable[i].uidstart = bandtable[i].uidbandno+j;

				bandtable[i].uidcnt++;
			}

			if (!bandtable[i].uidentries[j].name && bandtable[i].uidcnt)
				break;
		}
	}
}

char*	ToUpper(char*	crapstring)
{
	char*	tmpptr = crapstring;

	while (*tmpptr)
	{
		*tmpptr = toupper(*tmpptr);
		tmpptr++;
	}

	return crapstring;
}

void	WriteOutput(UIDBands* bandtable,int bandcnt,char* outfile)
{
	FILE* fp = fopen(outfile,"wt");
	if (fp)
	{
		int		uidcnt = 0;
		int		uiddummy = 0;
		bool	printedany;
		char	uidbandname[256];
		char	vox[256];
		char	vfile[256];
		int		start,end;
		int		noDone,missing,missingtot;
		FILE*	errfp = fopen("uiderrs.txt","wt");
		
		missingtot = 0;

		for (int i=0; i < bandcnt; i++)
		{
			sscanf(bandtable[i].bandname,"%s %s %s",vox,vfile,uidbandname);
			fprintf(fp,"TableScale:\t%s\t%d\t1\n",ToUpper(uidbandname),bandtable[i].uidstart);

			start = -1;
			end = -1;

			noDone = 0;
			missing=0;

			fprintf(fp,"%s\t%s\t%s\n",ToUpper(vox),ToUpper(vfile),ToUpper(uidbandname));
			for (int j=0; j<256; j++)
			{
				if (bandtable[i].uidentries[j].text)
				{
					fprintf(fp,"uid%x.wav\t%s\t\"%s\"\n",bandtable[i].uidbandno+j+1,
						ToUpper(bandtable[i].uidentries[j].name),
						bandtable[i].uidentries[j].text	);

					if (start == -1)
						start = j;

					noDone++;
				}
				else
				{
					if (	(start > -1)
						&&	bandtable[i].uidentries[j].name	)
					{
						if (noDone < bandtable[i].uidcnt)
						{
							fprintf(errfp,"%s\n",bandtable[i].uidentries[j].name);
							missing++;

							fprintf(fp,"uid%x.wav\t%s\t\"\"\n",bandtable[i].uidbandno+j+1,
								ToUpper(bandtable[i].uidentries[j].name));
						}
						else
						{
							end = j-1;
							break;
						}
					}
				}

				if (!bandtable[i].uidentries[j].name && (start > -1))
				{
					end = j-1;
					break;
				}
			}

			missingtot += missing;
			if (missing)
				fprintf(errfp,".... in %s\n\n",uidbandname);

			fprintf(fp,"\n");
			if (bandtable[i].uidstart)
				fprintf(fp,"Alias:\t%s = %s - %s\n\n",ToUpper(uidbandname),ToUpper(bandtable[i].uidentries[start].name),ToUpper(bandtable[i].uidentries[end].name));
		}

		fclose(errfp);
		fclose(fp);

		if (missingtot)
			fprintf(stdout,"\nThere were %d cases of missing text!\n\n",missingtot);
	}
	else
		fprintf(stdout,"ERROR:   Cannot open %s for output!\n\n",outfile);
}

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		UIDBands*	bandtable;
		MyString	bandnames[32];
		int			nobands;

		nobands = GetBandNames(bandnames,argv[1]);
		if (nobands)
		{
			bandtable = new UIDBands[nobands];
			if (bandtable)
			{
				PullBandInfo(bandnames,nobands,bandtable);
				WriteOutput(bandtable,nobands,argv[2]);
		
				delete []bandtable;
			}
		}
	}
	return 0;
}
