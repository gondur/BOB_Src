//------------------------------------------------------------------------------
//Filename       keymaps.h
//System         
//Author         Jim Taylor
//Date           Fri 3 Nov 1995
//Description    Keyboard mappings definition include file
//				Generally, this file declares CONSTs, but it also can make data.
//
// I am implementing the bloody view matrix 'cos if I don't we will never fit it in!
//
//------------------------------------------------------------------------------

////NOTE:	PLEASE READ THE NOTES!!!!
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr,unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.

#ifndef	KEYMAPS_Included
#define	KEYMAPS_Included
struct	KeyMapping
{
	UWord	scancode:10,
			shiftstate:6;
	UWord	bitflag;
};
#ifndef __BCPLUSPLUS__
enum	KeyVal3D	{keyVal3D_MAX=TOTALKEYBITFLAGS};
enum	KeyShift_BN	{	KEYSH_BN_norm=0,
						KEYSH_BN_extsh=1,
						KEYSH_BN_AltL=2,
						KEYSH_BN_CtrlL=3,
						KEYSH_BN_ShiftL=4,
						KEYSH_BN_Msg=5,
						KEYSH_BN_ShMsg=6,
						KEYSH_BN_Overlay=7
					};
#endif
#define	KeyName(keynum,keyname)				\
KeyVal3D	const	keyname=(KeyVal3D)(keynum*2);

//------------------------------------------------------------------------------
// Place new 3d key press equate definitions in the list below
// The first number must be sequential, but we can leave gaps
// The second field is the name used in the 3d
//The mapping to the keyboard keys goes in the next table 
//------------------------------------------------------------------------------

KeyName(00,ReservedKeyMapping)

//keys 01..07 now reserved for shifts:
//DEADCODE AMM 09/12/99 KeyName(01,KeySrc_BN_extsh)		/*(Extended Shift)*/
//DEADCODE AMM 09/12/99 KeyName(02,KeySrc_BN_AltL)		/*(Left Alt)*/
//DEADCODE AMM 09/12/99 KeyName(03,KeySrc_BN_AltGR)		/*(AltGr)*/
//DEADCODE AMM 09/12/99 KeyName(04,KeySrc_BN_CtrlL)
//DEADCODE AMM 09/12/99 KeyName(05,KeySrc_BN_CtrlR)
//DEADCODE AMM 09/12/99 KeyName(06,KeySrc_BN_ShiftL)
//DEADCODE AMM 09/12/99 KeyName(07,KeySrc_BN_ShiftR)


KeyName(01,KeySrc_BN_extsh)
KeyName(02,KeySrc_BN_AltL)
KeyName(03,KeySrc_BN_CtrlL)
KeyName(04,KeySrc_BN_ShiftL)
KeyName(05,KeySrc_BN_Msg)
KeyName(06,KeySrc_BN_ShMsg)
KeyName(07,KeySrc_BN_Overlay)

//DeadCode AMM 07Dec99 KeyName(8,ELEVATOR_BACK)		/*Elevator Back*/
//DeadCode AMM 07Dec99 KeyName(9,ELEVATOR_FORWARD)	/*Elevator Forward*/
//DeadCode AMM 07Dec99 KeyName(10,AILERON_RIGHT)		/*Aieron Right*/
//DeadCode AMM 07Dec99 KeyName(11,AILERON_LEFT)		/*Aileron Left*/
//DeadCode AMM 07Dec99 KeyName(12,RUDDER_LEFT)			/*Rudder Left*/
//DeadCode AMM 07Dec99 KeyName(13,RUDDER_RIGHT)		/*Rudder Right*/
//DeadCode AMM 07Dec99 KeyName(14,SENS_UP)				/*Increase Keyboard Sensitivity*/
//DeadCode AMM 07Dec99 KeyName(15,SENS_DOWN)			/*Decrease Keyboard Sensitivity*/

KeyName(8,KeySrc_BN_NormLock)		
KeyName(9,KeySrc_BN_SpareLock)
KeyName(10,KeySrc_BN_AltLock)		
KeyName(11,KeySrc_BN_CtrlLock)		
KeyName(12,KeySrc_BN_ShiftLock)		
KeyName(13,KeySrc_BN_MsgLock)		
KeyName(14,KeySrc_BN_ShMsgLock)		
KeyName(15,KeySrc_BN_OverlayLock)


KeyName(16,RPM_10)				/*10% Throttle*/
KeyName(17,RPM_20)				/*20% Throttle*/
KeyName(18,RPM_30)				/*30% Throttle*/
KeyName(19,RPM_40)				/*40% Throttle*/
KeyName(20,RPM_50)				/*50% Throttle*/
KeyName(21,RPM_60)				/*60% Throttle*/
KeyName(22,RPM_70)				/*70% Throttle*/
KeyName(23,RPM_80)				/*80% Throttle*/
KeyName(24,RPM_90)				/*90% Throttle*/
KeyName(25,RPM_00)				/*100% Throttle*/

KeyName(26,RPM_UP)				/*Throttle Up 1%*/
KeyName(27,RPM_DOWN)			/*Throttle Down 1%*/	
KeyName(28,RPM_BIG_UP)			/*Throttle Up 10%*/
KeyName(29,RPM_BIG_DOWN)		/*Throttle Down 10%*/

KeyName(30,MAXPROPPITCH)
KeyName(31,MINPROPPITCH)
KeyName(32,PROPPITCHUP)			//Increase Prop Pitch / Decrease RPM
KeyName(33,PROPPITCHDOWN)		//Decrease Prop Pitch / Increase RPM

//PD 19Feb96 - view zoom / rotation keys
KeyName(34,BIGROTDOWN)		/*Down Fast*/
KeyName(35,BIGROTUP)		/*Up Fast*/	
KeyName(36,BIGROTRIGHT)		/*Right Fast*/
KeyName(37,BIGROTLEFT)		/*Left Fast*/

KeyName(38,BIGROTDNLEFT)	/*Down Left Fast*/
KeyName(39,BIGROTDNRIGHT)	/*Down Right Fast*/
KeyName(40,BIGROTUPLEFT)	/*Up Left Fast*/
KeyName(41,BIGROTUPRIGHT)	/*Up Right Fast*/

KeyName(42,BIGZOOMIN)		/*Zoom In Fast*/
KeyName(43,BIGZOOMOUT)		/*Zoom Out Fast*/

KeyName(44,ROTDOWN)			/*Down/Back*/	
KeyName(45,ROTUP)			/*Up/Forward*/	
KeyName(46,ROTRIGHT)		/*Right*/		
KeyName(47,ROTLEFT)			/*Left*/		

KeyName(48,ROTDNLEFT)		/*Down/Back and Left*/	
KeyName(49,ROTDNRIGHT)		/*Down/Back and Right*/	
KeyName(50,ROTUPLEFT)		/*Up/Forward and Left*/	
KeyName(51,ROTUPRIGHT)		/*Up/Forward and Right*/

KeyName(52,ZOOMIN)			/*Zoom In*/				
KeyName(53,ZOOMOUT)			/*Zoom Out*/			

KeyName(54,ROTRESET)		/*View Reset*/					
KeyName(55,SCREENSHOT)		/*Screenshot*/	

KeyName(56,SHOOT)			/*Fire*/			
KeyName(57,PAUSEKEY)		/*Pause*/			
KeyName(58,INFOPANEL)		/*Info Panel Toggle*/
KeyName(59,DETAILUP)		/*Increase 3d detail*/

////PLEASE READ COMMENTS.

////NOTE:
//// View matrix reserves 8x8 key entries - keys 64 to 127:
//// viewee:	unchanged, pilot, fr, unf, gr, home	  		//5/8
//// viewtype:  unchanged, inside, outside, satelite, chase //5/8
//// Keys are not mapped to all these entries, but extras can be added externally
//// This will make gaps in the key lists above.
////
////
//// The following keys will form the start of the view matrix
////
////
//
// Row 0,(65,66,67,68,69,70,71 and Col 0 (72,80,88,96,104,112,120) only effect 1 axis
//
// Values inside grid effect both axes. 
//
//
KeyName(65,RESETVIEW)	/*Reset View*/	
KeyName(66,ENEMYVIEW)	/*Next Enemy View*/	
KeyName(67,FRNDVIEW)	/*Next Friend View*/
KeyName(68,GRNDTVIEW)	/*Next Ground Target View*/	
KeyName(69,WAYPTVIEW)	/*Next Waypoint View*/	


//PD 19Feb96 - view type select keys

KeyName(72,INSIDETOG)/*Cockpit Camera*/											//PD 19Feb96
//combination key
KeyName(74,INOUTTOG)/*Inside/Outside View Toggle*///inside+enemy-64						//JIM 23Oct96

KeyName(80,OUTSIDETOG)/*Track Camera*/										//PD 19Feb96
//combination key
KeyName(82,PADLOCKTOG)/*Padlock Toggle*/ //outside+enemy-64						//PD 26Sep96

KeyName(88,SATELLITOG)/*Satellite Cam*/										//PD 19Feb96
KeyName(96,CHASETOG)/*Chase Camera*/										//PD 19Feb96
KeyName(104,NOPITTOG)										//PD 19Feb96
/**/KeyName(112,OUTREVLOCKTOG)									//PD 27Jun96

KeyName(114,RESETENEMYVIEW)/*Reset Enemy View*/									//PD 19Feb96
KeyName(115,RESETFRNDVIEW)/*Reset Friend View*/									//PD 19Feb96
KeyName(116,RESETGRNDTVIEW)/*Reset Ground Target View*/									//PD 19Feb96
KeyName(117,RESETWAYPTVIEW)	/*Reset Waypoint View*/								//PD 19Feb96




/**/KeyName(128,KEY_JOYSTICKCONFIG)										//PD 20May96
KeyName(129,KEY_CONFIGMENU)			/*Preferences (Configuration*/											//PD 20May96
KeyName(130,ACCELKEY)				/*Accelerated Mode Toggle*/											//PD 20May96
/**/KeyName(131,AUTOKEY)											//PD 20May96
KeyName(132,CHEATLIFTKEY)			/*Increase Altitude by 1000ft*/										//RDH 21Jul96

KeyName(133,MSGVIEW)/*View of Subject of Current Msg*/											//PD 02Sep96


KeyName(140,DROPBOMB)											//RJS 12Aug96
KeyName(142,GOTOMAPKEY)	/*Map*/											//RDH 03Nov96

/**/KeyName(143,SHAPECHEATTOG)										//RJS 11Nov96
KeyName(144,NEXTSHAPEUP)/*Field of View: Zoom In*/										//RJS 11Nov96
KeyName(145,NEXTSHAPEDN)/*Field of View: Zoom Out*/										//RJS 11Nov96


