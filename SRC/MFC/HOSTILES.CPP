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

// RowanDialog: // Hostiles.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "Hostiles.h"
#include "uiicons.h"
#include	"mymath.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// HostilesList dialog


RDialog*	HostilesList::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_MAX),
			DialBox(FIL_D_HOSTILELIST,new HostilesList())
			);
}


HostilesList::HostilesList(CWnd* pParent /*=NULL*/)
	: RowanDialog(HostilesList::IDD, pParent)
{
	//{{AFX_DATA_INIT(HostilesList)
	//}}AFX_DATA_INIT
}


void HostilesList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HostilesList)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RBUTTONAUTHORISE, m_IDC_RBUTTONAUTHORISE);
	DDX_Control(pDX, IDC_RBUTTONASSIGNPATROL, m_IDC_RBUTTONASSIGNPATROL);
	DDX_Control(pDX, IDC_RBUTTONINTELL, m_IDC_RBUTTONINTELL);
	DDX_Control(pDX, IDC_RBUTTONMISSIONFOLDER, m_IDC_RBUTTONMISSIONFOLDER);
	DDX_Control(pDX, IDC_ATTARGET, m_IDC_ATTARGET);
	DDX_Control(pDX, IDC_FORMING, m_IDC_FORMING);
	DDX_Control(pDX, IDC_INCOMING, m_IDC_INCOMING);
	DDX_Control(pDX, IDC_RAID_ENGAGED, m_IDC_RAID_ENGAGED);
	DDX_Control(pDX, IDC_ENGAGED, m_IDC_ENGAGED);
	DDX_Control(pDX, IDC_NORESPONSE, m_IDC_NORESPONSE);
	DDX_Control(pDX, IDC_OUTGOING, m_IDC_OUTGOING);
	DDX_Control(pDX, IDC_RESPONSES, m_IDC_RESPONSES);
	//}}AFX_DATA_MAP
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->AddString("",0);
	rlistbox->AddColumn(32);										  //RDH 02/06/99
	rlistbox->AddColumn(20);										  //RDH 02/06/99
	rlistbox->AddColumn(2);
}


BEGIN_MESSAGE_MAP(HostilesList, CDialog)
	//{{AFX_MSG_MAP(HostilesList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HostilesList message handlers
