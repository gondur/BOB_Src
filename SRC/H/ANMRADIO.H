//------------------------------------------------------------------------------
//Filename       anmradio.h
//System         
//Author         Robert Slater
//Date           Thu 4 Feb 1999
//Description    
//				Radio chatter messages triggered by damage effects...
//
//
//------------------------------------------------------------------------------
#ifndef	ANMRADIO_Included
#define	ANMRADIO_Included

#define	DEFAULT_ANMRADIO 0



enum	VoxRandoms
{
	VOX_RAND_1IN2 = 32768,
	VOX_RAND_1IN4 = 16384,
	VOX_RAND_1IN8 = 8192,
	VOX_RAND_1IN16 = 4096,
	VOX_RAND_1IN24 = 3072,
	VOX_RAND_1IN32 = 2048,
	VOX_RAND_1IN64 = 1024,
	VOX_RAND = VOX_RAND_1IN16
};

enum	RadioDamage
{
	RADIO_NULL = 0,
	RADIO_GENERAL_LV1,
	RADIO_GENERAL_LV2,
	RADIO_ENGINEDAMAGE_LV1,
	RADIO_BLACKSMOKE,
	RADIO_FUELLEAK,
	RADIO_GLYCOL,
	RADIO_BADNEWS
};

struct	HitEffectRecord;

class	DamageChat
{
	AirStrucPtr	acHit;
	AirStrucPtr	acHitter;
	AirStrucPtr	buddy;
	AirStrucPtr	leader;
	Bool		acHitIsFriend;
	bool		acHitAlive;


public:

	void	ExecuteRadio(ItemPtr,ItemPtr,HitEffectRecord&);		//RJS 04Feb99

	DamageChat();

	void	PlayerSideBlewUp(AirStrucPtr);						//RDH 29Apr99
	void	OtherSideBlewUp(AirStrucPtr,AirStrucPtr,bool);		//RDH 20May99
	void	PlayerSidePiledIn(AirStrucPtr);						//RDH 29Apr99
	void	SayWeapon(SLong);									//RJS 13May99



private:

	void	PlayerSideDamageLevel1();
	void	PlayerSideDamageLevel2();
	void	OtherSideDamageLevel1();
	void	OtherSideDamageLevel2();
	void	FuelLeak();
	void	LeaderLeaking();
	void	FollowerLeaking();
	void	FuelLeakMsg(AirStrucPtr);

	void	BlackSmoke();
	void	SmokingBadly(AirStrucPtr);
	void	BlackSmokeMsg(AirStrucPtr);

	void	EjectMsg(AirStrucPtr);

	void	PlayerSideKilled();
	void	OtherSideKilled();

	void	AlertGoHome(AirStrucPtr);

	void	EngineDamage();
	void	EngineDamageGlycol();

};

extern	DamageChat	_DamageChat;

#endif