KeyName(146,ELEVTRIMUP)/*Forward Elevator Trim*/									//ARM 31Jul97
KeyName(147,ELEVTRIMDOWN)/*Aft Elevator Trim*/									//ARM 31Jul97
KeyName(148,AILTRIMUP)/*Right Aileron Trim*/								
KeyName(149,AILTRIMDOWN)/*Left Aileron Trim*/								
KeyName(150,RUDTRIMUP)/*Right Rudder Trim*/								
KeyName(151,RUDTRIMDOWN)/*Left Rudder Trim*/								

KeyName(152,FLAPSUP)	//Decrease Flap Deflection	//CSB 06/10/99	
KeyName(153,FLAPSDOWN)	//Increase Flap Deflection	//CSB 06/10/99	
KeyName(154,GEARUPDOWN)			/*Gear Toggle*/										//ARM 07Apr97
KeyName(155,CANOPYEJECT)
KeyName(156,SPEEDBRAKE)			/*Air Brake*/										//ARM 13Mar97
KeyName(157,LEFTWHEELBRAKE)		/*Left Wheel Brake*/								//ARM 27Feb97
KeyName(158,RIGHTWHEELBRAKE)	/*Right Wheel Brake*/								//ARM 27Feb97
KeyName(159,CYCLEENGINES)
KeyName(160,FUELGUAGESELECTOR)

KeyName(161,LASTWEAPON)/*Previous Weapon*/											//RJS 09Jun97
KeyName(162,NEXTWEAPON)/*Next Weapon*/										//RJS 09Jun97

KeyName(163,RELOADWEAPON)/*Reload Weapons*/									//RJS 10Jun97
KeyName(164,DUMPWEAPONS)/*Dump Weapons*/									//RJS 10Jun97

KeyName(165,RESURRECTKEY)		/*Jump out of  Regeneration(comms)*/										//ARM 05Dec96

KeyName(166,LOOKNE)/*Sticky Look Forward/Right*/												//PD 28Jan97
KeyName(167,LOOKE)/*Sticky Right*/											//PD 28Jan97
KeyName(168,LOOKSE)/*Sticky Look Back/Right*/											//PD 28Jan97
KeyName(169,LOOKS)/*Sticky Look Back*/											//PD 28Jan97
KeyName(170,LOOKSW)/*Sticky Look Back/Left*/											//PD 28Jan97
KeyName(171,LOOKW)/*Sticky Left*/											//PD 28Jan97
KeyName(172,LOOKNW)/*Sticky Look Forward/Left*/											//PD 28Jan97
KeyName(173,LOOKN)/*Sticky Look Forward*/											//PD 28Jan97
KeyName(174,LOOKUPNE)/*Sticky Look Up Forward/Right*/										//PD 28Jan97
KeyName(175,LOOKUPE)/*Sticky Look Up Righ*/										//PD 28Jan97
KeyName(176,LOOKUPSE)/*Sticky Look Up Back/Right*/										//PD 28Jan97
KeyName(177,LOOKUPS)/*Sticky Look Up Back*/										//PD 28Jan97
KeyName(178,LOOKUPSW)/*Sticky Look Up Back/Left*/										//PD 28Jan97
KeyName(179,LOOKUPW)/*Sticky Look Up Left*/										//PD 28Jan97
KeyName(180,LOOKUPNW)/*Sticky Look Up Forward/Left*/										//PD 28Jan97
KeyName(181,LOOKUPN)/*Sticky Look Up Forward*/										//PD 28Jan97

KeyName(182,LOOKUPTOG)/*Look up toggle for Sticky keys*/										//PD 28Jan97
KeyName(183,VIEWMODETOG)/*Panning/Fixed View Toggle*/									//PD 15Jul97
KeyName(184,PANLEFT)/*Pan Left*/									//PD 15Jul97
KeyName(185,PANRIGHT)/*Pan Right*/									//PD 15Jul97
KeyName(186,SUICIDE)/*Stop death sequence(comms)*/										//AMM 19Jun97

KeyName(187,AROTUPRIGHT)/*Alt: Up/Forward and Right*/										//PD 03Sep97
KeyName(188,AROTRIGHT)/*Alt: Right*/
KeyName(189,AROTDNRIGHT)/*Alt: Down/Back and Right*/
KeyName(190,AROTDOWN)/*Alt: Down/Back*/
KeyName(191,AROTDNLEFT)/*Alt: Down/Back and Left*/
KeyName(192,AROTLEFT)/*Alt: Left*/
KeyName(193,AROTUPLEFT)/*Alt: Up/Forward and Left*/
KeyName(194,AROTUP)/*Alt: Up/Forward*/
KeyName(195,AZOOMOUT)/*Alt: Zoom Out*/
KeyName(196,APANLEFT)/*Pan Left in Fixed View Mode*/
KeyName(197,APANRIGHT)/*Pan Right in Fixed View Mode*/										//PD 03Sep97
KeyName(198,ALOOKNE)/*Alt: Forward Right*/										//PD 03Sep97
KeyName(199,ALOOKSE)/*Alt: Back Right*/
KeyName(200,ALOOKS)/*Alt: Back*/
KeyName(201,ALOOKSW)/*Alt: Back Left*/
KeyName(202,ALOOKNW)/*Alt: Forward Left*/
KeyName(203,ALOOKN)	/*Alt: Forward*/										//PD 03Sep97
KeyName(204,ALOOKUPNE)/*Alt: Forward Right Up*/										//PD 03Sep97
KeyName(205,ALOOKUPSE)/*Alt: Back Right Up*/
KeyName(206,ALOOKUPSW)/*Alt: Back Left Up*/
KeyName(207,ALOOKUPNW)/*Alt: Forward Left Up*/										//PD 03Sep97
KeyName(208,ROTRESET2)/*Alt: View Reset*/										//RDH 15Sep97
KeyName(209,TOGGLEWOBBLEVIEW)/*Fixed/Free Camera for f6 View*/								//PD 07Oct97
KeyName(210,PREVENEMYVIEW)/*Previous Enemy View*/									//PD 08Oct97
KeyName(211,PREVFRNDVIEW)/*Previous Friend View*/										//PD 08Oct97
KeyName(212,PREVGRNDTVIEW)/*Previous Ground Target View*/									//PD 08Oct97
KeyName(213,PREVWAYPTVIEW)/*Previous Waypoint View*/									//PD 08Oct97

KeyName(214,FLOORVIEW)/*Sticky Look Down Through Floor Window*/
KeyName(215,HEADOUTVIEWL)
KeyName(216,HEADOUTVIEWR)

KeyName(217,EJECTPILOT)	/*Eject Pilot*/									//RJS 27Jan98
/**/KeyName(218,DETAILDIALS)										//RJS 27Jan98
/**/KeyName(219,DETAILCANOPY)										//RJS 27Jan98
/**/KeyName(220,DETAILPANEL)										//RJS 27Jan98
/**/KeyName(221,DETAILSIDES)										//RJS 27Jan98
/**/KeyName(222,DETAILSIGHT)										//RJS 27Jan98

KeyName(223,IMPACTTOG)/*Impact Toggle*/											//RJS 20Apr98
KeyName(224,CHEATTOG)/*Forward View- no cockpit*/											//RJS 20Apr98
KeyName(225,EXITKEY)/*Exit Game*/											//RJS 20Apr98
KeyName(226,SPINRECOVERY)/*Spin Recovery*/										//RJS 20Apr98

/**/KeyName(227,MENUMINUS)
/**/KeyName(228,MENUPLUS)
/**/KeyName(229,MENUBACK)
KeyName(230,BOXTARGET)/*Box Padlocked item*/										//RJS 05Nov98 //RDH 16/04/99
KeyName(231,RESTARTENGINE)/*Engine restart*/
KeyName(232,RECORDTOGGLE)/*Gun Camera Toggle*/
KeyName(233,RESETRECORD)/*Reset Gun Camera*/

KeyName(234,ACCELKEY2)/*Acclerated Mode on the Map*/											//PD 03Mar99
KeyName(235,RADIOCOMMS)	/*Initiate Radio Communications*/									//RDH 24/03/99
KeyName(236,HUDTOGGLE)/*Head Up InstrumentsToggle*/
KeyName(237,ANYBANDITS)/*Any Bandits*/													  //RDH 10/05/99
KeyName(238,CLEAR)/*Clear?/Clear*/
KeyName(239,BREAK)/*Break*/
KeyName(240,GROUPINFOMSG)/*Group Info Messages*/
KeyName(241,PRECOMBATMSG)/*Precombat Messages*/
KeyName(242,COMBATMSG)/*Combat Messages*/
KeyName(243,POSTCOMBATMSG)/*PostCombat Messages*/
KeyName(244,TOWERMSG)/*Tower Messages*/
KeyName(245,FACMSG)/*FAC  Messages*/													  //RDH 10/05/99
KeyName(246,CYCLETHROUGHWEAPONS)/*Cycle Through Weapons*/													  //RDH 10/05/99
KeyName(247,ESCORTEEVIEW)/*Escortee*/	
KeyName(248,AIUNFRIENDLYVIEW)/*A.I.Enemy View*/	
KeyName(249,SEEMIGS)/*See MiGs on 3d map*/
KeyName(250,TOGGLEMESSAGES)/*toggle displaying of radio message text in the 3d*/
KeyName(251,AROTRESET)/*View Reset*/
KeyName(252,ALOOKE)/*Look Right*/
KeyName(253,ALOOKW)/*Look Left*/
KeyName(254,ALOOKUP)/*Look Up*/
KeyName(255,DETAILDN)/*Decrease 3d detail*/
KeyName(256,VOICETOGGLE)/*Player Voice Toggle*/
KeyName(257,MENUSELECT)		//commented out for neatness [and they where duplicates]

KeyName(258,NOSEGUNNER)
KeyName(259,DORSALGUNNER)
KeyName(260,VENTRALGUNNER)
KeyName(261,EMERGENCYGEAR)
KeyName(262,RESETALLTRIM)/*Zero Elevator, Aileron and Rudder Trim*/
KeyName(263,ELEVATOR_BACK)		/*Elevator Back*/				//RJS 14Dec99
KeyName(264,ELEVATOR_FORWARD)	/*Elevator Forward*/
KeyName(265,AILERON_RIGHT)		/*Aieron Right*/
KeyName(266,AILERON_LEFT)		/*Aileron Left*/
KeyName(267,RUDDER_LEFT)			/*Rudder Left*/
KeyName(268,RUDDER_RIGHT)		/*Rudder Right*/
KeyName(269,SENS_UP)				/*Increase Keyboard Sensitivity*/
KeyName(270,SENS_DOWN)			/*Decrease Keyboard Sensitivity*/
KeyName(271,MOUSEMODETOGGLE)
//DeadCode JIM 31Aug00 KeyName(272,JOYSTICKMODETOGGLE)

