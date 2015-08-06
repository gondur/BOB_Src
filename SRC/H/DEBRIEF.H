//DEADCODE DAW 29/01/00 /*
//DEADCODE DAW 29/01/00 //{{AFX_INCLUDES()
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 //}}AFX_INCLUDES
//DEADCODE DAW 29/01/00 */
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 // Data structure for debrief info
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 #ifndef	DEBRIEF_INCLUDED
//DEADCODE DAW 29/01/00 #define	DEBRIEF_INCLUDED
//DEADCODE DAW 29/01/00 #include "bitcount.h"
//DEADCODE DAW 29/01/00 #include "infoitem.h"
//DEADCODE DAW 29/01/00 class	Debrief
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 public:
//DEADCODE DAW 29/01/00 	enum	Types	{	REDAC, MIG,YAK, AAA,
//DEADCODE DAW 29/01/00 						SUPPLY,MARTYARD,
//DEADCODE DAW 29/01/00 						RAILBRIDGE,ROADBRIDGE,
//DEADCODE DAW 29/01/00 						TRAIN,TRUCK,
//DEADCODE DAW 29/01/00 						AIRFIELD,
//DEADCODE DAW 29/01/00 						TROOPS,ARTILLERY,TANK,
//DEADCODE DAW 29/01/00 						LOSSESTOREDAC, LOSSESTOMIG,	LOSSESTOYAK, LOSSESTOAAA, LOSSESTOOTHER,
//DEADCODE DAW 29/01/00 						TARG_MAX};
//DEADCODE DAW 29/01/00 	struct	TargKills
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		int	count[TARG_MAX];
//DEADCODE DAW 29/01/00 		int	TotalLosses()	{return count[LOSSESTOREDAC]+count[LOSSESTOAAA]+count[LOSSESTOOTHER];}
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 		int& operator[](Types t) {return count[t];} 
//DEADCODE DAW 29/01/00 	};
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	struct	SquadKills
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		TargKills	count[(int)PT_GER_FLYABLE+1];		//+1 for all
//DEADCODE DAW 29/01/00 		TargKills&	operator[](SquadSelect s)	{return count[s];}
//DEADCODE DAW 29/01/00 	};
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	SquadKills	lastday,				//what happened on the last day
//DEADCODE DAW 29/01/00 				lastperiod,				//what happened on the last period
//DEADCODE DAW 29/01/00 				cumulative,
//DEADCODE DAW 29/01/00 				total;					//sum it all
//DEADCODE DAW 29/01/00 				//playerperiod,			//players actions last period. 
//DEADCODE DAW 29/01/00 										//not directly displayed, but has effects
//DEADCODE DAW 29/01/00 				//playertotal;			//sum for player's actions.
//DEADCODE DAW 29/01/00 	enum	{PERIOD=0, DAY, TOTAL};
//DEADCODE DAW 29/01/00 	char	displayperiod;
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	enum	PlayerTypes {SORTIES, COMBATS, KILLS, LOSSES, PC_MAX};
//DEADCODE DAW 29/01/00 	struct	PlayerCounts	
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00  		int	count[PC_MAX];
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 		int& operator[](PlayerTypes t) {return count[t];} 
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	};
//DEADCODE DAW 29/01/00 	struct	PlayerTotals
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		PlayerCounts	count[(int)PT_VEHICLES+1];
//DEADCODE DAW 29/01/00 		PlayerCounts&	operator[](SquadSelect s)	{return count[s];}
//DEADCODE DAW 29/01/00 	};
//DEADCODE DAW 29/01/00 	PlayerTotals	playertotals;
//DEADCODE DAW 29/01/00 	struct PlayQuickCounts
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		int	countground[TARG_MAX];
//DEADCODE DAW 29/01/00 		int	countair[PT_VEHICLES];
//DEADCODE DAW 29/01/00 		int&	operator[](SquadSelect s)	{return countair[s];}
//DEADCODE DAW 29/01/00 		int&	operator[](Types s)			{return countground[s];}
//DEADCODE DAW 29/01/00 	};
//DEADCODE DAW 29/01/00 	PlayQuickCounts	playerqmcounts,unqmcounts,redqmcounts;
//DEADCODE DAW 29/01/00 	int	barcapkills,barcaplost;	
//DEADCODE DAW 29/01/00 	
//DEADCODE DAW 29/01/00 	struct	PlayerLog
//DEADCODE DAW 29/01/00 	{	//8 bytes
//DEADCODE DAW 29/01/00 		UByte		role;
//DEADCODE DAW 29/01/00 		UByte		dummy;
//DEADCODE DAW 29/01/00 		UByte		kills;
//DEADCODE DAW 29/01/00 ONLYFIELD(UByte,	SquadSelect,pilotsquad);
//DEADCODE DAW 29/01/00 ONLYFIELD(UWord,	UniqueID, 	target1);
//DEADCODE DAW 29/01/00 ONLYFIELD(UWord,	UniqueID,	target2);
//DEADCODE DAW 29/01/00 	};
//DEADCODE DAW 29/01/00 	enum {DAYSPERCAMP=200,PERIODSPERDAY=3};	 //600*8=5K
//DEADCODE DAW 29/01/00 	PlayerLog	playerlog[DAYSPERCAMP][PERIODSPERDAY];
//DEADCODE DAW 29/01/00 	enum	{MAXSORTEDEVENTS=40};
//DEADCODE DAW 29/01/00 	EventEntry	sortedevents[MAXSORTEDEVENTS];
//DEADCODE DAW 29/01/00 	int		currlogday;
//DEADCODE DAW 29/01/00 	int		currperiod;
//DEADCODE DAW 29/01/00 	//Mark's display is:								//My flag:
//DEADCODE DAW 29/01/00 	//
//DEADCODE DAW 29/01/00 	//21/1/67											//DATE
//DEADCODE DAW 29/01/00 	//  Yalu Bridge		Repair crews spotted			//TARGUID
//DEADCODE DAW 29/01/00 	//  TaeJong			Blue forces taking the offensive//TARGUID
//DEADCODE DAW 29/01/00 	//22/1/97											//DATE
//DEADCODE DAW 29/01/00 	//  CIC				You are doing well. Keep it up	//NAME
//DEADCODE DAW 29/01/00 	//  TaeJong			Ground forces request assistance//DISCARDTARGUID
//DEADCODE DAW 29/01/00 	//
//DEADCODE DAW 29/01/00 	//Note the 2 character indents and there are no grid lines.
//DEADCODE DAW 29/01/00 	//You can view the dossier for TARGUID and DISCARDTARGUID lines
//DEADCODE DAW 29/01/00 	//If it's an ongoing battle node you see the Army form instead
//DEADCODE DAW 29/01/00 	//Thus, army requests in the DIS can be general.
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 		enum	DisEntry	{
//DEADCODE DAW 29/01/00 			L2_DISTITLE_0,
//DEADCODE DAW 29/01/00 			T_DefendWest01_H,
//DEADCODE DAW 29/01/00 			T_DefendWest02_H,
//DEADCODE DAW 29/01/00 			T_DefendWest03_H,
//DEADCODE DAW 29/01/00 			T_DefendWest04_H,
//DEADCODE DAW 29/01/00 			T_AttackWest01_H,
//DEADCODE DAW 29/01/00 			T_AttackWest02_H,
//DEADCODE DAW 29/01/00 			T_AttackWest03_H,
//DEADCODE DAW 29/01/00 			T_AttackWest04_H,
//DEADCODE DAW 29/01/00 			T_AttackWest05_H,
//DEADCODE DAW 29/01/00 			T_AttackWest06_H,
//DEADCODE DAW 29/01/00 			T_AttackCntr01_H,
//DEADCODE DAW 29/01/00 			T_AttackCntr02_H,
//DEADCODE DAW 29/01/00 			T_AttackCntr03_H,
//DEADCODE DAW 29/01/00 			T_AttackCntr04_H,
//DEADCODE DAW 29/01/00 			T_AttackCntr05_H,
//DEADCODE DAW 29/01/00 			T_AttackCntr06_H,
//DEADCODE DAW 29/01/00 			T_DefendCntr01_H,
//DEADCODE DAW 29/01/00 			T_DefendCntr02_H,
//DEADCODE DAW 29/01/00 			T_DefendCntr03_H,
//DEADCODE DAW 29/01/00 			T_DefendCntr04_H,
//DEADCODE DAW 29/01/00 			T_DefendCntr05_H,
//DEADCODE DAW 29/01/00 			T_DefendCntr06_H,
//DEADCODE DAW 29/01/00 			T_Advance01_H,
//DEADCODE DAW 29/01/00 			T_Advance02_H,
//DEADCODE DAW 29/01/00 			T_Advance03_H,
//DEADCODE DAW 29/01/00 			T_Advance04_H,
//DEADCODE DAW 29/01/00 			T_Advance05_H,
//DEADCODE DAW 29/01/00 			T_Retreat01_H,
//DEADCODE DAW 29/01/00 			T_DefendWest05_H,
//DEADCODE DAW 29/01/00 			D_BritsArrive_H,
//DEADCODE DAW 29/01/00 			T_Supply00_H,
//DEADCODE DAW 29/01/00 			T_Supply01_H,
//DEADCODE DAW 29/01/00 			T_Supply02_H,
//DEADCODE DAW 29/01/00 			T_FAC00_H,
//DEADCODE DAW 29/01/00 			T_Army00_H,
//DEADCODE DAW 29/01/00 			T_Army01_H,
//DEADCODE DAW 29/01/00 			T_Army02_H,
//DEADCODE DAW 29/01/00 			T_Army03_H,
//DEADCODE DAW 29/01/00 			T_Army04_H,
//DEADCODE DAW 29/01/00 			T_Army05_H,
//DEADCODE DAW 29/01/00 			T_Army06_H,
//DEADCODE DAW 29/01/00 			T_Army07_H,
//DEADCODE DAW 29/01/00 			T_FAC01_H,
//DEADCODE DAW 29/01/00 			T_FAC02_H,
//DEADCODE DAW 29/01/00 			T_FAC03_H,
//DEADCODE DAW 29/01/00 			D_Flak00_H,
//DEADCODE DAW 29/01/00 			D_Flak01_H,
//DEADCODE DAW 29/01/00 			D_Flak02_H,
//DEADCODE DAW 29/01/00 			D_Flak03_H,
//DEADCODE DAW 29/01/00 			T_DeceptionFound00_H,
//DEADCODE DAW 29/01/00 			D_DeceptionFound01_H,
//DEADCODE DAW 29/01/00 			T_Bombers00_H,
//DEADCODE DAW 29/01/00 			T_Bombers01_H,
//DEADCODE DAW 29/01/00 			T_FAC04_H,
//DEADCODE DAW 29/01/00 			D_DeceptionFound02_H,
//DEADCODE DAW 29/01/00 			D_DeceptionFound03_H,
//DEADCODE DAW 29/01/00 			T_Retreat02_H,
//DEADCODE DAW 29/01/00 			T_Retreat03_H,
//DEADCODE DAW 29/01/00 			D_Repairs00_H,
//DEADCODE DAW 29/01/00 			T_ByPassBuilt_H,
//DEADCODE DAW 29/01/00 			D_RailInterdict00_H,
//DEADCODE DAW 29/01/00 			T_AF00_H,
//DEADCODE DAW 29/01/00 			T_AF01_H,
//DEADCODE DAW 29/01/00 			T_AF02_H,
//DEADCODE DAW 29/01/00 			D_Repairs01_H,
//DEADCODE DAW 29/01/00 			T_Airfield00_H,
//DEADCODE DAW 29/01/00 			T_Airfield01_H,
//DEADCODE DAW 29/01/00 			T_Airfield02_H,
//DEADCODE DAW 29/01/00 			T_DefendWest06_H,
//DEADCODE DAW 29/01/00 			T_Airfield04_H,
//DEADCODE DAW 29/01/00 			T_Airfield05_H,
//DEADCODE DAW 29/01/00 			T_Airfield06_H,
//DEADCODE DAW 29/01/00 			T_USE_DAMAGED_WH_H,
//DEADCODE DAW 29/01/00 			T_Replenish_H,
//DEADCODE DAW 29/01/00 			D_AlJolson_H,
//DEADCODE DAW 29/01/00 			T_SquadRotate_H,
//DEADCODE DAW 29/01/00 			T_StoodDown_H,
//DEADCODE DAW 29/01/00 			D_MiniText00_H,
//DEADCODE DAW 29/01/00 			D_MiniText01_H,
//DEADCODE DAW 29/01/00 			D_MiniText02_H,
//DEADCODE DAW 29/01/00 			D_MiniText03_H,
//DEADCODE DAW 29/01/00 			D_MiniText04_H,
//DEADCODE DAW 29/01/00 			D_MiniText05_H,
//DEADCODE DAW 29/01/00 			D_MiniText06_H,
//DEADCODE DAW 29/01/00 			D_MiniText07_H,
//DEADCODE DAW 29/01/00 			D_MiniText08_H,
//DEADCODE DAW 29/01/00 			D_MiniText09_H,
//DEADCODE DAW 29/01/00 			D_MiniText10_H,
//DEADCODE DAW 29/01/00 			D_MiniText11_H,
//DEADCODE DAW 29/01/00 			D_MiniText12_H,
//DEADCODE DAW 29/01/00 			D_MiniText13_H,
//DEADCODE DAW 29/01/00 			D_MiniText14_H,
//DEADCODE DAW 29/01/00 			D_MiniText15_H,
//DEADCODE DAW 29/01/00 			D_MiniText16_H,
//DEADCODE DAW 29/01/00 			D_MiniText17_H,
//DEADCODE DAW 29/01/00 			D_MiniText18_H,
//DEADCODE DAW 29/01/00 			D_MiniText19_H,
//DEADCODE DAW 29/01/00 			D_MiniText20_H,
//DEADCODE DAW 29/01/00 			D_MiniText21_H,
//DEADCODE DAW 29/01/00 			D_MiniText22_H,
//DEADCODE DAW 29/01/00 			D_MiniText23_H,
//DEADCODE DAW 29/01/00 			D_MiniText24_H
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 		};
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	enum	OneOffDisses
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		OOD_HutTruck=1,
//DEADCODE DAW 29/01/00 		OOD_Monk=2,
//DEADCODE DAW 29/01/00 		//4
//DEADCODE DAW 29/01/00 		//8
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	};
//DEADCODE DAW 29/01/00 	int	oneoffdisses;
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	bool	OneOffDiss(OneOffDisses trial)	
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		if (oneoffdisses&(int)trial)
//DEADCODE DAW 29/01/00 			return	true;
//DEADCODE DAW 29/01/00 		oneoffdisses|=(int)trial;
//DEADCODE DAW 29/01/00 		return false;
//DEADCODE DAW 29/01/00 	}
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	enum	TypeFlag	{TARGUID,DATE,NAME,DISCARDTARGUID};
//DEADCODE DAW 29/01/00 	struct	DisLog
//DEADCODE DAW 29/01/00 	{	//4 bytes per item
//DEADCODE DAW 29/01/00 		ULong	typeflag:2,	
//DEADCODE DAW 29/01/00 			msgowner:15,
//DEADCODE DAW 29/01/00 			msgtextid:15;
//DEADCODE DAW 29/01/00 	};
//DEADCODE DAW 29/01/00 	enum	{DISISALLTOOMUCH=256,DISISITFORTODAY=20};
//DEADCODE DAW 29/01/00 	DisLog	alldis[DISISALLTOOMUCH];
//DEADCODE DAW 29/01/00 	int		disgoeshere;
//DEADCODE DAW 29/01/00 	//alldis is a circular list.
//DEADCODE DAW 29/01/00 	//vape up to the next date to make room for the next days requests
//DEADCODE DAW 29/01/00 	//so disgoeshere will generally point at an empty slot.
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	DisLog	disday[DISISITFORTODAY];
//DEADCODE DAW 29/01/00 	//disday is cleared out every day
//DEADCODE DAW 29/01/00 	//There would not be an initial DATE entry
//DEADCODE DAW 29/01/00 	//If we want, messages generated during the three periods could 
//DEADCODE DAW 29/01/00 	//be separated by DATE entries.
//DEADCODE DAW 29/01/00 	//When the disday is appended to the alldis, a DATE entry is manufactured,
//DEADCODE DAW 29/01/00 	//and any DISCARDTARGUIDs or DATE entries are ignored.
//DEADCODE DAW 29/01/00 	//disday is then cleared.
//DEADCODE DAW 29/01/00 	//we use msgowner to hold the day number
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 	struct	ArmyReq
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 	{	//these fields control what is printed in the list
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 		int			forcename;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 		int			forcenum;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 		int			requesttext;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 		//these fields control what happens when you hit authorise
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 		UniqueID	attacknode;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 		int			attackmethod;	//same idea as target type control in DIS
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 	};
//DEADCODE DAW 29/01/00 //DEADCODE JIM 03/03/99 	ArmyReq	armyrequests[3][16];
//DEADCODE DAW 29/01/00 	//3 fronts, 16 messages per front per day.
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 //	void	NextPeriod();
//DEADCODE DAW 29/01/00 //	void	NextPeriod(SquadKills& period,SquadKills& day);
//DEADCODE DAW 29/01/00 //	void	NextDay();
//DEADCODE DAW 29/01/00 };
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 #endif
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00