bool NodeData::Response(int pack, int firstsq)
{
 	bool	response = false;
	if (pack != -1)
	{
		Profile& pk = Todays_Packages.pack[pack];
		int rafpack = 0;

		
		UniqueID checkid=pk[firstsq].instance;
		if (checkid==UID_NULL)
		 	checkid=UniqueID(UID_BIT14+((pack)<<5));

		while	(		(rafpack < Profile::MAX_PACKS)
					&&	(!response)
				)
		{
			Profile* rafpk = &Todays_Packages.pack[rafpack];
			if  (	(Todays_Packages.pack[rafpack].packagestatus!=Profile::PS_SPARE)
				&&	(	(rafpk->packagetarget[0] == checkid)
					||	(rafpk->packagetarget[1] == checkid)
				)	)
				response = true;
			rafpack++;
		}
	}
	return (response);

}
void	HostilesList::FindPackages()
{
	currpacklist = 0;
	int pack=0;

	for (int i = 0; i < MAX_PACKLIST;i++)
		packlist[i].pack = 65535;

	while (pack < Profile::MAX_PACKS)
	{

	 	Profile& pk = Todays_Packages.pack[pack];
		if  (		(pk.attackmethod >= Profile::AM_LWPACKS)
			)
		{


			if	(			(Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)	  )

			{
				int i=0;
				UWord oldraidline = 0;
				UWord raidline;
				int targetnum = 0;
				UniqueID detectedflight=UID_NULL;
				int firstsq;
				if	(
						(	(!MMC.hostilefilters[HL_TARGETAREA])	&&	Todays_Packages.pack[pack].packagestatus  >Profile::PS_INCOMING && Todays_Packages.pack[pack].packagestatus  <Profile::PS_OUTGOING)
					||	(	(!MMC.hostilefilters[HL_FORMING])	&&	Todays_Packages.pack[pack].packagestatus  <=Profile::PS_FORMING)
					||	(	(!MMC.hostilefilters[HL_INCOMING])	&&	Todays_Packages.pack[pack].packagestatus  ==Profile::PS_INCOMING)
					||	(	(!MMC.hostilefilters[HL_OUTGOING])	&&	Todays_Packages.pack[pack].packagestatus  >=Profile::PS_OUTGOING)
					)

					while (i<pk.squadlist)
					{
						int strike=0,detachedescort =0, attachedescort =0;
						int striketo=0,detachedescortto =0, attachedescortto =0;
						int strikegruppe = -1, detachedgruppe = -1, attachedgruppe = -1;
						int totalac;
						int escortgruppe;

						while (i < pk.squadlist && pk.GetRaidIndFromSquadEntry(i)==oldraidline)
						{
							targetnum = 0;
							if (pk[i].playercansee)
							{
								detectedflight=pk[i].instance;
								if (pk[i].method == pk.attackmethod)
								{
									targetnum = pk[i].targetindex;
									strike += pk[i].numacleft;
									striketo = pk[i].takeofftime;
									strikegruppe = pk[i].squadnum;
								}
								if (pk[i].method >= Profile::AM_ATTACHED)
								{
									attachedescort += pk[i].numacleft;
									attachedescortto = pk[i].takeofftime;
									attachedgruppe  = pk[i].squadnum;
								}
								else if (pk[i].method >= Profile::AM_DETACHED)
								{
									detachedescort += pk[i].numacleft;
									detachedescortto = pk[i].takeofftime;
									detachedgruppe = pk[i].squadnum;
								}
							}
							i++;

						}
						totalac = strike + attachedescort +	detachedescort;
						escortgruppe = -1;
						if (attachedgruppe >=0)
							escortgruppe = attachedgruppe;
						else if (detachedgruppe >=0)
							escortgruppe = detachedgruppe;
						if (strike == 0)
						{
							strike =  attachedescort +	detachedescort;
							strikegruppe = escortgruppe;
							escortgruppe = -1;
						}
						firstsq = pk.raidnumentries[oldraidline].squadliststart;
						Profile::PackageStatus	responsestatus=Todays_Packages.FindBestResponseStatus(pack,firstsq);
		  				if (		(pk.raidnumentries[oldraidline].detector)
								&&	(strike)
								&&	(
										(	(!MMC.hostilefilters[HL_NORESPONSE])	&&	responsestatus==Profile::PS_SPARE)
									||	(	(!MMC.hostilefilters[HL_RESPONSES])		&&	responsestatus==Profile::PS_INCOMING)
									||	(	(!MMC.hostilefilters[HL_ENEMYSIGHTED])	&&	responsestatus==Profile::PS_ENEMYSIGHTED)
									)
							)
						{
							UniqueID trg=UID_NULL;
							if (Todays_Packages.pack[pack].packagestatus>Profile::PS_FORMING)
								if (Todays_Packages.pack[pack].doglegloc== UniqueID(Todays_Packages.pack[pack].packagetarget[targetnum]))
									trg=Todays_Packages.pack[pack].doglegloc;	//ON A STRAIGHT COURSE
								else
								{	//find out if current waypoint is past dogleg waypoint
									info_airgrpPtr ac=Persons2::ConvertPtrUID(detectedflight);

									UniqueID wpu=ac->wpref;
									while (wpu)
									{
										info_waypointPtr wpp=Persons2::ConvertPtrUID(wpu);
										breakif (wpp->uid.Evaluate()==-SGR_WPP_DogLeg);
										wpu=wpp->nextwp;
									}
									if (wpu)
										trg=Todays_Packages.pack[pack].doglegloc;
									else
										trg=Todays_Packages.pack[pack].packagetarget[targetnum];


								}
							FillPackList(pack, oldraidline, trg, pk.attackmethod, totalac, striketo, strikegruppe, escortgruppe);
						}


						if (i!=pk.squadlist)
							raidline = pk.GetRaidIndFromSquadEntry(i);
	//DeadCode JIM 8Aug00 					else
	//DeadCode JIM 8Aug00 						raidline=0;
						oldraidline=raidline;

					}
			}
		}


		pack++;
	}


}


void HostilesList::FindHiLight()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	currpack = -1;
	int p=0;
	while  (		(packlist[p].pack != 65535)
				&&	!(	(packlist[p].pack == Todays_Packages.hipack)
						&&	CorrectSquad(p)
					)
			)
	{
		p++;
	}
	if (		(packlist[p].pack == Todays_Packages.hipack)
			&&	CorrectSquad(p)
		)
	{
			currpack = p;
			rlistbox->SetHilightRow(currpack+1);
	}
}
bool HostilesList::CorrectSquad(int pack)
{
	Profile& pk = Todays_Packages.pack[packlist[pack].pack];
	int i = pk.raidnumentries[packlist[pack].raidline].squadliststart;
	int lastsq;
	lastsq = pk.RaidNumEntriesMaxSq(packlist[pack].raidline);
	bool correctsq = false;
	while (i <= lastsq)
	{
		if (i == Todays_Packages.hisquad)
		{
			correctsq = true;
			break;
		}

		i++;
	}
	return(correctsq);

}
void HostilesList::FillPackList(UWord	pack, UWord raidline, UniqueID	target, UByte method, UWord numofac, int takeofftime, int strikegruppe, int  escortgruppe)
{
	enum {WRAPTHROW=10};
	if (currpacklist == MAX_PACKLIST)
	{
		for (int i=0;i<MAX_PACKLIST-WRAPTHROW;i++)
			packlist[i]=packlist[i+WRAPTHROW];
		currpacklist-=WRAPTHROW;
	}
//DeadCode JIM 2Oct00 	if (currpacklist < MAX_PACKLIST)
//DeadCode JIM 2Oct00 	{
		packlist[currpacklist].pack = pack;
		packlist[currpacklist].raidline = raidline;
		packlist[currpacklist].target = target;
		packlist[currpacklist].method = method;
//DEADCODE RDH 06/04/00 		packlist[currpacklist].takeofftime = takeofftime;
		packlist[currpacklist].strikegruppe = strikegruppe;
		packlist[currpacklist].escortgruppe = escortgruppe;
		packlist[currpacklist++].numofac = numofac;
//DeadCode JIM 2Oct00 	}
}