// Cockpit keys...
KeyName(300,FK_THROTTLE0)										//RJS 14Dec99
KeyName(301,FK_THROTTLE1)
KeyName(302,FK_PROPPITCH0)
KeyName(303,FK_PROPPITCH1)
KeyName(304,FK_ELEVATORTRIM)
KeyName(305,FK_RUDDERTRIM)
KeyName(306,FK_EMERGENCYUC)
//DEADCODE CSB 20/01/00 KeyName(307,FK_FUELTANKSELECT)
KeyName(308,FK_ARMED)
KeyName(309,FK_LANDING)
KeyName(310,FK_GUNCAM)

KeyName(311,FK_PRIMER0)
KeyName(312,FK_PRIMER1)
KeyName(313,FK_FUELCOCK1)
KeyName(314,FK_FUELCOCK2)
KeyName(315,FK_FUELCOCK3)
KeyName(316,FK_FUELCOCK4)
KeyName(317,FK_ENGINESTARTER0)
KeyName(318,FK_ENGINESTARTER1)
KeyName(319,FK_BOOSTCUTOUT)
KeyName(320,FK_MAG01)
KeyName(321,FK_MAG02)
KeyName(322,FK_MAGS1)
KeyName(323,FK_MAGS2)

KeyName(324,RPM_ZERO)
//DeadCode CSB 03/12/99	KeyName(322,FK_MAG03)
//DeadCode CSB 03/12/99	KeyName(323,FK_MAG04)
//DeadCode CSB 03/12/99	KeyName(324,FK_MAG11)
//DeadCode CSB 03/12/99	KeyName(325,FK_MAG12)
//DeadCode CSB 03/12/99	KeyName(326,FK_MAG13)
//DeadCode CSB 03/12/99	KeyName(327,FK_MAG14)

KeyName(325,KEY_TOGGLE_DESC_TEXT)										//JON 17Oct00

//new keys go here^^^^^^^
KeyName(511,NULLKEY)
KeyName(512,ASCII_NULL)
// 1-30 are special. Use for function keys and misc
KeyName(513,ASCII_F1)
KeyName(514,ASCII_F2)
KeyName(515,ASCII_F3)
KeyName(516,ASCII_F4)
KeyName(517,ASCII_F5)
KeyName(518,ASCII_F6)
KeyName(519,ASCII_F7)
KeyName(520,ASCII_F8)
KeyName(521,ASCII_F9)
KeyName(522,ASCII_F10)
KeyName(523,ASCII_F11)
KeyName(524,ASCII_F12)
KeyName(525,ASCII_ESC)
KeyName(526,ASCII_ENTER)
KeyName(527,ASCII_RETURN)

KeyName(512+'A',ASCII_A)
KeyName(512+'B',ASCII_B)
KeyName(512+'C',ASCII_C)
KeyName(512+'D',ASCII_D)
KeyName(512+'E',ASCII_E)
KeyName(512+'F',ASCII_F)
KeyName(512+'G',ASCII_G)
KeyName(512+'H',ASCII_H)
KeyName(512+'I',ASCII_I)
KeyName(512+'J',ASCII_J)
KeyName(512+'K',ASCII_K)
KeyName(512+'L',ASCII_L)
KeyName(512+'M',ASCII_M)
KeyName(512+'N',ASCII_N)
KeyName(512+'O',ASCII_O)
KeyName(512+'P',ASCII_P)
KeyName(512+'Q',ASCII_Q)
KeyName(512+'R',ASCII_R)
KeyName(512+'S',ASCII_S)
KeyName(512+'T',ASCII_T)
KeyName(512+'U',ASCII_U)
KeyName(512+'V',ASCII_V)
KeyName(512+'W',ASCII_W)
KeyName(512+'X',ASCII_X)
KeyName(512+'Y',ASCII_Y)
KeyName(512+'Z',ASCII_Z)

KeyName(512+'a',ASCII_a)
KeyName(512+'b',ASCII_b)
KeyName(512+'c',ASCII_c)
KeyName(512+'d',ASCII_d)
KeyName(512+'e',ASCII_e)
KeyName(512+'f',ASCII_f)
KeyName(512+'g',ASCII_g)
KeyName(512+'h',ASCII_h)
KeyName(512+'i',ASCII_i)
KeyName(512+'j',ASCII_j)
KeyName(512+'k',ASCII_k)
KeyName(512+'l',ASCII_l)
KeyName(512+'m',ASCII_m)
KeyName(512+'n',ASCII_n)
KeyName(512+'o',ASCII_o)
KeyName(512+'p',ASCII_p)
KeyName(512+'q',ASCII_q)
KeyName(512+'r',ASCII_r)
KeyName(512+'s',ASCII_s)
KeyName(512+'t',ASCII_t)
KeyName(512+'u',ASCII_u)
KeyName(512+'v',ASCII_v)
KeyName(512+'w',ASCII_w)
KeyName(512+'x',ASCII_x)
KeyName(512+'y',ASCII_y)
KeyName(512+'z',ASCII_z)

KeyName(512+'1',ASCII_1)
KeyName(512+'2',ASCII_2)
KeyName(512+'3',ASCII_3)
KeyName(512+'4',ASCII_4)
KeyName(512+'5',ASCII_5)
KeyName(512+'6',ASCII_6)
KeyName(512+'7',ASCII_7)
KeyName(512+'8',ASCII_8)
KeyName(512+'9',ASCII_9)
KeyName(512+'0',ASCII_0)

KeyName(512+' ',ASCII_SPACE)
KeyName(512+'!',ASCII_EXCLAIM)
KeyName(512+'"',ASCII_DBLEQUOTE)
KeyName(512+'%',ASCII_PERCENT)
KeyName(512+'^',ASCII_HAT)
KeyName(512+'&',ASCII_APERSAND)
KeyName(512+'*',ASCII_MULTIPLY)
KeyName(512+'(',ASCII_OPENBRACKET)
KeyName(512+')',ASCII_CLOSEBRACKET)

KeyName(512+'-',ASCII_MINUS)
KeyName(512+'_',ASCII_UNDERLINE)
KeyName(512+'+',ASCII_PLUS)
KeyName(512+'=',ASCII_EQUAL)
KeyName(512+'[',ASCII_OPENSQUARE)
KeyName(512+']',ASCII_CLOSESQUARE)
KeyName(512+'{',ASCII_OPENCURLY)
KeyName(512+'}',ASCII_CLOSECURLY)
KeyName(512+';',ASCII_SEMICOLON)
KeyName(512+':',ASCII_COLON)
KeyName(512+'\'',ASCII_APOS)
KeyName(512+'@',ASCII_AT)
KeyName(512+'~',ASCII_TILDE)
KeyName(512+',',ASCII_COMMA)
KeyName(512+'.',ASCII_FULLSTOP)
KeyName(512+'<',ASCII_LESS)
KeyName(512+'>',ASCII_GREATER)
KeyName(512+'?',ASCII_QUESTION)
KeyName(512+'/',ASCII_FORWARDSLASH)
KeyName(512+'\\',ASCII_BACKSLASH)
KeyName(512+'|',ASCII_PIPE)


KeyName(640,OVERLAY_NULL)
KeyName(641,OVERLAY_OPT1)
KeyName(642,OVERLAY_OPT2)
KeyName(643,OVERLAY_OPT3)
KeyName(644,OVERLAY_OPT4)
KeyName(645,OVERLAY_OPT5)
KeyName(646,OVERLAY_OPT6)
KeyName(647,OVERLAY_OPT7)
KeyName(648,OVERLAY_OPT8)
KeyName(649,OVERLAY_OPT9)
KeyName(650,OVERLAY_OPT0)
KeyName(651,OVERLAY_ESC)
KeyName(652,OVERLAY_UPARROW)
KeyName(653,OVERLAY_DOWNARROW)
KeyName(653,OVERLAY_LEFTARROW)
KeyName(653,OVERLAY_RIGHTARROW)
KeyName(654,OVERLAY_MINUS)
KeyName(655,OVERLAY_PLUS)
KeyName(655,OVERLAY_SPACE)








KeyName(768,TOTALKEYBITFLAGS2)
//DeadCode JIM 22Nov96 };
#undef	KeyName
//------------------------------------------------------------------------------
// Place new 3d key press equate definitions in the list ABOVE
// The first number must be sequential
// The second field is the name used in the 3d
//The mapping to the keyboard keys goes in the next table 
//------------------------------------------------------------------------------
#endif		//file single pass

#ifdef	SPECIAL_KEYMAPS
#include	<dinput.h>
/**/enum	{KEYS_PER_STICK=40};

