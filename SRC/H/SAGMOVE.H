//////////////////////////////////////////////////////////////////////
//
// Module:      sagmove.h
//
// Created:     03/12/99 by JIM
//
// Description: SAG MOVEMENT ADDITION TO WORLDINC.H/INFOITEM.H
//
// Note	this header inserts identical extra functions 
//		into AirStruc and info_airgrp
//
//	The decision routine is called every 20 seconds in both 3d and 2d sections
//	The Movement routine is called every 4cs in 3d sections, 
//		but only every 20 seconds in 2d sections
//
//	These are the scenarios in r_airgrp.doc
//	fly on course,		Would move forward up to 5 km (300kmh)
//	flying home damaged 		Would move forward up to 5 km (300kmh)
//	bomb run approach		Would move forward up to 5 km (300kmh)
//	bomb run dive		No visible effect
//	bomb run level		Would move forward up to 5 km (300kmh)
//	engage approach		Would move toward unfriendly up to 5 km (300kmh)
//	engage circling		No visible effect. Heading may change internally.
//	engage pass through		Would move to cross unfriendly and move perhaps 2 km
//	stopped expanded		Won't occur on map
//	stopped destroyed		No visible effect
//
//////////////////////////////////////////////////////////////////////
//#define	 sagmove_REQUIRED	SAGAirstruc:AirStruc
//#include "sagmove.h"
//#define	 sagmove_REQUIRED	SAGairgrp:info_airgrp
//#define PARAMS	int p, int s
//#include "sagmove.h"  

#ifdef sagmove_REQUIRED
#ifndef PARAMS
#define PARAMS
#endif
struct	sagmove_REQUIRED
{
	static void	MoveAllSAGs(WorldStuff& world = *(WorldStuff*)NULL);
	void   MoveSAG(PARAMS);
	void   DecideSAG(PARAMS);
	void	SAGWPAction(PARAMS);

	void	SAGMovementWaitTakeOff(PARAMS);
	void	SAGDecisionWaitTakeOff(PARAMS);
	void	SAGMovementTakeOff(PARAMS);
	void	SAGDecisionTakeOff(PARAMS);
	void	SAGMovementFollowWP(PARAMS);
	void	SAGDecisionFollowWP(PARAMS);
	void	SAGMovementLanding(PARAMS);
	void	SAGDecisionLanding(PARAMS);
	void	SAGMovementPreCombat(PARAMS);
	void	SAGDecisionPreCombat(PARAMS);
	void	SAGMovementCombat(PARAMS);
	void	SAGDecisionCombat(PARAMS);
	void	SAGMovementCombatCircles(PARAMS);
	void	SAGDecisionCombatCircles(PARAMS);
	void	SAGMovementPostCombat(PARAMS);
	void	SAGDecisionPostCombat(PARAMS);
	void	SAGMovementBombingApproach(PARAMS);
	void	SAGDecisionBombingApproach(PARAMS);
	void	SAGMovementBombing(PARAMS);
	void	SAGDecisionBombing(PARAMS);
	void	SAGMovementTrackExpanded(PARAMS);
	void	SAGDecisionTrackExpanded(PARAMS);
	void	SAGMovementTrackExpandedCombat(PARAMS);
	void	SAGDecisionTrackExpandedCombat(PARAMS);
	void	SAGMovementDestroyed(PARAMS);
	void	SAGDecisionDestroyed(PARAMS);
	void	SAGMovementLanded(PARAMS);
	void	SAGDecisionLanded(PARAMS);
	void	SAGMovementDeathGlide(PARAMS);								//CSB 15Aug00
	void	SAGDecisionDeathGlide(PARAMS);								//CSB 15Aug00

//SAGairgrp specific:
//DEADCODE DAW 21/02/00 	int	GetCruiseAt(Coords3D& pos);
	void	SAGMovementFollowWP(int p,int s,int sparesecs);
	void	SAGExecuteWaypoint(int p,int s);
	int		FakeDamage(UniqueID target,int numbombers,PlaneTypeSelect attackertype,UniqueID reportsuccess);	//returns true if target becomes dead.
	static int	GetRefuellingTime(SquadNum sq);
	void	SetDisperse();
	void	SetLanding();
	void	SetBreakLoop(bool gobacktostart);
	info_airgrp* GetValidEscortee(int p,int s);
	void	FlyAsEscort(info_airgrp* escortee,int p,int s);
	int		FuelUse(Coords3D& pos,int velumcs,int timesecs);
	static bool	SendFighterPatrols(UniqueID packtrg,UniqueID instance,int pt,int st);
	UniqueID	SelectUnfriendly(int trgpack,int trgraid,int submethod,int& livesqs);
	bool PatchAppropriate();
};
#undef	sagmove_REQUIRED
#undef PARAMS
#endif sagmove_REQUIRED

typedef SAGAirstruc SAGAirStruc;