FileNum HostilesList::GetIconFileNum(UniqueID uid)
{
	IconsUI	filenum=ICON_NO_ICON;
	if (uid!=UID_NULL)
	{
		ItemBasePtr p = Persons2::ConvertPtrUID(uid);
		if (p)
		{
			int uidband;
			if (((info_base*)p)->SGT != UID_Null)
				uidband=Persons2::getbandfromUID(((info_base*)p)->SGT);	
			else	
				uidband=Persons2::getbandfromUID(uid);

			switch (uidband)
			{
				case		BritAAASiteBAND:
				case		BritAAALargeBAND:
				{
					filenum = ICON_FLAK;
					break;
				}
				case		GermAAASiteBAND:
				{
					filenum = ICON_FLAK;
					break;
				}
				case		CivilianBAND:
				{
					filenum = ICON_TOWN;
					break;
				}
				case		BritBridgeBAND:
				{
					filenum = ICON_TICK;
					break;
				}
				case		BritHistoricBAND:
				{
					filenum = ICON_TICK;
					break;
				}
				case		GermMobileBAND:
				{
					filenum = ICON_TICK;
					break;
				}
				case		BritMobileBAND:
				{
					filenum = ICON_TICK;
					break;
				}
				case	  	NeutMiscBAND:
				{
					filenum = ICON_TICK;
					break;
				}
				case		BritBoatBAND:
				{
					filenum = ICON_CONVOY;
					break;
				}
				case		GermBoatBAND:
				{
					filenum = ICON_CONVOY;
					break;
				}
				case		PowerStationBAND:
				{
					filenum = ICON_POWER;
					break;
				}
				case		OilRefineryBAND:
				{
					filenum = ICON_OIL;
					break;
				}
				case		IndustryBAND:
				{
					filenum = ICON_TUNNEL;
					break;
				}
				case		AircraftFactoryBAND:
				{
					filenum = ICON_FIGHTER;
					break;
				}
				case		DocksBAND:
				{
					filenum = ICON_CIV;
					break;
				}
				case		PortBAND:
				{
					filenum = ICON_CIV;
					break;
				}
				case		NavalBaseBAND:
				{
					filenum = ICON_NAVAL;
					break;
				}
				case		CityBAND:
				{
					filenum = ICON_CITY;
					break;
				}
				case		TownBAND:
				{
					filenum = ICON_TOWN;
					break;
				}
				case		VillageBAND:
				{
					filenum = ICON_VILLAGE;
					break;
				}
				case		RAF_FighterAFBAND:
				{
					filenum = ICON_AF_FIGHTER;
					break;
				}
				case		RAF_BomberAFBAND:
				{
					filenum = ICON_AF_BOMBER;
					break;
				}
				case		RAF_CoastalAFBAND:
				{
					filenum = ICON_AF_COASTAL;
					break;
				}
				case		CLRadarBAND:
				{
					filenum = ICON_CHL;
					break;
				}
				case		CHRadarBAND:
				{
					filenum = ICON_CH;
					break;
				}
				case		LUF_FighterLF2BAND:
				{
					filenum = ICON_AF_FIGHTER;
					break;
				}
				case		LUF_FighterLF3BAND:
				{
					filenum = ICON_AF_FIGHTER;
					break;
				}
				case		LUF_BomberLF2BAND:
				{
					filenum = ICON_AF_BOMBER;
					break;
				}
				case		LUF_BomberLF3BAND:
				{
					filenum = ICON_AF_BOMBER;
					break;
				}
				case		SagBAND:	
				{
					filenum = ICON_LW_FIGHTER;
					break;
				}

				default:
				{
	#ifndef NDEBUG
					filenum = ICON_TICK;
	#endif
					break;
				}
			}
			if	(filenum != ICON_NO_ICON)								//DAW 20Jun99 //RDH 05/01/00
			{
				TargetGroup* g=Node_Data[uid];
				if (g)
					if (g->PlayerStatus()!=Target::TS_FLAG_UNKNOWN)
						if (g->PlayerStatus()>Target::TS_LIGHTDAMAGE)
							if (g->PlayerStatus()>Target::TS_NEARLYDESTROYED)
								filenum = IconsUI(filenum+ICON_SELECT_2);	
							else
								filenum = IconsUI(filenum+ICON_SELECT_1);	
			}
		}
	}
	return((FileNum)filenum);
}





void	HostilesList::RefreshList()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);

	rlistbox->Clear();