enum Raw_Keys	{
		Raw_esc		=DIK_ESCAPE   	,	//01,
		Raw_n1		=DIK_1        	,	//02,
		Raw_n2		=DIK_2        	,	//03,
		Raw_n3		=DIK_3        	,	//04,
		Raw_n4		=DIK_4        	,	//05,
		Raw_n5		=DIK_5        	,	//06,
		Raw_n6		=DIK_6        	,	//07,
		Raw_n7		=DIK_7        	,	//08,
		Raw_n8		=DIK_8        	,	//09,
		Raw_n9		=DIK_9        	,	//10,
		Raw_n0		=DIK_0        	,	//11,
		Raw_minus	=DIK_MINUS    	,	//12,
		Raw_equal	=DIK_EQUALS   	,	//13,
		Raw_backspc	=DIK_BACK     	,	//14,
		Raw_tab		=DIK_TAB      	,	//15,
		Raw_q		=DIK_Q        	,	//16,
		Raw_w		=DIK_W        	,	//17,
		Raw_e		=DIK_E        	,	//18,
		Raw_r		=DIK_R        	,	//19,
		Raw_t		=DIK_T        	,	//20,
		Raw_y		=DIK_Y        	,	//21,
		Raw_u		=DIK_U        	,	//22,
		Raw_i		=DIK_I        	,	//23,
		Raw_o		=DIK_O        	,	//24,
		Raw_p		=DIK_P        	,	//25,
		Raw_open	=DIK_LBRACKET 	,	//26,
		Raw_close	=DIK_RBRACKET 	,	//27,
		Raw_enter	=DIK_RETURN   	,	//28,
		Raw_shiftctl=DIK_LCONTROL 	,	//29,
		Raw_a		=DIK_A        	,	//30,
		Raw_s		=DIK_S        	,	//31,
		Raw_d		=DIK_D        	,	//32,
		Raw_f		=DIK_F        	,	//33,
		Raw_g		=DIK_G        	,	//34,
		Raw_h		=DIK_H        	,	//35,
		Raw_j		=DIK_J        	,	//36,
		Raw_k		=DIK_K        	,	//37,
		Raw_l		=DIK_L        	,	//38,
		Raw_semi	=DIK_SEMICOLON	,	//39,
		Raw_quote	=DIK_APOSTROPHE	,	//40,
		Raw_hash	=DIK_GRAVE    	,	//41,
		Raw_shiftlef=DIK_LSHIFT   	,	//42,
		Raw_bslash	=DIK_BACKSLASH	,	//43,
		Raw_z		=DIK_Z        	,	//44,
		Raw_x		=DIK_X        	,	//45,
		Raw_c		=DIK_C        	,	//46,
		Raw_v		=DIK_V        	,	//47,
		Raw_b		=DIK_B        	,	//48,
		Raw_n		=DIK_N        	,	//49,
		Raw_m		=DIK_M        	,	//50,
		Raw_comma	=DIK_COMMA    	,	//51,
		Raw_stop	=DIK_PERIOD   	,	//52,
		Raw_slash	=DIK_SLASH    	,	//53,
		Raw_shiftrig=DIK_RSHIFT   	,	//54,
		Raw_print	=DIK_MULTIPLY 	,	//55,
		Raw_shiftalt=DIK_LMENU    	,	//56,
		Raw_space	=DIK_SPACE    	,	//57,
		Raw_lockcap	=DIK_CAPITAL  	,	//58,
		Raw_f1		=DIK_F1       	,	//59,
		Raw_f2		=DIK_F2       	,	//60,
		Raw_f3		=DIK_F3       	,	//61,
		Raw_f4		=DIK_F4       	,	//62,
		Raw_f5		=DIK_F5       	,	//63,
		Raw_f6		=DIK_F6       	,	//64,
		Raw_f7		=DIK_F7       	,	//65,
		Raw_f8		=DIK_F8       	,	//66,
		Raw_f9		=DIK_F9       	,	//67,
		Raw_f10		=DIK_F10      	,	//68,
		Raw_locknum	=DIK_NUMLOCK 	,	//69,
		Raw_lockscr	=DIK_SCROLL  	,	//70,
		Raw_movehome=DIK_NUMPAD7 	,	//71,
		Raw_moveup	=DIK_NUMPAD8 	,	//72,
		Raw_pageup	=DIK_NUMPAD9 	,	//73,
		Raw_numminus=DIK_SUBTRACT	,	//74,
		Raw_moveleft=DIK_NUMPAD4 	,	//75,
		Raw_movefive=DIK_NUMPAD5 	,	//76,
		Raw_moveright=DIK_NUMPAD6 	,	//77,
		Raw_numplus	=DIK_ADD     	,	//78,
		Raw_moveend	=DIK_NUMPAD1 	,	//79,
		Raw_movedown=DIK_NUMPAD2 	,	//80,
		Raw_pagedown=DIK_NUMPAD3 	,	//81,
		Raw_insert	=DIK_NUMPAD0 	,	//82,
		Raw_delete	=DIK_DECIMAL 	,	//83,
		Raw_DISABLED=DIK_F11+1	,		//00,

		Raw_F11		=DIK_F11	,		//87,	//VF on Jap keyboard
		Raw_F12		=DIK_F12	,		//88,
		Raw_F13		=DIK_F13	,		//100,	//VF on Jap keyboard
		Raw_F14		=DIK_F14	 ,		//101,
		Raw_F15		=DIK_F15	  ,		//102,
//extra keys on japanese keyboard:
		Raw_J_kana		=DIK_KANA,           //112,
		Raw_J_convert	=DIK_CONVERT,		//121,
		Raw_J_noconv	=DIK_NOCONVERT,		//123,
		Raw_J_yen		=DIK_YEN,			//124,
		Raw_J_equal		=DIK_NUMPADEQUALS,  	//141,
		Raw_J_circum	=DIK_CIRCUMFLEX,		//144,
		Raw_J_at		=DIK_AT,				//145,
		Raw_J_colon		=DIK_COLON,			//146,
		Raw_J_under		=DIK_UNDERLINE,		//147,
		Raw_J_kanji		=DIK_KANJI,			//148,
		Raw_J_stop		=DIK_STOP,			//149,
		Raw_J_ax		=DIK_AX,				//150,
		Raw_J_blank		=DIK_UNLABELED,		//151,

		//Were ExtShift in MS-DOS: Called _J_ in Japanese conversion of FCG
		Raw_J_enter		=DIK_NUMPADENTER,	//156,
		Raw_shiftctr		=DIK_RCONTROL,	//157,
		Raw_J_comma		=DIK_NUMPADCOMMA,	//179,
		Raw_J_lockscr	=DIK_DIVIDE,		//181,
		Raw_J_sysreq	=DIK_SYSRQ,			//183,
		Raw_shiftagr	=DIK_RMENU,			//184,
		Raw_J_movehome	=DIK_HOME       ,	//199,
		Raw_J_moveup	=DIK_UP         ,	//200,
		Raw_J_pageup	=DIK_PRIOR      ,	//201,
		Raw_J_moveleft	=DIK_LEFT       ,	//203,
		Raw_J_moveright	=DIK_RIGHT		,	//205,
		Raw_J_moveend	=DIK_END        ,	//207,
		Raw_J_movedown	=DIK_DOWN       ,	//208,
		Raw_J_pagedown	=DIK_NEXT       ,	//209,
		Raw_J_insert	=DIK_INSERT     ,	//210,
		Raw_J_delete	=DIK_DELETE     ,	//211,

		//extra keys on win'95 keyboard:
		Raw_WinL	=DIK_LWIN	,			//219,
		Raw_WinR	=DIK_RWIN	,			//220,
		Raw_WinM	=DIK_APPS	,			//221,


		Raw_A1_Fire		=260,	//260,		//Joystick key codes
		Raw_A1_b1		=261,	//261,
		Raw_A1_b2		=262,	//262,
		Raw_A1_b3		=263,	//263,
		Raw_A1_b4		=264,	//264,
		Raw_A1_b5		=265,	//265,
		Raw_A1_b6		=266,	//266,
		Raw_A1_b7		=267,	//267,
		Raw_A1_b8		=268,	//268,
		Raw_A1_b9		=269,	//269,
		Raw_A1_b10		=270,	//270,
		Raw_A1_b11		=271,	//271,
		Raw_A1_b12		=272,	//272,
		Raw_A1_b13		=273,	//273,
		Raw_A1_b14		=274,	//274,
		Raw_A1_b15		=275,	//275,
		Raw_A1_b16		=276,	//276,
		Raw_A1_b17		=277,	//277,
		Raw_A1_b18		=278,	//278,
		Raw_A1_b19		=279,	//279,
		Raw_A1_b20		=280,	//280,
		Raw_A1_b21		=281,	//281,
		Raw_A1_b22		=282,	//282,
		Raw_A1_b23		=283,	//283,
		Raw_A1_b24		=284,	//284,
		Raw_A1_b25		=285,	//285,
		Raw_A1_b26		=286,	//286,
		Raw_A1_b27		=287,	//287,
		Raw_A1_b28		=288,	//288,
		Raw_A1_b29		=289,	//289,
		Raw_A1_b30		=290,	//290,
		Raw_A1_b31		=291,	//291,
		Raw_A1_b32		=292,	//292,
		Raw_A1_b33		=293,	//293,
		Raw_A1_b34		=294,	//294,
		Raw_A1_b35		=295,	//295,
		Raw_A1_b36		=296,	//296,
		Raw_A1_b37		=297,	//297,
		Raw_A1_b38		=298,	//298,
		Raw_A1_b39		=299,	//299,

		Raw_A2_Fire		=300,	//300,		//Joystick key codes
		Raw_A2_b1		=301,	//301,
		Raw_A2_b2		=302,	//302,
		Raw_A2_b3		=303,	//303,
		Raw_A2_b4		=304,	//304,
		Raw_A2_b5		=305,	//305,
		Raw_A2_b6		=306,	//306,
		Raw_A2_b7		=307,	//307,
		Raw_A2_b8		=308,	//308,
		Raw_A2_b9		=309,	//309,
		Raw_A2_b10		=310,	//310,
		Raw_A2_b11		=311,	//311,
		Raw_A2_b12		=312,	//312,
		Raw_A2_b13		=313,	//313,
		Raw_A2_b14		=314,	//314,
		Raw_A2_b15		=315,	//315,
		Raw_A2_b16		=316,	//316,
		Raw_A2_b17		=317,	//317,
		Raw_A2_b18		=318,	//318,
		Raw_A2_b19		=319,	//319,
		Raw_A2_b20		=320,	//320,
		Raw_A2_b21		=321,	//321,
		Raw_A2_b22		=322,	//322,
		Raw_A2_b23		=323,	//323,
		Raw_A2_b24		=324,	//324,
		Raw_A2_b25		=325,	//325,
		Raw_A2_b26		=326,	//326,
		Raw_A2_b27		=327,	//327,
		Raw_A2_b28		=328,	//328,
		Raw_A2_b29		=329,	//329,

		Raw_A3_Fire		=340,	//340,
		Raw_A3_b1		=341,	//341,
		Raw_A3_b2		=342,	//342,
		Raw_A3_b3		=343,	//343,
		Raw_A3_b4		=344,	//344,
		Raw_A3_b5		=345,	//345,
		Raw_A3_b6		=346,	//346,
		Raw_A3_b7		=347,	//347,
		Raw_A3_b8		=348,	//348,
		Raw_A3_b9		=349,	//349,

		Raw_A4_Fire		=380,	//380,		//Joystick key codes
		Raw_A4_b1		=381,	//381,
		Raw_A4_b2		=382,	//382,
		Raw_A4_b3		=383,	//383,
		Raw_A4_b4		=384,	//384,
		Raw_A4_b5		=385,	//385,
		Raw_A4_b6		=386,	//386,
		Raw_A4_b7		=387,	//387,
		Raw_A4_b8		=388,	//388,
		Raw_A4_b9		=389,	//389,

		Raw_A5_Fire		=420,	//420,		//Joystick key codes
		Raw_A5_b1		=421,	//421,					//First 8 are reserved for buttons
		Raw_A5_b2		=422,	//422,
		Raw_A5_b3		=423,	//423,
		Raw_A5_b4		=424,	//424,
		Raw_A5_b5		=425,	//425,
		Raw_A5_b6		=426,	//426,
		Raw_A5_b7		=427,	//427,
		Raw_A5_b8		=428,	//428,
		Raw_A5_b9		=429,	//429,

		Raw_A5_b39		=429,	//459,

