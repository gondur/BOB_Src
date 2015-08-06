//------------------------------------------------------------------------------
//Filename       animmove.h
//System         
//Author         Robert Slater
//Date           Tue 20 Oct 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	ANIMMOVE_Included
#define	ANIMMOVE_Included

#define	DEFAULT_ANIMMOVE 0


enum	AnimMoves						
{
	BLOKE_NULL = -1,		// basic moves
	BLOKE_STAND = 0,
	BLOKE_WALK,													//RJS 22Dec99
	BLOKE_RUN,													//RJS 22Dec99
	BLOKE_DIVE,													//RJS 22Dec99
	BLOKE_PULLCHUTE,											//RJS 22Dec99
	BLOKE_GOODCHUTE,											//RJS 22Dec99
	BLOKE_WAAAH,												//RJS 22Dec99
	BLOKE_LANDGOOD,												//RJS 22Dec99
	BLOKE_LANDSPLAT,											//RJS 22Dec99
	BLOKE_DIVEFORCOVER,											//RJS 22Dec99
	BLOKE_BORED1,												//RJS 22Dec99
	BLOKE_BORED2,												//RJS 22Dec99
	BLOKE_BORED3,												//RJS 22Dec99
	BLOKE_BORED4,												//RJS 22Dec99
	BLOKE_TALK1,												//RJS 22Dec99
	BLOKE_TALK2,												//RJS 22Dec99
	BLOKE_TALK3,												//RJS 22Dec99
	BLOKE_TALK4,												//RJS 22Dec99
	BLOKE_RUNCHICKEN,											//RJS 17Apr00
	BLOKE_SHOT													//RJS 22Dec99
};

enum	tAnimation
{
	ANIMATION_STAND = 0,
	ANIMATION_BORED,											//RJS 12Jan00
	ANIMATION_WALK,
	ANIMATION_RUN,												//RJS 22Dec99
	ANIMATION_DIVE,												//RJS 22Dec99
	ANIMATION_PULL_CHUTE,										//RJS 22Dec99
	ANIMATION_GOOD_CHUTE,										//RJS 22Dec99
	ANIMATION_AARGH,											//RJS 22Dec99
	ANIMATION_LAND_GOOD,										//RJS 22Dec99
	ANIMATION_LAND_SPLAT,										//RJS 22Dec99
	ANIMATION_DIVE_FOR_COVER,									//RJS 22Dec99
	ANIMATION_SHOT,												//RJS 22Dec99
	ANIMATION_RUNCHICKEN,										//RJS 14Apr00
	ANIMATION_TALK,												//RJS 14Apr00
	ANIMATION_SHOTDEAD,											//RJS 26Apr00

	ANIMATION_NULL,
	ANIMATION_LAST
} ;


// Relative clothing offsets...

enum	tClothing												//RJS 22Dec99
{																//RJS 22Dec99
	CLOTHING_RAFPILOT = 0,										//RJS 22May00
	CLOTHING_LWPILOT,											//RJS 22May00
	CLOTHING_GROUND,											//RJS 22May00
	CLOTHING_WOMAN,												//RJS 22Dec99
	CLOTHING_ENEMY,												//RJS 22Dec99
	CLOTHING_FARMER,											//RJS 22Dec99
	CLOTHING_CIVILIAN											//RJS 22Dec99
} ;																//RJS 22Dec99


#define	MAXANIMSCRIPT	16

class	ViewPoint;

struct	ANIMCONTROLSTRUC
{
	AnimMoves	from[MAXANIMSCRIPT];
	AnimMoves	mid[MAXANIMSCRIPT];
	AnimMoves	to[MAXANIMSCRIPT];
	UByte		acnt;

public:

	ANIMCONTROLSTRUC()	{acnt = 0;}
	~ANIMCONTROLSTRUC()	{acnt = 0;}

	void	SetAnim(AnimMoves pre, AnimMoves trans, AnimMoves post, SWord tokumtime=0) ;
	void	SetAnim(AnimMoves pre, AnimMoves post, SWord tokumtime=0) ;
	void	SetAnim(AnimMoves post, SWord tokumtime=0) ;

	AnimMoves	GetAnimMove(AnimMoves oldanim,AnimMoves&	trans)
	{
		int	i = 0;

 		while (i < acnt)
 		{
 			if ((from[i] == oldanim) || (from[i] == BLOKE_NULL))
 			{
 				trans = mid[i];
 				return(to[i]);
 			}
 			i++;
 		}
		trans = BLOKE_NULL;
		return(BLOKE_STAND);
	}

	AnimMoves	GetAnimMove();
};

class	AnimControl
{
	ANIMCONTROLSTRUC	animlist[ANIMATION_LAST];
	ViewPoint*			View_Point;
	
public:

	AnimControl();
	~AnimControl();

	ANIMCONTROLSTRUC*	GetAnimControl(tAnimation animtype) ;
	AnimMoves			GetAnimMove(tAnimation,AnimMoves,AnimMoves&);
	void				SetViewPoint(ViewPoint*);
	bool				SetPlayerAnim(ItemPtr, UWord);
	bool				Finished(ItemPtr,const tAnimation&);
	bool				NeverStarted(ItemPtr, const tAnimation&);



	
};

extern class AnimControl Anim_Control;

#endif