//DeadCode RDH 27Oct00 	rlistbox->AddColumn(30); //46
//DeadCode RDH 27Oct00 	rlistbox->AddColumn(28);										  //RDH 02/06/99
//DeadCode RDH 27Oct00 	rlistbox->AddColumn(42);	//50										  //RDH 02/06/99
//DeadCode RDH 27Oct00 	rlistbox->AddColumn(48);		//60										  //RDH 02/06/99
//DeadCode RDH 27Oct00 	rlistbox->AddColumn(46);										  //RDH 02/06/99
//DeadCode RDH 27Oct00 	rlistbox->AddColumn(80);
//DeadCode RDH 27Oct00 	rlistbox->AddIconColumn(28);										  //RDH 02/06/99
//DeadCode RDH 27Oct00 	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
//DeadCode RDH 27Oct00 	rlistbox->AddColumn(24);										  //RDH 02/06/99
//DeadCode JIM 11Nov00 //DeadCode RDH 31Oct00 	rlistbox->AddColumn(32);										  //RDH 02/06/99
//DeadCode JIM 11Nov00 //DeadCode RDH 31Oct00 	rlistbox->AddColumn(20);										  //RDH 02/06/99
//DeadCode JIM 11Nov00 //DeadCode RDH 31Oct00 	rlistbox->AddColumn(2);
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(50);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(RAID),0);
	rlistbox->AddString(RESSTRING(HL_SIZE),1);
	rlistbox->AddString(RESSTRING(TYPE),2);
	rlistbox->AddString(RESSTRING(HL_ESCORT),3);
	rlistbox->AddString(RESSTRING(ALT),4);
	rlistbox->AddString(RESSTRING(HL_STATUS),5);
	rlistbox->AddString("",6);
	rlistbox->AddString(RESSTRING(HL_TARGET),7);

	rlistbox->AddString(RESSTRING(OUT),8);
	rlistbox->AddString(RESSTRING(CMBT),9);
	rlistbox->AddString(RESSTRING(IN),10);

//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_STATUS),6);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_RESPONSE),6);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_INTERCEPT),8);
	rlistbox->AddString(RESSTRING(HL_TALLY),11);



	int p=0;
	int t;
	while (packlist[p].pack != 65535)
	{
		Profile& pk = Todays_Packages.pack[packlist[p].pack];
		if (packlist[p].method < Profile::AM_DETACHED)
		{
//DEADCODE RDH 12/04/00 			rlistbox->AddString(CSprintf("R%03i", pk.raidnumentries[packlist[p].raidline].raidnum),0);


			char* raidletter = Todays_Packages.RaidFormatString(packlist[p].pack,packlist[p].raidline);
			rlistbox->AddString(CSprintf(raidletter, pk.raidnumentries[packlist[p].raidline].raidnum),0);




//DEADCODE RDH 12/04/00  			rlistbox->AddString(CSprintf("R%03i", packlist[p].raidline),0);
			rlistbox->AddString(CSprintf("%i", packlist[p].numofac),1);

			Squadron* sq  = Node_Data[(SquadNum)packlist[p].strikegruppe];
			rlistbox->AddString(RESLIST(SPIT_A, sq->AcType()),2);
			if (packlist[p].escortgruppe >= 0)
			{
				sq  = Node_Data[(SquadNum)packlist[p].escortgruppe];
				rlistbox->AddString(RESLIST(SPIT_A, sq->AcType()),3);
			}else
				rlistbox->AddString(RESSTRING(NONE_NOAIRCRAFT),3);

			int firstsq = pk.raidnumentries[packlist[p].raidline].squadliststart;
			ItemBasePtr item = Persons2::ConvertPtrUID(pk[firstsq].instance);
			if (item)
			{
 				int alt = item->World.Y;
				if (alt < 0 )
					alt = 0;
				alt = alt*10/Save_Data.alt.mediummm;
				alt = 100*((alt + 50)/100);
				rlistbox->AddString(CSprintf("%i%s",alt,LoadResString(Save_Data.alt.mediumabbr)),4);
			}else
				rlistbox->AddString(" ",4);
//DeadCode RJS 12Nov00 			info_airgrpPtr item = Persons2::ConvertPtrUID(pk[firstsq].instance);
//DeadCode RJS 12Nov00 			if (item)
//DeadCode RJS 12Nov00 			{
//DeadCode RJS 12Nov00  				int alt = item->knownposition.Y;
//DeadCode RJS 12Nov00 				if (alt < 0 )
//DeadCode RJS 12Nov00 					alt = 0;
//DeadCode RJS 12Nov00 				alt = alt*10/Save_Data.alt.mediummm;
//DeadCode RJS 12Nov00 				alt = 100*((alt + 50)/100);
//DeadCode RJS 12Nov00 				rlistbox->AddString(CSprintf("%i%s",alt,LoadResString(Save_Data.alt.mediumabbr)),4);
//DeadCode RJS 12Nov00 			}else
//DeadCode RJS 12Nov00 				rlistbox->AddString(" ",4);


			
			rlistbox->AddString(RESLIST(PS_SPARE,pk.packagestatus),5);
		 	TargetNoDetail* trg = NULL;
			if (packlist[p].target)
			{
				trg=Node_Data[packlist[p].target];
				rlistbox->AddString(GetTargName(packlist[p].target),7);
			}
			else
				rlistbox->AddString("",7);

			if (trg)
			{
				int j = trg->truestatus;
				if		(j >= Target::TS_NEARLYDESTROYED)		j = 3;
				elseif	(j>Target::TS_BADDAMAGE)				j=2;
				elseif	(j>Target::TS_LIGHTDAMAGE)				j=1;
				else											j=0;
//DeadCode JON 4Sep00 				if (j >= 100)
//DeadCode JON 4Sep00 					j = 3;
//DeadCode JON 4Sep00 				else
//DeadCode JON 4Sep00 				{
//DeadCode JON 4Sep00 					j = j/4;
//DeadCode JON 4Sep00 					if (j >= 3)
//DeadCode JON 4Sep00 						j =2;
//DeadCode JON 4Sep00 				}
				FileNum filenum = GetIconFileNum(packlist[p].target);
				rlistbox->AddIcon(filenum,6);

//DEADCODE RDH 21/01/00 				rlistbox->AddIcon((FileNum)ICON_AF_FIGHTER,5);
//DEADCODE RDH 20/01/00 				rlistbox->AddString(RESLIST(UNDAMAGED, j),5);
			}
			else
				rlistbox->AddIcon(FIL_NULL,6);

			int i = firstsq;
			int lastsq;
			lastsq = pk.RaidNumEntriesMaxSq(packlist[p].raidline);


			int acnum = 0, acorg = 0, acleft = 0;
			while (i <= lastsq)
			{
				acorg += pk[i].numacoriginal;
				acleft += pk[i].numacleft;
				i++;
			}
			int losses = acorg - acleft;

			int kills;
			int	acincoming = 0;
			int	acengaged = 0;
			int acoutgoing = 0;

			FindKillsandAcNumbers(packlist[p].pack, packlist[p].raidline, acleft, kills, acincoming, acengaged,acoutgoing);

			rlistbox->AddString(CSprintf("%i", acincoming),8);
			rlistbox->AddString(CSprintf("%i", acengaged),9);
			rlistbox->AddString(CSprintf("%i", acoutgoing),10);

			//losses are RAF gains, it is an RAF dialog so lead with RAF gains
			rlistbox->AddString(CSprintf("+%i -%i", losses, kills),11);

		}
		p++;
	}
}