		Raw_A6_Fire		=460,	//460,		//Joystick key codes
		Raw_A6_b1		=461,	//461,					//First 8 are reserved for buttons
		Raw_A6_b2		=462,	//462,
		Raw_A6_b3		=463,	//463,
		Raw_A6_b4		=464,	//464,
		Raw_A6_b5		=465,	//465,
		Raw_A6_b6		=466,	//466,
		Raw_A6_b7		=467,	//467,
		Raw_A6_b8		=468,	//468,
		Raw_A6_b9		=469,	//469,

		Raw_A6_b39		=499,	//499,		//Joystick key codes

		Raw_A7_fire		=500,	//500,		//Joystick 7 can only have 11 keys if no coolie hats!
		Raw_A7_b11		=511,	//511,

		Raw_H10_N		=432,	//432,		//Note stick 5 is limited if>6 hats enabled
		Raw_H9_N		=440,	//440,		//And stick 6 is no longer available.
		Raw_H8_N		=448,	//448,		//10 hats means max 12 buttons	//9 hats allows 20 buttons
		Raw_H7_N		=456,	//456,		//8 hats allows 28 buttons		//7 hats allows 36 buttons

		Raw_H6_N		=464,	//464,		//Note that joystick 6 is limited by the
		Raw_H6_NE		=465,	//465,		//total number of coolie hats attached.
		Raw_H6_E		=466,	//466,		//6 hats leaves 4 buttons
		Raw_H6_SE		=467,	//467,		//5 hats allows 12 buttons
		Raw_H6_S		=468,	//468,		//4 hats allows 20 buttons
		Raw_H6_SW		=469,	//469,		//3 hats allows 28 buttons
		Raw_H6_W		=470,	//470,		//2 hats allows 36 buttons
		Raw_H6_NW		=471,	//471,		//1 hat allows full use of joystick 6
								  		
		Raw_H5_N		=472,	//472,	
		Raw_H5_NE		=473,	//473,
		Raw_H5_E		=474,	//474,
		Raw_H5_SE		=475,	//475,
		Raw_H5_S		=476,	//476,
		Raw_H5_SW		=477,	//477,
		Raw_H5_W		=478,	//478,
		Raw_H5_NW		=479,	//479,

		Raw_H4_N		=480,	//480,
		Raw_H4_NE		=481,	//481,
		Raw_H4_E		=482,	//482,
		Raw_H4_SE		=483,	//483,
		Raw_H4_S		=484,	//484,
		Raw_H4_SW		=485,	//485,
		Raw_H4_W		=486,	//486,
		Raw_H4_NW		=487,	//487,

		Raw_H3_N		=488,	//488,
		Raw_H3_NE		=489,	//489,
		Raw_H3_E		=490,	//490,
		Raw_H3_SE		=491,	//491,
		Raw_H3_S		=492,	//492,
		Raw_H3_SW		=493,	//493,
		Raw_H3_W		=494,	//494,
		Raw_H3_NW		=495,	//495,

		Raw_H2_N		=496,	//496,
		Raw_H2_NE		=497,	//497,
		Raw_H2_E		=498,	//498,
		Raw_H2_SE		=499,	//499,
		Raw_H2_S		=500,	//500,
		Raw_H2_SW		=501,	//501,
		Raw_H2_W		=502,	//502,
		Raw_H2_NW		=503,	//503,

		Raw_H1_N		=504,	//504,
		Raw_H1_NE		=505,	//505,
		Raw_H1_E		=506,	//506,
		Raw_H1_SE		=507,	//507,
		Raw_H1_S		=508,	//508,
		Raw_H1_SW		=509,	//509,
		Raw_H1_W		=510,	//510,
		Raw_H1_NW		=511,	//511,

		Raw_NOMORE	=0,	//0,
		};

#if	SPECIAL_KEYMAPS

