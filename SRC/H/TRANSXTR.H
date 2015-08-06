//------------------------------------------------------------------------------
//Filename       transxtr.h
//System         
//Author         Robert Slater
//Date           Wed 17 Nov 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	TRANSXTR_Included
#define	TRANSXTR_Included

#define	DEFAULT_TRANSXTR 0


class	MinAnimData;

const	SLong	MINWEAP = -1;										//RJS 07Dec99
const	SLong	MAXWEAP = LT_BOMB;

const	SWord		OrdinaryDrag		=	100;
const	SWord		RetardedDrag		=	500;

class	DeathTollLink					
{
	MinAnimData*	adptr;
	DeathTollLink*	next;


public:		

	DeathTollLink(MinAnimData*,DeathTollLink*);
	~DeathTollLink();

};	




#endif