Profile::PackageStatus	PackageList::FindBestResponseStatus(int tpack,int tsqline)
{
	Profile::PackageStatus	rv=Profile::PS_SPARE;
	UniqueID tinst=pack[tpack][tsqline].instance;
	for (int p=0;p < Profile::MAX_PACKS;p++)
		if (pack[p].packagestatus!=Profile::PS_SPARE)
			if (pack[p].packagetarget[0]==tinst || pack[p].packagetarget[1]==tinst)
				if (pack[p].packagestatus==Profile::PS_ENEMYSIGHTED)
					return Profile::PS_ENEMYSIGHTED;
				else
					rv=Profile::PS_INCOMING;
	return rv;
}

void	HostilesList::FindKillsandAcNumbers(int pack, int raid, int& acleft, int& kills, int& acincoming, int& acengaged, int& acoutgoing)
{
	int rafpack = 0;
	int t;
	int acorg = 0;
	acleft = 0;
	acincoming = 0;
	acengaged = 0;
	acoutgoing = 0;
	Profile& pk = Todays_Packages.pack[pack];

	int i = pk.raidnumentries[raid].squadliststart;
	int lastsq;
	lastsq = pk.RaidNumEntriesMaxSq(raid);


	while (i <= lastsq)													//RDH 1Nov00
	{
		UniqueID pki_instance=pk[i].instance;
		while (rafpack < Profile::MAX_PACKS)
		{
			if (Todays_Packages.pack[rafpack].packagestatus != Profile::PS_SPARE)
			{
				Profile& rafpk = Todays_Packages.pack[rafpack];
				if (rafpk.attackmethod < Profile::AM_LWPACKS)
				{
					for (int t = 0; t < Profile::MAX_TARGETS; t++)
					{
						if  (		(rafpk.packagetarget[t] != UID_NULL)
								&&	(rafpk.packagetarget[t] == pki_instance)
							)
						{


							int j=0;

							while (j < rafpk.squadlist)
							{
								acorg += rafpk[j].numacoriginal;
								acleft += rafpk[j].numacleft;
								if (Todays_Packages.pack[rafpack].packagestatus < Profile::PS_ENEMYSIGHTED)
									acincoming += rafpk[j].numacleft;
								else if (Todays_Packages.pack[rafpack].packagestatus == Profile::PS_ENEMYSIGHTED)
									acengaged += rafpk[j].numacleft;
								else
									acoutgoing += rafpk[j].numacleft;


								j++;
							}
						}
					}

				}
			}
			rafpack++;
		}
		i++;
	}
	kills = (acorg - acleft);

}

int HostilesList::FindNearestPack(int packnum,int psmin,int psmax)
{
	int nearestpack = -1;
	int pack = packlist[packnum].pack;
	int raid = packlist[packnum].raidline;
	if (pack != 65535) //>= 0)											//RDH 22Aug00
	{
		int nearestdistance = 2000000000;
		ULong range = 0;
		int rafpack = 0;
		Profile& pk = Todays_Packages.pack[pack];

		int firstsq = pk.raidnumentries[raid].squadliststart;

		ItemBasePtr lwitem = Persons2::ConvertPtrUID(pk[firstsq].instance);
 
		while (rafpack < Profile::MAX_PACKS)
		{
			if (Todays_Packages.pack[rafpack].packagestatus>=psmin && Todays_Packages.pack[rafpack].packagestatus<=psmax)
			{
				Profile& rafpk = Todays_Packages.pack[rafpack];
				if (rafpk.attackmethod == Profile::AM_PATROL)
					{
						ItemBasePtr rafitem = Persons2::ConvertPtrUID(rafpk[0].instance);
 						if (rafitem)
						{
							UWord sbrg;
							Math_Lib.InterceptHdg(rafitem->World.X, rafitem->World.Z, 
													lwitem->World.X, lwitem->World.Z, range, sbrg);

							if (range < nearestdistance)
							{
								nearestdistance=range;					//MS 3Jul00
								nearestpack = rafpack;
							}
						}
					}
				}
			rafpack++;
		}
	}
	return (nearestpack);
}