#define	KeyMap(keyname,rawname,rawshift)	\
		{Raw_##rawname,KEYSH_BN_##rawshift,keyname},

//DeadCode AMM 07Dec99 #define	KeyAll(keyname,rawname)	\
//DeadCode AMM 07Dec99 		{Raw_##rawname,KEYSH_BN_norm	,keyname},	\
//DeadCode AMM 07Dec99 		{Raw_##rawname,KEYSH_BN_extsh	,keyname},	\
//DeadCode AMM 07Dec99 		{Raw_##rawname,KEYSH_BN_AltL	,keyname},	\
//DeadCode AMM 07Dec99 		{Raw_##rawname,KEYSH_BN_AltGR	,keyname},	\
//DeadCode AMM 07Dec99 		{Raw_##rawname,KEYSH_BN_CtrlL	,keyname},	\
//DeadCode AMM 07Dec99 		{Raw_##rawname,KEYSH_BN_CtrlR	,keyname},	\
//DeadCode AMM 07Dec99 		{Raw_##rawname,KEYSH_BN_ShiftL	,keyname},	\
//DeadCode AMM 07Dec99 		{Raw_##rawname,KEYSH_BN_ShiftR	,keyname},


#define	KeyAll(keyname,rawname)	\
		{Raw_##rawname,KEYSH_BN_norm	,keyname},	\
		{Raw_##rawname,KEYSH_BN_extsh	,keyname},	\
		{Raw_##rawname,KEYSH_BN_AltL	,keyname},	\
		{Raw_##rawname,KEYSH_BN_CtrlL	,keyname},	\
		{Raw_##rawname,KEYSH_BN_ShiftL	,keyname},

//	\
//		{Raw_##rawname,KEYSH_BN_Msg		,keyname},	\
//		{Raw_##rawname,KEYSH_BN_ShMsg	,keyname},	\
//		{Raw_##rawname,KEYSH_BN_Overlay	,keyname},

//Line 900 of keymaps.h
//------------------------------------------------------------------------------
//	Define the physical mapping of the keys in the table below. 
//	Order is unimportant for code but important for us to keep tabs on key usage//RDH 07Aug98
//  3 fields:
//		1)	name of key used in game, as defined in above table
//		2)	name of raw key to be pressed
//		3)	shift key that should be pressed
//			this is one of:
//				norm	-	key with no shift
//				AltL	-	alt key	(used to have seperate laft and right, but not any more!)
//				CtrlL	-	control key
//				ShiftL	-	shift key
//				Msg		-	caps lock: type a message
//				ShMsg	-	caps lock: type a message holding shift
//				Overlay	-	when text menus are active
//				8th state - spare!
//
//	"J_" keys 	are the "gray" home and arrow keys 
//				plus some extra keys defined for the Japanese NEC PC machine.
//
//		If you want a key to work with a number of different shifts,
//		or a number of different keys, then list it separately for each mapping.
//		If you want it for all mappings you can use KeyAll instead of KeyMap
//------------------------------------------------------------------------------
static	KeyMapping	ThisKeyMapping[]	=	{
//------------------------------------------------------------------------------

//shift keys mapped to generate shifts...
//DeadCode AMM 08Dec99 	KeyAll(KeySrc_BN_extsh,lockcap)

	KeyAll(KeySrc_BN_MsgLock,lockcap)

	KeyAll(KeySrc_BN_AltL,shiftalt)
 	KeyAll(KeySrc_BN_AltL,shiftagr)

	KeyAll(KeySrc_BN_CtrlL,shiftctl)
	KeyAll(KeySrc_BN_CtrlL,shiftctr)

	KeyAll(KeySrc_BN_ShiftL,shiftlef)
	KeyAll(KeySrc_BN_ShiftL,shiftrig)

	KeyMap(KeySrc_BN_MsgLock,lockcap,Msg)
	KeyMap(KeySrc_BN_MsgLock,lockcap,ShMsg)


	KeyMap(KeySrc_BN_ShMsgLock,shiftlef,Msg)
	KeyMap(KeySrc_BN_ShMsgLock,shiftrig,Msg)

//Keys put in order to aid administration						//RDH 07Aug98

//------------------------------------------------------------------------------
//Top Line
		KeyMap(RESETVIEW,		esc,	norm)						

		KeyMap(ENEMYVIEW,		f1,		norm)						
		KeyMap(RESETENEMYVIEW,	f1,		CtrlL)						
//DeadCode AMM 07Dec99 		KeyMap(RESETENEMYVIEW,	f1,		CtrlR)						
		KeyMap(PREVENEMYVIEW,	f1,		ShiftL)						
//DeadCode AMM 07Dec99 		KeyMap(PREVENEMYVIEW,	f1,		ShiftR)						
		KeyMap(AIUNFRIENDLYVIEW,	f1,		AltL)						
//DeadCode AMM 07Dec99 		KeyMap(AIUNFRIENDLYVIEW,	f1,		AltGR)						

		KeyMap(FRNDVIEW,		f2,		norm)						
		KeyMap(RESETFRNDVIEW,	f2,		CtrlL)						
//DeadCode AMM 07Dec99 		KeyMap(RESETFRNDVIEW,	f2,		CtrlR)						
		KeyMap(PREVFRNDVIEW,	f2,		ShiftL)						
//DeadCode AMM 07Dec99 		KeyMap(PREVFRNDVIEW,	f2,		ShiftR)						
		KeyMap(ESCORTEEVIEW,	f2,		AltL)						
//DeadCode AMM 07Dec99 		KeyMap(ESCORTEEVIEW,	f2,		AltGR)						


		KeyMap(GRNDTVIEW,		f3,		norm)						
		KeyMap(RESETGRNDTVIEW,	f3,		CtrlL)						
//DeadCode AMM 07Dec99 		KeyMap(RESETGRNDTVIEW,	f3,		CtrlR)						
		KeyMap(PREVGRNDTVIEW,	f3,		ShiftL)						
//DeadCode AMM 07Dec99 		KeyMap(PREVGRNDTVIEW,	f3,		ShiftR)						

		KeyMap(WAYPTVIEW,		f4,		norm)						
		KeyMap(RESETWAYPTVIEW,	f4,		CtrlL)						
//DeadCode AMM 07Dec99 		KeyMap(RESETWAYPTVIEW,	f4,		CtrlR)						
		KeyMap(PREVWAYPTVIEW,	f4,		ShiftL)						
//DeadCode AMM 07Dec99 		KeyMap(PREVWAYPTVIEW,	f4,		ShiftR)						

		KeyMap(MSGVIEW,			f5,		norm)						

		KeyMap(OUTREVLOCKTOG,	f6,		AltL)						
		KeyMap(OUTSIDETOG,		f6,		norm)						
		KeyMap(TOGGLEWOBBLEVIEW,	f6,			ShiftL)				  //RDH 02/06/99
//DeadCode AMM 07Dec99 		KeyMap(TOGGLEWOBBLEVIEW,	f6,			ShiftR)				  //RDH 02/06/99

		KeyMap(INSIDETOG,		f7,		norm)						
		KeyMap(CHEATTOG,		f8,		norm)						
		KeyMap(CHASETOG,		f9,		norm)						
		KeyMap(SATELLITOG,		f10,	norm)						
		KeyMap(IMPACTTOG,		F11,	norm)						
		KeyMap(KEY_CONFIGMENU,	F12,	norm)						

		KeyAll(SCREENSHOT,		J_sysreq)							
		KeyAll(LOOKUPTOG,		lockscr)							
		KeyAll(VIEWMODETOG,		locknum)							
		KeyMap(PANLEFT,			J_lockscr,	norm)			//slash key on number pad				
		KeyMap(PANRIGHT,		print,		norm)						//multiple in number pad		

//------------------------------------------------------------------------------
//numbers

		KeyMap(RPM_ZERO,		bslash,		norm)
		KeyMap(RPM_ZERO,		hash,		norm)

		KeyMap(RPM_10,			n1,			norm)
		KeyMap(RPM_20,			n2,			norm)
		KeyMap(RPM_30,			n3,			norm)
		KeyMap(RPM_40,			n4,			norm)
		KeyMap(RPM_50,			n5,			norm)
		KeyMap(RPM_60,			n6,			norm)
		KeyMap(RPM_70,			n7,			norm)
		KeyMap(RPM_80,			n8,			norm)
		KeyMap(RPM_90,			n9,			norm)
		KeyMap(RPM_00,			n0,			norm)

//DeadCode DAW 19Jun99 #if	defined(NDEBUG)
		KeyMap(GROUPINFOMSG,	n1,			ShiftL)
		KeyMap(PRECOMBATMSG,	n2,			ShiftL)
		KeyMap(COMBATMSG,		n3,			ShiftL)
		KeyMap(POSTCOMBATMSG,	n4,			ShiftL)
		KeyMap(TOWERMSG,		n5,			ShiftL)
		KeyMap(FACMSG,			n6,			ShiftL)
//DeadCode DAW 19Jun99 #endif
//DeadCode AMM 07Dec99 		KeyMap(GROUPINFOMSG,	n1,			ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(PRECOMBATMSG,	n2,			ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(COMBATMSG,		n3,			ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(POSTCOMBATMSG,	n4,			ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(TOWERMSG,		n5,			ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(FACMSG,			n6,			ShiftR)

		KeyMap(AROTDNLEFT,		n1,			AltL)
		KeyMap(AROTDOWN,		n2,			AltL)
		KeyMap(AROTDNRIGHT,		n3,			AltL)
		KeyMap(AROTLEFT,		n4,			AltL)
		KeyMap(AROTRESET,		n5,			AltL)
		KeyMap(AROTRIGHT,		n6,			AltL)
		KeyMap(AROTUPLEFT,		n7,			AltL)
		KeyMap(AROTUP,			n8,			AltL)
		KeyMap(AROTUPRIGHT,		n9,			AltL)

		KeyMap(AROTDNLEFT,		n1,			AltL)
		KeyMap(AROTDOWN,		n2,			AltL)
		KeyMap(AROTDNRIGHT,		n3,			AltL)
		KeyMap(AROTLEFT,		n4,			AltL)
		KeyMap(AROTRESET,		n5,			AltL)
		KeyMap(AROTRIGHT,		n6,			AltL)
		KeyMap(AROTUPLEFT,		n7,			AltL)
		KeyMap(AROTUP,			n8,			AltL)
		KeyMap(AROTUPRIGHT,		n9,			AltL)

		KeyMap(ALOOKSW,			n1,			CtrlL)
		KeyMap(ALOOKS,	 		n2,			CtrlL)
		KeyMap(ALOOKSE,			n3,			CtrlL)
		KeyMap(ALOOKW,			n4,			CtrlL)
		KeyMap(ALOOKUP,			n5,			CtrlL)
		KeyMap(ALOOKE,			n6,			CtrlL)
		KeyMap(ALOOKNW,			n7,			CtrlL)
		KeyMap(ALOOKN,	 		n8,			CtrlL)
		KeyMap(ALOOKNE,			n9,			CtrlL)

		KeyMap(ALOOKSW,			n1,			CtrlL)
		KeyMap(ALOOKS,	 		n2,			CtrlL)
		KeyMap(ALOOKSE,			n3,			CtrlL)
		KeyMap(ALOOKW,			n4,			CtrlL)
		KeyMap(ALOOKUP,			n5,			CtrlL)
		KeyMap(ALOOKE,			n6,			CtrlL)
		KeyMap(ALOOKNW,			n7,			CtrlL)
		KeyMap(ALOOKN,	 		n8,			CtrlL)
		KeyMap(ALOOKNE,			n9,			CtrlL)

		KeyMap(MAXPROPPITCH,	n9,			ShiftL)
//DeadCode AMM 07Dec99 		KeyMap(MAXPROPPITCH,	n9,			ShiftR)
		KeyMap(MINPROPPITCH,	n0,			ShiftL)
//DeadCode AMM 07Dec99 		KeyMap(MINPROPPITCH,	n0,			ShiftR)

//------------------------------------------------------------------------------
//letters

		KeyAll(ANYBANDITS,			a)							  //RDH 10/05/99

		KeyMap(DROPBOMB,			b,			norm)

		KeyMap(RECORDTOGGLE,		c,			norm)
		KeyMap(SHAPECHEATTOG,		c,			CtrlL)
//DeadCode AMM 07Dec99 		KeyMap(SHAPECHEATTOG,		c,			CtrlR)

		KeyMap(SPEEDBRAKE,		 	d,			norm)
		KeyMap(DETAILDN,		 	d,			ShiftL)
//DeadCode AMM 07Dec99 		KeyMap(DETAILDN,		 	d,			ShiftR)
		KeyMap(DETAILUP,			d,			CtrlL)
//DeadCode AMM 07Dec99 		KeyMap(DETAILUP,			d,			CtrlR)

		KeyMap(CYCLEENGINES,		e,			norm)
		KeyMap(EJECTPILOT,			e,			CtrlL)
//DeadCode AMM 07Dec99 		KeyMap(EJECTPILOT,			e,			CtrlR)

		KeyMap(FLAPSUP,				f,			norm)				//RJS 23May00	
		KeyMap(FUELGUAGESELECTOR,	f,			CtrlL)
//DeadCode AMM 07Dec99 		KeyMap(FUELGUAGESELECTOR,	f,			CtrlR)

		KeyMap(GEARUPDOWN,			g,			norm)
		KeyMap(EMERGENCYGEAR,		g,			CtrlL)
//DeadCode AMM 07Dec99 		KeyMap(EMERGENCYGEAR,		g,			CtrlR)

		KeyMap(HUDTOGGLE,			h,			norm)

		KeyMap(INFOPANEL,			i,			norm)

		KeyMap(RESURRECTKEY,		j,			norm)

		KeyMap(SENS_UP,				k,			norm)
		KeyMap(SENS_DOWN,			k,			ShiftL)
//DeadCode AMM 07Dec99 		KeyMap(SENS_DOWN,			k,			ShiftR)

		KeyMap(FLOORVIEW,			l,			norm)

		KeyMap(GOTOMAPKEY,			m,			norm)
		KeyMap(TOGGLEMESSAGES,		m,			ShiftL)
//DeadCode AMM 07Dec99 		KeyMap(TOGGLEMESSAGES,		m,			ShiftR)
		KeyMap(SEEMIGS,				m,			CtrlL)
//DeadCode AMM 07Dec99 		KeyMap(SEEMIGS,				m,			CtrlR)

		KeyMap(CYCLETHROUGHWEAPONS,	n,			norm)

		KeyMap(CANOPYEJECT,			o,			norm)

		KeyAll(PAUSEKEY,			p)
		KeyMap(SCREENSHOT,			p,			CtrlL)
//DeadCode AMM 07Dec99 		KeyMap(SCREENSHOT,			p,			CtrlR)

		KeyMap(HEADOUTVIEWL,		q,			norm)

		KeyMap(RADIOCOMMS,			r,			norm)
		KeyMap(RELOADWEAPON,		r,			CtrlL)				  //RDH 16/04/99
//DeadCode AMM 07Dec99 		KeyMap(RELOADWEAPON,		r,			CtrlR)				  //RDH 16/04/99

		KeyMap(SUICIDE,				s,			norm)
		KeyMap(SPINRECOVERY,		s,			ShiftL)

		KeyMap(BOXTARGET,			t,			ShiftL)					//JON 17Oct00
		KeyMap(KEY_TOGGLE_DESC_TEXT,t,			norm)		//JON 17Oct00

		KeyAll(CHEATLIFTKEY,		u)

		KeyMap(FLAPSDOWN,			v,			norm)				//RJS 23May00	
		KeyMap(VOICETOGGLE,			v,			CtrlL)
//DeadCode AMM 07Dec99 		KeyMap(VOICETOGGLE,			v,			CtrlR)

		KeyMap(HEADOUTVIEWR,		w,			norm)
		KeyMap(DUMPWEAPONS,			w,			CtrlL)					  //RDH 16/04/99
//DeadCode AMM 07Dec99 		KeyMap(DUMPWEAPONS,			w,			CtrlR)					  //RDH 16/04/99
//use x for video reset
		KeyMap(RESETRECORD,			x,			norm)
		KeyMap(EXITKEY,				x,			AltL)

//DeadCode JIM 31Aug00 		KeyMap(JOYSTICKMODETOGGLE,	y,			norm)

		KeyMap(BREAK,				z,			norm)

//------------------------------------------------------------------------------
//miscellaneous
//From top to bottom on keyboard

		KeyMap(ACCELKEY,			tab,		norm)
		KeyMap(ACCELKEY2,			tab,		ShiftL)
//DeadCode AMM 07Dec99 		KeyMap(ACCELKEY2,			tab,		ShiftR)

		KeyMap(RPM_DOWN,			minus,		norm)
		KeyMap(PROPPITCHUP,			minus,		ShiftL)	//CSB 05/10/99	
//DeadCode AMM 07Dec99 		KeyMap(PROPPITCHUP,			minus,		ShiftR)	//CSB 05/10/99	
		KeyMap(APANLEFT,			minus,		AltL)
//DeadCode AMM 07Dec99 		KeyMap(APANLEFT,			minus,		AltGR)

		KeyMap(RPM_UP,				equal,		norm)
		KeyMap(PROPPITCHDOWN,		equal,		ShiftL)	//CSB 05/10/99	
//DeadCode AMM 07Dec99 		KeyMap(PROPPITCHDOWN,		equal,		ShiftR)	//CSB 05/10/99	
		KeyMap(APANRIGHT,			equal,		AltL)
//DeadCode AMM 07Dec99 		KeyMap(APANRIGHT,			equal,		AltGR)

		KeyMap(INOUTTOG,			backspc,	norm)

		KeyMap(LASTWEAPON,			open,		norm)

		KeyMap(NEXTWEAPON,			close,		norm)

		KeyMap(PADLOCKTOG,			enter,		norm)

		KeyMap(LEFTWHEELBRAKE,		comma,		norm)	//CSB 13/01/99
		KeyMap(RIGHTWHEELBRAKE,		stop,		norm)	//CSB 13/01/99


		KeyMap(CLEAR,  				slash,		norm)

		KeyAll(SHOOT,				space)

//------------------------------------------------------------------------------
//numberpad


		KeyMap(ROTDOWN,				movedown,		norm)
		KeyMap(ROTUP,				moveup,			norm)
		KeyMap(ROTRIGHT,			moveright,		norm)
		KeyMap(ROTLEFT,				moveleft,		norm)
		KeyMap(ROTDNLEFT,			moveend,		norm)
		KeyMap(ROTDNRIGHT,			pagedown,		norm)
		KeyMap(ROTUPLEFT,			movehome,		norm)
		KeyMap(ROTUPRIGHT,			pageup,			norm)
		KeyMap(ZOOMOUT,				numplus,		norm)
		KeyMap(ZOOMIN,				numminus,		norm)
		KeyMap(ROTRESET,			movefive, 		norm)
		KeyMap(RUDDER_LEFT,			insert,			norm)
		KeyMap(RUDDER_RIGHT,		delete,			norm)
//Dead		KeyMap(DROPBOMB,			J_enter,		norm)

		KeyMap(BIGROTDOWN,			movedown,	 	ShiftL)
		KeyMap(BIGROTUP,			moveup,		 	ShiftL)
		KeyMap(BIGROTRIGHT,			moveright,	 	ShiftL)
		KeyMap(BIGROTLEFT,			moveleft,	 	ShiftL)
		KeyMap(BIGROTDNLEFT,		moveend, 		ShiftL)
		KeyMap(BIGROTDNRIGHT,		pagedown,		ShiftL)
		KeyMap(BIGROTUPLEFT, 		movehome,		ShiftL)
		KeyMap(BIGROTUPRIGHT,		pageup,	 		ShiftL)
		KeyMap(BIGZOOMOUT,	 		numplus, 		ShiftL)
		KeyMap(BIGZOOMIN,	 		numminus,		ShiftL)
		KeyMap(ROTRESET,			movefive,		ShiftL)

//DeadCode AMM 07Dec99 		KeyMap(BIGROTDOWN,	 		movedown,	 	ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(BIGROTUP,	 		moveup,		 	ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(BIGROTRIGHT,	 		moveright,	 	ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(BIGROTLEFT,	 		moveleft, 	 	ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(BIGROTDNLEFT, 		moveend,  		ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(BIGROTDNRIGHT,		pagedown, 		ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(BIGROTUPLEFT, 		movehome, 		ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(BIGROTUPRIGHT,		pageup,	  		ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(BIGZOOMOUT,	 		numplus,  		ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(BIGZOOMIN,	 		numminus, 		ShiftR)
//DeadCode AMM 07Dec99 		KeyMap(ROTRESET2,			movefive,		ShiftR)

		KeyMap(NEXTSHAPEUP,			numplus,		CtrlL)
		KeyMap(NEXTSHAPEDN,			numminus,		CtrlL)

//DeadCode AMM 07Dec99 		KeyMap(NEXTSHAPEDN,			numminus,		CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(NEXTSHAPEUP,			numplus,		CtrlR)

//Gunner
//		KeyMap(NOSEGUNNER,			moveup,			norm)
//		KeyMap(DORSALGUNNER,		movefive,		norm)
//		KeyMap(VENTRALGUNNER,		movedown,		norm)


//------------------------------------------------------------------------------
//arrow keys
		KeyAll(AILERON_LEFT,		J_moveleft)
		KeyAll(AILERON_RIGHT,		J_moveright)
		KeyAll(ELEVATOR_FORWARD,	J_moveup)
		KeyAll(ELEVATOR_BACK,		J_movedown)


//------------------------------------------------------------------------------
//6 key pad

		KeyMap(LOOKNE,			J_pageup,			norm)
		KeyMap(LOOKSE,			J_pagedown,			norm)
		KeyMap(LOOKS,			J_moveend,			norm)
		KeyMap(LOOKSW,			J_delete,			norm)
		KeyMap(LOOKNW,			J_insert,			norm)
		KeyMap(LOOKN,			J_movehome,			norm)

		KeyMap(ELEVTRIMDOWN,	J_moveend,			CtrlL)
		KeyMap(ELEVTRIMUP,		J_movehome,			CtrlL)
		KeyMap(AILTRIMDOWN,		J_insert,			CtrlL)
		KeyMap(AILTRIMUP,		J_pageup,			CtrlL)
		KeyMap(RUDTRIMDOWN,		J_delete,			CtrlL)
		KeyMap(RUDTRIMUP,		J_pagedown,			CtrlL)

//DeadCode AMM 07Dec99 		KeyMap(ELEVTRIMDOWN,	J_moveend,			CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(ELEVTRIMUP,		J_movehome,			CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(AILTRIMDOWN,		J_insert,			CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(AILTRIMUP,		J_pageup,			CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(RUDTRIMDOWN,		J_delete,			CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(RUDTRIMUP,		J_pagedown,			CtrlR)

		KeyMap(RESETALLTRIM,	J_moveend,			AltL)
//DeadCode AMM 07Dec99 		KeyMap(RESETALLTRIM,	J_moveend,			AltGR)

		KeyMap(LOOKE,			moveright,			AltL)
		KeyMap(LOOKW,			moveleft,			AltL)
//DeadCode AMM 07Dec99 		KeyMap(LOOKE,			moveright,			AltGR)
//DeadCode AMM 07Dec99 		KeyMap(LOOKW,			moveleft,			AltGR)


		KeyMap(LOOKUPNE,		pageup,				CtrlL)
		KeyMap(LOOKUPE,			moveright,			CtrlL)
		KeyMap(LOOKUPSE,		pagedown,		 	CtrlL)
		KeyMap(LOOKUPS,			movedown,		  	CtrlL)
		KeyMap(LOOKUPSW,		moveend,			CtrlL)
		KeyMap(LOOKUPW,			moveleft,			CtrlL)
		KeyMap(LOOKUPNW,		movehome,			CtrlL)
		KeyMap(LOOKUPN,			moveup,				CtrlL)

// message mode keys

		KeyMap(ASCII_ESC, 		esc, 				Msg)
		KeyMap(ASCII_ESC, 		esc, 				ShMsg)
		KeyMap(ASCII_RETURN, 	enter,				Msg)
		KeyMap(ASCII_RETURN, 	enter,				ShMsg)
		KeyMap(ASCII_a,			a,					Msg)
		KeyMap(ASCII_A,			a,					ShMsg)
		KeyMap(ASCII_b,			b,					Msg)
		KeyMap(ASCII_B,			b,					ShMsg)
		KeyMap(ASCII_c,			c,					Msg)
		KeyMap(ASCII_C,			c,					ShMsg)
		KeyMap(ASCII_d,			d,					Msg)
		KeyMap(ASCII_D,			d,					ShMsg)
		KeyMap(ASCII_e,			e,					Msg)
		KeyMap(ASCII_E,			e,					ShMsg)
		KeyMap(ASCII_f,			f,					Msg)
		KeyMap(ASCII_F,			f,					ShMsg)
		KeyMap(ASCII_g,			g,					Msg)
		KeyMap(ASCII_G,			g,					ShMsg)
		KeyMap(ASCII_h,			h,					Msg)
		KeyMap(ASCII_H,			h,					ShMsg)
		KeyMap(ASCII_i,			i,					Msg)
		KeyMap(ASCII_I,			i,					ShMsg)
		KeyMap(ASCII_j,			j,					Msg)
		KeyMap(ASCII_J,			j,					ShMsg)
		KeyMap(ASCII_k,			k,					Msg)
		KeyMap(ASCII_K,			k,					ShMsg)
		KeyMap(ASCII_l,			l,					Msg)
		KeyMap(ASCII_L,			l,					ShMsg)
		KeyMap(ASCII_m,			m,					Msg)
		KeyMap(ASCII_M,			m,					ShMsg)
		KeyMap(ASCII_n,			n,					Msg)
		KeyMap(ASCII_N,			n,					ShMsg)
		KeyMap(ASCII_o,			o,					Msg)
		KeyMap(ASCII_O,			o,					ShMsg)
		KeyMap(ASCII_p,			p,					Msg)
		KeyMap(ASCII_P,			p,					ShMsg)
		KeyMap(ASCII_q,			q,					Msg)
		KeyMap(ASCII_Q,			q,					ShMsg)
		KeyMap(ASCII_r,			r,					Msg)
		KeyMap(ASCII_R,			r,					ShMsg)
		KeyMap(ASCII_s,			s,					Msg)
		KeyMap(ASCII_S,			s,					ShMsg)
		KeyMap(ASCII_t,			t,					Msg)
		KeyMap(ASCII_T,			t,					ShMsg)
		KeyMap(ASCII_u,			u,					Msg)
		KeyMap(ASCII_U,			u,					ShMsg)
		KeyMap(ASCII_v,			v,					Msg)
		KeyMap(ASCII_V,			v,					ShMsg)
		KeyMap(ASCII_w,			w,					Msg)
		KeyMap(ASCII_W,			w,					ShMsg)
		KeyMap(ASCII_x,			x,					Msg)
		KeyMap(ASCII_X,			x,					ShMsg)
		KeyMap(ASCII_y,			y,					Msg)
		KeyMap(ASCII_Y,			y,					ShMsg)
		KeyMap(ASCII_z,			z,					Msg)
		KeyMap(ASCII_Z,			z,					ShMsg)

		KeyMap(ASCII_1,			n1,					Msg)
		KeyMap(ASCII_2,			n2,					Msg)
		KeyMap(ASCII_3,			n3,					Msg)
		KeyMap(ASCII_4,			n4,					Msg)
		KeyMap(ASCII_5,			n5,					Msg)
		KeyMap(ASCII_6,			n6,					Msg)
		KeyMap(ASCII_7,			n7,					Msg)
		KeyMap(ASCII_8,			n8,					Msg)
		KeyMap(ASCII_9,			n9,					Msg)
		KeyMap(ASCII_0,			n0,					Msg)

		KeyMap(ASCII_EXCLAIM,	n1,					ShMsg)
		KeyMap(ASCII_DBLEQUOTE,	n2,					ShMsg)
		KeyMap(ASCII_PERCENT,	n5,					ShMsg)
		KeyMap(ASCII_HAT,		n6,					ShMsg)
		KeyMap(ASCII_APERSAND,	n7,					ShMsg)
		KeyMap(ASCII_MULTIPLY,	n8,					ShMsg)
		KeyMap(ASCII_OPENBRACKET,	n9,				ShMsg)
		KeyMap(ASCII_CLOSEBRACKET,	n0,				ShMsg)

		KeyMap(ASCII_MINUS,		minus,				Msg)
		KeyMap(ASCII_EQUAL,		equal,				Msg)
		KeyMap(ASCII_UNDERLINE,	minus,				ShMsg)
		KeyMap(ASCII_PLUS,		equal,				ShMsg)
		KeyMap(ASCII_OPENSQUARE,open,				Msg)
		KeyMap(ASCII_OPENCURLY,	open,				ShMsg)
		KeyMap(ASCII_CLOSESQUARE,	close,				Msg)
		KeyMap(ASCII_CLOSECURLY,	close,				ShMsg)
		KeyMap(ASCII_SEMICOLON,		semi,				Msg)
		KeyMap(ASCII_COLON,			semi,				ShMsg)
		KeyMap(ASCII_APOS,			quote,				Msg)
		KeyMap(ASCII_AT,			quote,				ShMsg)
		KeyMap(ASCII_TILDE,			hash,				ShMsg)
		KeyMap(ASCII_COMMA,			comma,				Msg)
		KeyMap(ASCII_LESS,			comma,				ShMsg)
		KeyMap(ASCII_FULLSTOP,		stop,				Msg)
		KeyMap(ASCII_GREATER,		stop,				ShMsg)
		KeyMap(ASCII_FORWARDSLASH,	slash,				Msg)
		KeyMap(ASCII_QUESTION,		slash,				ShMsg)
		KeyMap(ASCII_BACKSLASH,		bslash,				Msg)
		KeyMap(ASCII_PIPE,			bslash,				ShMsg)

		KeyMap(ASCII_SPACE,		space,				ShMsg)

// overlay mode keys

		KeyMap(OVERLAY_OPT1,		n1,				Overlay)
		KeyMap(OVERLAY_OPT2,		n2,				Overlay)
		KeyMap(OVERLAY_OPT3,		n3,				Overlay)
		KeyMap(OVERLAY_OPT4,		n4,				Overlay)
		KeyMap(OVERLAY_OPT5,		n5,				Overlay)
		KeyMap(OVERLAY_OPT6,		n6,				Overlay)
		KeyMap(OVERLAY_OPT7,		n7,				Overlay)
		KeyMap(OVERLAY_OPT8,		n8,				Overlay)
		KeyMap(OVERLAY_OPT9,		n9,				Overlay)
		KeyMap(OVERLAY_OPT0,		n0,				Overlay)
		KeyMap(OVERLAY_ESC,			esc,			Overlay)
		KeyMap(OVERLAY_UPARROW,		moveup,			Overlay)
		KeyMap(OVERLAY_DOWNARROW,	movedown,		Overlay)
		KeyMap(OVERLAY_LEFTARROW,	moveleft,		Overlay)
		KeyMap(OVERLAY_RIGHTARROW,	moveright,		Overlay)
		KeyMap(OVERLAY_MINUS,	 	minus,			Overlay)
		KeyMap(OVERLAY_PLUS,	 	equal,			Overlay)
		KeyMap(OVERLAY_SPACE,	 	space,			Overlay)



//DeadCode AMM 07Dec99 		KeyMap(LOOKUPNE,		pageup,				CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(LOOKUPE,			moveright,			CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(LOOKUPSE,		pagedown,		 	CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(LOOKUPS,			movedown,		  	CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(LOOKUPSW,		moveend,			CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(LOOKUPW,			moveleft,			CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(LOOKUPNW,		movehome,			CtrlR)
//DeadCode AMM 07Dec99 		KeyMap(LOOKUPN,			moveup,				CtrlR)

//DeadCode AMM 07Dec99 //DEAD		KeyMap(ROOKUPNE,		pageup,				CtrlR)
//DeadCode AMM 07Dec99 //DEAD		KeyMap(ROOKUPE,			moveright,			CtrlR)
//DeadCode AMM 07Dec99 //DEAD		KeyMap(ROOKUPSE,		pagedown,		 	CtrlR)
//DeadCode AMM 07Dec99 //DEAD		KeyMap(ROOKUPS,			movedown,		  	CtrlR)
//DeadCode AMM 07Dec99 //DEAD		KeyMap(ROOKUPSW,		moveend,			CtrlR)
//DeadCode AMM 07Dec99 //DEAD		KeyMap(ROOKUPW,			moveleft,			CtrlR)
//DeadCode AMM 07Dec99 //DEAD		KeyMap(ROOKUPNW,		movehome,			CtrlR)
//DeadCode AMM 07Dec99 //DEAD		KeyMap(ROOKUPN,			moveup,				CtrlR)

//------------------------------------------------------------------------------
//Joystick keys:
// First joystick
		KeyAll(SHOOT,			A1_Fire)			//Joystick key codes
		KeyAll(ROTRESET2,		A1_b1)						//First 8 are reserved for buttons
		KeyAll(PADLOCKTOG,		A1_b2)
		KeyAll(INOUTTOG,		A1_b3)
		KeyAll(ELEVTRIMUP,		A1_b4)
 		KeyAll(FLOORVIEW,		A1_b5)
		KeyAll(ELEVTRIMDOWN,	A1_b6)
		KeyAll(DROPBOMB,		A1_b7)
		KeyAll(SPEEDBRAKE,		A1_b8)
		KeyAll(RESETALLTRIM,	A1_b9)

		KeyAll(ROTUP,		H1_N)					//second 8 are reserved for first hat
		KeyAll(ROTUPRIGHT ,	H1_NE)
		KeyAll(ROTRIGHT,	H1_E)
		KeyAll(ROTDNRIGHT ,	H1_SE)
		KeyAll(ROTDOWN,		H1_S)
		KeyAll(ROTDNLEFT ,	H1_SW)
		KeyAll(ROTLEFT,		H1_W)
		KeyAll(ROTUPLEFT ,	H1_NW)

		KeyAll(LOOKN,		H2_N)					//third 8 are reserved for 2nd hat
		KeyAll(LOOKNE ,		H2_NE)
//DeadCode AMM 2Aug00 		KeyAll(LOOKW,		H2_E)
		KeyAll(LOOKE,		H2_E)
//DeadCode AMM 2Aug00 		KeyAll(LOOKSW,		H2_SE)
		KeyAll(LOOKSE,		H2_SE)
		KeyAll(LOOKS,		H2_S)
		KeyAll(LOOKSW,		H2_SW)
		KeyAll(LOOKW,		H2_W)
		KeyAll(LOOKNW,		H2_NW)

//DeadCode AMM 2Aug00 		KeyAll(GROUPINFOMSG,	H3_N)					//4th 8 are reserved for 3rd hat
//DeadCode AMM 2Aug00 		KeyAll(PRECOMBATMSG,	H3_NE)
//DeadCode AMM 2Aug00 		KeyAll(COMBATMSG,		H3_E)
//DeadCode AMM 2Aug00 		KeyAll(POSTCOMBATMSG,	H3_SE)
//DeadCode AMM 2Aug00 		KeyAll(TOWERMSG,		H3_S)
//DeadCode AMM 2Aug00 		KeyAll(FACMSG,			H3_SW)
//DeadCode AMM 2Aug00 		KeyAll(GOTOMAPKEY,		H3_W)
//DeadCode AMM 2Aug00 		KeyAll(KEY_CONFIGMENU,	H3_NW)

		KeyAll(FLAPSUP,			H3_N)					//4th 8 are reserved for 3rd hat
		KeyAll(NEXTWEAPON,		H3_NE)
		KeyAll(NEXTWEAPON,		H3_E)
		KeyAll(NEXTWEAPON,		H3_SE)
		KeyAll(FLAPSDOWN,		H3_S)
		KeyAll(LASTWEAPON,		H3_SW)
		KeyAll(LASTWEAPON,		H3_W)
		KeyAll(LASTWEAPON,		H3_NW)

//First mouse:
		KeyAll(MENUSELECT,		A2_Fire)			//Joystick key codes
		KeyAll(MOUSEMODETOGGLE,	A2_b1)
		KeyAll(ROTRESET2,		A2_b2)
//DEADCODE  01/11/99 		KeyAll(WINGSPANDOWN,A2_b1)						//First 8 are reserved for buttons
//DEADCODE  01/11/99 		KeyMap(WINGSPANUP,	A2_b1,ShiftL)
//DEADCODE AMM 13/12/99 		KeyAll(SUICIDE,		A2_b2)

//Third analogue input device										  //JIM 13/05/99
		KeyAll(SHOOT,			A3_Fire)			//Joystick key codes
		KeyAll(ROTRESET,		A3_b1)						//First 8 are reserved for buttons
		KeyAll(PADLOCKTOG,		A3_b2)
		KeyAll(INOUTTOG,		A3_b3)
		KeyAll(ELEVTRIMUP,		A3_b4)
 		KeyAll(FLOORVIEW,		A3_b5)
		KeyAll(ELEVTRIMDOWN,	A3_b6)
		KeyAll(DROPBOMB,		A1_b7)
		KeyAll(SPEEDBRAKE,		A3_b8)
		KeyAll(RESETALLTRIM,	A3_b9)
//DeadCode JIM 15Oct00 		KeyAll(SHOOT,			A3_Fire)			//Joystick key codes
//DeadCode JIM 15Oct00 		KeyAll(ROTRESET,		A3_b1)						//First 8 are reserved for buttons
//DeadCode JIM 15Oct00 		KeyAll(PADLOCKTOG,		A3_b2)
//DeadCode JIM 15Oct00 		KeyAll(INOUTTOG,		A3_b3)
//DEADCODE  01/11/99 		KeyAll(ELEVTRIMFWD,		A3_b4)
//DEADCODE  01/11/99 		KeyAll(GUNRANGEUP,		A3_b5)


//------------------------------------------------------------------------------
				{0,0,0}			};
//------------------------------------------------------------------------------
//	Define the physical mapping of the keys in the table below. 
//	Order is unimportant for code but important for us to keep tabs on key usage//RDH 07Aug98
//  3 fields:
//		1)	name of key used in game, as defined in above table
//		2)	name of raw key to be pressed
//		3)	shift key that should be pressed
//			this is one of:
//				norm	-	white key with no shift
//				AltL	-	alt key
//				CtrlL	-	control key
//				ShiftL	-	shift key
//				Msg		-	caps lock: type a message
//				ShMsg	-	caps lock: type a message holding shift
//				Overlay	-	when text menus are active
//				8th state - spare!
//
//		If you want a key to work with a number of different shifts,
//		or a number of different keys, then list it separately for each mapping.
//		If you want it for all mappings you can use KeyAll instead of KeyMap
//------------------------------------------------------------------------------
#undef	KeyMap
#undef	KeyAll
#endif
#undef	SPECIAL_KEYMAPS
#endif

