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

//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	// Battle Node Generation
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	// MiG Alley stuff!
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	#include	<stdio.h>
//deadcode JIM 19/06/01	#include	<string.h>
//deadcode JIM 19/06/01	#define	F_GRAFIX
//deadcode JIM 19/06/01	#define	F_COMMON
//deadcode JIM 19/06/01	#define F_SOUNDS
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#include	"dosdefs.h"
//deadcode JIM 19/06/01	#include	"files.g"
//deadcode JIM 19/06/01	#include	"..\mfc\resource.h"
//deadcode JIM 19/06/01	#include "uniqueid.h"
//deadcode JIM 19/06/01	#include "flyinit.h"
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//the following include files are to silence "node.h"
//deadcode JIM 19/06/01		   
//deadcode JIM 19/06/01	//With mark's changes, all these consts can be commented out!
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	/*
//deadcode JIM 19/06/01	The following phrases are available for use in battlefields:
//deadcode JIM 19/06/01		IDS_PHRASE_RIVERBANK	" river bank"
//deadcode JIM 19/06/01		IDS_PHRASE_RUINEDBUILDINGS	" ruined buildings"
//deadcode JIM 19/06/01		IDS_PHRASE_PADDYFIELDS	" paddyfields"
//deadcode JIM 19/06/01		IDS_PHRASE_WOODEDAREA	" wooded area"
//deadcode JIM 19/06/01		IDS_PHRASE_RIDGELINE	" ridge line"
//deadcode JIM 19/06/01		IDS_PHRASE_HILLTOWN	" hill, overlooking town"
//deadcode JIM 19/06/01		IDS_PHRASE_HILLROAD	" hill, commanding the road"
//deadcode JIM 19/06/01		IDS_PHRASE_HILLSIDE	" hillside"
//deadcode JIM 19/06/01		IDS_PHRASE_HILLTOP	" hilltop"
//deadcode JIM 19/06/01		IDS_PHRASE_POSOTOWN	" outskirts"
//deadcode JIM 19/06/01		IDS_PHRASE_POSSTOWN	" suburbs"
//deadcode JIM 19/06/01		IDS_PHRASE_POSCIVILIAN	" civilian buildings"
//deadcode JIM 19/06/01		IDS_PHRASE_POSMAINSTREET	" positions covering street"
//deadcode JIM 19/06/01		IDS_PHRASE_LINEMAINROAD	" line over main road"
//deadcode JIM 19/06/01		IDS_PHRASE_ENTRYTOTOWN	" town entrance"
//deadcode JIM 19/06/01		IDS_PHRASE_ENTRYGULLEY	" gully entrance"
//deadcode JIM 19/06/01		IDS_PHRASE_RIVERFORD	" river ford"
//deadcode JIM 19/06/01		IDS_PHRASE_BRIDGECROSSING	" bridge crossing"
//deadcode JIM 19/06/01		IDS_PHRASE_FERRYPOINT	" ferry point"
//deadcode JIM 19/06/01		IDS_PHRASE_BLOCKINGPOS	" road block"
//deadcode JIM 19/06/01		IDS_PHRASE_TREELINE	" tree line"
//deadcode JIM 19/06/01		IDS_PHRASE_FORESTAREA	" forest area"
//deadcode JIM 19/06/01		IDS_PHRASE_OPENGROUND	" open ground"
//deadcode JIM 19/06/01		IDS_PHRASE_TOWNCENTRE	" town center"
//deadcode JIM 19/06/01		IDS_PHRASE_CROSSROADS	" crossroads"
//deadcode JIM 19/06/01		IDS_PHRASE_STREAM	" stream"
//deadcode JIM 19/06/01		IDS_PHRASE_SMALLVILLAGE	" small village"
//deadcode JIM 19/06/01		IDS_PHRASE_GROUPOFHUTS	" group of huts"
//deadcode JIM 19/06/01		IDS_PHRASE_VALLEYFLOOR	" valley floor"
//deadcode JIM 19/06/01		IDS_PHRASE_VALLEYRIM	" valley rim"
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		IDS_PHRASE_ONMAINHIGHWAY	" on main highway."
//deadcode JIM 19/06/01		IDS_PHRASE_ONROAD	" on road."
//deadcode JIM 19/06/01		IDS_PHRASE_CROSSOPEN	" crossing open ground."
//deadcode JIM 19/06/01		IDS_PHRASE_THROUGHPADDY	" moving through paddyfields."
//deadcode JIM 19/06/01		IDS_PHRASE_FORDINGRIVER	" fording the river."
//deadcode JIM 19/06/01		IDS_PHRASE_INPASS	" in the pass."
//deadcode JIM 19/06/01		IDS_PHRASE_HEADMAINSTREET	" heading along the main-street."
//deadcode JIM 19/06/01		IDS_PHRASE_USESIDESTREET	" using side-streets."
//deadcode JIM 19/06/01		IDS_PHRASE_THROUGHBUILDINGS	" moving through buildings."
//deadcode JIM 19/06/01		IDS_PHRASE_THROUGHTREES	" cutting through the trees."
//deadcode JIM 19/06/01		IDS_PHRASE_SKIRTINGTREES	" skirting tree-line."
//deadcode JIM 19/06/01		IDS_PHRASE_ROUGHTERRAIN	" slowly crossing rough terrain."
//deadcode JIM 19/06/01		IDS_PHRASE_BASEOFSLOPE	" following base of slope."
//deadcode JIM 19/06/01		IDS_PHRASE_RAILCUTTING	" following rail-cutting."
//deadcode JIM 19/06/01	*/
//deadcode JIM 19/06/01	const int IDS_CP=IDS_PHRASE_BLOCKINGPOS;
//deadcode JIM 19/06/01	const int IDS_FRONTLEFTFLANK=IDS_PHRASE_HILLROAD;
//deadcode JIM 19/06/01	const int IDS_FRONTOPEN=IDS_PHRASE_OPENGROUND;
//deadcode JIM 19/06/01	const int IDS_FRONTHILL=IDS_PHRASE_HILLSIDE;
//deadcode JIM 19/06/01	const int IDS_FERRY=IDS_PHRASE_FERRYPOINT;
//deadcode JIM 19/06/01	const int IDS_TOWN_NW=IDS_PHRASE_POSOTOWN;
//deadcode JIM 19/06/01	const int IDS_TOWN_NE=IDS_PHRASE_POSSTOWN;
//deadcode JIM 19/06/01	const int IDS_TOWN_W=IDS_PHRASE_ENTRYTOTOWN;
//deadcode JIM 19/06/01	const int IDS_COVERROAD=IDS_PHRASE_LINEMAINROAD;
//deadcode JIM 19/06/01	const int IDS_CITYSOUTHOFRIVER=IDS_PHRASE_RIVERBANK;
//deadcode JIM 19/06/01	const int IDS_RIVERCROSSING=IDS_PHRASE_BRIDGECROSSING;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//these need fixing!!!!
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_2e=(UniqueID)-12;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_3c=(UniqueID)-13;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_4b=(UniqueID)-14;
//deadcode JIM 19/06/01	//const UniqueID UID_BNC_1e_i=(UniqueID)-15;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_0a_i=(UniqueID)-17;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_0b_i=(UniqueID)-18;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_0c_i=(UniqueID)-19;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_0d_i=(UniqueID)-20;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_0e_i=(UniqueID)-21;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_0f_i=(UniqueID)-22;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_2e_i=(UniqueID)-23;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_3c_i=(UniqueID)-24;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_4b_i=(UniqueID)-25;
//deadcode JIM 19/06/01	//const UniqueID UID_BNC_1e_o=(UniqueID)-26;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_2e_o=(UniqueID)0;//-33;
//deadcode JIM 19/06/01	//const UniqueID UID_BNW_3c_o=(UniqueID)0;//-34;
//deadcode JIM 19/06/01	//DEADCODE %JIM %DATE //const UniqueID UID_BNW_4b_o=(UniqueID)0;//-35;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//these are 'real' fakes!!
//deadcode JIM 19/06/01	const UniqueID UID_BNW_0a_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNW_0b_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNW_0c_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNW_0d_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNW_0e_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNW_0f_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNC_0a_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNC_0b_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNC_0c_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNC_0d_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNC_0e_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNC_0f_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNE_0a_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNE_0b_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNE_0c_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNE_0d_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNE_0e_o=(UniqueID)0;
//deadcode JIM 19/06/01	const UniqueID UID_BNE_0f_o=(UniqueID)0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#undef	NODE
//deadcode JIM 19/06/01	#define	NODE(x)	 set(x)
//deadcode JIM 19/06/01	UniqueID	NodeTable[]=
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		UID_NULL,
//deadcode JIM 19/06/01	#pragma message(__HERE__ "include batuids.h")
//deadcode JIM 19/06/01	#include "batuids.h"	
//deadcode JIM 19/06/01		UID_NULL,
//deadcode JIM 19/06/01		UID_NULL
//deadcode JIM 19/06/01	};
//deadcode JIM 19/06/01	#undef	NODE
//deadcode JIM 19/06/01	#pragma message(__HERE__ "include batuids.h")
//deadcode JIM 19/06/01	#define	NODE(x)	 set(x)_i
//deadcode JIM 19/06/01	UniqueID	NodeTableI[]=
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		UID_NULL,
//deadcode JIM 19/06/01	#pragma message(__HERE__ "include batuids.h")
//deadcode JIM 19/06/01	#include "batuids.h"	
//deadcode JIM 19/06/01		UID_NULL,
//deadcode JIM 19/06/01		UID_NULL
//deadcode JIM 19/06/01	};
//deadcode JIM 19/06/01	#undef	NODE
//deadcode JIM 19/06/01	#pragma message(__HERE__ "include batuids.h")
//deadcode JIM 19/06/01	#define	NODE(x)	 set(x)_o
//deadcode JIM 19/06/01	UniqueID	NodeTableO[]=
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		UID_NULL,
//deadcode JIM 19/06/01	#pragma message(__HERE__ "include batuids.h")
//deadcode JIM 19/06/01	#include "batuids.h"	
//deadcode JIM 19/06/01		UID_NULL,
//deadcode JIM 19/06/01		UID_NULL
//deadcode JIM 19/06/01	};
//deadcode JIM 19/06/01	#undef	NODE
//deadcode JIM 19/06/01	#define	NODE(x)	#x
//deadcode JIM 19/06/01	char*		NodeNames[]=
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		"NULL",
//deadcode JIM 19/06/01	#pragma message(__HERE__ "include batuids.h")
//deadcode JIM 19/06/01	#include "batuids.h"
//deadcode JIM 19/06/01		"HEADER","HEADER"
//deadcode JIM 19/06/01	};
//deadcode JIM 19/06/01	enum	LocalUniqueID
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#undef	NODE
//deadcode JIM 19/06/01	#define NODE(x)		 set(x)_XX
//deadcode JIM 19/06/01		UID_NULL_XX,
//deadcode JIM 19/06/01	#pragma message(__HERE__ "include batuids.h")
//deadcode JIM 19/06/01	#include "batuids.h"
//deadcode JIM 19/06/01		HEADER_REF,
//deadcode JIM 19/06/01		MAX_BAT_BLOCKS,
//deadcode JIM 19/06/01		NUM_MASK =0x0fff,
//deadcode JIM 19/06/01		REF_LEFT =0x1000,
//deadcode JIM 19/06/01		REF_RIGHT=0x2000,
//deadcode JIM 19/06/01		REF_DOWN =0x3000,
//deadcode JIM 19/06/01		DEF_HERE =0x4000
//deadcode JIM 19/06/01	};
//deadcode JIM 19/06/01	#undef	NODE
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	struct	LocalUID
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		typedef	LocalUniqueID	UniqueID;
//deadcode JIM 19/06/01		#include	"batnode.h"
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	};
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	typedef	LocalUID::SuperBattleNode::FlankLink	F;
//deadcode JIM 19/06/01	typedef	LocalUID::SuperBattleNode::IntraLink	L;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#define INITFORCE(aforce,hforce) ((L::TerrainType) (L::INITFORCE+LocalUID::TeamDef::aforce+256*LocalUID::TeamDef::hforce))	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//#define	NODE(num)		UID_BNC_##num
//deadcode JIM 19/06/01	//#define	NODE(num)		UID_BNW_##num
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#define	PLACE(num,text)	NODE(num),IDS_##text
//deadcode JIM 19/06/01	#define	BATTLE(fil,equ)	{fil,equ,__HERE__ "(" fil "): "}
//deadcode JIM 19/06/01	#define	UID_NULL	UID_NULL_XX
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#include	"BN_east.h"
//deadcode JIM 19/06/01	#include	"BN_cent.h"
//deadcode JIM 19/06/01	#include	"BN_west.h"
//deadcode JIM 19/06/01				
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	LocalUID::UniqueID	references[MAX_BAT_BLOCKS];
//deadcode JIM 19/06/01	void	Translate(LocalUID::UniqueID& id)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		id=(LocalUID::UniqueID)NodeTable[id];
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	void	TranslateI(LocalUID::UniqueID& id,LocalUID::UniqueID main)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		id=(LocalUID::UniqueID)NodeTableI[main];
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	void	TranslateO(LocalUID::UniqueID& id,LocalUID::UniqueID main)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		id=(LocalUID::UniqueID)NodeTableO[main];
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	bool	Define(LocalUID::UniqueID id)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		if (references[id]&DEF_HERE)
//deadcode JIM 19/06/01			return false;
//deadcode JIM 19/06/01		references[id]=LocalUID::UniqueID(references[id]|DEF_HERE);
//deadcode JIM 19/06/01		return true;
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	void	Reference(LocalUID::UniqueID id,LocalUID::UniqueID by,LocalUID::UniqueID dir)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		references[id]=LocalUID::UniqueID(by+dir+(references[id]&DEF_HERE));
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	int main()
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		FILE* d=fopen("\\bob\\src\\batnode.fil","wt");
//deadcode JIM 19/06/01		fputs("[files]\n135\tdir.dir\n",d);
//deadcode JIM 19/06/01		int errors=0,writes=0;
//deadcode JIM 19/06/01		LocalUID::SuperBattleDesc* battledescs=eastbattledescs;
//deadcode JIM 19/06/01		do{
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			for (int i=0;battledescs[i].names.filename;i++)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				int j;
//deadcode JIM 19/06/01				for (j=0;j<MAX_BAT_BLOCKS;j++)
//deadcode JIM 19/06/01					references[j]=UID_NULL_XX;
//deadcode JIM 19/06/01				char* defining=battledescs[i].names.filename;
//deadcode JIM 19/06/01				Reference(battledescs[i].header.awayreinforceleft,HEADER_REF,REF_DOWN);
//deadcode JIM 19/06/01				Translate(battledescs[i].header.awayreinforceleft);
//deadcode JIM 19/06/01				Reference(battledescs[i].header.homereinforceleft,HEADER_REF,REF_DOWN);
//deadcode JIM 19/06/01				Translate(battledescs[i].header.homereinforceleft);
//deadcode JIM 19/06/01				for (j=0;battledescs[i].nodelist[j].mainuid;j++)
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01					LocalUID::UniqueID u=battledescs[i].nodelist[j].mainuid;
//deadcode JIM 19/06/01					if (!Define(battledescs[i].nodelist[j].mainuid))
//deadcode JIM 19/06/01						printf("%s Node %s defined twice\n",battledescs[i].names.linenum,NodeNames[u],errors++);
//deadcode JIM 19/06/01					if (	!(battledescs[i].nodelist[j].flanks.nonlinks&F::NOT_LEFT)
//deadcode JIM 19/06/01						&&	!battledescs[i].nodelist[j].flanks.left	)
//deadcode JIM 19/06/01						printf("%s Node %s left link null but not flagged!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
//deadcode JIM 19/06/01					if (	!(battledescs[i].nodelist[j].flanks.nonlinks&F::NOT_RIGHT)
//deadcode JIM 19/06/01						&&	!battledescs[i].nodelist[j].flanks.right	)
//deadcode JIM 19/06/01						printf("%s Node %s right link null but not flagged!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
//deadcode JIM 19/06/01					if (battledescs[i].nodelist[j].flanks.left==u)
//deadcode JIM 19/06/01						printf("%s Node %s left link self reference!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
//deadcode JIM 19/06/01					if (battledescs[i].nodelist[j].flanks.right==u)
//deadcode JIM 19/06/01						printf("%s Node %s right link self reference!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
//deadcode JIM 19/06/01					if (battledescs[i].nodelist[j].innerlink.uid==u)
//deadcode JIM 19/06/01						printf("%s Node %s down link self reference!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01					Translate(battledescs[i].nodelist[j].mainuid);
//deadcode JIM 19/06/01					TranslateI(battledescs[i].nodelist[j].in.uid,u);
//deadcode JIM 19/06/01					TranslateO(battledescs[i].nodelist[j].out.uid,u);
//deadcode JIM 19/06/01	//				if (	(battledescs[i].nodelist[j].out.uid==UID_NULL)
//deadcode JIM 19/06/01	//					==	((battledescs[i].nodelist[j].out.terrain&32768)==0)
//deadcode JIM 19/06/01	//					)
//deadcode JIM 19/06/01	//					printf("%s Node %s: node0/terrain type incompatability!\n",battledescs[i].names.linenum,NodeNames[u],errors++);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01					Reference(battledescs[i].nodelist[j].flanks.left,u,REF_LEFT);
//deadcode JIM 19/06/01					Reference(battledescs[i].nodelist[j].flanks.right,u,REF_RIGHT);
//deadcode JIM 19/06/01					Reference(battledescs[i].nodelist[j].innerlink.uid,u,REF_DOWN);
//deadcode JIM 19/06/01					Translate(battledescs[i].nodelist[j].flanks.left);
//deadcode JIM 19/06/01					Translate(battledescs[i].nodelist[j].flanks.right);
//deadcode JIM 19/06/01					Translate(battledescs[i].nodelist[j].innerlink.uid);
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01				for (int k=1;k<MAX_BAT_BLOCKS;k++)
//deadcode JIM 19/06/01					if (references[k])
//deadcode JIM 19/06/01						if (!(references[k]&DEF_HERE))
//deadcode JIM 19/06/01							if ((references[k]&REF_DOWN)>REF_RIGHT)
//deadcode JIM 19/06/01								printf("%s Node %s references undefined node %s downwards!\n",battledescs[i].names.linenum,NodeNames[references[k]&NUM_MASK],NodeNames[k],errors++);
//deadcode JIM 19/06/01							else if ((references[k]&REF_DOWN)==REF_RIGHT)
//deadcode JIM 19/06/01								printf("%s Node %s references undefined node %s on right flank!\n",battledescs[i].names.linenum,NodeNames[references[k]&NUM_MASK],NodeNames[k],errors++);
//deadcode JIM 19/06/01							else
//deadcode JIM 19/06/01								printf("%s Node %s references undefined node %s on left flank!\n",battledescs[i].names.linenum,NodeNames[references[k]&NUM_MASK],NodeNames[k],errors++);
//deadcode JIM 19/06/01						else
//deadcode JIM 19/06/01							if (!(references[k]&REF_DOWN))
//deadcode JIM 19/06/01								printf("%s Node %s is defined but not used!\n",battledescs[i].names.linenum,NodeNames[k],errors++);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				char buffer[100];
//deadcode JIM 19/06/01				strcpy(buffer,"\\bob\\game\\bfields\\batnode\\");
//deadcode JIM 19/06/01				strcat(buffer,battledescs[i].names.filename);
//deadcode JIM 19/06/01				FILE* f=fopen(buffer,"wb");
//deadcode JIM 19/06/01				if (!f)
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01					printf("%s couldn't write file %i called \"%s\"\n",battledescs[i].names.linenum,i,buffer);
//deadcode JIM 19/06/01					errors++;
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01				else
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01					writes++;
//deadcode JIM 19/06/01					fprintf(d,"\t%s\t%s\n",battledescs[i].names.filename,battledescs[i].names.equatename);
//deadcode JIM 19/06/01					fwrite(&battledescs[i].header,1,sizeof(LocalUID::SuperBattleDesc::Header),f);
//deadcode JIM 19/06/01					fwrite(battledescs[i].nodelist,j,sizeof(LocalUID::SuperBattleNode),f);
//deadcode JIM 19/06/01					fclose(f);
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			if (battledescs==eastbattledescs)
//deadcode JIM 19/06/01			   battledescs=centralbattledescs;
//deadcode JIM 19/06/01			elseif (battledescs==centralbattledescs)
//deadcode JIM 19/06/01			   battledescs=westbattledescs;
//deadcode JIM 19/06/01			else
//deadcode JIM 19/06/01			   battledescs=NULL;
//deadcode JIM 19/06/01		}while (battledescs);
//deadcode JIM 19/06/01		printf("%i files written. %i problems\n",writes,errors);
//deadcode JIM 19/06/01		fclose(d);
//deadcode JIM 19/06/01		return errors;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	}