void	HostilesList::RefreshButtons()
{
	if (currpack != -1)
	{
		CRButton*	but = GETDLGITEM(IDC_RBUTTONAUTHORISE);
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
		but = GETDLGITEM(IDC_RBUTTONASSIGNPATROL);
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
		but = GETDLGITEM(IDC_RBUTTONINTELL);
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
		but = GETDLGITEM(IDC_RBUTTONMISSIONFOLDER);
	 	Profile& pk = Todays_Packages.pack[packlist[currpack].pack];
		int firstsq = pk.raidnumentries[packlist[currpack].raidline].squadliststart;

		if (Node_Data.Response(packlist[currpack].pack, firstsq))
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetDisabled(false);
		}else
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(false);
		}
	}else
	{
		CRButton*	but = GETDLGITEM(IDC_RBUTTONAUTHORISE);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);											//RDH 30Sep00
		but = GETDLGITEM(IDC_RBUTTONASSIGNPATROL);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);											//RDH 30Sep00
		but = GETDLGITEM(IDC_RBUTTONINTELL);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);											//RDH 30Sep00
		but = GETDLGITEM(IDC_RBUTTONMISSIONFOLDER);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);											//RDH 30Sep00
	}
}
void HostilesList::RefreshData(int childnum)
{
	if (childnum == -2)
	{
		TotalRefresh();
	}
}

void HostilesList::TotalRefresh()
{
//DeadCode JIM 8Nov00 	RefreshTickBoxes();
	FindPackages();
	RefreshList();
  	FindHiLight();
	RefreshButtons();

	CRButton* b = GETDLGITEM(IDC_ATTARGET);
	b->SetPressed(!MMC.hostilefilters[HL_TARGETAREA]);

	b = GETDLGITEM(IDC_ENGAGED);
	b->SetPressed(!MMC.hostilefilters[HL_ENEMYSIGHTED]);

	b = GETDLGITEM(IDC_FORMING);
	b->SetPressed(!MMC.hostilefilters[HL_FORMING]);

	b = GETDLGITEM(IDC_INCOMING);
	b->SetPressed(!MMC.hostilefilters[HL_INCOMING]);

	b = GETDLGITEM(IDC_NORESPONSE);
	b->SetPressed(!MMC.hostilefilters[HL_NORESPONSE]);

	b = GETDLGITEM(IDC_RESPONSES);
	b->SetPressed(!MMC.hostilefilters[HL_RESPONSES]);

//DeadCode JIM 8Aug00 	b = GETDLGITEM(IDC_NOTENGAGED);
//DeadCode JIM 8Aug00 	b->SetPressed(!MMC.hostilefilters[HL_ENEMYNOTSIGHTED]);

	b = GETDLGITEM(IDC_OUTGOING);
	b->SetPressed(!MMC.hostilefilters[HL_OUTGOING]);


}

void HostilesList::RefreshTickBoxes()
{
 	CRButton* b;
	

//TEMPCODE RDH 20/01/00 	b = GETDLGITEM(IDC_PLANNED);
//TEMPCODE RDH 20/01/00 	b->SetPressed(!MMC.lwplanned);
//TEMPCODE RDH 20/01/00 
//TEMPCODE RDH 20/01/00 	b = GETDLGITEM(IDC_ACTIVE);
//TEMPCODE RDH 20/01/00 	b->SetPressed(!MMC.lwactive);
//TEMPCODE RDH 20/01/00 
//TEMPCODE RDH 20/01/00 	b = GETDLGITEM(IDC_LANDED);
//TEMPCODE RDH 20/01/00 	b->SetPressed(!MMC.lwlanded);
//TEMPCODE RDH 20/01/00 
//TEMPCODE RDH 20/01/00 	b = GETDLGITEM(IDC_STRIKE);
//TEMPCODE RDH 20/01/00 	b->SetPressed(!MMC.lwstrike);
//TEMPCODE RDH 20/01/00 
//TEMPCODE RDH 20/01/00 	b = GETDLGITEM(IDC_ESCORT);
//TEMPCODE RDH 20/01/00 	b->SetPressed(!MMC.lwattachedescort);
//TEMPCODE RDH 20/01/00 
//TEMPCODE RDH 20/01/00 	b = GETDLGITEM(IDC_SWEEP);
//TEMPCODE RDH 20/01/00 	b->SetPressed(!MMC.lwdetachedescort);
//TEMPCODE RDH 20/01/00 
//TEMPCODE RDH 20/01/00 	b = GETDLGITEM(IDC_RECONN);
//TEMPCODE RDH 20/01/00 	b->SetPressed(!MMC.lwreconn);
}


BOOL HostilesList::OnInitDialog() 
{
	CDialog::OnInitDialog();

	currpack = -1;		
	TotalRefresh();


	
//DEADCODE RDH 20/01/00 	CRListBox* rlistbox;
//DEADCODE RDH 20/01/00 	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DEADCODE RDH 20/01/00 	rlistbox->Clear();
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(50);
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(30);										  //RDH 02/06/99
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(60);										  //RDH 02/06/99
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(60);										  //RDH 02/06/99
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(60);
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(50);										  //RDH 02/06/99
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(40);										  //RDH 02/06/99
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(60);
//DEADCODE RDH 20/01/00 	rlistbox->AddColumn(50);										  //RDH 02/06/99
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HOSTILE),0);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_SIZE),1);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_BOMBER),2);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_ESCORT),3);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_STATUS),4);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_TARGET),5);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_STATUS),6);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_RESPONSE),7);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_INTERCEPT),8);
//DEADCODE RDH 20/01/00 	rlistbox->AddString(RESSTRING(HL_TALLY),9);
//DEADCODE RDH 20/01/00 
//DEADCODE RDH 20/01/00 	
//DEADCODE RDH 20/01/00 	rlistbox->AddString("H100",0);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("200",1);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("Heinkels",2);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("109s",3);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("Incoming",4);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("Biggin Hill",5);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("OK",6);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("None",7);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("None",8);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("N/A",9);
//DEADCODE RDH 20/01/00 
//DEADCODE RDH 20/01/00 	rlistbox->AddString("H101",0);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("30",1);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("Dorniers",2);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("109s",3);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("Out Going",4);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("Kenley",5);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("Damged",6);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("36",7);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("24/36",8);
//DEADCODE RDH 20/01/00 	rlistbox->AddString("3/2",9);
//DEADCODE RDH 20/01/00 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(HostilesList, CDialog)
    //{{AFX_EVENTSINK_MAP(HostilesList)
	ON_EVENT(HostilesList, IDC_RBUTTONASSIGNPATROL, 1 /* Clicked */, OnClickedRbuttonassignpatrol, VTS_NONE)
	ON_EVENT(HostilesList, IDC_RBUTTONAUTHORISE, 1 /* Clicked */, OnClickedRbuttonauthorise, VTS_NONE)
	ON_EVENT(HostilesList, IDC_RBUTTONINTELL, 1 /* Clicked */, OnClickedRbuttonintell, VTS_NONE)
	ON_EVENT(HostilesList, IDC_RBUTTONMISSIONFOLDER, 1 /* Clicked */, OnClickedRbuttonmissionfolder, VTS_NONE)
	ON_EVENT(HostilesList, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(HostilesList, IDC_ATTARGET, 1 /* Clicked */, OnClickedAttarget, VTS_NONE)
	ON_EVENT(HostilesList, IDC_ENGAGED, 1 /* Clicked */, OnClickedEngaged, VTS_NONE)
	ON_EVENT(HostilesList, IDC_FORMING, 1 /* Clicked */, OnClickedForming, VTS_NONE)
	ON_EVENT(HostilesList, IDC_INCOMING, 1 /* Clicked */, OnClickedIncoming, VTS_NONE)
	ON_EVENT(HostilesList, IDC_NORESPONSE, 1 /* Clicked */, OnClickedNoresponse, VTS_NONE)
//DeadCode JIM 8Aug00 	ON_EVENT(HostilesList, IDC_NOTENGAGED, 1 /* Clicked */, OnClickedNotengaged, VTS_NONE)
	ON_EVENT(HostilesList, IDC_OUTGOING, 1 /* Clicked */, OnClickedOutgoing, VTS_NONE)
	ON_EVENT(HostilesList, IDC_RESPONSES, 1 /* Clicked */, OnClickedResponses, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void HostilesList::OnClickedRbuttonassignpatrol() 
{
	Profile& lwpk = Todays_Packages.pack[packlist[currpack].pack];
	int nearestpack = FindNearestPack( currpack ,Profile::PS_ACTIVE_MIN,Profile::PS_ACTIVE_MAX);
	if (nearestpack < 0)
		RDialog::RMessageBox(IDS_NOPATROLS, IDS_NOPATROLSAVAIL,IDS_CONTINUE);
	else
	{

		Profile& pk = Todays_Packages.pack[nearestpack];
		int squadnum = lwpk.raidnumentries[packlist[currpack].raidline].squadliststart;
		pk.ReassignTo((UniqueID)lwpk[squadnum].instance, true);
		TotalRefresh();

 	}
		
}

void HostilesList::OnClickedRbuttonauthorise() 
{
#ifndef	BOB_DEMO_VER

	int pack = packlist[currpack].pack;
	if (pack  != 65535)//>=0)											//RDH 22Aug00
	{
		Profile& pk = Todays_Packages.pack[pack];
		int squadnum = pk.RaidNumEntriesMinSq(packlist[currpack].raidline);
		int	squadmax = pk.RaidNumEntriesMaxSq(packlist[currpack].raidline);
		for (int sqt=squadnum;sqt<=squadmax;sqt++)
			if (pk[sqt].playercansee)
			{
				squadnum=sqt;
				break;
			}
		Directives::RAF::MissTypes 	misstype = RAFDirectivesResults::RAFInterceptType(pack, squadnum);


		int	packnum=Todays_Packages_NewPackage(pk[squadnum].instance,
			MMC.directives.raf.userprofiles[misstype]);

		if (packnum < 0)
			RDialog::RMessageBox(IDS_WARNING, IDS_NOAIRCRAFTAVAIL,NULL,NULL,IDS_CONTINUE);
		else
		{
			Todays_Packages[packnum].CalcRoutePositionsAndTime();
			RDialog::m_pView->SetHiLightInfo(packnum, 0,UID_Null);
			MainToolBar().OnClickedMissionfolder();

			Todays_Packages.InvalidateRoute(&Todays_Packages[packnum],true,true);
		}
	}
//DEADCODE RDH 05/04/00 	MainToolBar().OnClickedHostileslist();
#endif
}

void HostilesList::OnClickedRbuttonintell() 
{
#ifndef	BOB_DEMO_VER

	int pack = packlist[currpack].pack;
//DeadCode JIM 20Oct00 	int raid = packlist[currpack].raidline;
	if (pack  != 65535 && packlist[currpack].target)//>= 0)											//RDH 22Aug00
	{
		MainToolBar().OpenDossier(packlist[currpack].target);
	}
#endif	
}

void HostilesList::OnClickedRbuttonmissionfolder() 
{
#ifndef	BOB_DEMO_VER

	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	int rafpack = 0;
	bool packfound  = false;
	while (	(!packfound) &&  (rafpack < Profile::MAX_PACKS))
	{
		Profile& rafpk = Todays_Packages.pack[rafpack];
//##this check needs to be improved. We only count those squad with target == squads in lw pack
				if  (	(Todays_Packages.pack[rafpack].packagestatus!=Profile::PS_SPARE)
					&&	(	rafpk.packagetarget[0].currentid == pk[0].instance
						||	rafpk.packagetarget[1].currentid == pk[0].instance
					)	)
				{
					packfound = true;
				}else
					rafpack++;
	}
	if (packfound)
	{
		RDialog::m_pView->SetHiLightInfo(rafpack, 0,UID_Null);
		MainToolBar().OnClickedMissionfolder();
	}
#endif	
}

void HostilesList::OnSelectRlistboxctrl1(long row, long column) 
{
	if (row > 0)
	{
		currpack = row - 1;
		RefreshButtons();
		RDialog::m_pView->SetHiLightInfo(packlist[currpack].pack, 0,UID_Null);
		m_pView->m_mapdlg.Invalidate();
	}
	
}

void HostilesList::OnClickedAttarget() 
{
	if	(MMC.hostilefilters[HL_TARGETAREA])
	   MMC.hostilefilters %= HL_TARGETAREA;
	else
	   MMC.hostilefilters |= HL_TARGETAREA;
	TotalRefresh();
	
}

void HostilesList::OnClickedEngaged() 
{
	if	(MMC.hostilefilters[HL_ENEMYSIGHTED])
	   MMC.hostilefilters %= HL_ENEMYSIGHTED;
	else
	   MMC.hostilefilters |= HL_ENEMYSIGHTED;
	TotalRefresh();
	
}

void HostilesList::OnClickedForming() 
{
	if	(MMC.hostilefilters[HL_FORMING])
	   MMC.hostilefilters %= HL_FORMING;
	else
	   MMC.hostilefilters |= HL_FORMING;
	TotalRefresh();
	
}

void HostilesList::OnClickedIncoming() 
{
	if	(MMC.hostilefilters[HL_INCOMING])
	   MMC.hostilefilters %= HL_INCOMING;
	else
	   MMC.hostilefilters |= HL_INCOMING;
	TotalRefresh();
	
}

void HostilesList::OnClickedNoresponse() 
{
	if	(MMC.hostilefilters[HL_NORESPONSE])
	   MMC.hostilefilters %= HL_NORESPONSE;
	else
	   MMC.hostilefilters |= HL_NORESPONSE;
	TotalRefresh();
	
}

//DeadCode JIM 8Aug00 void HostilesList::OnClickedNotengaged() 
//DeadCode JIM 8Aug00 {
//DeadCode JIM 8Aug00 	if	(MMC.hostilefilters[HL_ENEMYNOTSIGHTED])
//DeadCode JIM 8Aug00 	   MMC.hostilefilters %= HL_ENEMYNOTSIGHTED;
//DeadCode JIM 8Aug00 	else
//DeadCode JIM 8Aug00 	   MMC.hostilefilters |= HL_ENEMYNOTSIGHTED;
//DeadCode JIM 8Aug00 	TotalRefresh();
//DeadCode JIM 8Aug00 	
//DeadCode JIM 8Aug00 }

void HostilesList::OnClickedOutgoing() 
{
	if	(MMC.hostilefilters[HL_OUTGOING])
	   MMC.hostilefilters %= HL_OUTGOING;
	else
	   MMC.hostilefilters |= HL_OUTGOING;
	TotalRefresh();
	
}


void HostilesList::OnClickedResponses() 
{
	if	(MMC.hostilefilters[HL_RESPONSES])
	   MMC.hostilefilters %= HL_RESPONSES;
	else
	   MMC.hostilefilters |= HL_RESPONSES;
	TotalRefresh();
	
}
