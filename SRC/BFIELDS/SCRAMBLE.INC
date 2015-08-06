//------------------------------------------------------------------------------
//Filename       scramble.inc
//System         
//Author         R. Hyde 
//Date           Sun 25 Aug 1996
//Description    
//------------------------------------------------------------------------------
//Basic Trainin x 3
//	RAF	Take-off
//	RAF	Landing
//	RAF	Circuits around field and Landing
//	LUF	Take-off
//	LUF	Landing
//	LUF	Circuits around field and Landing
//Airfield Training x 4
//	RAF	Squadron takeoff
//	RAF	Landing in bad weather
//	RAF	Landing with an engine failure
//	RAF	Landing with heavy damage
//	LUF	Squadron takeoff
//	LUF	Landing in bad weather
//	LUF	Landing with an engine failure
//	LUF	Landing with heavy damage
//Familiarisation x 3
//	RAF 	Follow the leader
//	RAF	Flying in formation
//	RAF	Hedge-hopping		
//	LUF 	Follow the leader
//	LUF	Flying in formation
//	LUf	Hedge-hopping		
//Combat x 5
//	Turkey
//	One on One
//	Random advantage
//	RAF advantage
//	LW advantage
//GroundWork x 4	
//	Escort bombers
//	Dive bomb attack
//	Anti shipping
//	Very low level surprise attack by fighters
//Intercepts x 6
//	Unescorted bomber,  Just spotted, random position
//	Close Escort + High Escort - RAF comes in from front 2 sqds in formation
//	Close Escort + High Escort - RAF comes in from behind 2 sqds in formation
//	German Escort is scattered, RAF is scattered
//	
//Historic Missions x 8
//	1: Defiants End
//	2: Aldertag morning ?
//	3: Aldertag afternoon ? aug 13 th
//	4: Battle of Britain day 15th Sep
//	5: ???
//	6: sep 9th
//	7: Black Thursday Morning 15th Aug
//	8: Black Thursday Afternoon 15th Aug
//--------------------------------
	BattleField
	{
		FileName	FIL_OneOnOneBrit=SCRM04AL.BF
	};

//--------------------------------
//BASIC TRAINING : RAF takeoff

	BattleField
	{
		FileName	FIL_QUICKMISSION_00=QUICKM00.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target	{Pack_Target0},	
					Action	wpatakeoffno
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000},
						 Rel	{Bearing	ANGLES_180Deg,
								 Pitch	ANGLES_0Deg,
								 Range	METRES4000
								}
						}
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				MoveCode	AUTO_TRAININGTAKEOFF
  			}
 		}
	};

//--------------------------------
//BASIC TRAINING : RAF landing

	BattleField
	{

		FileName	FIL_QUICKMISSION_01=QUICKM01.BF,

		Setval	(AngleStepSize, Int (List PackTrgNum,60,150,170,200,315,315,315,315,180,180,180,180,180,180,180,180,180,180,180,180)),

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{
						 Abs	{Pack_Target0},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing {Select ANGLES_0Deg,AngleStepSize,ANGLES_1Deg},
							 Range	METRES8000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				MoveCode	AUTO_TRAININGLANDING
  			}
 		}							 
	};

//--------------------------------
//BASIC TRAINING : RAF Circuits

	BattleField
	{
		FileName	FIL_QUICKMISSION_02=QUICKM02.BF,

		Setval	(AngleStepSize, Int (List PackTrgNum,60,150,170,200,315,315,315,315,180,180,180,180,180,180,180,180,180,180,180,180)),
		Setval	(RandAngle, Heading {Select ANGLES_0Deg,AngleStepSize,ANGLES_1Deg)},

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target	{Pack_Target0},
					Posn	
						{
						 Abs	{Pack_Target0},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing {Select ANGLES_90Deg,AngleStepSize,ANGLES_1Deg},
							 Range	METRES4000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Attitude	{Heading RandAngle},
				MoveCode	AUTO_TRAININGLANDING
  			}
 		}
	};

//--------------------------------
//BASIC TRAINING : LUF take-off

	BattleField
	{
		FileName	FIL_QUICKMISSION_03=QUICKM03.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target	{Pack_Target0},	
					Action	wpatakeoffno
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000},
						 Rel	{Bearing	ANGLES_180Deg,
								 Pitch	ANGLES_0Deg,
								 Range	METRES4000
								}
						}
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Bombs	1,		//MS 05Sep00
				MoveCode	AUTO_TRAININGTAKEOFF
  			}
 		}
	};

//--------------------------------
//BASIC TRAINING : LUF landing

	BattleField
	{
		FileName	FIL_QUICKMISSION_04=QUICKM04.BF,

		Setval	(AngleStepSize, Int (List PackTrgNum,60,150,170,200,315,315,315,315,180,180,180,180,180,180,180,180,180,180,180,180)),

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing {Select ANGLES_0Deg,AngleStepSize,ANGLES_1Deg},
							 Range	METRES8000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Bombs	1,		//MS 05Sep00
				MoveCode	AUTO_TRAININGLANDING
  			}
 		}							 
	};

//--------------------------------
//BASIC TRAINING : LUF circuits

	BattleField
	{
		FileName	FIL_QUICKMISSION_05=QUICKM05.BF,

		Setval	(AngleStepSize, Int (List PackTrgNum,60,150,170,200,315,315,315,315,180,180,180,180,180,180,180,180,180,180,180,180)),
		Setval	(RandAngle, Heading {Select ANGLES_0Deg,AngleStepSize,ANGLES_1Deg)},

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target	{Pack_Target0},
					Posn	
						{
						 Abs	{Pack_Target0},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing {Select ANGLES_90Deg,AngleStepSize,ANGLES_1Deg},
							 Range	METRES4000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Attitude	{Heading RandAngle},
				Bombs	1,		//MS 05Sep00
				MoveCode	AUTO_TRAININGLANDING
  			}
 		}
	};

//--------------------------------
//AIRFIELD TRAINING : RAF squadron takeoff

	BattleField
	{
		FileName	FIL_QUICKMISSION_06=QUICKM06.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target	{Pack_Target0},	
					Action	wpatakeoffno
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000},
						 Rel	{Bearing	ANGLES_180Deg,
								 Pitch	ANGLES_0Deg,
								 Range	METRES6000
								}
						}
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
  			NumInForm	Scram_G0_AC,

//DeadCode MS 31Jul00 			Formation	SQD_RAFVIC_VIC,
  			DUTYMIGCAP,
				

  			Posn	{Abs	{Pack_Target0}},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				MoveCode	AUTO_TRAININGTAKEOFF
  			}
 		}
	};

//--------------------------------
//AIRFIELD TRAINING : RAF landing bad weather -> Squadron landing

	BattleField
	{
		FileName	FIL_QUICKMISSION_07=QUICKM07.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{
						 Abs	{Pack_Target0},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES7000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
  			NumInForm	Scram_G0_AC,

  			DUTYMIGCAP,
			Formation	SQD_RAFVIC_VIC,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	METRES8000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				MoveCode	AUTO_TRAININGLANDING
//TempCode MS 13Jul00 				MoveCode	AUTO_LANDING
  			}
 		}							 
	};

Damage QMD_EP_40={Select QMD_ENGINEPHASE,QMD_LEVEL,40},
Damage QMD_LWI_DANGER={Select QMD_LEFTWINGIN,QMD_HIGH},
//--------------------------------
//AIRFIELD TRAINING : RAF landing engine failure
 
	BattleField
	{
		FileName	FIL_QUICKMISSION_08=QUICKM08.BF,

		Setval	(AngleStepSize, Int (List PackTrgNum,60,150,170,200,315,315,315,315,180,180,180,180,180,180,180,180,180,180,180,180)),

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing {Select ANGLES_0Deg,AngleStepSize,ANGLES_1Deg},
							 Range	METRES8000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				MoveCode	AUTO_TRAININGLANDING,
				Damage	{List	QMD_EP_40,
								Damage {Select QMD_ENGINELEFT,QMD_LEVEL,252},
								Damage {Select QMD_FUELKILOS,QMD_LEVEL,0}
						}
  			}
 		}
	};

//--------------------------------
//AIRFIELD TRAINING : RAF landing heavy damage

	BattleField
	{
		FileName	FIL_QUICKMISSION_09=QUICKM09.BF,

		Setval	(AngleStepSize, Int (List PackTrgNum,60,150,170,200,315,315,315,315,180,180,180,180,180,180,180,180,180,180,180,180)),

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing {Select ANGLES_0Deg,AngleStepSize,ANGLES_1Deg},
							 Range	METRES8000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				MoveCode	AUTO_TRAININGLANDING,
				Damage	{List	QMD_LWI_DANGER,
						Damage	{Select	QMD_RIGHTWINGIN,QMD_MED},
						Damage	{Select	QMD_RIGHTWHEEL,QMD_DANGER}
					}
  			}
 		}
	};
	
//--------------------------------
//AIRFIELD TRAINING : LUF squadron takeoff

	BattleField
	{
		FileName	FIL_QUICKMISSION_10=QUICKM10.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target	{Pack_Target0},	
					Action	wpatakeoffno
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000},
						 Rel	{Bearing	ANGLES_180Deg,
								 Pitch	ANGLES_0Deg,
								 Range	METRES6000
								}
						}
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	4,
  			NumInForm	Scram_G1_AC,

			Formation	SQD_FINGER_VIC,
  			DUTYMIGCAP,
				

  			Posn	{Abs	{Pack_Target0}},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Bombs	1,		//MS 05Sep00
				MoveCode	AUTO_TRAININGTAKEOFF
  			}
 		}
	};


//--------------------------------
//AIRFIELD TRAINING : LUF landing bad weather - > squadron landing

	BattleField
	{
		FileName	FIL_QUICKMISSION_11=QUICKM11.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	4,
  			NumInForm	Scram_G1_AC,

  			DUTYMIGCAP,
			Formation	SQD_LWVIC_VIC,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	METRES5000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Bombs	1,		//MS 05Sep00
				MoveCode	AUTO_TRAININGLANDING
  			}
 		}							 
	};

//--------------------------------
//AIRFIELD TRAINING : LUF landing engine failure

	BattleField
	{
		FileName	FIL_QUICKMISSION_12=QUICKM12.BF,

		Setval	(AngleStepSize, Int (List PackTrgNum,60,150,170,200,315,315,315,315,180,180,180,180,180,180,180,180,180,180,180,180)),
		Setval	(RangeStepSize, Int (List Scram_G1_Squad,1,1,1,1,1,1,1,1,0,0,0,0,0)),

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{
						 Abs	{Pack_Target0},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing {Select ANGLES_0Deg,AngleStepSize,ANGLES_1Deg},
							 Range	{Select METRES6000,RangeStepSize,METRES2000},
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				MoveCode	AUTO_TRAININGLANDING,
				Bombs	1,		//MS 05Sep00
				Damage	{List	QMD_EP_40,
								Damage {Select QMD_ENGINELEFT,QMD_LEVEL,252},
								Damage {Select QMD_FUELKILOS,QMD_LEVEL,0}
						},
				Vel 600000
  			}
 		}
	};

//--------------------------------
//AIRFIELD TRAINING : LUF landing heavy damage

	BattleField
	{
		FileName	FIL_QUICKMISSION_13=QUICKM13.BF,

		Setval	(AngleStepSize, Int (List PackTrgNum,60,150,170,200,315,315,315,315,180,180,180,180,180,180,180,180,180,180,180,180)),

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{
						 Abs	{Pack_Target0},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing {Select ANGLES_0Deg,AngleStepSize,ANGLES_1Deg},
							 Range	METRES8000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				MoveCode	AUTO_TRAININGLANDING,
				Bombs	1,		//MS 05Sep00
				Damage	{List	QMD_LWI_DANGER,
						Damage	{Select	QMD_RIGHTWINGIN,QMD_MED},
						Damage	{Select	QMD_RIGHTWHEEL,QMD_DANGER}
					}
  			}
 		}
	};

//--------------------------------
//FAMILIARISATION : RAF	follow the leader

	BattleField
	{
		FileName	FIL_QUICKMISSION_14=QUICKM14.BF,
//TempCode MS 12Apr00 		AirGroup	
//TempCode MS 12Apr00 		{
//TempCode MS 12Apr00 			Route	
//TempCode MS 12Apr00 			{
//TempCode MS 12Apr00 				WayPoint	
//TempCode MS 12Apr00 				{
//TempCode MS 12Apr00 					Posn	
//TempCode MS 12Apr00 						{Abs	{Pack_Target0}, 
//TempCode MS 12Apr00 						 Abs	{Y Scram_G0_Alt}
//TempCode MS 12Apr00 						},
//TempCode MS 12Apr00 					Action	wpacnoactionno	
//TempCode MS 12Apr00 				},
//TempCode MS 12Apr00 				WayPoint	
//TempCode MS 12Apr00 				{
//TempCode MS 12Apr00 					Posn	
//TempCode MS 12Apr00 						{Abs	{Pack_Target0}, 
//TempCode MS 12Apr00 						 Abs	{Y Scram_G0_Alt}
//TempCode MS 12Apr00 						},
//TempCode MS 12Apr00  					Range	METRES4000,
//TempCode MS 12Apr00 					Action	wpalandingno
//TempCode MS 12Apr00 				}
//TempCode MS 12Apr00  			},
//TempCode MS 12Apr00 
//TempCode MS 12Apr00 			NumInWing	1,
//TempCode MS 12Apr00   			NumInForm	1,
//TempCode MS 12Apr00 			Formation	SQD_RAFVIC_VIC,
//TempCode MS 12Apr00 
//TempCode MS 12Apr00   			DUTYMIGCAP,
//TempCode MS 12Apr00 
//TempCode MS 12Apr00   			Posn	{Abs	{Pack_Target0}, 
//TempCode MS 12Apr00   					 Abs	{Y Scram_G0_Alt},
//TempCode MS 12Apr00 					 Rel	{Bearing ANGLES_180Deg,
//TempCode MS 12Apr00 							 Range	METRES8000,
//TempCode MS 12Apr00 							 Pitch	ANGLES_0Deg
//TempCode MS 12Apr00 							}
//TempCode MS 12Apr00 					},	
//TempCode MS 12Apr00 
//TempCode MS 12Apr00 			AirItem
//TempCode MS 12Apr00 			{
//TempCode MS 12Apr00 				PT_HURR_A,
//TempCode MS 12Apr00 				Home	Pack_Target0,
//TempCode MS 12Apr00   				NAT_RAF,
//TempCode MS 12Apr00 				MORALE_HIGH,
//TempCode MS 12Apr00   				Scram_G0_Skill,
//TempCode MS 12Apr00 				MoveCode	AUTO_FOLLOWTHELEADER
//TempCode MS 12Apr00   			}
//TempCode MS 12Apr00  		},
//TempCode MS 12Apr00 		AirGroup	
//TempCode MS 12Apr00 		{
//TempCode MS 12Apr00 			NumInWing	1,
//TempCode MS 12Apr00   			NumInForm	1,
//TempCode MS 12Apr00 			Formation	SQD_RAFVIC_VIC,
//TempCode MS 12Apr00 
//TempCode MS 12Apr00   			DUTYMIGCAP,
//TempCode MS 12Apr00 
//TempCode MS 12Apr00   			Posn	{Abs	{Pack_Target0}, 
//TempCode MS 12Apr00   					 Abs	{Y Scram_G0_Alt},
//TempCode MS 12Apr00 					 Rel	{Bearing ANGLES_180Deg,
//TempCode MS 12Apr00 							 Range	{Select METRES8000,1,METRES200},
//TempCode MS 12Apr00 							 Pitch	ANGLES_0Deg
//TempCode MS 12Apr00 							}
//TempCode MS 12Apr00 					},	
//TempCode MS 12Apr00 
//TempCode MS 12Apr00 			AirItem
//TempCode MS 12Apr00 			{
//TempCode MS 12Apr00 				PT_SPIT_A,
//TempCode MS 12Apr00 				Home	Pack_Target0,
//TempCode MS 12Apr00   				NAT_RAF,
//TempCode MS 12Apr00 				MORALE_HIGH,
//TempCode MS 12Apr00   				Scram_G0_Skill,
//TempCode MS 12Apr00 				Leader 	0
//TempCode MS 12Apr00   			}
//TempCode MS 12Apr00  		}
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,
			Formation	SQD_RAFVIC_VIC,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	{Select METRES8000,1,METRES200},
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		},
		AirGroup	
		{

			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,
			Formation	SQD_RAFVIC_VIC,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	METRES8000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				SKILL_HERO,
				MoveCode	AUTO_FOLLOWTHELEADER
  			}
 		}
	};

//--------------------------------
//FAMILIARISATION : RAF flying in formation

	BattleField
	{
		FileName	FIL_QUICKMISSION_15=QUICKM15.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing ANGLES_135Deg,
								 Range	METRES5000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing ANGLES_90Deg,
								 Range	METRES5000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing ANGLES_45Deg,
								 Range	METRES5000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing ANGLES_45Deg,
								 Range	KM10,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			

			NumInWing	3,
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing ANGLES_160Deg,
							 Range	METRES5000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				MoveCode	AUTO_TRAININGFORMATION
  			}
 		}
	};

//--------------------------------
//FAMILIARISATION : Free Flight

	BattleField
	{
		FileName	FIL_QUICKMISSION_16=QUICKM16.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{Pack_Target0},	
						 	 Abs	{Y Scram_G0_Alt}
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing	ANGLES_0Deg,
								 Pitch	ANGLES_0Deg,
								 Range	KM10
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	METRES4000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				Target	Pack_Target0
 		}	}
	};


//--------------------------------
//FAMILIARISATION : LUF follow the leader

	BattleField
	{	
		FileName	FIL_QUICKMISSION_17=QUICKM17.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,
			Formation	SQD_LWVIC_VIC,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	{Select METRES8000,1,METRES200},
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
  				Scram_G1_Skill
  			}
 		},
		AirGroup	
		{

			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,
			Formation	SQD_LWVIC_VIC,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	METRES8000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				SKILL_HERO,
				Bombs	1,		//MS 05Sep00
				MoveCode	AUTO_FOLLOWTHELEADER
  			}
 		}
	};

//--------------------------------
//FAMILIARISATION : LUF flying in formation

	BattleField
	{
		FileName	FIL_QUICKMISSION_18=QUICKM18.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt},
						 Rel	{Bearing ANGLES_135Deg,
								 Range	METRES5000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt},
						 Rel	{Bearing ANGLES_90Deg,
								 Range	METRES5000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt},
						 Rel	{Bearing ANGLES_45Deg,
								 Range	METRES5000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt},
						 Rel	{Bearing ANGLES_45Deg,
								 Range	KM10,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			

			NumInWing	4,
  			NumInForm	Scram_G1_AC,
			Formation	SQD_FINGER_VIC,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing ANGLES_160Deg,
							 Range	METRES5000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Bombs	1,		//MS 05Sep00
				MoveCode	AUTO_TRAININGFORMATION
  			}
 		}
	};

//--------------------------------
//FAMILIARISATION : Free Flight LUF

	BattleField
	{
		FileName	FIL_QUICKMISSION_19=QUICKM19.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	{Abs	{Pack_Target0},	
						 	 Abs	{Y Scram_G1_Alt}
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt},
						 Rel	{Bearing	ANGLES_0Deg,
								 Pitch	ANGLES_0Deg,
								 Range	KM10
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	METRES4000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	Pack_Target0,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Bombs	1,		//MS 05Sep00
				Target	Pack_Target0
 		}	}
	};

//--------------------------------
//COMBAT : turkey RAF side

	BattleField
	{
		FileName	FIL_QUICKMISSION_20=QUICKM20.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing ANGLES_0Deg,
								 Range	METRES5000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Target	{UID_AF_BIGGINHILL},
					Posn	
						{
						 Abs	{UID_AF_BIGGINHILL},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0},
  					 Abs	{Y Scram_G0_Alt}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	UID_AF_BIGGINHILL,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		},

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt},
				 		 Rel	{Bearing ANGLES_0Deg,
								 Range	METRES5000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_Wissant},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,

			DUTYMIGCAP,

			Posn		
				{Abs	{Pack_Target0}, 
				 Abs	{Y Scram_G1_Alt},
		 		 Rel	{Bearing ANGLES_0Deg,
						 Range	METRES300
						} 
				},

		   	AirItem
			{
				Home	UID_AF_Wissant,
				Scram_G1_Squad,
				NAT_LUF,
  				Scram_G1_Skill,
				Bombs	1,		//MS 05Sep00
				MORALE_HIGH
			}
		}
	};

//--------------------------------
//COMBAT : one on one

	BattleField
	{
		FileName	FIL_QUICKMISSION_21=QUICKM21.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg},
								 Range	METRES500
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
		   		{
					Posn
						{
						 Abs	{UID_AF_BIGGINHILL},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

			Posn		
				{Abs	{Pack_Target0}, 
				 Abs	{Y Scram_G0_Alt},
		 		 Rel	{Bearing {Random ANGLES_315Deg,90,ANGLES_1Deg},
						 Range	METRES500
						} 
				},


			AirItem	QUICK21_AC_00 =
			{
				Scram_G0_Squad,
				Home	UID_AF_BIGGINHILL,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
				ACM_TURNINGFIGHT
  			}
 		},

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt},
				 		 Rel	{Bearing {Random ANGLES_315Deg,90,ANGLES_1Deg},
								 Range	METRES5000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_Wissant},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,

			DUTYMIGCAP,

			Posn		
				{Abs	{Pack_Target0}, 
				 Abs	{Y Scram_G1_Alt},
		 		 Rel	{Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg},
						 Range	METRES500
						} 
				},

		   AirItem
			{
				Home		UID_AF_Wissant,
				Scram_G1_Squad,
				NAT_LUF,
  				Scram_G1_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Target	QUICK21_AC_00,
				Attacker	QUICK21_AC_00	
			}
		}
	};

//--------------------------------
//COMBAT : random advantage
//DONE - UNTESTED

	BattleField
	{
		FileName	FIL_QUICKMISSION_22=QUICKM22.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{FriendHomeBase, UID_AF_BIGGINHILL},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},
		Setval	{HeightSize, Y {Random Scram_G1_Alt,3,FT_1000}},
//MARK, DON'T SCREW WITH ANY ANGLES - TOO MUCH HEAD WRECK

		AirGroup	//group 0 - RAF
		{
			Route
			{
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target0},
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing	RandAngle,
								 Pitch	ANGLES_0Deg,
						 		 Range	METRES5000
								}
						}
				},
				WayPoint	
				{
					Target	{FriendHomeBase},
					Posn	
						{
						 Abs	{Y FT_3000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,
			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt}
					},	

		   AirItem
			{
				Home		FriendHomeBase,
				Scram_G0_Squad,
				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill
			}
		},
		AirGroup	//group 01 - LUF 
		{
			Route	
			{
				WayPoint	QUICK22_WP_00 =
				{
					Posn	
						{Abs	{Pack_Target0},
						 Abs	{Y HeightSize},
						 Rel	{Bearing	{Random RandAngle,8,ANGLES_45Deg},
								 Pitch	ANGLES_0Deg,
							 	 Range	{Random METRES2000,3,METRES1000}
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	{EnemyScoutHomeBase},
					Posn	
						{
						 Abs	{Y FT_3000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	4,
   			NumInForm	Scram_G1_AC,
  			DUTYMIGCAP,
			SQD_SCHWARM_VIC,
			
  			Posn	{Abs	QUICK22_WP_00, 
  					 Abs	{Y HeightSize},
  					 Rel	{Bearing	{Random RandAngle,2,ANGLES_180Deg},
							 Pitch	ANGLES_0Deg,
							 Range	{Random METRES2000,3,METRES1000}
							}
					},	
			AirItem	     	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_LUF,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
  				Scram_G1_Skill
  			}
 		}
	};

//--------------------------------
//COMBAT : RAF advantage

	BattleField
	{
		FileName	FIL_QUICKMISSION_23=QUICKM23.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{FriendHomeBase, UID_AF_BIGGINHILL},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},
//MARK, DON'T SCREW WITH ANY ANGLES - TOO MUCH HEAD WRECK

		AirGroup	//group 1 - LUFTWAFFE
		{
			Route
			{
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target0},
						 Abs	{Y Scram_G1_Alt},
						 Rel	{Bearing	{Select RandAngle,1,ANGLES_225Deg},
						 		 Range	METRES5000
								}
						}
				},
				WayPoint	
				{
					Posn	
						{Abs	{EnemyScoutHomeBase}, 
						 Abs	{Y FT_3000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},

			NumInWing	4,
  			NumInForm	Scram_G1_AC,
			Formation	SQD_SCHWARM_VIC,
			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt}
					},	

		   AirItem
			{
				Home		EnemyScoutHomeBase,
				Scram_G1_Squad,
				NAT_LUF,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
  				Scram_G1_Skill
			}
		},
		AirGroup	//group 00 - RAF 
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0},
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_3000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	3,
   			NumInForm	Scram_G0_AC,
  			DUTYMIGCAP,
			SQD_RAFVIC_VIC,
			
  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Bearing	{Random RandAngle,90,ANGLES_1Deg},
							 Range	{Random METRES1000,3,METRES500}
							}
					},	
			AirItem	     	
			{
				Scram_G0_Squad,
				Home	FriendHomeBase,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		}
	};

//--------------------------------
//COMBAT : LUF advantage

	BattleField
	{
		FileName	FIL_QUICKMISSION_24=QUICKM24.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{FriendHomeBase, UID_AF_BIGGINHILL},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},
//MARK, DON'T SCREW WITH ANY ANGLES - TOO MUCH HEAD WRECK

		AirGroup	//group 0 - RAF
		{
			Route
			{
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target0},
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing	{Select RandAngle,1,ANGLES_225Deg},
						 		 Range	METRES5000
								}
						}
				},
				WayPoint	
				{
					Posn	
						{Abs	{FriendHomeBase}, 
						 Abs	{Y FT_3000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,
			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt}
					},	

		   AirItem
			{
				Home		FriendHomeBase,
				Scram_G0_Squad,
				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill
			}
		},
		AirGroup	//group 01 - LUF 
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0},
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{EnemyScoutHomeBase}, 
						 Abs	{Y FT_3000}
						},
 					Range	METRES5000,
					Action	wpalandingno
				}
 			},
			
  			NumInWing	4,
   			NumInForm	Scram_G1_AC,
  			DUTYMIGCAP,
			SQD_SCHWARM_VIC,
			
  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Bearing	{Random RandAngle,90,ANGLES_1Deg},
							 Range	{Random METRES1000,3,METRES500}
							}
					},	
			AirItem	     	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_LUF,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
  				Scram_G1_Skill
  			}
 		}
	};

//--------------------------------
//Turkey LUFT side

	BattleField
	{
		FileName	FIL_QUICKMISSION_25=QUICKM25.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing ANGLES_0Deg,
								 Range	METRES5000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Target	{UID_AF_BIGGINHILL},
					Posn	
						{
						 Abs	{UID_AF_BIGGINHILL},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,

			Posn		
				{Abs	{Pack_Target0}, 
				 Abs	{Y Scram_G0_Alt},
		 		 Rel	{Bearing ANGLES_0Deg,
						 Range	METRES300
						} 
				},

			AirItem
			{
				Scram_G0_Squad,
				Home	UID_AF_BIGGINHILL,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		},

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt},
				 		 Rel	{Bearing ANGLES_0Deg,
								 Range	METRES5000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_Wissant},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,

			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0},
  					 Abs	{Y Scram_G0_Alt}
					},	

		   	AirItem
			{
				Home	UID_AF_Wissant,
				Scram_G1_Squad,
				NAT_LUF,
  				Scram_G1_Skill,
				Bombs	1,		//MS 05Sep00
				MORALE_HIGH
			}
		}
	};

//--------------------------------
//GROUNDWORK : dive bomb attack 2

	BattleField
	{
		FileName	FIL_QUICKMISSION_26=QUICKM26.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_90Deg,135,ANGLES_1Deg}},
		Setval	(PlyrWingSize, NumInWing (List Scram_G1_Squad,4,4,4,4,4,4,4,4,3,3,3,3,3)),
//TempCode MS 05Sep00 	 	Setval	{ParentRand, Int {List RangeStepSize,3,3,3,3,3,3,3,3,3,}},

		AirGroup	//group 0, RAF interceptors
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	{UID_AF_KENLEY},
					Posn	
						{
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Bearing	{Random ANGLES_270Deg,135,ANGLES_1Deg},
							 Range		{Random	METRES6000,4,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AF_KENLEY,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				Morale MORALE_HIGH
				
			}
		},
		AirGroup	//group 1 - Luft Strike
		{
			Route	quick_26_G1_route =	
			{
				WayPoint	
				{
					Posn	{
						 Abs	{Pack_Target0},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	{Select METRES4000,9,METRES100},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Target	{Pack_Target0},	
					Posn	{
						 	 Abs	{Y Scram_G1_Alt}
						},
 					Range	{Select METRES4000,8,METRES100},
					Action	wpbombno	
				},
				WayPoint	
				{
					Target	UID_AF_Wissant,
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}

 			},

			NumInWing	PlyrWingSize,
  			NumInForm	Scram_G1_AC,
	       		Formation	GRUP_LWVIC_VIC_VIC,

			AM_DIVEBOMB,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Bearing	RandAngle,
						 	 Range	METRES5000
							}
					},	

		   AirItem	quick_26_G1_aircraft =
			{
				Scram_G1_Squad,
				Home	UID_AF_Wissant,
				NAT_LUF,
  				Scram_G1_Skill,
				Morale	MORALE_HIGH,
//TempCode MS 06Jan100 				Bombs Weap_BombFuel,
				Target	Pack_Target0
			}
		},

		AirGroup	//group 2 - LUF Fighter Escort
		{

			NumInWing	4,
  			NumInForm	Scram_G2_AC,
			Formation	GRUP_FINGER_VIC_ABOVE,

			DUTYESCORT,

		   AirItem	
			{
				Scram_G2_Squad,
				Home	UID_AF_Audembert,
				NAT_LUF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Leader	0,
				Bombs 1
			}
		}
	};

//--------------------------------
//GROUNDWORK : anti-shipping

	BattleField
	{
		FileName	FIL_QUICKMISSION_27=QUICKM27.BF,

	 	Setval	{RandAngle, Bearing {Random ANGLES_90Deg,135,ANGLES_1Deg}},
		Setval	(PlyrWingSize, NumInWing (List Scram_G1_Squad,4,4,4,4,4,4,4,4,3,3,3,3,3)),

		AirGroup	//group 0, RAF interceptors
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	{UID_AF_KENLEY},
					Posn	
						{
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Intercept	{Pack_Target0,UID_AF_Audembert},
							 Bearing	{Random ANGLES_90Deg,135,ANGLES_1Deg},
							 Range		{Random	METRES7000,4,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AF_KENLEY,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				Morale MORALE_HIGH
				
			}
		},

		AirGroup	//group 1 - Luft Strike
		{
			Route	quick_27_G1_route =	
			{
				WayPoint	
				{
					Target	{Pack_Target0},	
					Posn	{
						 	 Abs	{Y Scram_G1_Alt}
							},
 					Range	METRES4000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Target	UID_AF_Audembert,
					Posn	
						{
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	PlyrWingSize,
  			NumInForm	Scram_G1_AC,
			Formation	GRUP_LWVIC_VIC_VIC,

			AM_DIVEBOMB,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Bearing	RandAngle,
						 	 Range	METRES5000
							}
					},	

		   AirItem	quick_27_G1_aircraft =
			{
				Scram_G1_Squad,
				Home	UID_AF_Audembert,
				NAT_LUF,
  				Scram_G1_Skill,
				Morale	MORALE_HIGH,
				Target	Pack_Target0
			}
		},

		AirGroup	//group 2 - LUF Fighter Escort
		{
			Route	quick_27_G1_route,

//DeadCode MS 05Sep00 			NumInWing	2,
//DeadCode MS 05Sep00   			NumInForm	Scram_G2_AC,
//DeadCode MS 05Sep00 			Formation	SQD_SCHWARM_VIC,
//DeadCode MS 05Sep00 
//DeadCode MS 05Sep00 			DUTYESCORT,
//DeadCode MS 05Sep00 
//DeadCode MS 05Sep00   			Posn	{Abs	quick_27_G1_aircraft, 
//DeadCode MS 05Sep00   					 Abs	{Y Scram_G2_Alt},
//DeadCode MS 05Sep00   					 Rel	{Bearing	{Select RandAngle,1,ANGLES_270Deg},
//DeadCode MS 05Sep00 						 	 Range	METRES1000
//DeadCode MS 05Sep00 							}
//DeadCode MS 05Sep00 					},	
//DeadCode MS 05Sep00 
//DeadCode MS 05Sep00 		   AirItem	
//DeadCode MS 05Sep00 			{
//DeadCode MS 05Sep00 				Scram_G2_Squad,
//DeadCode MS 05Sep00 				Home	UID_AF_Audembert,
//DeadCode MS 05Sep00 				NAT_LUF,
//DeadCode MS 05Sep00   				Scram_G2_Skill,
//DeadCode MS 05Sep00 				MORALE_HIGH,
//DeadCode MS 05Sep00 				Leader	0,
//DeadCode MS 05Sep00 				Bombs 1,
//DeadCode MS 05Sep00 				Attitude	{
//DeadCode MS 05Sep00 							 Heading	{Select RandAngle,1,ANGLES_180Deg},
//DeadCode MS 05Sep00 							 Pitch ANGLES_0Deg
//DeadCode MS 05Sep00 							}
//DeadCode MS 05Sep00 			}
//DeadCode MS 05Sep00 		}

			NumInWing	4,
  			NumInForm	Scram_G2_AC,
			Formation	GRUP_FINGER_VIC_ABOVE,

			DUTYESCORT,

		   AirItem	
			{
				Scram_G2_Squad,
				Home	UID_AF_Audembert,
				NAT_LUF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Leader	0,
				Bombs 1
			}
		}
	};

//--------------------------------
//GROUNDWORK : low level

	BattleField
	{
		FileName	FIL_QUICKMISSION_28=QUICKM28.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_90Deg,135,ANGLES_1Deg}},
		Setval	(PlyrWingSize, NumInWing (List Scram_G1_Squad,4,4,4,4,4,4,4,4,3,3,3,3,3)),

//TempCode MS 07Apr00 		AirGroup	//group 0, RAF landing
//TempCode MS 07Apr00 		{
//TempCode MS 07Apr00 			Route	
//TempCode MS 07Apr00 			{
//TempCode MS 07Apr00 				WayPoint	
//TempCode MS 07Apr00 				{
//TempCode MS 07Apr00 					Posn	
//TempCode MS 07Apr00 						{Abs	{Pack_Target0}, 
//TempCode MS 07Apr00 						 Abs	{Y Scram_G0_Alt}
//TempCode MS 07Apr00 						},
//TempCode MS 07Apr00 					Action	wpacnoactionno	
//TempCode MS 07Apr00 				},
//TempCode MS 07Apr00 				WayPoint	
//TempCode MS 07Apr00 				{
//TempCode MS 07Apr00 					Target	{Pack_Target0},
//TempCode MS 07Apr00 					Posn	
//TempCode MS 07Apr00 						{
//TempCode MS 07Apr00 						 Abs	{Y Scram_G0_Alt}
//TempCode MS 07Apr00 						},
//TempCode MS 07Apr00  					Range	METRES4000,
//TempCode MS 07Apr00 					Action	wpalandingno
//TempCode MS 07Apr00 				}
//TempCode MS 07Apr00  			},
//TempCode MS 07Apr00 
//TempCode MS 07Apr00 			NumInWing	3,	
//TempCode MS 07Apr00   			NumInForm	Scram_G0_AC,
//TempCode MS 07Apr00 
//TempCode MS 07Apr00 			DUTYMIGCAP,
//TempCode MS 07Apr00 			Formation	SQD_RAFVIC_VIC,
//TempCode MS 07Apr00 			
//TempCode MS 07Apr00   			Posn	{Abs	{Pack_Target0}, 
//TempCode MS 07Apr00   					 Abs	{Y Scram_G0_Alt},
//TempCode MS 07Apr00   					 Rel	{Intercept	{Pack_Target0,UID_AF_NORTHOLT},
//TempCode MS 07Apr00 							 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
//TempCode MS 07Apr00 							 Pitch		ANGLES_0Deg,
//TempCode MS 07Apr00 							 Range		{Random	METRES8000,3,METRES1000}
//TempCode MS 07Apr00 							}
//TempCode MS 07Apr00 					},	
//TempCode MS 07Apr00 
//TempCode MS 07Apr00 		   AirItem	
//TempCode MS 07Apr00 			{
//TempCode MS 07Apr00 				Home		Pack_Target0,
//TempCode MS 07Apr00 				Scram_G0_Squad,
//TempCode MS 07Apr00 				NAT_RAF,
//TempCode MS 07Apr00   				Scram_G0_Skill,
//TempCode MS 07Apr00 				Morale MORALE_HIGH
//TempCode MS 07Apr00 			}
//TempCode MS 07Apr00 		},

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target	{Pack_Target0},	
					Action	wpatakeoffno,
					Start	{S TakeOffTime,M 1}
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000},
						 Rel	{Bearing	ANGLES_180Deg,
								 Pitch	ANGLES_0Deg,
								 Range	METRES4000
								}
						}
				},
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y FT_2000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
  			NumInForm	Scram_G0_AC,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill,
			   	MoveCode	AUTO_WAIT4TIME
  			}
 		},

		AirGroup	//group 1 - Luft Strike
		{
			Route
			{
//TempCode MS 05Sep00 				WayPoint	
//TempCode MS 05Sep00 				{
//TempCode MS 05Sep00 					Posn	{
//TempCode MS 05Sep00 							 Abs 	{Pack_Target0},
//TempCode MS 05Sep00 						 	 Abs	{Y FT_300}
//TempCode MS 05Sep00 							},
//TempCode MS 05Sep00 					Action	wpacnoactionno		
//TempCode MS 05Sep00 				},
				WayPoint	
				{
					Target	{Pack_Target0},	
					Posn	{
						 	 Abs	{Y FT_750}
							},
 					Range	METRES4000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_Audembert, 
						 Abs	{Y FT_2000}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	PlyrWingSize,
  			NumInForm	Scram_G1_AC,

			AM_DIVEBOMB,
       		Formation	GRUP_LWVIC_VIC_VIC,

  			Posn	{Abs	{Pack_Target0}, 
					 Abs	{Y FT_750},
  					 Rel	{Intercept	{UID_AF_NORTHOLT,Pack_Target0},
							 Pitch 		ANGLES_0Deg,
							 Bearing	{Random ANGLES_315Deg,90,ANGLES_1Deg},
							 Range		METRES4000
							}
					},

		   AirItem	
			{
				Scram_G1_Squad,
				Home	UID_AF_Audembert,
				NAT_LUF,
  				Scram_G1_Skill,
				Morale	MORALE_HIGH,
//TempCode MS 06Jan100 				Bombs Weap_BombFuel,
				Target	{Pack_Target0}
			}
		}
	};

//--------------------------------
//INTERCEPTS : 1 Lone Bomber vs Lone Fighter

	BattleField
	{
		FileName	FIL_QUICKMISSION_29=QUICKM29.BF,

		AirGroup	//luft bomber
		{
			Route	quick_29_G1_route =
			{
				WayPoint	
				{
					Target		{Pack_Target0},
					Posn		
						{
						 Abs	{Y Scram_G1_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_Audembert, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	1,
  			NumInForm	1,

			Formation	SQD_LWVIC_ASTERN,
			Duty	DA_LEVEL,

  			Posn	{Abs	Pack_Target0, 
				 	 Abs	{Y Scram_G1_Alt},
			 		 Rel	{Bearing {Random ANGLES_90Deg,180,ANGLES_1Deg},
							 Pitch 	ANGLES_0Deg,
						 	 Range {Select KM10}
						} 
					},	

			AirItem	quick_29_G1_aircraft=
			{
				Scram_G1_Squad,
				Home	UID_AF_Audembert,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Target	Pack_Target0
  			}
 		},
//LONE RAF
		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	quick_29_G1_aircraft, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_BIGGINHILL, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	1,
  			NumInForm	1,

			DUTYMIGCAP,
			Formation	SQD_RAFVIC_VIC,

			Posn		
				{Abs	quick_29_G1_aircraft, 
				 Abs	{Y Scram_G0_Alt},
				 Rel	{Bearing {Random ANGLES_0Deg,7,ANGLES_45Deg},
						 Pitch 	ANGLES_0Deg,
					 	 Range	METRES2000
						} 
				},

		   	AirItem
			{
				Home	UID_AF_BIGGINHILL,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH,
				Target	quick_29_G1_aircraft
//TempCode MS 08Nov00 				ACM_TURNINGFIGHT
			}
		}
	};

//--------------------------------
//INTERCEPTS : 2	FIGHTERS VS BOMBERS WITH CLOSE ESCORT
//Close Escort + High Escort - RAF comes in from front 2 sqds in formation

	BattleField
	{
		FileName	FIL_QUICKMISSION_30=QUICKM30.BF,
	 	Setval	{AngleStepSize, Int {Random 135,45,2}},

	 	Setval	{RandAngle, Bearing {Random ANGLES_90Deg,180,ANGLES_1Deg}},

		AirGroup	//luft bombers
		{	//GROUP 1: LW Bombers
			Route	quick_30_G2_route =
			{
				WayPoint	
				{
					Target		{Pack_Target0},
					Posn		
						{
						 Abs	{Y Scram_G2_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_Audembert, 
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
  			NumInForm	Scram_G2_AC,
			Duty	AM_LEVELBOMB,

			Formation	GRUP_LWVIC_ASTERN_ASTERN,

  			Posn	{Abs	Pack_Target0, 
				 	 Abs	{Y Scram_G2_Alt},
			 		 Rel	{Bearing RandAngle,
							 Pitch 	ANGLES_0Deg,
						 	 Range	METRES8000
						} 
					},	

			AirItem	quick_30_G2_aircraft=
			{
				Scram_G2_Squad,
				Home	UID_AF_Audembert,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G2_Skill,
				Target	Pack_Target0
  			}
 		},
		AirGroup   
		{
			NumInWing	4,
  			NumInForm	Scram_G3_AC,

			DUTYESCORT,	  
			Formation	GRUP_FINGER_ASTERN_LEFT,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G3_Squad,
				NAT_LUF,
  				Scram_G3_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	quick_30_G2_aircraft	
			}
		},
		AirGroup   
		{
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			DUTYESCORT,	  
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	quick_30_G2_aircraft	
			}
//RAF
		},
		AirGroup   
		{	
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	quick_30_G2_aircraft, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_BIGGINHILL, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn		
				{Abs	quick_30_G2_aircraft, 
				 Abs	{Y Scram_G0_Alt},
				 Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_1Deg},
						 Pitch 	ANGLES_0Deg,
					 	 Range	{Random METRES5000,4,METRES500}
						} 
				},

		   	AirItem
			{
				Home	UID_AF_BIGGINHILL,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH
			}
		},
		AirGroup   
		{	
			NumInWing	3,
  			NumInForm	Scram_G1_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

		   	AirItem
			{
				Home	UID_AF_BIGGINHILL,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				MORALE_HIGH,
				Leader	0
			}
		}
	};

//--------------------------------
//INTERCEPTS : 3
//	Close Escort + High Escort - RAF comes in from behind 2 sqds in formation

	BattleField
	{
		FileName	FIL_QUICKMISSION_31=QUICKM31.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_90Deg,180,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 270,180,1}},


		AirGroup	//luft bombers
		{	//GROUP 1: LW Bombers
			Route	quick_31_G2_route =
			{
				WayPoint	
				{
					Target		{Pack_Target0},
					Posn		
						{
						 Abs	{Y Scram_G2_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_Audembert, 
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
  			NumInForm	Scram_G2_AC,
			Duty	DA_LEVEL,

			Formation	GRUP_LWVIC_ASTERN_ASTERN,

  			Posn	{Abs	Pack_Target0, 
				 	 Abs	{Y Scram_G2_Alt},
			 		 Rel	{Bearing RandAngle,
							 Pitch 	ANGLES_0Deg,
						 	 Range	METRES8000
						} 
					},	

			AirItem	quick_31_G2_aircraft=
			{
				Scram_G2_Squad,
				Home	UID_AF_Audembert,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G2_Skill,
				Target	Pack_Target0
  			}
 		},
		AirGroup   
		{
			NumInWing	4,
  			NumInForm	Scram_G3_AC,

			DUTYESCORT,	  
			Formation	GRUP_FINGER_ASTERN_LEFT,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G3_Squad,
				NAT_LUF,
  				Scram_G3_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	quick_31_G2_aircraft
			}
		},
		AirGroup   
		{
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			DUTYESCORT,	  
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	quick_31_G2_aircraft	
			}
//RAF
		},
		AirGroup   
		{	
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	quick_31_G2_aircraft, 
						 Abs	{Y Scram_G2_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_BIGGINHILL, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn		
				{Abs	quick_31_G2_aircraft, 
				 Abs	{Y Scram_G0_Alt},
				 Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_1Deg},
						 Pitch 	ANGLES_0Deg,
					 	 Range	{Random METRES1000,4,METRES500}
						} 
				},

		   	AirItem
			{
				Home	UID_AF_BIGGINHILL,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH
			}
		},
		AirGroup   
		{	
			NumInWing	3,
  			NumInForm	Scram_G1_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

		   	AirItem
			{
				Home	UID_AF_BIGGINHILL,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				MORALE_HIGH,
				Leader	0
			}
		}
//DeadCode MS 05Sep00 //EXTRAS These Guys are taking off from Debden
//DeadCode MS 05Sep00 		AirGroup   
//DeadCode MS 05Sep00 		{	
//DeadCode MS 05Sep00 			Route	
//DeadCode MS 05Sep00 			{
//DeadCode MS 05Sep00 				WayPoint	
//DeadCode MS 05Sep00 				{
//DeadCode MS 05Sep00 					Target	{UID_AF_DEBDEN},
//DeadCode MS 05Sep00 					Action	wpatakeoffno
//DeadCode MS 05Sep00 				},
//DeadCode MS 05Sep00 				WayPoint	
//DeadCode MS 05Sep00 				{
//DeadCode MS 05Sep00 					Posn		
//DeadCode MS 05Sep00 //TempCode MS 11Jul00 						{Abs	Pack_Target0, 
//DeadCode MS 05Sep00 						{Abs	UID_AF_BIGGINHILL, 
//DeadCode MS 05Sep00 						 Abs	{Y FT_10000}
//DeadCode MS 05Sep00 						},
//DeadCode MS 05Sep00 					Action	wpacnoactionno	
//DeadCode MS 05Sep00 				},
//DeadCode MS 05Sep00 				WayPoint	
//DeadCode MS 05Sep00 				{
//DeadCode MS 05Sep00 					Posn	
//DeadCode MS 05Sep00 						{Abs	UID_AF_DEBDEN, 
//DeadCode MS 05Sep00 						 Abs	{Y FT_5000}
//DeadCode MS 05Sep00 						},
//DeadCode MS 05Sep00  					Range	METRES6000,
//DeadCode MS 05Sep00 					Action	wpalandingno
//DeadCode MS 05Sep00 				}
//DeadCode MS 05Sep00  			},
//DeadCode MS 05Sep00 
//DeadCode MS 05Sep00 			NumInWing	3,
//DeadCode MS 05Sep00   			NumInForm	6,
//DeadCode MS 05Sep00 
//DeadCode MS 05Sep00 			DUTYMIGCAP,
//DeadCode MS 05Sep00 //TempCode MS 11Jul00 			Formation	WING_RAFVIC_VIC_VIC,
//DeadCode MS 05Sep00 
//DeadCode MS 05Sep00   			Posn	{Abs	{UID_AF_DEBDEN}},	
//DeadCode MS 05Sep00 
//DeadCode MS 05Sep00 		   	AirItem
//DeadCode MS 05Sep00 			{
//DeadCode MS 05Sep00 				Home	UID_AF_DEBDEN,
//DeadCode MS 05Sep00 				Scram_G0_Squad,
//DeadCode MS 05Sep00 				NAT_RAF,
//DeadCode MS 05Sep00   				Scram_G0_Skill,
//DeadCode MS 05Sep00 				MORALE_HIGH,
//DeadCode MS 05Sep00 				MoveCode	AUTO_TAKEOFF
//DeadCode MS 05Sep00 			}
//DeadCode MS 05Sep00 		}
	};


//--------------------------------
//INTERCEPTS : 4
//Everyone is scattered, german escort is detached

	BattleField
	{
		FileName	FIL_QUICKMISSION_32=QUICKM32.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_90Deg,180,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 270,180,1}},

		AirGroup	//luft bombers
		{	
			Route	
			{
				WayPoint	
				{
					Target		{Pack_Target0},
					Posn		
						{
						 Abs	{Y Scram_G2_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_Audembert, 
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
  			NumInForm	Scram_G2_AC,
			Duty	DA_LEVEL,

			Formation	GRUP_LWVIC_ASTERN_ASTERN,

  			Posn	{Abs	Pack_Target0, 
				 	 Abs	{Y Scram_G2_Alt},
			 		 Rel	{Bearing RandAngle,
							 Pitch 	ANGLES_0Deg,
						 	 Range	METRES8000
						} 
					},	

			AirItem	quick_32_G2_aircraft=	
			{
				Scram_G2_Squad,
				Home	UID_AF_Audembert,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G2_Skill,
				Target	Pack_Target0
  			}
 		},
		AirGroup   
		{		//DETACHED ESCORT	
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	quick_32_G2_aircraft, 
				 		 Abs	{Y Scram_G3_Alt},
				 		 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
						 		 Pitch 	ANGLES_0Deg,
					 	 		 Range	METRES8000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_Audembert, 
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			NumInWing	4,
  			NumInForm	Scram_G3_AC,

			DUTYESCORT,	  
			Formation	GRUP_SCHWARM_VIC_VIC,

			Posn		
				{Abs	quick_32_G2_aircraft, 
				 Abs	{Y Scram_G3_Alt},
				 Rel	{Bearing {Random ANGLES_0Deg,4,ANGLES_90Deg},
						 Pitch 	ANGLES_0Deg,
					 	 Range	{Random METRES1000,8,METRES500}
						} 
				},

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G3_Squad,
				NAT_LUF,
  				Scram_G3_Skill,
				Bombs	1,		//MS 05Sep00
				MORALE_HIGH
			}
		},
		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	quick_32_G2_aircraft, 
				 		 Abs	{Y Scram_G4_Alt},
				 		 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
						 		 Pitch 	ANGLES_0Deg,
					 	 		 Range	METRES8000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_Audembert, 
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			DUTYESCORT,	  
			Formation	GRUP_SCHWARM_VIC_VIC,

			Posn		
				{Abs	quick_32_G2_aircraft, 
				 Abs	{Y Scram_G4_Alt},
				 Rel	{Bearing {Random ANGLES_25Deg,4,ANGLES_90Deg},
						 Pitch 	ANGLES_0Deg,
					 	 Range	{Random METRES1000,8,METRES500}
						} 
				},

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				Bombs	1,		//MS 05Sep00
				MORALE_HIGH
			}
//RAF
		},
		AirGroup   
		{	
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	quick_32_G2_aircraft, 
				 		 Abs	{Y Scram_G0_Alt},
				 		 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
						 		 Pitch 	ANGLES_0Deg,
					 	 		 Range	METRES8000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_BIGGINHILL, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn		
				{Abs	quick_32_G2_aircraft, 
				 Abs	{Y Scram_G0_Alt},
				 Rel	{Bearing {Random ANGLES_50Deg,4,ANGLES_90Deg},
						 Pitch 	ANGLES_0Deg,
					 	 Range	{Random METRES1000,8,METRES500}
						} 
				},

		   	AirItem
			{
				Home	UID_AF_BIGGINHILL,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH
			}
		},
		AirGroup   
		{	
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	quick_32_G2_aircraft, 
				 		 Abs	{Y Scram_G1_Alt},
				 		 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
						 		 Pitch 	ANGLES_0Deg,
					 	 		 Range	METRES8000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_BIGGINHILL, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G1_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn		
				{Abs	quick_32_G2_aircraft, 
				 Abs	{Y Scram_G1_Alt},
				 Rel	{Bearing {Random ANGLES_80Deg,4,ANGLES_90Deg},
						 Pitch 	ANGLES_0Deg,
					 	 Range	{Random METRES1000,8,METRES500}
						} 
				},

		   	AirItem
			{
				Home	UID_AF_BIGGINHILL,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				MORALE_HIGH
			}
		}
	};

//--------------------------------
//DEMO 1

	BattleField
	{
		FileName	FIL_QUICKMISSION_33=QUICKM33.BF,
//LUFTWAFFE
		AirGroup	//luft bombers
		{	//first wave to Shorts
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G2_Alt}
						},
					Action	wpacnoactionno,
					Range	METRES7000
				},
				WayPoint	
				{
					Target	{Pack_Target0},	
					Posn	{
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES7000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_AntwerpDeurne, 
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
			NumInForm	Scram_G2_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,
			Duty	DA_LEVEL,

			Posn	
				{Abs	{Pack_Target0}, 
				 Abs	{Y Scram_G2_Alt},
		 		 Rel	{Bearing	ANGLES_150Deg,
						 Pitch	ANGLES_0Deg,
						 Range	SMILES10
						}
				},

			AirItem		QUICKM33G2_item =
			{
				Scram_G2_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G2_Skill,
				Target	Pack_Target0
  			}
 		},
//wave  2
		AirGroup	//luft bombers
		{	//2nd wave to follow above to shorts
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G4_Alt}
						},
					Range	METRES7000,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	{Pack_Target0},	
					Posn	{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES7000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_AntwerpDeurne, 
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
			NumInForm	Scram_G4_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,
			Duty	DA_LEVEL,

			Posn	
				{Abs	{Pack_Target0}, 
				 Abs	{Y Scram_G4_Alt},
		 		 Rel	{Bearing	ANGLES_150Deg,
						 Pitch	ANGLES_0Deg,
						 Range	{Select SMILES10,1,METRES1000}
						}
				},

			AirItem	QUICKM33G4_item =	
			{
				Scram_G4_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G4_Skill,
				Target	Pack_Target0
  			}
 		},
//RAF 
		AirGroup	//Spits	111 sqdn
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	QUICKM33G2_item, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_CROYDON},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	QUICKM33G2_item, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Intercept	{QUICKM33G2_item,Pack_Target0},
							 Bearing	{Random ANGLES_300Deg,60,ANGLES_1Deg},
							 Range		METRES3000,
							 Pitch	ANGLES_0Deg
							}
					},	

		   AirItem	
			{
				Home		UID_AF_CROYDON,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				Morale MORALE_HIGH
				
			}
		},
		AirGroup	//Hurrs wave 1 151 sqdn NORTHWEALD
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	QUICKM33G2_item, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_NORTHWEALD},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G1_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	QUICKM33G2_item, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Intercept	{QUICKM33G2_item,Pack_Target0},
							 Bearing	{Random ANGLES_45Deg,45,ANGLES_1Deg},
							 Range		{Random	METRES3000,3,METRES1000},
							 Pitch	ANGLES_0Deg
							}
					},	

		   AirItem	
			{
				Home		UID_AF_NORTHWEALD,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				Morale MORALE_HIGH
				
			}
		},
//Escort
		AirGroup //escort wave 1
		{	
			NumInWing	4,
  			NumInForm	Scram_G3_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G3_Squad,
				NAT_LUF,
  				Scram_G3_Skill,
				MORALE_HIGH,
				Leader	QUICKM33G2_item
			}
		},

//Escort
		AirGroup //escort for second wave  
		{	
			NumInWing	4,
  			NumInForm	Scram_G5_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Leader	QUICKM33G4_item
			}
		},
//FOLLOW UP Waves
		AirGroup   
		{	//Wave 1, Group 2

			NumInWing	5,
			NumInForm	Scram_G2_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_ASTERN_VIC,

		   	AirItem	QUICKM33G2_item_b =
			{
				Scram_G2_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G2_Skill,
				Target	Pack_Target0,
				Leader	QUICKM33G2_item
			}
		},
		AirGroup   
		{	//Wave 1, Group 3

			NumInWing	5,
			NumInForm	Scram_G2_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_ASTERN_VIC2,

		   	AirItem	QUICKM33G2_item_c =
			{
				Scram_G2_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G2_Skill,
				Target	Pack_Target0,
				Leader	QUICKM33G2_item
			}
		},
		AirGroup   
		{	//Wave 2, Group 2

			NumInWing	5,
			NumInForm	Scram_G4_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_ASTERN_VIC,

		   	AirItem
			{
				Scram_G4_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G4_Skill,
				Target	UID_AF_EASTCHURCH,
				Leader	QUICKM33G4_item
			}
		},
		AirGroup   
		{	//Wave 2, Group 3

			NumInWing	5,
			NumInForm	Scram_G4_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_ASTERN_VIC2,

		   	AirItem
			{
				Scram_G4_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G4_Skill,
				Target	UID_AF_EASTCHURCH,
				Leader	QUICKM33G4_item
			}
		},
//Follow Up escorts
		AirGroup //escort wave 1 pt 2
		{	
			NumInWing	4,
  			NumInForm	Scram_G3_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_RIGHT,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G3_Squad,
				NAT_LUF,
  				Scram_G3_Skill,
				MORALE_HIGH,
				Leader	QUICKM33G2_item_b
			}
		},
		AirGroup //escort wave 2 pt 2
		{	
			NumInWing	4,
  			NumInForm	Scram_G5_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_LEFT,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Leader	QUICKM33G2_item_c
			}
		}
	};

//--------------------------------
//DEMO 2

	BattleField
	{
		FileName	FIL_QUICKMISSION_34=QUICKM34.BF,
//DUMMY TO STOP CRASHES*************************
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
  			NumInForm	16,

  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	METRES4000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		},
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
  			NumInForm	16,

  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
  					 Abs	{Y Scram_G1_Alt},
					 Rel	{Bearing ANGLES_0Deg,
							 Range	METRES4000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G1_Skill
  			}
 		}
	};

//--------------------------------
//HISTORIC : 1
//END OF THE DEFIANT

	BattleField
	{
		FileName	FIL_QUICKMISSION_35=QUICKM35.BF,

		AirGroup	//DEFIANTS
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_CV_FOLKESTONE},
						 Abs	{Y Scram_G1_Alt},
						 Rel	{Bearing ANGLES_180Deg,
							 	 Pitch	ANGLES_0Deg,
							 	 Range	METRES6000	
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_CV_FOLKESTONE},
						 Abs	{Y Scram_G1_Alt},
						 Rel	{Bearing ANGLES_170Deg,
							 	 Pitch	ANGLES_0Deg,
							 	 Range	METRES6000	
								}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_2000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
  			NumInForm	Scram_G1_AC,
			Formation	SQD_RAFVIC_VIC,

  			DUTYMIGCAP,

			Posn	
				{Abs	{UID_CV_FOLKESTONE}, 
		 		Abs	{Y Scram_G1_Alt},
		 		Rel	{Bearing ANGLES_180Deg,
			 		Pitch	ANGLES_0Deg,
			 		Range	METRES6000	
					}
				},

			AirItem	quick_35_G1_aircraft =
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G1_Skill
//TempCode MS 20Jan00  				MoveCode	ACM_STRAIGHTANDLEVEL
  			}
 		},
		AirGroup	//HURRICANES IN DISTANCE
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_CV_FOLKESTONE}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_2000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,

  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
  					 Abs	{Y Scram_G0_Alt}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		},
		AirGroup	//ME109s diving down
		{
			Route	
			{
//TempCode MS 14Jan00 				WayPoint	
//TempCode MS 14Jan00 				{
//TempCode MS 14Jan00 					Posn	{Abs	quick_35_G1_aircraft,
//TempCode MS 14Jan00 						 Abs	{Y Scram_G1_Alt}
//TempCode MS 14Jan00 						}, 
//TempCode MS 14Jan00 					Action	wpacnoactionno
//TempCode MS 14Jan00 				},
				WayPoint	
				{
				 Posn	
						{Abs	{UID_CV_FOLKESTONE}, 
		 				Abs	{Y Scram_G1_Alt},
		 				Rel	{Bearing ANGLES_180Deg,
			 				Pitch	ANGLES_0Deg,
			 				Range	METRES6000	
							}
						},
					Action	wpacnoactionno
				},

				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_Audembert}, 
						 Abs	{Y FT_2000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	4,
  			NumInForm	Scram_G2_AC,
			Formation	SQD_SCHWARM_VIC,

  			DUTYMIGCAP,

//TempCode MS 14Jan00   			Posn	{Abs	{quick_35_G1_aircraft}, 
//TempCode MS 14Jan00   					 Abs	{Y Scram_G2_Alt},
//TempCode MS 14Jan00 					 Rel	{Bearing ANGLES_180Deg,
//TempCode MS 14Jan00 							 Pitch	ANGLES_0Deg,
//TempCode MS 14Jan00 							 Range	METRES2000
//TempCode MS 14Jan00 					},	

			Posn	
				{Abs	{UID_CV_FOLKESTONE}, 
		 		Abs	{Y Scram_G2_Alt},
		 		Rel	{Bearing ANGLES_180Deg,
			 		Pitch	ANGLES_0Deg,
			 		Range	METRES8000	
					}
				},

			AirItem
			{
				Scram_G2_Squad,
				Home	UID_AF_Audembert,
  				NAT_LUF,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
  				Scram_G2_Skill
//TempCode MS 14Jan00 				Target	quick_35_G1_aircraft
  			}
 		}
	};

//--------------------------------
//HISTORIC : 2 BOLLOX
//AlderTag Morning

	BattleField
	{
		FileName	FIL_QUICKMISSION_36=QUICKM36.BF
//DeadCode MS 06Jul00 		AirGroup	//luft bombers
//DeadCode MS 06Jul00 		{
//DeadCode MS 06Jul00 			Route	quick_36_G3_route =
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Target		{UID_AF_EASTCHURCH},
//DeadCode MS 06Jul00 					Posn		
//DeadCode MS 06Jul00 						{
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G0_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00 					Range	METRES5000,
//DeadCode MS 06Jul00 					Action	wpbombno	
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	UID_AF_Arras, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G0_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00  					Range	METRES6000,
//DeadCode MS 06Jul00 					Action	wpalandingno
//DeadCode MS 06Jul00 				}
//DeadCode MS 06Jul00  			},
//DeadCode MS 06Jul00 			
//DeadCode MS 06Jul00 			NumInWing	3,
//DeadCode MS 06Jul00   			NumInForm	12,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Formation	GRUP_LWVIC_ASTERN_ASTERN,
//DeadCode MS 06Jul00 			Duty	DA_LEVEL,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00   			Posn	{Abs	UID_AF_EASTCHURCH, 
//DeadCode MS 06Jul00 				 	 Abs	{Y Scram_G0_Alt},
//DeadCode MS 06Jul00 			 		 Rel	{Bearing ANGLES_90Deg,
//DeadCode MS 06Jul00 							 Pitch 	ANGLES_0Deg,
//DeadCode MS 06Jul00 						 	 Range KM10
//DeadCode MS 06Jul00 						} 
//DeadCode MS 06Jul00 					},	
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			AirItem	quick_36_G0_aircraft=
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Scram_G0_Squad,
//DeadCode MS 06Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 06Jul00   				NAT_LUF,
//DeadCode MS 06Jul00 				MORALE_HIGH,
//DeadCode MS 06Jul00   				Scram_G0_Skill,
//DeadCode MS 06Jul00 				Target	Pack_Target0
//DeadCode MS 06Jul00   			}
//DeadCode MS 06Jul00  		},

//TempCode MS 18Feb00 		AirGroup   
//TempCode MS 18Feb00 		{
//TempCode MS 18Feb00 			Route	quick_36_G0_route,
//TempCode MS 18Feb00 
//TempCode MS 18Feb00 			Posn		
//TempCode MS 18Feb00 				{Abs	quick_36_G0_aircraft, 
//TempCode MS 18Feb00 				 Abs	{Y Scram_G2_Alt}
//TempCode MS 18Feb00 				},
//TempCode MS 18Feb00 
//TempCode MS 18Feb00 			NumInWing	5,
//TempCode MS 18Feb00   			NumInForm	Scram_G2_AC,
//TempCode MS 18Feb00 
//TempCode MS 18Feb00 			Duty	DA_LEVEL,
//TempCode MS 18Feb00 			Formation	GRUP_LWVIC_ASTERN_ASTERN,
//TempCode MS 18Feb00 
//TempCode MS 18Feb00 		   	AirItem
//TempCode MS 18Feb00 			{
//TempCode MS 18Feb00 				Home	UID_AF_Audembert,
//TempCode MS 18Feb00 				Scram_G2_Squad,
//TempCode MS 18Feb00 				NAT_RED,
//TempCode MS 18Feb00   				Scram_G2_Skill,
//TempCode MS 18Feb00 				MORALE_HIGH,
//TempCode MS 18Feb00 				Leader	0
//TempCode MS 18Feb00 			}
//TempCode MS 18Feb00 		},

//TempCode MS 18Feb00 		AirGroup   
//TempCode MS 18Feb00 		{
//TempCode MS 18Feb00 //TempCode MS 17Feb00 			Route	quick_36_G0_route,
//TempCode MS 18Feb00 
//TempCode MS 18Feb00 			Posn		
//TempCode MS 18Feb00 				{Abs	quick_36_G0_aircraft, 
//TempCode MS 18Feb00 				 Abs	{Y Scram_G3_Alt}
//TempCode MS 18Feb00 				},
//TempCode MS 18Feb00 
//TempCode MS 18Feb00 			NumInWing	5,
//TempCode MS 18Feb00   			NumInForm	Scram_G3_AC,
//TempCode MS 18Feb00 
//TempCode MS 18Feb00 			Duty	DA_LEVEL,
//TempCode MS 18Feb00 			Formation	GRUP_LWVIC_ASTERN_ASTERN,
//TempCode MS 18Feb00 
//TempCode MS 18Feb00 		   	AirItem
//TempCode MS 18Feb00 			{
//TempCode MS 18Feb00 				Home	UID_AF_Audembert,
//TempCode MS 18Feb00 				Scram_G3_Squad,
//TempCode MS 18Feb00 				NAT_RED,
//TempCode MS 18Feb00   				Scram_G3_Skill,
//TempCode MS 18Feb00 				MORALE_HIGH,
//TempCode MS 18Feb00 				Leader	0
//TempCode MS 18Feb00 			}
//TempCode MS 18Feb00 		},
//TempCode MS 18Feb00 
//DeadCode MS 06Jul00 		AirGroup   
//DeadCode MS 06Jul00 		{
//DeadCode MS 06Jul00 			Route	
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn		
//DeadCode MS 06Jul00 						{Abs	quick_36_G0_aircraft, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G1_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00 					Action	wpacnoactionno	
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	UID_AF_BIGGINHILL, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G1_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00  					Range	METRES6000,
//DeadCode MS 06Jul00 					Action	wpalandingno
//DeadCode MS 06Jul00 				}
//DeadCode MS 06Jul00  			},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			NumInWing	3,
//DeadCode MS 06Jul00   			NumInForm	Scram_G1_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			DUTYMIGCAP,
//DeadCode MS 06Jul00 			Formation	SQD_RAFVIC_VIC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Posn		
//DeadCode MS 06Jul00 				{Abs	quick_36_G0_aircraft, 
//DeadCode MS 06Jul00 				 Abs	{Y Scram_G1_Alt},
//DeadCode MS 06Jul00 				 Rel	{Intercept	{quick_36_G0_aircraft,Pack_Target0},
//DeadCode MS 06Jul00 			 	 		 Bearing {Random ANGLES_310Deg,120,ANGLES_1Deg},
//DeadCode MS 06Jul00 						 Pitch 	ANGLES_0Deg,
//DeadCode MS 06Jul00 					 	 Range	{Random METRES2000,5,METRES500}
//DeadCode MS 06Jul00 						} 
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		   	AirItem
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Home	UID_AF_BIGGINHILL,
//DeadCode MS 06Jul00 				Scram_G1_Squad,
//DeadCode MS 06Jul00 				NAT_RAF,
//DeadCode MS 06Jul00   				Scram_G1_Skill,
//DeadCode MS 06Jul00 				MORALE_HIGH
//DeadCode MS 06Jul00 			}
//DeadCode MS 06Jul00 		}
	};

//--------------------------------
//HISTORIC : 3
//AlderTag Afternoon Aug 13th

	BattleField
	{
		FileName	FIL_QUICKMISSION_37=QUICKM37.BF,
		Setval	(PlyrWingSize, NumInWing (List Scram_G7_Squad,4,4,4,4,4,4,4,4,3,3,3,3,3)),

//WAVE 1
//KG 54 going to Portland

Setval	{firstobject,0x3fff};
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target		{UID_NB_Portland},
					Posn		
						{
						 Abs	{Y Scram_G4_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
  			NumInForm	Scram_G4_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,
			Duty	DA_LEVEL,

  			Posn	{Abs	UID_NB_Portland, 
				 	 Abs	{Y Scram_G4_Alt},
			 		 Rel	{Bearing ANGLES_100Deg,
							 Pitch 	ANGLES_0Deg,
						 	 Range SMILES10
						} 
					},	

			AirItem	//quick_37_G4_aircraft=
			{
				Scram_G4_Squad,
				Home	UID_AF_Evreaux,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G4_Skill,
				Target	UID_NB_Portland
  			}
 		},
Setval	{WPP_Msg0,firstobject};
Setval	{firstobject,0x3fff};

//WAVE 2
// Me 110s from V/LG1 Caen link up with KG54

		AirGroup   
		{
			Route
			{
				WayPoint	
				{
					Posn		
						{
//DeadCode RJS 10Nov00 						 Abs	quick_37_G4_aircraft,
						 Abs	WPP_Msg0,
						 Abs	{Y Scram_G5_Alt},
						 Rel	{Bearing ANGLES_260Deg,
								 Pitch ANGLES_0Deg,
								 Range METRES3000
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn		
						{
						 Abs	{UID_NB_Portland},
						 Abs	{Y Scram_G5_Alt},
						 Rel	{Bearing ANGLES_260Deg,
								 Pitch ANGLES_0Deg,
								 Range METRES3000
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				}
 			},

			Posn		
				{
				 Abs	WPP_Msg0,	//quick_37_G4_aircraft,
				 Abs	{Y Scram_G5_Alt},
				 Rel	{Bearing ANGLES_100Deg,
						 Pitch ANGLES_0Deg,
						 Range METRES3000
						}
				},

			NumInWing	4,
  			NumInForm	Scram_G5_AC,

  			DUTYMIGCAP,
			Formation	GRUP_SCHWARM_VIC_VIC,

		   	AirItem	//quick_37_G5_aircraft=
			{
				Home	UID_AF_Caen,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				Bombs	1,		//MS 05Sep00
				MORALE_HIGH
			}
		},

Setval	{WPP_Msg1,firstobject};
Setval	{firstobject,0x3fff};
//WAVE 3
//LG1 JU88s to Southampton

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target		{UID_DK_Southampton},
					Posn		
						{
						 Abs	{Y Scram_G6_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G6_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G6_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G6_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
  			NumInForm	Scram_G6_AC,

			Formation	GRUP_LWVIC_VIC_VIC,
			Duty	DA_LEVEL,

  			Posn	{Abs	UID_DK_Southampton, 
				 	 Abs	{Y Scram_G6_Alt},
			 		 Rel	{Bearing ANGLES_150Deg,
							 Pitch 	ANGLES_0Deg,
						 	 Range SMILES10
						} 
					},	

			AirItem	//quick_37_G6_aircraft=
			{
				Scram_G6_Squad,
				Home	UID_AF_Dreux,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G6_Skill,
				Target	UID_DK_Southampton
  			}
 		},

Setval	{WPP_Msg2,firstobject};
Setval	{firstobject,0x3fff};

//WAVE 4
//JU87 II/St.G to Middle Wallop, Hit at Lyme Regis
//?????????

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target		{UID_AF_MIDDLEWALLOP},
					Posn		
						{
						 Abs	{Y Scram_G7_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G7_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G7_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	PlyrWingSize,
  			NumInForm	Scram_G7_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,
			Duty	AM_DIVEBOMB,

  			Posn	{Abs	UID_AF_MIDDLEWALLOP, 
				 	 Abs	{Y Scram_G7_Alt},
			 		 Rel	{Bearing ANGLES_220Deg,
							 Pitch 	ANGLES_0Deg,
						 	 Range SMILES10
						} 
					},	

			AirItem	//quick_37_G7_aircraft=
			{
				Scram_G7_Squad,
				Home	UID_AF_Lannion,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G7_Skill,
				Target	UID_AF_MIDDLEWALLOP
  			}
 		},

Setval	{WPP_Msg3,firstobject};
Setval	{firstobject,0x3fff};

//152 spits from Warmwell intercept east of Portland

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg0,	//quick_37_G4_aircraft,
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_WARMWELL, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	SQD_RAFVIC_VIC,

			Posn		
				{
				 Abs	{UID_NB_Portland},
				 Abs	{Y Scram_G0_Alt},
				 Rel	{Bearing ANGLES_20Deg,
						 Pitch ANGLES_0Deg,
						 Range METRES3000
					}
				},

		   	AirItem
			{
				Home	UID_AF_WARMWELL,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH
			}
		},

//213 from exeter close to KG 54

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg0,	//quick_37_G4_aircraft,
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_EXETER, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G1_AC,

			DUTYMIGCAP,
			Formation	SQD_RAFVIC_VIC,

			Posn		
				{
				 Abs	WPP_Msg0,	//quick_37_G4_aircraft,
				 Abs	{Y Scram_G1_Alt},
				 Rel	{Bearing ANGLES_250Deg,
						 Pitch ANGLES_0Deg,
						 Range METRES5000
					}
				},

		   	AirItem
			{
				Home	UID_AF_EXETER,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				MORALE_HIGH
			}
		},

//609 squadron from Middle Wallop

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg3,	//quick_37_G7_aircraft,
						 Abs	{Y Scram_G2_Alt},
						 Rel	{Bearing	ANGLES_270Deg,
								 Range	METRES5000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_MIDDLEWALLOP, 
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G2_AC,

			DUTYMIGCAP,
			Formation	SQD_RAFVIC_VIC,
			Posn		
				{
				 Abs	WPP_Msg3,	//quick_37_G7_aircraft,
				 Abs	{Y Scram_G2_Alt},
				 Rel	{Bearing ANGLES_20Deg,
						 Pitch ANGLES_0Deg,
						 Range METRES5000
					}
				},

		   	AirItem
			{
				Home	UID_AF_MIDDLEWALLOP,
				Scram_G2_Squad,
				NAT_RAF,
  				Scram_G2_Skill,
				MORALE_HIGH
			}
		},

//WAVE 5
//43 +257 squadrons from ??

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg2,	//quick_37_G6_aircraft,
						 Abs	{Y Scram_G3_Alt},
						 Rel	{Bearing	ANGLES_90Deg,
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_MIDDLEWALLOP, 
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G3_AC,

			DUTYMIGCAP,
			Formation	SQD_RAFVIC_VIC,

			Posn		
				{
				 Abs	WPP_Msg2,	//quick_37_G6_aircraft,
				 Abs	{Y Scram_G3_Alt},
				 Rel	{Bearing ANGLES_30Deg,
						 Pitch ANGLES_0Deg,
						 Range METRES5000
					}
				},

		   	AirItem
			{
				Home	UID_AF_MIDDLEWALLOP,
				Scram_G3_Squad,
				NAT_RAF,
  				Scram_G3_Skill,
				MORALE_HIGH
			}
		},

//EXTRA WAVES

//WAVE 1 Pt 2

		AirGroup	
		{
			
			NumInWing	5,
  			NumInForm	Scram_G4_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,
			Duty	DA_LEVEL,

			AirItem	
			{
				Scram_G4_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_StAndreDeLEure,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G4_Skill,
				Target	UID_NB_Portland,
				Leader	WPP_Msg0	//quick_37_G4_aircraft
  			}
 		},

//WAVE 1 Pt 3

		AirGroup	
		{
			
			NumInWing	5,
  			NumInForm	10,

			Formation	GRUP_LWVIC_ASTERN_VIC2,
			Duty	DA_LEVEL,

			AirItem	
			{
				Scram_G4_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_BeaumontLeRoger,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G4_Skill,
				Target	UID_NB_Portland,
				Leader	WPP_Msg0	//quick_37_G4_aircraft
  			}
 		},

//WAVE 2 Pt 2

		AirGroup   
		{

			NumInWing	4,
  			NumInForm	Scram_G5_AC,

  			DUTYMIGCAP,
			Formation	GRUP_SCHWARM_VIC_VIC,

		   	AirItem	
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Plumetot,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg1	//quick_37_G5_aircraft
			}
		},

//WAVE 2 Pt 3

		AirGroup   
		{

			NumInWing	4,
  			NumInForm	Scram_G5_AC,

  			DUTYMIGCAP,
			Formation	GRUP_SCHWARM_VIC_VIC2,

		   	AirItem	
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Crepon,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg1	//quick_37_G5_aircraft
			}
		},

//WAVE 3 Pt 2

		AirGroup	
		{
			
			NumInWing	5,
  			NumInForm	Scram_G6_AC,

			Formation	GRUP_LWVIC_VIC_VIC,
			Duty	DA_LEVEL,

			AirItem	
			{
				Scram_G6_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Guyancourt,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G6_Skill,
				Target	UID_DK_Southampton,
				Leader	WPP_Msg2	//quick_37_G6_aircraft
  			}
 		},

//WAVE 3 Pt 3

		AirGroup	
		{
			
			NumInWing	5,
  			NumInForm	Scram_G6_AC,

			Formation	GRUP_LWVIC_VIC_VIC2,
			Duty	DA_LEVEL,

			AirItem	
			{
				Scram_G6_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Villacoublay,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G6_Skill,
				Target	UID_DK_Southampton,
				Leader	WPP_Msg2	//quick_37_G6_aircraft
  			}
 		},

//WAVE 3 Pt 4 Going to Andover

Setval	{firstobject,0x3fff};

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target		{UID_AF_ANDOVER},
					Posn		
						{
						 Abs	{Y Scram_G6_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G6_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G6_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
  			NumInForm	Scram_G6_AC,

			Formation	GRUP_LWVIC_VIC_VIC,
			Duty	DA_LEVEL,

  			Posn	{Abs	WPP_Msg2,	//quick_37_G6_aircraft, 
				 	 Abs	{Y Scram_G6_Alt},
			 		 Rel	{Bearing ANGLES_270Deg,
							 Pitch 	ANGLES_0Deg,
						 	 Range METRES5000
						} 
					},	

			AirItem	//quick_37_G6_aircraft_b=
			{
				Scram_G6_Squad,
				Home	UID_AF_CormeillesEnVexin,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G6_Skill,
				Target	UID_AF_ANDOVER
  			}
 		},

Setval	{WPP_Msg4,firstobject};
Setval	{firstobject,0x3fff};

//WAVE 3 Pt 5 Going to Andover

		AirGroup	
		{
			
			NumInWing	5,
  			NumInForm	Scram_G6_AC,

			Formation	GRUP_LWVIC_VIC_VIC,
			Duty	DA_LEVEL,

			AirItem	
			{
				Scram_G6_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Orly,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G6_Skill,
				Target	UID_AF_ANDOVER,
				Leader	WPP_Msg4	//quick_37_G6_aircraft_b
  			}
 		},

//WAVE 4 Pt 2

		AirGroup	
		{
			
			NumInWing	PlyrWingSize,
  			NumInForm	Scram_G7_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,
			Duty	AM_DIVEBOMB,

			AirItem	
			{
				Scram_G7_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Dinan,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G7_Skill,
				Target	UID_AF_WARMWELL,
				Leader	WPP_Msg3	//quick_37_G7_aircraft
  			}
 		},

//WAVE 5 Pt 2
//257 squadrons

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg2,	//quick_37_G6_aircraft,
						 Abs	{Y Scram_G3_Alt},
						 Rel	{Bearing	ANGLES_270Deg,
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_MIDDLEWALLOP, 
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G3_AC,

			DUTYMIGCAP,
			Formation	SQD_RAFVIC_VIC,

			Posn		
				{
				 Abs	WPP_Msg2,	//quick_37_G6_aircraft,
				 Abs	{Y Scram_G3_Alt},
				 Rel	{Bearing ANGLES_340Deg,
						 Pitch ANGLES_0Deg,
						 Range METRES5000
					}
				},

		   	AirItem
			{
				Home	UID_AF_MIDDLEWALLOP,
				Scram_G3_Squad,
				NAT_RAF,
  				Scram_G3_Skill,
				MORALE_HIGH
			}
		},

//601 Sqdn from Tangmere

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg0,	//quick_37_G4_aircraft,
						 Abs	{Y Scram_G0_Alt},
						 Rel	{Bearing ANGLES_260Deg,
								 Pitch ANGLES_0Deg,
								 Range METRES3000
								}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_TANGMERE, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	SQD_RAFVIC_VIC,

			Posn		
//TempCode MS 10Oct00 				{
//TempCode MS 10Oct00 				 Abs	quick_37_G5_aircraft,
//TempCode MS 10Oct00 				 Abs	{Y Scram_G0_Alt},
//TempCode MS 10Oct00 				 Rel	{Bearing ANGLES_80Deg,
//TempCode MS 10Oct00 						 Pitch ANGLES_0Deg,
//TempCode MS 10Oct00 						 Range METRES3000
//TempCode MS 10Oct00 					}
				{
				 Abs	WPP_Msg0,	//quick_37_G4_aircraft,
				 Abs	{Y Scram_G0_Alt},
				 Rel	{Bearing ANGLES_135Deg,
						 Pitch ANGLES_0Deg,
						 Range METRES3000
					}
				},

		   	AirItem
			{
				Home	UID_AF_TANGMERE,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH
//TempCode MS 10Oct00 				Target	quick_37_G5_aircraft
			}
		}

	};

//--------------------------------
//HISTORIC : 4	BIG WING BATTLE OF BRITAIN DAY

	BattleField
	{
		FileName	FIL_QUICKMISSION_38=QUICKM38.BF,

Setval	{firstobject,0x3fff};

		AirGroup	//luft bombers
		{	//GROUP 1:	LW BOMBERS
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G3_Alt}
						},
					Action	wpacnoactionno,
					Range	KM10	
				},
				WayPoint	
				{
					Target	{Pack_Target0},	
					Posn	{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	3,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	4,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
			NumInForm	Scram_G3_AC,

			Formation	GRUP_LWVIC_VIC_ASTERN,
			Duty	DA_LEVEL,

			Posn	
				{Abs	{Pack_Target0}, 
				 Abs	{Y Scram_G3_Alt},
		 		 Rel	{Intercept	{Pack_Target0,UID_NV_DUNGENESS},
				 		 Bearing	ANGLES_0Deg,
						 Pitch	ANGLES_0Deg,
						 Range	METRES20KM
						}
				},

			AirItem		//QUICK38_AC_00 =
			{
				Scram_G3_Squad,
				Home	UID_AF_Tramecourt,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G3_Skill,
				Target	Pack_Target0
  			}
 		},

Setval	{WPP_Msg0,firstobject};
Setval	{firstobject,0x3fff};

//THE SECOND SET OF BOMBERS THAT BOTTLE IT
		AirGroup	//luft bombers
		{	//GROUP 1:	LW BOMBERS
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{Pack_Target0}, 
						 Abs	{Y Scram_G4_Alt},
				 		 Rel	{Intercept	{Pack_Target0,UID_NV_DUNGENESS},
						 		 Bearing	ANGLES_315Deg,
								 Pitch	ANGLES_0Deg,
						 		 Range	METRES750
								}
						},
					Action	wpacnoactionno,
					Range	KM10	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	3,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	4,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
			NumInForm	Scram_G4_AC,

			Formation	GRUP_LWVIC_VIC_ASTERN,
			Duty	DA_LEVEL,

			Posn	
				{Abs	WPP_Msg0,	//QUICK38_AC_00, 
				 Abs	{Y Scram_G4_Alt},
		 		 Rel	{Intercept	{Pack_Target0,UID_NV_DUNGENESS},
				 		 Bearing	ANGLES_315Deg,
						 Pitch	ANGLES_0Deg,
						 Range	METRES750
						}
				},

			AirItem	//QUICK38_AC_01 =	
			{
				Scram_G4_Squad,
				Home	UID_AF_Abbeville,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G4_Skill,
				Target	Pack_Target0
  			}
 		},

Setval	{WPP_Msg1,firstobject};
Setval	{firstobject,0x3fff};

//Escort Wave 1

		AirGroup   
		{	
			NumInWing	4,
  			NumInForm	Scram_G5_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_LEFT,

		   	AirItem	//QUICK38_AC_01b = 
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg0	//QUICK38_AC_00
			}
		},

Setval	{WPP_Msg2,firstobject};
Setval	{firstobject,0x3fff};


//RAF
//1st set of paired squadrons

		AirGroup   
		{	//GROUP 0: RAF AIRCRAFT
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	WPP_Msg0,	//QUICK38_AC_00, 
				 		 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_KENLEY, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES2000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn	
				{Abs	WPP_Msg0,	//QUICK38_AC_00, 
		 		 Abs	{Y Scram_G0_Alt},
 		 		 Rel	{Intercept	{Pack_Target0,UID_NV_DUNGENESS},
				 		 Pitch		ANGLES_0Deg,
		 		 		 Bearing	ANGLES_180Deg,
				 		 Range	METRES4000
						}
				},

		   	AirItem		QUICK38_AC_G0a = 
			{
				Home	UID_AF_KENLEY,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH,
				Target	WPP_Msg0,	//QUICK38_AC_00,
				ACM_STRAIGHTANDLEVEL
			}
		},

//DUXFORD WING
		AirGroup   
		{	//GROUP 0: RAF AIRCRAFT
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	WPP_Msg0,	//QUICK38_AC_00, 
				 		 Abs	{Y Scram_G3_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_DUXFORD, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES2000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G1_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn	
				{Abs	WPP_Msg0,	//QUICK38_AC_00, 
		 		 Abs	{Y Scram_G1_Alt},
 		 		 Rel	{Intercept	{UID_NV_DUNGENESS,Pack_Target0},
				 		 Pitch		ANGLES_0Deg,
		 		 		 Bearing	ANGLES_270Deg,
				 		 Range	{Select METRES3000,0,METRES100}
						}
				},

		   	AirItem		QUICK38_AC_02 = 
			{
				Home	UID_AF_DUXFORD,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				MORALE_HIGH,
				Target	WPP_Msg0,	//QUICK38_AC_00,
				ACM_DIVEANDZOOM
			}
		},
//ESCORT SPITS
		AirGroup   
		{	//RAF AIRCRAFT
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	WPP_Msg0,	//QUICK38_AC_00, 
				 		 Abs	{Y Scram_G5_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_DUXFORD, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES2000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G2_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn	
				{Abs	QUICK38_AC_02, 
		 		 Abs	{Y Scram_G2_Alt},
 		 		 Rel	{Intercept	{Pack_Target0,UID_NV_DUNGENESS},
		 		 		 Bearing	ANGLES_90Deg,
				 		 Pitch		ANGLES_0Deg,
				 		 Range	METRES500
						}
				},

		   	AirItem	QUICK38_AC_03=
			{
				Home	UID_AF_DUXFORD,
				Scram_G2_Squad,
				NAT_RAF,
  				Scram_G2_Skill,
				MORALE_HIGH
//DeadCode MS 13Nov00 				Target	WPP_Msg2,	//QUICK38_AC_01b,
//DeadCode MS 13Nov00 				ACM_DIVEANDZOOM
			}
		},

//THIS IS WHERE ALL THE EXTRA GROUPS GO!!!!!!!
		AirGroup   
		{	//GROUP 2: IN FORMATION WITH GROUP 0

			NumInWing	5,
			NumInForm	Scram_G3_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_ASTERN,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G3_Squad,
				NAT_LUF,
  				Scram_G3_Skill,
				MORALE_HIGH,
				Leader	WPP_Msg0	//QUICK38_AC_00
			}
		},
		AirGroup   
		{	//GROUP 3: INFORMATION WITH GROUP 0

			NumInWing	5,
			NumInForm	Scram_G3_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_ASTERN2,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Tramecourt,
				Scram_G3_Squad,
				NAT_LUF,
  				Scram_G3_Skill,
				MORALE_HIGH,
				Leader	WPP_Msg0	//QUICK38_AC_00
			}
		},
		AirGroup   
		{	//GROUP 2: IN FORMATION WITH GROUP 1

			NumInWing	5,
			NumInForm	Scram_G4_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_ASTERN,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Abbeville,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Leader	WPP_Msg1	//QUICK38_AC_01
			}
		},
		AirGroup   
		{	//GROUP 3: INFORMATION WITH GROUP 1

			NumInWing	5,
			NumInForm	Scram_G4_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_ASTERN2,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Tramecourt,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Leader	WPP_Msg1	//QUICK38_AC_01
			}
		},
//EXTRA ESCORT
		AirGroup   
		{	
			NumInWing	4,
  			NumInForm	Scram_G5_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_RIGHT,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg0	//QUICK38_AC_00
			}
		},
//Escort Wave 2

		AirGroup   
		{	
			NumInWing	4,
  			NumInForm	Scram_G5_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_LEFT,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg1	//QUICK38_AC_01
			}
		},

		AirGroup   
		{	
			NumInWing	4,
  			NumInForm	Scram_G5_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_RIGHT,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg1	//QUICK38_AC_01
			}
		},
//EXTRA RAF - Oh, Joy
		AirGroup   
		{	

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

		   	AirItem
			{
				Home	UID_AF_KENLEY,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH,
				Leader	QUICK38_AC_G0a
			}
		},
//2nd set of paired sqdns
		AirGroup   
		{	//GROUP 0: RAF AIRCRAFT
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	WPP_Msg1,	//QUICK38_AC_01, 
				 		 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_MANSTON, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn	
				{Abs	WPP_Msg1,	//QUICK38_AC_01, 
		 		 Abs	{Y Scram_G0_Alt},
 		 		 Rel	{Intercept	{Pack_Target0,UID_NV_DUNGENESS},
				 		 Pitch		ANGLES_0Deg,
		 		 		 Bearing	ANGLES_180Deg,
				 		 Range	METRES5000
						}
				},

		   	AirItem		QUICK38_AC_G0b =
			{
				Home	UID_AF_DUXFORD,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH,
				Target	WPP_Msg1,	//QUICK38_AC_01,
				ACM_STRAIGHTANDLEVEL
			}
		},
		AirGroup   
		{	

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

		   	AirItem
			{
				Home	UID_AF_DUXFORD,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH,
				Leader	QUICK38_AC_G0b
			}
		},
//EXTRA WAVES DUXFORD WING HURRIS
		AirGroup   
		{	

			NumInWing	3,
  			NumInForm	Scram_G1_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

		   	AirItem
			{
				Home	UID_AF_DUXFORD,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				MORALE_HIGH,
				Leader	QUICK38_AC_02
			}
		},
		AirGroup   
		{	

			NumInWing	3,
  			NumInForm	Scram_G1_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC2,

		   	AirItem
			{
				Home	UID_AF_DUXFORD,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				MORALE_HIGH,
				Leader	QUICK38_AC_02
			}
		},
//EXTRA WAVES DUXFORD WING SPITS
		AirGroup   
		{	
			NumInWing	3,
  			NumInForm	Scram_G2_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

		   	AirItem	
			{
				Home	UID_AF_DUXFORD,
				Scram_G2_Squad,
				NAT_RAF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Leader	QUICK38_AC_03
			}
		}
	};

//--------------------------------
//HISTORIC : 5

	BattleField
	{
		FileName	FIL_QUICKMISSION_39=QUICKM39.BF,

		AirGroup	//luft bombers
		{
			Route	quick_39_G3_route =
			{
				WayPoint	
				{
					Target		{UID_AF_EASTCHURCH},
					Posn		
						{
						 Abs	{Y Scram_G1_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_Arras, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
  			NumInForm	12,

			Formation	GRUP_LWVIC_ASTERN_ASTERN,
			Duty	DA_LEVEL,

  			Posn	{Abs	UID_AF_EASTCHURCH, 
				 	 Abs	{Y Scram_G1_Alt},
			 		 Rel	{Bearing ANGLES_90Deg,
							 Pitch 	ANGLES_0Deg,
						 	 Range KM10
						} 
					},	

			AirItem	quick_39_G1_aircraft=
			{
				Scram_G1_Squad,
				Home	UID_AF_Arras,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Target	Pack_Target0
  			}
 		},

		AirGroup   
		{
//TempCode MS 01Mar00 			Route	quick_39_G1_route,

			Posn		
				{Abs	quick_39_G1_aircraft, 
				 Abs	{Y Scram_G2_Alt}
				},

			NumInWing	5,
  			NumInForm	Scram_G2_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_ASTERN_ASTERN,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G2_Squad,
				NAT_LUF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Leader	0
			}
		},

		AirGroup   
		{
//TempCode MS 17Feb00 			Route	quick_39_G1_route,

			Posn		
				{Abs	quick_39_G1_aircraft, 
				 Abs	{Y Scram_G3_Alt}
				},

			NumInWing	5,
  			NumInForm	Scram_G3_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_ASTERN_ASTERN,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G3_Squad,
				NAT_LUF,
  				Scram_G3_Skill,
				MORALE_HIGH,
				Leader	0
			}
		},

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{Abs	quick_39_G1_aircraft, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_BIGGINHILL, 
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	SQD_RAFVIC_VIC,

			Posn		
				{Abs	quick_39_G1_aircraft, 
				 Abs	{Y Scram_G0_Alt},
				 Rel	{Intercept	{quick_39_G1_aircraft,Pack_Target0},
			 	 		 Bearing {Random ANGLES_310Deg,120,ANGLES_1Deg},
						 Pitch 	ANGLES_0Deg,
					 	 Range	{Random METRES2000,5,METRES500}
						} 
				},

		   	AirItem
			{
				Home	UID_AF_BIGGINHILL,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH
			}
		}
	};

//--------------------------------
//HISTORIC : 6 Sep 9th

	BattleField
	{
		FileName	FIL_QUICKMISSION_40=QUICKM40.BF,
//DeadCode MS 06Jul00 		AirGroup	//luft bombers
//DeadCode MS 06Jul00 		{	//GROUP 1:	LW BOMBERS
//DeadCode MS 06Jul00 			Route	
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	{Pack_Target0}, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G3_Alt},
//DeadCode MS 06Jul00 						 Rel	{Bearing	ANGLES_135Deg,
//DeadCode MS 06Jul00 								 Pitch	ANGLES_0Deg,
//DeadCode MS 06Jul00 								 Range	{Select KM10,1,KM10}
//DeadCode MS 06Jul00 								}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00 					Action	wpacnoactionno	
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	UID_AF_Audembert, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G3_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00  					Range	METRES6000,
//DeadCode MS 06Jul00 					Action	wpalandingno
//DeadCode MS 06Jul00 				}
//DeadCode MS 06Jul00  			},
//DeadCode MS 06Jul00 			
//DeadCode MS 06Jul00 			NumInWing	3,
//DeadCode MS 06Jul00 			NumInForm	Scram_G3_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Formation	GRUP_LWVIC_VIC_ASTERN,
//DeadCode MS 06Jul00 			Duty	DA_LEVEL,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00   			Posn	{Abs	Pack_Target0, 
//DeadCode MS 06Jul00 				 	 Abs	{Y Scram_G3_Alt},
//DeadCode MS 06Jul00 			 		 Rel	{Bearing {Random ANGLES_90Deg,90,ANGLES_1Deg},
//DeadCode MS 06Jul00 							 Pitch 	ANGLES_0Deg,
//DeadCode MS 06Jul00 						 	 Range METRES2000
//DeadCode MS 06Jul00 						} 
//DeadCode MS 06Jul00 					},	
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			AirItem	
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				PT_JU88,
//DeadCode MS 06Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 06Jul00   				NAT_LUF,
//DeadCode MS 06Jul00 				MORALE_HIGH,
//DeadCode MS 06Jul00   				Scram_G3_Skill,
//DeadCode MS 06Jul00 				Target	Pack_Target0
//DeadCode MS 06Jul00   			}
//DeadCode MS 06Jul00  		},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		AirGroup   
//DeadCode MS 06Jul00 		{	//GROUP 2: IN FORMATION WITH GROUP 1
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			NumInWing	3,
//DeadCode MS 06Jul00   			NumInForm	Scram_G4_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Duty	DA_LEVEL,
//DeadCode MS 06Jul00 			Formation	GRUP_LWVIC_VIC_ASTERN,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		   	AirItem
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 06Jul00 				PT_JU88,
//DeadCode MS 06Jul00 				NAT_LUF,
//DeadCode MS 06Jul00   				Scram_G4_Skill,
//DeadCode MS 06Jul00 				MORALE_HIGH,
//DeadCode MS 06Jul00 				Leader	0
//DeadCode MS 06Jul00 			}
//DeadCode MS 06Jul00 		},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		AirGroup   
//DeadCode MS 06Jul00 		{	//GROUP 3: INFORMATION WITH GROUP 0
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			NumInWing	3,
//DeadCode MS 06Jul00   			NumInForm	Scram_G5_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Duty	DA_LEVEL,
//DeadCode MS 06Jul00 			Formation	GRUP_LWVIC_VIC_ASTERN2,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		   	AirItem
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 06Jul00 				PT_JU88,
//DeadCode MS 06Jul00 				NAT_LUF,
//DeadCode MS 06Jul00   				Scram_G5_Skill,
//DeadCode MS 06Jul00 				MORALE_HIGH,
//DeadCode MS 06Jul00 				Leader	0
//DeadCode MS 06Jul00 			}
//DeadCode MS 06Jul00 		},
//DeadCode MS 06Jul00 //GERMAN FIGHTERs
//DeadCode MS 06Jul00 		AirGroup   
//DeadCode MS 06Jul00 		{	//GROUP 4: German Fighter Sweep
//DeadCode MS 06Jul00 			Route	
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	{Pack_Target0}, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G3_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00 					Action	wpacnoactionno	
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	UID_AF_Wissant, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G3_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00  					Range	METRES6000,
//DeadCode MS 06Jul00 					Action	wpalandingno
//DeadCode MS 06Jul00 				}
//DeadCode MS 06Jul00  			},
//DeadCode MS 06Jul00 			
//DeadCode MS 06Jul00 			NumInWing	2,
//DeadCode MS 06Jul00 			NumInForm	Scram_G3_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Formation	GRUP_SCHWARM_VIC_VIC,
//DeadCode MS 06Jul00   			DUTYMIGCAP,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00   			Posn	{Abs	Pack_Target0, 
//DeadCode MS 06Jul00 				 	 Abs	{Y Scram_G3_Alt},
//DeadCode MS 06Jul00 			 		 Rel	{Bearing {Random ANGLES_90Deg,90,ANGLES_1Deg},
//DeadCode MS 06Jul00 							 Pitch 	ANGLES_0Deg,
//DeadCode MS 06Jul00 						 	 Range METRES2000
//DeadCode MS 06Jul00 						} 
//DeadCode MS 06Jul00 					},	
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			AirItem	
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Scram_G3_Squad,
//DeadCode MS 06Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 06Jul00   				NAT_LUF,
//DeadCode MS 06Jul00 				MORALE_HIGH,
//DeadCode MS 06Jul00   				Scram_G3_Skill
//DeadCode MS 06Jul00   			}
//DeadCode MS 06Jul00  		},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		AirGroup   
//DeadCode MS 06Jul00 		{	//GROUP 5: IN FORMATION WITH GROUP 4
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			NumInWing	2,
//DeadCode MS 06Jul00   			NumInForm	Scram_G4_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Duty	DA_LEVEL,
//DeadCode MS 06Jul00 			Formation	GRUP_SCHWARM_VIC_VIC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		   	AirItem
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 06Jul00 				Scram_G4_Squad,
//DeadCode MS 06Jul00 				NAT_LUF,
//DeadCode MS 06Jul00   				Scram_G4_Skill,
//DeadCode MS 06Jul00 				MORALE_HIGH,
//DeadCode MS 06Jul00 				Leader	0
//DeadCode MS 06Jul00 			}
//DeadCode MS 06Jul00 		},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		AirGroup   
//DeadCode MS 06Jul00 		{	//GROUP 6: INFORMATION WITH GROUP 4
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			NumInWing	3,
//DeadCode MS 06Jul00   			NumInForm	Scram_G5_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Duty	DA_LEVEL,
//DeadCode MS 06Jul00 			Formation	GRUP_LWVIC_VIC_ASTERN2,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		   	AirItem
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 06Jul00 				Scram_G5_Squad,
//DeadCode MS 06Jul00 				NAT_LUF,
//DeadCode MS 06Jul00   				Scram_G5_Skill,
//DeadCode MS 06Jul00 				MORALE_HIGH,
//DeadCode MS 06Jul00 				Leader	0
//DeadCode MS 06Jul00 			}
//DeadCode MS 06Jul00 		},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		AirGroup   
//DeadCode MS 06Jul00 		{	//GROUP 0: RAF AIRCRAFT
//DeadCode MS 06Jul00 			Route	
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	{Pack_Target0}, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G0_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00 					Action	wpacnoactionno	
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	UID_AF_MANSTON, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G0_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00  					Range	METRES2000,
//DeadCode MS 06Jul00 					Action	wpalandingno
//DeadCode MS 06Jul00 				}
//DeadCode MS 06Jul00  			},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			NumInWing	3,
//DeadCode MS 06Jul00   			NumInForm	Scram_G0_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			DUTYMIGCAP,
//DeadCode MS 06Jul00 			Formation	SQD_RAFVIC_VIC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Posn		
//DeadCode MS 06Jul00 				{Abs	{Pack_Target0}, 
//DeadCode MS 06Jul00 				 Abs	{Y Scram_G0_Alt},
//DeadCode MS 06Jul00 				 Rel	{Intercept	{Pack_Target0,UID_AF_MANSTON},
//DeadCode MS 06Jul00 			 	 		 Bearing {Random ANGLES_355Deg,10,ANGLES_1Deg},
//DeadCode MS 06Jul00 						 Pitch 	ANGLES_0Deg,
//DeadCode MS 06Jul00 					 	 Range	{Random METRES1000,3,METRES500}
//DeadCode MS 06Jul00 						} 
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		   	AirItem
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Home	UID_AF_MANSTON,
//DeadCode MS 06Jul00 				Scram_G0_Squad,
//DeadCode MS 06Jul00 				NAT_RAF,
//DeadCode MS 06Jul00   				Scram_G0_Skill,
//DeadCode MS 06Jul00 				MORALE_HIGH
//DeadCode MS 06Jul00 			}
//DeadCode MS 06Jul00 		},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		AirGroup   
//DeadCode MS 06Jul00 		{	//GROUP 1: RAF AIRCRAFT	HURRICANES
//DeadCode MS 06Jul00 			Route	
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	{Pack_Target0}, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G1_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00 					Action	wpacnoactionno	
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	UID_AF_HAWKINGE, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G1_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00  					Range	METRES2000,
//DeadCode MS 06Jul00 					Action	wpalandingno
//DeadCode MS 06Jul00 				}
//DeadCode MS 06Jul00  			},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			NumInWing	3,
//DeadCode MS 06Jul00   			NumInForm	Scram_G1_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			DUTYMIGCAP,
//DeadCode MS 06Jul00 			Formation	SQD_RAFVIC_VIC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Posn		
//DeadCode MS 06Jul00 				{Abs	{Pack_Target0}, 
//DeadCode MS 06Jul00 				 Abs	{Y Scram_G1_Alt},
//DeadCode MS 06Jul00 				 Rel	{Intercept	{Pack_Target0,UID_AF_HAWKINGE},
//DeadCode MS 06Jul00 			 	 		 Bearing {Random ANGLES_355Deg,10,ANGLES_1Deg},
//DeadCode MS 06Jul00 						 Pitch 	ANGLES_0Deg,
//DeadCode MS 06Jul00 					 	 Range	{Random METRES3000,5,METRES500}
//DeadCode MS 06Jul00 						} 
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		   	AirItem
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Home	UID_AF_HAWKINGE,
//DeadCode MS 06Jul00 				Scram_G1_Squad,
//DeadCode MS 06Jul00 				NAT_RAF,
//DeadCode MS 06Jul00   				Scram_G1_Skill,
//DeadCode MS 06Jul00 				MORALE_HIGH
//DeadCode MS 06Jul00 			}
//DeadCode MS 06Jul00 		},
//DeadCode MS 06Jul00 		AirGroup   
//DeadCode MS 06Jul00 		{	//GROUP 2: RAF AIRCRAFT	HURRICANES
//DeadCode MS 06Jul00 			Route	
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	{Pack_Target0}, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G2_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00 					Action	wpacnoactionno	
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 				WayPoint	
//DeadCode MS 06Jul00 				{
//DeadCode MS 06Jul00 					Posn	
//DeadCode MS 06Jul00 						{Abs	UID_AF_HAWKINGE, 
//DeadCode MS 06Jul00 						 Abs	{Y Scram_G2_Alt}
//DeadCode MS 06Jul00 						},
//DeadCode MS 06Jul00  					Range	METRES2000,
//DeadCode MS 06Jul00 					Action	wpalandingno
//DeadCode MS 06Jul00 				}
//DeadCode MS 06Jul00  			},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			NumInWing	3,
//DeadCode MS 06Jul00   			NumInForm	Scram_G2_AC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			DUTYMIGCAP,
//DeadCode MS 06Jul00 			Formation	SQD_RAFVIC_VIC,
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 			Posn		
//DeadCode MS 06Jul00 				{Abs	{Pack_Target0}, 
//DeadCode MS 06Jul00 				 Abs	{Y Scram_G2_Alt},
//DeadCode MS 06Jul00 				 Rel	{Intercept	{Pack_Target0,UID_AF_HAWKINGE},
//DeadCode MS 06Jul00 			 	 		 Bearing {Random ANGLES_355Deg,10,ANGLES_1Deg},
//DeadCode MS 06Jul00 						 Pitch 	ANGLES_0Deg,
//DeadCode MS 06Jul00 					 	 Range	{Random METRES8000,5,METRES500}
//DeadCode MS 06Jul00 						} 
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 
//DeadCode MS 06Jul00 		   	AirItem
//DeadCode MS 06Jul00 			{
//DeadCode MS 06Jul00 				Home	UID_AF_HAWKINGE,
//DeadCode MS 06Jul00 				Scram_G2_Squad,
//DeadCode MS 06Jul00 				NAT_RAF,
//DeadCode MS 06Jul00   				Scram_G2_Skill,
//DeadCode MS 06Jul00 				MORALE_HIGH
//DeadCode MS 06Jul00 			}
//DeadCode MS 06Jul00 		}

//WAVE 1 He111s Going to Farnborough

Setval	{firstobject,0x3fff};

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_CROYDON, 
						 Abs	{Y Scram_G4_Alt},
			 			 Rel	{Bearing ANGLES_0Deg,
								 Pitch 	ANGLES_0Deg,
						 		 Range METRES2000
								} 
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Target		{UID_FA_Farnborough},
					Posn		
						{
						 Abs	{Y Scram_G4_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	3,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
  			NumInForm	Scram_G4_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,
			Duty	DA_LEVEL,

  			Posn	{Abs	UID_AF_CROYDON, 
				 	 Abs	{Y Scram_G4_Alt},
			 		 Rel	{Bearing ANGLES_80Deg,
							 Pitch 	ANGLES_0Deg,
						 	 Range {Select METRES6000,1,METRES500}
							} 
					},	

			AirItem	//quick_40_G4_aircraft=
			{
				Scram_G4_Squad,
				Home	UID_AF_Tramecourt,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G4_Skill,
				Target	UID_FA_Farnborough
  			}
 		},

Setval	{WPP_Msg0,firstobject};

//WAVE 2 Me110s escort
		AirGroup	
		{
			
			NumInWing	4,
  			NumInForm	Scram_G5_AC,

			Formation	GRUP_FINGER_VIC_ABOVE,
			DUTYESCORT,

			AirItem	
			{
				Scram_G5_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Guines,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G5_Skill,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg0	//quick_40_G4_aircraft
  			}
 		},

//WAVE 3 Me109s escort

		AirGroup	
		{
			
			NumInWing	4,
  			NumInForm	Scram_G6_AC,

			Formation	GRUP_FINGER_VIC_LEFT,
			DUTYESCORT,

			AirItem	
			{
				Scram_G6_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Marquise,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G6_Skill,
				Leader	WPP_Msg0,	//quick_40_G4_aircraft,
				Bombs	1,		//MS 05Sep00
				Damage {Select QMD_FUELPERCENT,QMD_LEVEL,44}
				
  			}
 		},

//WAVE 4 JU88s Going to Biggin Hill then Weybridge Brooklands

Setval	{firstobject,0x3fff};

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Target		{UID_AF_BIGGINHILL},
					Posn		
						{
						 Abs	{Y Scram_G7_Alt}
						},
					Range	METRES5000,
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Target		{UID_FA_BrooklandsHawker},
					Posn		
						{
						 Abs	{Y Scram_G7_Alt}
						},
					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G7_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G7_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G7_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
  			NumInForm	Scram_G7_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,

			Duty	DA_LEVEL,

  			Posn	{Abs	UID_AF_BIGGINHILL, 
				 	 Abs	{Y Scram_G7_Alt},
			 		 Rel	{Bearing ANGLES_170Deg,
							 Pitch 	ANGLES_0Deg,
						 	 Range {Select KM10,1,METRES2000}
						} 
					},	

			AirItem	//quick_40_G7_aircraft=
			{
				Scram_G7_Squad,
				Home	UID_AF_Barley,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G7_Skill,
				Target	UID_FA_BrooklandsHawker
  			}
 		},

Setval	{WPP_Msg1,firstobject};
Setval	{firstobject,0x3fff};

//WAVE 5 Hurrs from 605 sqdn Croydon

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg0,	//quick_40_G4_aircraft,
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_CROYDON, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn	
				{Abs	UID_AF_CROYDON, 
				 Abs	{Y Scram_G0_Alt},
	 			 Rel	{Bearing ANGLES_0Deg,
						 Pitch 	ANGLES_0Deg,
				 		 Range METRES2000
						} 
				},

		   	AirItem	quick_40_G0_aircraft =
			{
				Home	UID_AF_CROYDON,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH,
				Target	WPP_Msg0,	//quick_40_G4_aircraft,
 				MoveCode	ACM_STRAIGHTANDLEVEL
			}
		},

//WAVE 6 Spits from 66 sqdn Kenley

		AirGroup   
		{
			NumInWing	3,
  			NumInForm	Scram_G1_AC,

			DUTYESCORT,
			Formation	WING_RAFVIC_VIC_VIC,

		   	AirItem	
			{
				Home	UID_AF_KENLEY,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				MORALE_HIGH,
				Leader	quick_40_G0_aircraft
			}
		},

//WAVE 7 Hurrs from 604 sqdn Croydon

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg0,	//quick_40_G4_aircraft,
						 Abs	{Y Scram_G2_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_CROYDON, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn		
				{
				 Abs	{UID_AF_CROYDON},
				 Abs	{Y Scram_G2_Alt},
		 		 Rel	{Bearing ANGLES_160Deg,
						 Pitch 	ANGLES_0Deg,
					 	 Range METRES4000
						} 
				},

		   	AirItem	quick_40_G2_aircraft =
			{
				Home	UID_AF_CROYDON,
				Scram_G2_Squad,
				NAT_RAF,
  				Scram_G2_Skill,
				MORALE_HIGH
			}
		},

//WAVE 8 Spits from 92 sqdn Biggin Hill

		AirGroup   
		{
			NumInWing	3,
  			NumInForm	Scram_G3_AC,

			DUTYESCORT,
			Formation	WING_RAFVIC_VIC_VIC,

		   	AirItem	
			{
				Home	UID_AF_BIGGINHILL,
				Scram_G3_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH,
				Leader	quick_40_G2_aircraft
			}
		},

//EXTRA WAVES
//Wave 1 pt 2 1 staffel breaks off and goes south to Biggin Hill

		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_CROYDON, 
					 	 Abs	{Y {Select Scram_G4_Alt,1,-FT_200}},
			 		 	 Rel	{Bearing ANGLES_0Deg,
								 Pitch 	ANGLES_0Deg,
						 	 	 Range METRES2000
								} 
						},
					Action	wpacnoactionno,
					Range	{Select METRES3000,1,METRES500}
				},
				WayPoint	
				{
					Posn		
						{Abs	{UID_AF_BIGGINHILL}, 
						 Abs	{Y Scram_G4_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_Arras, 
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES8000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
  			NumInForm	Scram_G4_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,
			Duty	DA_LEVEL,

  			Posn	{Abs	UID_AF_CROYDON, 
				 	 Abs	{Y {Select Scram_G4_Alt,1,-FT_200}},
			 		 Rel	{Bearing ANGLES_80Deg,
							 Pitch 	ANGLES_0Deg,
						 	 Range METRES6000
						} 
					},	

			AirItem	
			{
				Scram_G4_Squad,
				Home	UID_AF_Arras,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G4_Skill,
				Target	UID_FA_Farnborough
  			}
 		},

//WAVE 3 Pt 2

		AirGroup	
		{
			
			NumInWing	4,
  			NumInForm	Scram_G6_AC,

			Formation	GRUP_FINGER_VIC_RIGHT,
			DUTYESCORT,

			AirItem	
			{
				Scram_G6_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Caffiers,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G6_Skill,
				Bombs	1,		//MS 05Sep00
				Damage {Select QMD_FUELPERCENT,QMD_LEVEL,44},
				Leader	WPP_Msg0	//quick_40_G4_aircraft
  			}
 		},

//WAVE 4 Pt 2 

		AirGroup	
		{
			NumInWing	5,
  			NumInForm	Scram_G7_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC,

			Duty	DA_LEVEL,

			AirItem	
			{
				Scram_G7_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Colombert,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G7_Skill,
				Target	UID_AF_BIGGINHILL,
				Leader	WPP_Msg1	//quick_40_G7_aircraft
  			}
 		},

//WAVE 4 Pt 3

		AirGroup	
		{
			NumInWing	5,
  			NumInForm	Scram_G7_AC,

			Formation	GRUP_LWVIC_ASTERN_VIC2,

			Duty	DA_LEVEL,

			AirItem	
			{
				Scram_G7_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Desvres,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G7_Skill,
				Target	UID_AF_BIGGINHILL,
				Leader	WPP_Msg1	//quick_40_G7_aircraft
  			}
 		},

//Hurrs from 253 Kenley defend Biggin Hill

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg1,	//quick_40_G7_aircraft,
						 Abs	{Y {Select Scram_G7_Alt,1,FT_1000}}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_KENLEY, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn		
				{
				 Abs	WPP_Msg1,	//quick_40_G7_aircraft,
				 Abs	{Y {Select Scram_G7_Alt,1,FT_1000}},
		 		 Rel	{Intercept	{WPP_Msg1,UID_AF_KENLEY},
						 Bearing ANGLES_0Deg,
						 Pitch 	ANGLES_0Deg,
					 	 Range METRES6000
						} 
				},

		   	AirItem	
			{
				Home	UID_AF_KENLEY,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				MORALE_HIGH
			}
		},

//Hurrs from 303 Northolt defend Biggin Hill

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	WPP_Msg1,	//quick_40_G7_aircraft,
						 Abs	{Y {Select Scram_G7_Alt,1,FT_2000}}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_NORTHOLT, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G2_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn		
				{
				 Abs	WPP_Msg1,	//quick_40_G7_aircraft,
				 Abs	{Y {Select Scram_G7_Alt,1,FT_2000}},
		 		 Rel	{Intercept	{WPP_Msg1,UID_AF_NORTHOLT},
						 Bearing ANGLES_0Deg,
						 Pitch 	ANGLES_0Deg,
					 	 Range METRES6000
						} 
				},

		   	AirItem	
			{
				Home	UID_AF_NORTHOLT,
				Scram_G2_Squad,
				NAT_RAF,
  				Scram_G2_Skill,
				MORALE_HIGH
			}
		},
//??? Paired Squadrons from Northolt

		AirGroup   
		{
			Route	
			{
				WayPoint	
				{
					Posn		
						{
						 Abs	UID_AF_CROYDON,
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_NORTHOLT, 
						 Abs	{Y FT_5000}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,
  			NumInForm	Scram_G0_AC,

			DUTYMIGCAP,
			Formation	WING_RAFVIC_VIC_VIC,

			Posn		
				{
				 Abs	{UID_AF_CROYDON},
				 Abs	{Y Scram_G0_Alt},
		 		 Rel	{Intercept	{UID_AF_CROYDON,UID_AF_NORTHOLT},
						 Bearing ANGLES_0Deg,
						 Pitch 	ANGLES_0Deg,
					 	 Range METRES4000
						} 
				},

		   	AirItem	quick_40_Gx_aircraft =
			{
				Home	UID_AF_NORTHOLT,
				Scram_G2_Squad,
				NAT_RAF,
  				Scram_G2_Skill,
				MORALE_HIGH
			}
		},
		AirGroup   
		{
			NumInWing	3,
  			NumInForm	Scram_G2_AC,

			DUTYESCORT,
			Formation	WING_RAFVIC_VIC_VIC,

		   	AirItem	
			{
				Home	UID_AF_NORTHOLT,
				Scram_G2_Squad,
				NAT_RAF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Leader	quick_40_Gx_aircraft
			}
		}
	};

//--------------------------------
//HISTORIC : 7
//AUG 15 Black Thursday MORNING

	BattleField
	{
		FileName	FIL_QUICKMISSION_41=QUICKM41.BF,
		Setval	(PlyrWingSize, NumInWing (List Scram_G2_Squad,4,4,4,4,4,4,4,4,3,3,3,3,3)),
		Setval	(EnemyWingSize00, NumInWing (List Scram_G4_Squad,4,4,4,4,4,4,4,4,3,3,3,3,3)),
//RAF Yaaayy!!! hurris
		AirGroup	
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{UID_DK_Dover}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_HAWKINGE},
						 Abs	{Y FT_4000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	{UID_DK_Dover}, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Bearing	ANGLES_270Deg,
							 Range		{Select	METRES5000,2,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AF_HAWKINGE,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				Morale MORALE_HIGH
				
			}
		},
//RAF 2 Spits
		AirGroup	
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{UID_DK_Dover}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_MANSTON},
						 Abs	{Y FT_4000}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G1_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	{UID_DK_Dover}, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Bearing	ANGLES_270Deg,
							 Range		{Select	METRES5000,2,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AF_MANSTON,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				Morale MORALE_HIGH
				
			}
		},
//LUFTWAFFE boooo!!!!
//Dive Bombers Wave 1 pt 1 go to hawkinge
Setval	{firstobject,0x3fff};
		AirGroup	
		{
			Route
			{
				WayPoint	
				{
					Target	{UID_AF_HAWKINGE},	
					Posn	{
						 	 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	3,
					Posn	
						{
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	4,
					Posn	
						{
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	PlyrWingSize,
  			NumInForm	Scram_G2_AC,
	 	      	Formation	GRUP_LWVIC_ASTERN_ASTERN,

			AM_DIVEBOMB,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
  					 Abs	{Y Scram_G2_Alt},
  					 Rel	{Intercept	{UID_AF_HAWKINGE,UID_AF_Tramecourt},
							 Bearing	ANGLES_0Deg,
							 Pitch		ANGLES_0Deg,
							 Range		METRES4000
							}
					},	

			AirItem //QUICK41_AC_00 = 
			{
				Scram_G2_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Tramecourt,
				NAT_LUF,
  				Scram_G2_Skill,
				Morale	MORALE_HIGH,
				Target	UID_AF_HAWKINGE
			}
		},
Setval	{WPP_Msg0,firstobject};
Setval	{firstobject,0x3fff};
//Top Cover 1 Pt 1
		AirGroup	
		{
			Route
			{
				WayPoint	
				{
					Posn	{
							 Abs	{UID_AF_HAWKINGE},
							 Abs	{Y Scram_G3_Alt}
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	3,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	4,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	4,
  			NumInForm	Scram_G3_AC,
			Formation	GRUP_SCHWARM_VIC_VIC,

			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
  					 Abs	{Y Scram_G3_Alt},
  					 Rel	{Intercept	{UID_AF_HAWKINGE,UID_AF_Marck},
							 Bearing	ANGLES_0Deg,
							 Pitch		ANGLES_0Deg,
							 Range		METRES5000
							}
					},	

		   AirItem	//QUICK41_AC_01 =
			{
				Scram_G3_Squad,
				Home	UID_AF_Marck,
				NAT_LUF,
  				Scram_G3_Skill,
				Bombs	1,		//MS 05Sep00
				Morale	MORALE_HIGH
			}
		},
//Dive Bombers Wave 2 pt 1 go to Lympne
Setval	{WPP_Msg1,firstobject};
Setval	{firstobject,0x3fff};
		AirGroup	
		{
			Route
			{
				WayPoint	
				{
					Target	{UID_AF_LYMPNE},	
					Posn	{
						 	 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	3,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	4,
					Posn	
						{
						 Abs	{Y Scram_G4_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	EnemyWingSize00,
  			NumInForm	Scram_G4_AC,
		       	Formation	GRUP_LWVIC_ASTERN_ASTERN,

			AM_DIVEBOMB,

  			Posn	{Abs	{UID_AF_LYMPNE}, 
  					 Abs	{Y Scram_G4_Alt},
  					 Rel	{Intercept	{UID_AF_LYMPNE,UID_AF_Marck},
							 Bearing	ANGLES_0Deg,
							 Pitch		ANGLES_0Deg,
							 Range		METRES4000
							}
					},	

		   AirItem	//QUICK41_AC_02 =
			{
				Scram_G4_Squad,
				Home	UID_AF_Marck,
				NAT_LUF,
  				Scram_G4_Skill,
				Morale	MORALE_HIGH,
				Target	UID_AF_LYMPNE
			}
		},
//Top Cover 1 Pt 2
Setval	{WPP_Msg2,firstobject};
Setval	{firstobject,0x3fff};
		AirGroup	
		{
			Route
			{
				WayPoint	
				{
					Posn	{
							 Abs	{UID_AF_LYMPNE},
							 Abs	{Y Scram_G5_Alt}
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{
						 Abs	{UID_AF_Marck},
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	3,
					Posn	
						{
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	4,
					Posn	
						{
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},

			NumInWing	4,
  			NumInForm	Scram_G5_AC,
			Formation	GRUP_SCHWARM_VIC_VIC,

			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_LYMPNE}, 
  					 Abs	{Y Scram_G5_Alt},
  					 Rel	{Intercept	{UID_AF_LYMPNE,UID_AF_Marck},
							 Bearing	ANGLES_0Deg,
							 Pitch		ANGLES_0Deg,
							 Range		METRES5000
							}
					},	

			AirItem //QUICK41_AC_03 =
			{
				Scram_G5_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Marck,
				NAT_LUF,
  				Scram_G5_Skill,
				Bombs	1,		//MS 05Sep00
				Morale	MORALE_HIGH
			}
		},
Setval	{WPP_Msg3,firstobject};
Setval	{firstobject,0x3fff};
//Dive Bombers Wave 1 pt 2
		AirGroup	
		{

			NumInWing	PlyrWingSize,
  			NumInForm	Scram_G2_AC,
		       	Formation	GRUP_LWVIC_ASTERN_ASTERN2,

			AM_DIVEBOMB,

			AirItem	
			{
				Scram_G2_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Tramecourt,
				NAT_LUF,
  				Scram_G2_Skill,
				Morale	MORALE_HIGH,
				Target	UID_AF_HAWKINGE,
				Leader	WPP_Msg0	//QUICK41_AC_00
			}
		},
//Dive Bombers Wave 2 pt 2
		AirGroup	
		{

			NumInWing	EnemyWingSize00,
  			NumInForm	Scram_G4_AC,
		       	Formation	GRUP_LWVIC_ASTERN_ASTERN2,

			AM_DIVEBOMB,

			AirItem	
			{
				Scram_G4_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Marck,
				NAT_LUF,
  				Scram_G4_Skill,
				Morale	MORALE_HIGH,
				Target	UID_AF_LYMPNE,
				Leader	WPP_Msg2	//QUICK41_AC_02
			}
		},

//Top Cover 1 Pt 2
		AirGroup	
		{

			NumInWing	4,
  			NumInForm	Scram_G3_AC,
			Formation	GRUP_SCHWARM_VIC_VIC,

			DUTYMIGCAP,

			AirItem	
			{
				Scram_G3_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Marck,
				NAT_LUF,
  				Scram_G3_Skill,
				Morale	MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg1	//QUICK41_AC_01
			}
		},
//Top Cover 2 Pt 2
		AirGroup	
		{

			NumInWing	4,
  			NumInForm	Scram_G5_AC,
			Formation	GRUP_SCHWARM_VIC_VIC,

			DUTYMIGCAP,

			AirItem	
			{
				Scram_G5_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_Marck,
				NAT_LUF,
  				Scram_G5_Skill,
				Morale	MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg3	//QUICK41_AC_03
			}
		}

	};

//--------------------------------
//HISTORIC : 8 Black Thursday Afternoon

	BattleField
	{
		FileName	FIL_QUICKMISSION_42=QUICKM42.BF,
//RAF 
		AirGroup	//Spits	111 sqdn
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{UID_IN_Faversham}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{UID_FA_ShortsBros}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_CROYDON},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	{UID_IN_Faversham}, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Intercept	{UID_NV_EASTGOODWIN,UID_IN_Faversham},
							 Bearing	{Random ANGLES_350Deg,20,ANGLES_1Deg},
							 Range		{Random	METRES1000,3,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AF_CROYDON,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				Morale MORALE_HIGH
				
			}
		},
		AirGroup	//Hurrs wave 1 151 sqdn NORTHWEALD
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{UID_IN_Faversham}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{UID_FA_ShortsBros}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_NORTHWEALD},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G1_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	{UID_IN_Faversham}, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Intercept	{UID_NV_EASTGOODWIN,UID_IN_Faversham},
							 Bearing	{Random ANGLES_45Deg,45,ANGLES_1Deg},
							 Range		{Random	METRES2000,3,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AF_NORTHWEALD,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				Morale MORALE_HIGH
				
			}
		},
		AirGroup	//Hurrs wave 2 from 64 sqdn Kenley
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{UID_IN_Faversham}, 
						 Abs	{Y Scram_G2_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{UID_FA_ShortsBros}, 
						 Abs	{Y Scram_G2_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_KENLEY},
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G2_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	{UID_IN_Faversham}, 
  					 Abs	{Y Scram_G2_Alt},
  					 Rel	{Intercept	{UID_NV_EASTGOODWIN,UID_IN_Faversham},
							 Bearing	{Random ANGLES_225Deg,90,ANGLES_1Deg},
							 Range		{Random	METRES2000,3,METRES1000}
							}
					},	

		   AirItem	
			{
				Home		UID_AF_KENLEY,
				Scram_G2_Squad,
				NAT_RAF,
  				Scram_G2_Skill,
				Morale MORALE_HIGH
				
			}
		},
//LUFTWAFFE
Setval	{firstobject,0x3fff};
		AirGroup	//luft bombers
		{	//first wave to Shorts
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_IN_Faversham}, 
						 Abs	{Y Scram_G3_Alt}
						},
					Action	wpacnoactionno,
					Range	METRES6000
				},
				WayPoint	
				{
					Target	{UID_FA_ShortsBros},	
					Posn	{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	3,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	4,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	5,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	6,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	7,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	8,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	9,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	10,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	11,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	12,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	13,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	14,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	15,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	16,
					Posn	
						{Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
			NumInForm	Scram_G3_AC,

			Formation	GRUP_LWVIC_VIC_VIC,
			Duty	DA_LEVEL,

			Posn	
				{Abs	{UID_IN_Faversham}, 
				 Abs	{Y Scram_G3_Alt},
		 		 Rel	{Intercept	{UID_IN_Faversham,UID_NV_EASTGOODWIN},
				 		 Bearing	ANGLES_0Deg,
						 Pitch	ANGLES_0Deg,
						 Range	METRES8000
						}
				},

			AirItem		//quick_42_G3_item =
			{
				Scram_G3_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G3_Skill,
				Target	UID_FA_ShortsBros
  			}
 		},
Setval	{WPP_Msg0,firstobject};
Setval	{firstobject,0x3fff};
//wave  2
		AirGroup	//luft bombers
		{	//2nd wave to eastchurch
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_IN_Faversham}, 
						 Abs	{Y Scram_G5_Alt}
						},
					Action	wpacnoactionno,
					Range	METRES6000
				},
				WayPoint	
				{
					Target	{UID_AF_EASTCHURCH},	
					Posn	{
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES4000,
					Action	wpbombno	
				},
				WayPoint	
				{
					ApplyGroup	0,
					Posn	
						{
						 Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	1,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	2,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	3,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	4,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	5,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	6,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	7,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	8,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	9,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	10,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	11,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	12,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	13,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	14,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	15,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				},
				WayPoint	
				{
					ApplyGroup	16,
					Posn	
						{Abs	{Y Scram_G5_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
			NumInForm	Scram_G5_AC,

			Formation	GRUP_LWVIC_VIC_VIC,
			Duty	DA_LEVEL,

			Posn	
				{Abs	{UID_IN_Faversham}, 
				 Abs	{Y Scram_G5_Alt},
		 		 Rel	{Intercept	{UID_IN_Faversham,UID_NV_EASTGOODWIN},
				 		 Bearing	ANGLES_0Deg,
						 Pitch	ANGLES_0Deg,
						 Range	{Select METRES8000,1,METRES500}
						}
				},

			AirItem	//quick_42_G5_item =	
			{
				Scram_G5_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G5_Skill,
				Target	UID_AF_EASTCHURCH
  			}
 		},
Setval	{WPP_Msg1,firstobject};
Setval	{firstobject,0x3fff};
//Escort
		AirGroup //escort wave 1
		{	
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_LEFT,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg0	//quick_42_G3_item
			}
		},

//Escort
		AirGroup //escort for second wave  
		{	
			NumInWing	4,
  			NumInForm	Scram_G6_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_LEFT,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G6_Squad,
				NAT_LUF,
  				Scram_G6_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg1	//quick_42_G5_item
			}
		},
//Follow Up escorts
		AirGroup //escort wave 1 pt 2
		{	
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_RIGHT,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg0	//quick_42_G3_item
			}
		},
		AirGroup //escort wave 1 pt 3
		{	
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg0	//quick_42_G3_item
			}
		},
		AirGroup //escort wave 2 pt 2
		{	
			NumInWing	4,
  			NumInForm	Scram_G6_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_RIGHT,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G6_Squad,
				NAT_LUF,
  				Scram_G6_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg1	//quick_42_G5_item
			}
		},
		AirGroup //escort wave 2 pt 3
		{	
			NumInWing	4,
  			NumInForm	Scram_G6_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G6_Squad,
				NAT_LUF,
  				Scram_G6_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg1	//quick_42_G5_item
			}
		},
//FOLLOW UP Waves
Setval	{firstobject,0x3fff};
		AirGroup   
		{	//Wave 1, Group 2

			NumInWing	5,
			NumInForm	Scram_G3_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_VIC,

		   	AirItem	//quick_42_G3_item_b =
			{
				Scram_G3_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G3_Skill,
				Target	UID_FA_ShortsBros,
				Leader	WPP_Msg0	//quick_42_G3_item
			}
		},
Setval	{WPP_Msg2,firstobject};
Setval	{firstobject,0x3fff};
		AirGroup   
		{	//Wave 1, Group 3

			NumInWing	5,
			NumInForm	Scram_G3_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_VIC2,

		   	AirItem	//quick_42_G3_item_c =
			{
				Scram_G3_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G3_Skill,
				Target	UID_FA_ShortsBros,
				Leader	WPP_Msg0	//quick_42_G3_item
			}
		},
Setval	{WPP_Msg3,firstobject};
Setval	{firstobject,0x3fff};
		AirGroup   
		{	//Wave 2, Group 2

			NumInWing	5,
			NumInForm	Scram_G5_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_VIC,

		   	AirItem
			{
				Scram_G5_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G5_Skill,
				Target	UID_AF_EASTCHURCH,
				Leader	WPP_Msg1	//quick_42_G5_item
			}
		},
		AirGroup   
		{	//Wave 2, Group 3

			NumInWing	5,
			NumInForm	Scram_G5_AC,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_VIC2,

		   	AirItem
			{
				Scram_G5_Squad,
//DeadCode RJS 10Nov00 				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G5_Skill,
				Target	UID_AF_EASTCHURCH,
				Leader	WPP_Msg1	//quick_42_G5_item
			}
		},
//ARGGHHHHH More escorts
		AirGroup 
		{	
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_RIGHT,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G4_Squad,	
//DeadCode MS 25May00 				PT_JU87,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg2	//quick_42_G3_item_b
			}
		},
		AirGroup
		{	
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G4_Squad,
//DeadCode MS 25May00 				PT_JU87,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg2	//quick_42_G3_item_b
			}
		},
//ARGGHHHHH More escorts 2
		AirGroup 
		{	
			NumInWing	4,
  			NumInForm	Scram_G6_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_LEFT,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G6_Squad,
//DeadCode MS 25May00 				PT_JU87,
				NAT_LUF,
  				Scram_G6_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg3	//quick_42_G3_item_c
			}
		},
		AirGroup
		{	
			NumInWing	4,
  			NumInForm	Scram_G6_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
//DeadCode RJS 10Nov00 				Home	UID_AF_Audembert,
				Scram_G6_Squad,
//DeadCode MS 25May00 				PT_JU87,
				NAT_LUF,
  				Scram_G6_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	WPP_Msg3	//quick_42_G3_item_c
			}
		}

//TempCode MS 24May00 //LOOSE ESCORT
//TempCode MS 24May00 		AirGroup	//luft bombers
//TempCode MS 24May00 		{	//first wave to Shorts
//TempCode MS 24May00 			Route	
//TempCode MS 24May00 			{
//TempCode MS 24May00 //TempCode MS 24May00 				WayPoint	
//TempCode MS 24May00 //TempCode MS 24May00 				{
//TempCode MS 24May00 //TempCode MS 24May00 					Posn	
//TempCode MS 24May00 //TempCode MS 24May00 						{Abs	{UID_IN_Faversham}, 
//TempCode MS 24May00 //TempCode MS 24May00 						 Abs	{Y {Select Scram_G3_Alt,1,FT_5000}}
//TempCode MS 24May00 //TempCode MS 24May00 						},
//TempCode MS 24May00 //TempCode MS 24May00 					Action	wpacnoactionno
//TempCode MS 24May00 //TempCode MS 24May00 				},
//TempCode MS 24May00 				WayPoint	
//TempCode MS 24May00 				{
//TempCode MS 24May00 					Target	{UID_FA_ShortsBros},	
//TempCode MS 24May00 					Posn	{
//TempCode MS 24May00 						 Abs	{Y {Select Scram_G3_Alt,1,FT_5000}}
//TempCode MS 24May00 						},
//TempCode MS 24May00 					Action	wpacnoactionno
//TempCode MS 24May00 				},
//TempCode MS 24May00 				WayPoint	
//TempCode MS 24May00 				{
//TempCode MS 24May00 					Posn	
//TempCode MS 24May00 						{Abs	UID_AF_AntwerpDeurne, 
//TempCode MS 24May00 						 Abs	{Y {Select Scram_G3_Alt,1,FT_5000}}
//TempCode MS 24May00 						},
//TempCode MS 24May00  					Range	METRES6000,
//TempCode MS 24May00 					Action	wpalandingno
//TempCode MS 24May00 				}
//TempCode MS 24May00  			},
//TempCode MS 24May00 			
//TempCode MS 24May00 			NumInWing	2,
//TempCode MS 24May00 			NumInForm	Scram_G4_AC,
//TempCode MS 24May00 
//TempCode MS 24May00 			Formation	GRUP_SCHWARM_VIC_VIC,
//TempCode MS 24May00 
//TempCode MS 24May00 			Posn	
//TempCode MS 24May00 				{Abs	{UID_IN_Faversham}, 
//TempCode MS 24May00 				 Abs	{Y {Select Scram_G3_Alt,1,FT_5000}}
//TempCode MS 24May00 //TempCode MS 24May00 		 		 Rel	{Intercept	{UID_IN_Faversham,UID_NV_EASTGOODWIN},
//TempCode MS 24May00 //TempCode MS 24May00 				 		 Bearing	ANGLES_0Deg,
//TempCode MS 24May00 //TempCode MS 24May00 						 Pitch	ANGLES_0Deg,
//TempCode MS 24May00 //TempCode MS 24May00 						 Range	METRES4000
//TempCode MS 24May00 //DeadCode MS 24May00 				 		}
//TempCode MS 24May00 				},
//TempCode MS 24May00 
//TempCode MS 24May00 			AirItem
//TempCode MS 24May00 			{
//TempCode MS 24May00 				Scram_G4_Squad,
//TempCode MS 24May00 				Home	UID_AF_Audembert,
//TempCode MS 24May00   				NAT_LUF,
//TempCode MS 24May00 				MORALE_HIGH,
//TempCode MS 24May00   				Scram_G4_Skill
//TempCode MS 24May00   			}
//TempCode MS 24May00  		}

	};

//--------------------------------

//DeadCode MS 10Jan100 	BattleField
//DeadCode MS 10Jan100 	{
//DeadCode MS 10Jan100 		FileName	FIL_FAC_1TARGET= fac_1.BF
//DeadCode MS 10Jan100 	};
//DeadCode MS 10Jan100 
//DeadCode MS 10Jan100 
//DeadCode MS 10Jan100 	BattleField
//DeadCode MS 10Jan100 	{
//DeadCode MS 10Jan100 		FileName	FIL_FAC_2TARGET= fac_2.BF
//DeadCode MS 10Jan100 	};
//DeadCode MS 10Jan100 	BattleField
//DeadCode MS 10Jan100 	{
//DeadCode MS 10Jan100 		FileName	FIL_FAC_3TARGET= fac_3.BF
//DeadCode MS 10Jan100 	};
//DeadCode MS 10Jan100 
//DeadCode MS 10Jan100 	BattleField
//DeadCode MS 10Jan100 	{
//DeadCode MS 10Jan100 		FileName	FIL_TAC_1TARGET= tac_1.BF
//DeadCode MS 10Jan100 	};
//DeadCode MS 10Jan100 
//DeadCode MS 10Jan100 	BattleField
//DeadCode MS 10Jan100 	{
//DeadCode MS 10Jan100 		FileName	FIL_TAC_2TARGET= tac_2.BF
//DeadCode MS 10Jan100 	};
//DeadCode MS 10Jan100 
//DeadCode MS 10Jan100 	BattleField
//DeadCode MS 10Jan100 	{
//DeadCode MS 10Jan100 		FileName	FIL_TAC_3TARGET= tac_3.BF
//DeadCode MS 10Jan100 	};


//--------------------------------
//AIRFIELD BUZZ: HELICOPTER	LAND

	BattleField
	{
		FileName	FIL_AFBUZZ00=AFBUZZ00.BF,
		AirGroup	
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{
						 Abs	{Pack_Target0},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
  			NumInForm	6,

  			DUTYMIGCAP,

  			Posn	{Abs	{Pack_Target0}, 
  					 Abs	{Y Scram_G0_Alt},
					 Rel	{Bearing ANGLES_180Deg,
							 Range	METRES5000,
							 Pitch	ANGLES_0Deg
							}
					},	

			AirItem
			{
				Scram_G0_Squad,
				Home	Pack_Target0,
  				NAT_RAF,
				MORALE_HIGH,
  				Scram_G0_Skill
  			}
 		}							 
	};

//--------------------------------
//AIRFIELD BUZZ: TRANSPORT

	BattleField
	{
		FileName	FIL_AFBUZZ01=AFBUZZ01.BF,
//RAF 
		AirGroup	
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	{UID_IN_Faversham}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{UID_FA_ShortsBros}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_CROYDON},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G0_AC,
			Formation	WING_RAFVIC_VIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	{UID_IN_Faversham}, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Intercept	{UID_NV_EASTGOODWIN,UID_IN_Faversham},
							 Bearing	{Random ANGLES_350Deg,20,ANGLES_1Deg},
							 Range		{Random	METRES1000,3,METRES1000}
							}
					},	

		   AirItem	afbuzz_01_G0_item =
			{
				Home		UID_AF_CROYDON,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				Morale MORALE_HIGH
				
			}
		},
//LUFTWAFFE
		AirGroup	//luft bombers
		{	//first wave to Shorts
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_IN_Faversham}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno,
					Range	METRES6000
				},
				WayPoint	
				{
					Target	{UID_FA_ShortsBros},	
					Posn	{
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_AntwerpDeurne, 
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	5,
			NumInForm	15,

//TempCode MS 02Jun00 			Formation	GRUP_LWVIC_VIC_ASTERN,
			Formation	GRUP_LWVIC_VIC_ABOVE,

			Duty	DA_LEVEL,

			Posn	
				{Abs	{UID_IN_Faversham}, 
				 Abs	{Y Scram_G1_Alt},
		 		 Rel	{Intercept	{UID_IN_Faversham,UID_NV_EASTGOODWIN},
				 		 Bearing	ANGLES_0Deg,
						 Pitch	ANGLES_0Deg,
						 Range	METRES8000
						}
				},

			AirItem		afbuzz_01_G1_item =
			{
				Scram_G1_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Target	UID_FA_ShortsBros
  			}
 		},
		AirGroup   
		{
		 	NumInWing	5,
			NumInForm	15,

			Duty	DA_LEVEL,
//TempCode MS 02Jun00 			Formation	GRUP_LWVIC_VIC_ASTERN,
			Formation	GRUP_LWVIC_VIC_ABOVE2,

			AirItem		afbuzz_01_G1_item_b =
			{
				Scram_G1_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Target	UID_FA_ShortsBros,
				Leader	afbuzz_01_G1_item
			}
		},
		AirGroup   
		{
		 	NumInWing	5,
			NumInForm	15,

			Duty	DA_LEVEL,
//TempCode MS 02Jun00 			Formation	GRUP_LWVIC_VIC_VIC2,
			Formation	GRUP_LWVIC_VIC_ABOVE2,

			AirItem		afbuzz_01_G1_item_c =
			{
				Scram_G1_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G1_Skill,
				Target	UID_FA_ShortsBros,
				Leader	afbuzz_01_G1_item
			}
		},
//ESCORTS
		AirGroup 
		{	
			NumInWing	4,
  			NumInForm	Scram_G2_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_VIC_LEFT,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G2_Squad,	
				NAT_LUF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	afbuzz_01_G1_item
			}
		},
		AirGroup 
		{	
			NumInWing	4,
  			NumInForm	Scram_G2_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_VIC_RIGHT,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G2_Squad,	
				NAT_LUF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	afbuzz_01_G1_item
			}
		},
		AirGroup 
		{	
			NumInWing	4,
  			NumInForm	Scram_G2_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_FRONT,

		   	AirItem
			{
				Home	UID_AF_Audembert,
//TempCode MS 30May00 				Scram_G2_Squad,	
				PT_ME110,
				NAT_LUF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	afbuzz_01_G1_item
			}
		},
		AirGroup 
		{	
			NumInWing	4,
  			NumInForm	Scram_G2_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_BACK,

		   	AirItem
			{
				Home	UID_AF_Audembert,
//TempCode MS 30May00 				Scram_G2_Squad,	
				PT_ME110,
				NAT_LUF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	afbuzz_01_G1_item
			}
		},
		AirGroup 
		{	
			NumInWing	4,
  			NumInForm	Scram_G2_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
				Home	UID_AF_Audembert,
//TempCode MS 30May00 				Scram_G2_Squad,	
				PT_ME110,
				NAT_LUF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Bombs	1,		//MS 05Sep00
				Leader	afbuzz_01_G1_item
			}
		},
		AirGroup 
		{	
			NumInWing	4,
  			NumInForm	Scram_G2_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_BELOW,

		   	AirItem
			{
				Home	UID_AF_Audembert,
//TempCode MS 30May00 				Scram_G2_Squad,	
				PT_ME110,
				NAT_LUF,
  				Scram_G2_Skill,
				MORALE_HIGH,
				Leader	afbuzz_01_G1_item
			}
		},
//MORE RAF
		AirGroup   
		{
		 	NumInWing	3,
			NumInForm	12,

			Formation	WING_RAFVIC_VIC_VIC,
			DUTYMIGCAP,

			AirItem		
			{
				Home		UID_AF_CROYDON,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				Morale MORALE_HIGH,
				Leader	afbuzz_01_G0_item
			}
		},
		AirGroup   
		{
		 	NumInWing	3,
			NumInForm	12,

			Formation	WING_RAFVIC_VIC_VIC2,
			DUTYMIGCAP,

			AirItem		
			{
				Home		UID_AF_CROYDON,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				Morale MORALE_HIGH,
				Leader	afbuzz_01_G0_item
			}
		}
	};

//--------------------------------
//AIRFIELD BUZZ: FIGHTERS

	BattleField
	{
		FileName	FIL_AFBUZZ02=AFBUZZ02.BF
	};


//--------------------------------
//AIRFIELD BUZZ: NAVY AIRCRAFT

	BattleField
	{
		FileName	FIL_AFBUZZ03=AFBUZZ03.BF
	};

//--------------------------------
//EGRESS BUZZ: GENERAL

	BattleField
	{
		FileName	FIL_RVBUZZ00=RVBUZZ00.BF
	};

//--------------------------------
//RENDEZVOUS BUZZ: OTHER

	BattleField
	{
		FileName	FIL_RVBUZZ01=RVBUZZ01.BF
	};


//--------------------------------
//8 deathmathch battlefields

//THE RING OF DEATH

 	BattleField
	{
		FileName	FIL_deathmatch0= death0.BF,
		Setval	{FriendHomeBase, UID_AF_Audembert},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn			//AMM 12May99
						{Abs	{UID_AF_HAWKINGE}, //AMM 12May99
						 Abs	{Y HeightSize}//AMM 12May99
						},		//AMM 12May99
//DeadCode AMM 12Mar99 					Posn	
//DeadCode AMM 12Mar99 						{Abs	{UID_AF_HAWKINGE}, 
//DeadCode AMM 12Mar99 						 Abs	{Y HeightSize}
//DeadCode AMM 12Mar99 						},
//DeadCode AMM 12May99 					Posn	
//DeadCode AMM 12May99 						{Abs	{EnemyScoutHomeBase}, 
//DeadCode AMM 12May99 						 Rel	{Y FT_2000,X FT_50}
//DeadCode AMM 12May99 						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 		
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},			
//DeadCode AMM 12Mar99   			Posn	{Abs	{UID_AF_HAWKINGE}, 
//DeadCode AMM 12Mar99 				     Abs	{Y {Random HeightSize,10,FT_100}},
//DeadCode AMM 12Mar99   					 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
//DeadCode AMM 12Mar99 					 		 Range METRES750,
//DeadCode AMM 12Mar99 							 Pitch ANGLES_0Deg
//DeadCode AMM 12Mar99 							}
//DeadCode AMM 12Mar99 					},	
//DeadCode AMM 12May99   			Posn	{Abs	EnemyScoutHomeBase, 
//DeadCode AMM 12May99   					 Rel	{Y FT_2000,X FT_100},
//DeadCode AMM 12May99 		 		 Rel	{Bearing ANGLES_90Deg,Range METRES50}
//DeadCode AMM 12May99 					},	

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G0_Skill
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn			//AMM 12May99
						{Abs	{UID_AF_HAWKINGE}, //AMM 12May99
						 Abs	{Y HeightSize}//AMM 12May99
						},		//AMM 12May99
//DeadCode AMM 12Mar99 					Posn	
//DeadCode AMM 12Mar99 						{Abs	{UID_AF_HAWKINGE}, 
//DeadCode AMM 12Mar99 						 Abs	{Y HeightSize}
//DeadCode AMM 12Mar99 						},
//DeadCode AMM 12May99 					Posn	
//DeadCode AMM 12May99 						{Abs	{EnemyScoutHomeBase}, 
//DeadCode AMM 12May99 						 Rel	{Y FT_2000,X -FT_50}
//DeadCode AMM 12May99 						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 		
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}	
					},		
//DeadCode AMM 12Mar99   			Posn	{Abs	{UID_AF_HAWKINGE}, 
//DeadCode AMM 12Mar99 				     Abs	{Y {Random HeightSize,10,FT_100}},
//DeadCode AMM 12Mar99   					 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
//DeadCode AMM 12Mar99 					 		 Range METRES750,
//DeadCode AMM 12Mar99 							 Pitch ANGLES_0Deg
//DeadCode AMM 12Mar99 							}
//DeadCode AMM 12Mar99 					},	
//DeadCode AMM 12May99   			Posn	{Abs	EnemyScoutHomeBase, 
//DeadCode AMM 12May99   					 Rel	{Y FT_2000},
//DeadCode AMM 12May99 		 		 Rel	{Bearing ANGLES_90Deg,Range METRES50
//DeadCode AMM 12May99 						} 
//DeadCode AMM 12May99 
//DeadCode AMM 12May99 					},	

			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G1_Skill
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G2_Skill
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G3_Skill
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G4_Skill
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G5_Skill
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G6_Skill
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y HeightSize}
						},

					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
					 		 Range METRES750,
							 Pitch ANGLES_0Deg
							}
					},	

			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G7_Skill
  			}
 		}

	};

//**************************************************************************
//PAIRS

 	BattleField
	{
		FileName	FIL_deathmatch1= death1.BF,
		Setval	{FriendHomeBase, UID_AF_Audembert},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
//PAIR 1
		AirGroup
		{
			Route	
			{
				WayPoint D1_WP_00 =	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
				    	 Abs	{Y {Random HeightSize,10,FT_100}},
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range METRES2000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg},
					 		 Range METRES1000,
							 Pitch ANGLES_0Deg
							}
					},	
			AirItem	D1_AC_00 =  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G0_Skill
  			}
 		},
//ELEMENT
		AirGroup
		{
			Route	
			{
				WayPoint
				{
						Posn	
							{Abs	D1_WP_00}, 
						Action	wpacnoactionno
				}
 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	D1_AC_00, 
  					 Rel	{Bearing {Random ANGLES_315Deg,1,ANGLES_180Deg},
					 		 Range METRES50,
							 Pitch ANGLES_0Deg
							}
					},
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G1_Skill
  			}
 		},
//PAIR 2
		AirGroup
		{
			Route	
			{
				WayPoint D1_WP_02 =	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
				    	 Abs	{Y {Random HeightSize,10,FT_100}},
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range METRES2000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Random ANGLES_225Deg,90,ANGLES_1Deg},
					 		 Range METRES1000,
							 Pitch ANGLES_0Deg
							}
					},	
			AirItem	D1_AC_02 =  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G2_Skill
  			}
 		},
//ELEMENT
		AirGroup
		{
			Route	
			{
				WayPoint
				{
						Posn	
							{Abs	D1_WP_02}, 
						Action	wpacnoactionno
				}
 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	D1_AC_02, 
  					 Rel	{Bearing {Random ANGLES_315Deg,1,ANGLES_180Deg},
					 		 Range METRES50,
							 Pitch ANGLES_0Deg
							}
					},
	
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G3_Skill
  			}
 		},
//PAIR 3
		AirGroup
		{
			Route	
			{
				WayPoint D1_WP_04 =	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
				    	 Abs	{Y {Random HeightSize,10,FT_100}},
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range METRES2000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Random ANGLES_315Deg,90,ANGLES_1Deg},
					 		 Range METRES1000,
							 Pitch ANGLES_0Deg
							}
					},	
			AirItem	D1_AC_04 =  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G4_Skill
  			}
 		},
//ELEMENT
		AirGroup
		{
			Route	
			{
				WayPoint
				{
						Posn	
							{Abs	D1_WP_04}, 
						Action	wpacnoactionno
				}
 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	D1_AC_04, 
  					 Rel	{Bearing {Random ANGLES_315Deg,1,ANGLES_180Deg},
					 		 Range METRES50,
							 Pitch ANGLES_0Deg
							}
					},
	
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G5_Skill
  			}
 		},
//PAIR 4
		AirGroup
		{
			Route	
			{
				WayPoint D1_WP_06 =	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
				    	 Abs	{Y {Random HeightSize,10,FT_100}},
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range METRES2000,
								 Pitch ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	{UID_AF_HAWKINGE}, 
				     Abs	{Y {Random HeightSize,10,FT_100}},
  					 Rel	{Bearing {Random ANGLES_45Deg,90,ANGLES_1Deg},
					 		 Range METRES1000,
							 Pitch ANGLES_0Deg
							}
					},	
			AirItem	D1_AC_06 =  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
  				Scram_G6_Skill
  			}
 		},
//ELEMENT
		AirGroup
		{
			Route	
			{
				WayPoint
				{
						Posn	
							{Abs	D1_WP_06}, 
						Action	wpacnoactionno
				}
 			},


			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

  			Posn	{Abs	D1_AC_06, 
  					 Rel	{Bearing {Random ANGLES_315Deg,1,ANGLES_180Deg},
					 		 Range METRES50,
							 Pitch ANGLES_0Deg
							}
					},
	
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G7_Skill
  			}
 		}
	};

//**************************************************************************
//THE STRING/WHEEL OF DEATH

 	BattleField
	{
		FileName	FIL_deathmatch2= death2.BF,

		Setval	{FriendHomeBase, UID_AF_Audembert},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},

	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G0_Skill
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G1_Skill
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,2,FT_750}},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G2_Skill
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,2,FT_750}},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G3_Skill
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G4_Skill
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G5_Skill
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,2,FT_750}},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G6_Skill
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,2,FT_750}},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Select HeightSize,1,FT_750}},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES750,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G7_Skill
  			}
 		}
	};

//**************************************************************************
//RANDOM HORIZ

 	BattleField
	{
		FileName	FIL_deathmatch3= death3.BF,
		Setval	{FriendHomeBase, UID_AF_Audembert},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},

	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G0_Skill
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G1_Skill
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G2_Skill
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G3_Skill
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G4_Skill
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G5_Skill
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G6_Skill
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,20,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G7_Skill
  			}
 		}
	};

//**************************************************************************
//RANDOM VERT

 	BattleField
	{
		FileName	FIL_deathmatch4= death4.BF,
		Setval	{FriendHomeBase, UID_AF_Audembert},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},

	 	Setval	{HeightSize, Y {Random FT_4000,16,FT_1000}},

		AirGroup
		{
			Route	
			{
				WayPoint						 
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G0_Skill
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G1_Skill
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G2_Skill
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G3_Skill
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G4_Skill
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G5_Skill
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G6_Skill
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,100,FT_100}},	
						 Rel	{Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg},
								 Range	{Random METRES100,20,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G7_Skill
  			}
 		}
	};
//**************************************************************************
//EXPLODE

 	BattleField
	{
		FileName	FIL_deathmatch5= death5.BF,
		Setval	{FriendHomeBase, UID_AF_Audembert},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},

	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G0_Skill
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G1_Skill
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G2_Skill
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G3_Skill
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G4_Skill
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G5_Skill
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G6_Skill
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES20,
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G7_Skill
  			}
 		}
	};
//**************************************************************************
//PIGGEY IN THE MIDDLE
 	BattleField
	{
		FileName	FIL_deathmatch6= death6.BF,
		Setval	{FriendHomeBase, UID_AF_Audembert},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
		Setval	{ParentRand, Int {Random 0,8,1}},

		Setval	(RangeStepSize, Int (List ParentRand,0,1,1,1,1,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{UID_AF_HAWKINGE},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G0_Skill
  			}
 		},
//NUMBER 2
		Setval	(RangeStepSize, Int (List ParentRand,1,0,1,1,1,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{UID_AF_HAWKINGE},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G1_Skill
  			}
 		},

//NUMBER 3
		Setval	(RangeStepSize, Int (List ParentRand,1,1,0,1,1,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{UID_AF_HAWKINGE},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G2_Skill
  			}
 		},
//NUMBER 4
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,0,1,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{UID_AF_HAWKINGE},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G3_Skill
  			}
 		},
//NUMBER 5
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,1,0,1,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{UID_AF_HAWKINGE},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G4_Skill
  			}
 		},
//NUMBER 6
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,1,1,0,1,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{UID_AF_HAWKINGE},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G5_Skill
  			}
 		},
//NUMBER 7
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,1,1,1,0,1)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{UID_AF_HAWKINGE},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G6_Skill
  			}
 		},
//NUMBER 8
		Setval	(RangeStepSize, Int (List ParentRand,1,1,1,1,1,1,1,0)),

		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing RandAngle,
								 Range	METRES10,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			Posn	
				{Abs	{UID_AF_HAWKINGE},
	  			 Abs	{Y HeightSize},	
				 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
						 Range	{Select 0,RangeStepSize,METRES1000},
						 Pitch	ANGLES_0Deg
						}
				},

			AirItem  	
			{
				Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G7_Skill
  			}
 		}
	};
//**************************************************************************
//FLYBY
 	BattleField
	{
		FileName	FIL_deathmatch7= death7.BF,
		Setval	{FriendHomeBase, UID_AF_Audembert},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},
		Setval	{FriendHomeBase, UID_AF_Audembert},
		Setval	{EnemyScoutHomeBase, UID_AF_Audembert},
	 	Setval	{RangeStepSize, Int {Random 0,7,1}},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_00 =
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_0Deg},
								 Range	{Select METRES250,3,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_00,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_270Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G0_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL
  			}
 		},
//NUMBER 2
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_01 =
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_0Deg},
								 Range	{Select METRES250,2,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_01,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_90Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G1_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL
  			}
 		},
//NUMBER 3
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_02 =
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_0Deg},
								 Range	{Select METRES250,1,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_02,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_270Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G2_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL
  			}
 		},
//NUMBER 4
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_03 =
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_0Deg},
								 Range	{Select METRES250,0,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_03,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_90Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G3_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL
  			}
 		},
//NUMBER 5
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_04 =
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_180Deg},
								 Range	{Select METRES250,0,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_04,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_270Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G4_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL
  			}
 		},
//NUMBER 6
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_05 =
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_180Deg},
								 Range	{Select METRES250,1,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_05,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_270Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G5_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL
  			}
 		},
//NUMBER 7
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_06 =
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_180Deg},
								 Range	{Select METRES250,2,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_06,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_90Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G6_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL
  			}
 		},
//NUMBER 8
		AirGroup
		{
			Route	
			{
				WayPoint	WP_D7_07 =
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y {Random HeightSize,10,FT_100}},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_180Deg},
								 Range	{Select METRES250,3,METRES500},
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	WP_D7_07,
						 Rel	{Bearing {Select RandAngle,1,ANGLES_90Deg},
								 Range	METRES500,
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Type	Scram_G7_Squad,
				Home	EnemyScoutHomeBase,
  				NAT_RAF,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL
  			}
 		}
	};
//-----------------------------------------------------------------
//8 team play battlefields
//-----------------------------------------------------------------
//TEAM, NO ADVANTAGE


 	BattleField
	{
		FileName	FIL_teamplay0= teamply0.BF,

	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},

//AC 00--------------

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		SimpleItem	Item_Team00_End00 =	
		{
  			Posn	
					{Abs	UID_AF_HAWKINGE, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start00 =	
		{
			Posn		
					{Abs	Item_Team00_End00, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End00},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start00, 
					 Rel	{Intercept 	{Item_Team00_Start00,Item_Team00_End00},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,0,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		SimpleItem	Item_Team00_End01 =	
		{
  			Posn	
					{Abs	UID_AF_HAWKINGE, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start01 =	
		{
			Posn		
					{Abs	Item_Team00_End01, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End01},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start01, 
					 Rel	{Intercept 	{Item_Team00_Start01,Item_Team00_End01},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,1,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 2--------------

	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		SimpleItem	Item_Team00_End02 =	
		{
  			Posn	
					{Abs	UID_AF_HAWKINGE, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start02 =	
		{
			Posn		
					{Abs	Item_Team00_End02, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End02},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start02, 
					 Rel	{Intercept 	{Item_Team00_Start02,Item_Team00_End02},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,2,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		SimpleItem	Item_Team00_End03 =	
		{
  			Posn	
					{Abs	UID_AF_HAWKINGE, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start03 =	
		{
			Posn		
					{Abs	Item_Team00_End03, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End03},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start03, 
					 Rel	{Intercept 	{Item_Team00_Start03,Item_Team00_End03},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,3,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 4--------------

	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		SimpleItem	Item_Team00_End04 =	
		{
  			Posn	
					{Abs	UID_AF_HAWKINGE, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start04 =	
		{
			Posn		
					{Abs	Item_Team00_End04, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End04},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start04, 
					 Rel	{Intercept 	{Item_Team00_Start04,Item_Team00_End04},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,4,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		SimpleItem	Item_Team00_End05 =	
		{
  			Posn	
					{Abs	UID_AF_HAWKINGE, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start05 =	
		{
			Posn		
					{Abs	Item_Team00_End05, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End05},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start05, 
					 Rel	{Intercept 	{Item_Team00_Start05,Item_Team00_End05},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,5,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 6--------------

	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		SimpleItem	Item_Team00_End06 =	
		{
  			Posn	
					{Abs	UID_AF_HAWKINGE, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start06 =	
		{
			Posn		
					{Abs	Item_Team00_End06, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End06},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start06, 
					 Rel	{Intercept 	{Item_Team00_Start06,Item_Team00_End06},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,6,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------

	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{AngleStepSize, Int {List  EncounterSize,1,3)),
	 	Setval	{HeightStepSize, Int {List  EncounterSize,0,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		SimpleItem	Item_Team00_End07 =	
		{
  			Posn	
					{Abs	UID_AF_HAWKINGE, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,AngleStepSize,ANGLES_90Deg},
						 	Range	METRES500
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		SimpleItem	Item_Team00_Start07 =	
		{
			Posn		
					{Abs	Item_Team00_End07, 
				 	 Abs	{Y HeightSize},
					 	 	Rel	{Bearing {Select RandAngle,HeightStepSize,ANGLES_180Deg},
						 	Range	METRES1000
							} 
					},
			UIDBand		CivilianBAND,
			Shape		EMPTY
		},

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
					Posn	{Abs Item_Team00_End07},	
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	Item_Team00_Start07, 
					 Rel	{Intercept 	{Item_Team00_Start07,Item_Team00_End07},
							 Bearing	ANGLES_135Deg,
							 Range		{Select 0,7,FT_200},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};

//-------------------------------------------------------------------------
//TEAM01: FLIGHTS, UN ADVANTAGE

//EncounterSize is the side: 0 is red, 1 is blue
//RandAngle is the Angle that UN come in at


 	BattleField
	{
		FileName	FIL_teamplay1= teamply1.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},

//AC 00--------------

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select 0,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 2--------------


	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_600,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 4--------------


	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_800,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1000,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 6--------------


	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------


	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};

//-------------------------------------------------------------------------
//TEAM02: FLIGHTS, RED ADVANTAGE

//EncounterSize is the side: 1 is red, 0 is blue
//RandAngle is the Angle that UN come in at

 	BattleField
	{
		FileName	FIL_teamplay2= teamply2.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},

//AC 00--------------

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select 0,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 2--------------


	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_600,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 4--------------


	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_800,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1000,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 6--------------


	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------


	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_1000}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}

	};

//-------------------------------------------------------------------------
//TEAM03: FLIGHTS, RANDOM ADVANTAGE

//EncounterSize is the side: 
//RangeStepsize is the side index:
//RandAngle is the Angle that UN come in at

 	BattleField
	{
		FileName	FIL_teamplay3= teamply3.BF,
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,2,ANGLES_180Deg}},
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},
		Setval	{RangeStepSize, Int {Random 0,2,1}},

//AC 00--------------

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select 0,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 2--------------


	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_600,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 4--------------


	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_800,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_0,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 6--------------


	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1200,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------


	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),


		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 	 		 	 Rel	{Bearing ANGLES_0Deg,
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
			Posn		
					{Abs	UID_AF_HAWKINGE, 
		 	 		 Abs	{Y {Select HeightSize,EncounterSize,FT_0}},
					 Rel	{Bearing	{Select 0,EncounterSize,RandAngle},
							 Range		{Select FT_1400,EncounterSize,METRES500},
							 Pitch		ANGLES_0Deg
							}
					},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}



	};


//-------------------------------------------------------------------------
//TEAM04: ELEMENTS SCATTERED

//EncounterSize is the side: 
//RandAngle is the Angle that each element comes in at
//AngleStepSize is their waypoint offset

 	BattleField
	{
		FileName	FIL_teamplay4= teamply4.BF,
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},

//AC 00-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 0,359,1}},
	 	Setval	{HeightStepSize, Int {Random 0,50,1}},
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 02-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 0,359,1}},
	 	Setval	{HeightStepSize, Int {Random 0,50,1}},
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},
//AC 04-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 0,359,1}},
	 	Setval	{HeightStepSize, Int {Random 0,50,1}},
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},
//AC 06-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},
	 	Setval	{AngleStepSize, Int {Random 0,359,1}},
	 	Setval	{HeightStepSize, Int {Random 0,50,1}},
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		Setval	{RangeStepSize, Int {Select 0,EncounterSize,1}},
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),

		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select 0,AngleStepSize,ANGLES_1Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,RangeStepSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};


//-------------------------------------------------------------------------
//TEAM05: ELEMENTS CLOSE

//EncounterSize is the side: 
//RandAngle is the Angle that each element comes in at
//AngleStepSize is their waypoint offset

 	BattleField
	{
		FileName	FIL_teamplay5= teamply5.BF,
	 	Setval	{HeightSize, Y {Random FT_4000,25,FT_1000}},

//AC 00-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G0_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,11,1}},
		Setval	{HeightStepSize, Int {Random 0,20,1}},
	
	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 1--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G1_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 02-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G2_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,11,1}},
		Setval	{HeightStepSize, Int {Random 0,20,1}},
	
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G2_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 3--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G3_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G3_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},
//AC 04-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G4_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,11,1}},
		Setval	{HeightStepSize, Int {Random 0,20,1}},
	
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G4_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 5--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G5_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G5_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},
//AC 06-------------- LEAD

	 	Setval	{EncounterSize, Int {List  Scram_G6_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
	 	Setval	{RandAngle, Bearing {Random ANGLES_135Deg,90,ANGLES_1Deg}},
		Setval	{RangeStepSize, Int {Random 0,11,1}},
		Setval	{HeightStepSize, Int {Random 0,20,1}},
	
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES1000
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G6_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		},

//AC 7--------------	WINGMAN

	 	Setval	{EncounterSize, Int {List  Scram_G7_Squad,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)),
		
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup	
		{
			Route	
			{
				WayPoint
				{
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_0Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	METRES5000
									} 
							},
					Action	wpacnoactionno	
				},
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE}, 
						 Abs	{Y FT_5000}
						},
					Action	wpalandingno
				}
 			},
			
  					Posn	
							{Abs	UID_AF_HAWKINGE, 
				 	 		 Abs	{Y {Select HeightSize,HeightStepSize,FT_100}},
					 	 		 	 Rel	{Bearing {Select RandAngle,EncounterSize,ANGLES_180Deg},
									 Pitch	ANGLES_0Deg,
						 		 	 Range	{Select METRES1000,1,FT_250}
									} 
							},

			NumInWing	1,
  			NumInForm	1,

  			DUTYMIGCAP,
		    SQD_RAFVIC_VIC,

			AirItem	 
			{
				Scram_G7_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
				MORALE_HIGH,
  				SKILL_HERO
  			}
 		}
	};


//-------------------------------------------------
//TEAM 06: IMPLODE !!!!!
 	BattleField
	{
		FileName	FIL_teamplay6= teamply6.BF,

	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	{Random METRES500,15,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G0_Skill
  			}
 		},
//NUMBER 2
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	{Random METRES500,15,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G1_Skill
  			}
 		},
//NUMBER 3
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	{Random METRES500,15,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G2_Skill
  			}
 		},
//NUMBER 4
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	{Random METRES500,15,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G3_Skill
  			}
 		},
//NUMBER 5
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	{Random METRES500,15,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G4_Skill
  			}
 		},
//NUMBER 6
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	{Random METRES500,15,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G5_Skill
  			}
 		},
//NUMBER 7
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	{Random METRES500,15,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G6_Skill
  			}
 		},
//NUMBER 8
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES200,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	{Random METRES500,15,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G7_Skill
  			}
 		}
	};

//--------------------------------------------------------------------------
//TEAM 07 EXPLODE
 	BattleField
	{
		FileName	FIL_teamplay7= teamply7.BF,
	 	Setval	{HeightSize, Y {Random FT_4000,21,FT_1000}},
	 	Setval	{RandAngle, Bearing {Random ANGLES_0Deg,359,ANGLES_1Deg}},

	 	Setval	{NAT_ENEMY, Side {List  Scram_G0_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,0,ANGLES_45Deg},
								 Range	{Random METRES20,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},

			AirItem  	
			{
				Scram_G0_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G0_Skill
  			}
 		},
//NUMBER 2
	 	Setval	{NAT_ENEMY, Side {List  Scram_G1_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,1,ANGLES_45Deg},
								 Range	{Random METRES20,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,
	
			AirItem  	
			{
				Scram_G1_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G1_Skill
  			}
 		},
//NUMBER 3
	 	Setval	{NAT_ENEMY, Side {List  Scram_G2_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,2,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G2_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G2_Skill
  			}
 		},
//NUMBER 4
	 	Setval	{NAT_ENEMY, Side {List  Scram_G3_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,3,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G3_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G3_Skill
  			}
 		},
//NUMBER 5
	 	Setval	{NAT_ENEMY, Side {List  Scram_G4_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,4,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

			AirItem  	
			{
				Scram_G4_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G4_Skill
  			}
 		},
//NUMBER 6
	 	Setval	{NAT_ENEMY, Side {List  Scram_G5_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,5,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G5_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G5_Skill
  			}
 		},
//NUMBER 7
	 	Setval	{NAT_ENEMY, Side {List  Scram_G6_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,6,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G6_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G6_Skill
  			}
 		},
//NUMBER 8
	 	Setval	{NAT_ENEMY, Side {List  Scram_G7_Squad,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_LUF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF,NAT_RAF)),
		AirGroup
		{
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	METRES2000,
								 Pitch	ANGLES_0Deg
								}
						},
					Action	wpacnoactionno
				}

 			},
			
  			NumInWing	1,
  			NumInForm	1,
  			DUTYMIGCAP,

					Posn	
						{Abs	{UID_AF_HAWKINGE},
	  					 Abs	{Y HeightSize},	
						 Rel	{Bearing {Select RandAngle,7,ANGLES_45Deg},
								 Range	{Random METRES100,10,METRES100},
								 Pitch	ANGLES_0Deg
								}
						},
			AirItem  	
			{
				Scram_G7_Squad,
				Home	UID_AF_HAWKINGE,
  				NAT_ENEMY,
  				MORALE_HIGH,
 				MoveCode	ACM_STRAIGHTANDLEVEL,
				Scram_G7_Skill
  			}
 		}
	};

//--------------------------------
//HOT SHOT

	BattleField
	{	//This quick mission should no longer rely on globrefs!
		FileName	FIL_HOTSHOT=HOTSHOT.BF,
//LUFTWAFFE
		AirGroup	//luft bombers
		{	//first wave to Shorts
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_IN_Faversham}, 
						 Abs	{Y Scram_G2_Alt}
						},
					Action	wpacnoactionno,
					Range	METRES6000
				},
				WayPoint	
				{
					Target	{UID_FA_ShortsBros},	
					Posn	{
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_AntwerpDeurne, 
						 Abs	{Y Scram_G2_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
			NumInForm	9,

			Formation	GRUP_LWVIC_VIC_VIC,
			Duty	DA_LEVEL,

			Posn	
				{Abs	{UID_IN_Faversham}, 
				 Abs	{Y Scram_G2_Alt},
		 		 Rel	{Intercept	{UID_IN_Faversham,UID_NV_EASTGOODWIN},
				 		 Bearing	ANGLES_0Deg,
						 Pitch	ANGLES_0Deg,
						 Range	METRES8000
						}
				},

			AirItem		HOTSHOT_G2_item =
			{
				Scram_G2_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G2_Skill,
				Target	UID_FA_ShortsBros
  			}
 		},
//wave  2
		AirGroup	//luft bombers
		{	//2nd wave to follow above to shorts
			Route	
			{
				WayPoint	
				{
					Posn	
						{Abs	{UID_IN_Faversham}, 
						 Abs	{Y Scram_G3_Alt}
						},
					Range	METRES6000,
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Target	{UID_FA_ShortsBros},	
					Posn	{
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES5000,
					Action	wpbombno	
				},
				WayPoint	
				{
					Posn	
						{Abs	UID_AF_AntwerpDeurne, 
						 Abs	{Y Scram_G3_Alt}
						},
 					Range	METRES6000,
					Action	wpalandingno
				}
 			},
			
			NumInWing	3,
			NumInForm	9,

			Formation	GRUP_LWVIC_VIC_VIC,
			Duty	DA_LEVEL,

			Posn	
				{Abs	{UID_IN_Faversham}, 
				 Abs	{Y Scram_G3_Alt},
		 		 Rel	{Intercept	{UID_IN_Faversham,UID_NV_EASTGOODWIN},
				 		 Bearing	ANGLES_0Deg,
						 Pitch	ANGLES_0Deg,
						 Range	{Select METRES8000,1,METRES500}
						}
				},

			AirItem	HOTSHOT_G3_item =	
			{
				Scram_G3_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G3_Skill,
				Target	UID_AF_EASTCHURCH
  			}
 		},
//RAF 
		AirGroup	//Spits	111 sqdn
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	HOTSHOT_G2_item, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{UID_FA_ShortsBros}, 
						 Abs	{Y Scram_G0_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_CROYDON},
						 Abs	{Y Scram_G0_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G0_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	HOTSHOT_G2_item, 
  					 Abs	{Y Scram_G0_Alt},
  					 Rel	{Intercept	{UID_NV_EASTGOODWIN,UID_IN_Faversham},
							 Bearing	{Random ANGLES_300Deg,60,ANGLES_1Deg},
							 Range		METRES3000,
							 Pitch	ANGLES_0Deg
							}
					},	

		   AirItem	
			{
				Home		UID_AF_CROYDON,
				Scram_G0_Squad,
				NAT_RAF,
  				Scram_G0_Skill,
				Morale MORALE_HIGH
				
			}
		},
		AirGroup	//Hurrs wave 1 151 sqdn NORTHWEALD
		{
			Route	
			{
				WayPoint		
				{
					Posn	
						{Abs	HOTSHOT_G2_item, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint		
				{
					Posn	
						{Abs	{UID_FA_ShortsBros}, 
						 Abs	{Y Scram_G1_Alt}
						},
					Action	wpacnoactionno
				},
				WayPoint	
				{
					Posn	
						{
						 Abs	{UID_AF_NORTHWEALD},
						 Abs	{Y Scram_G1_Alt}
						},
 					Range	METRES4000,
					Action	wpalandingno
				}
 			},

			NumInWing	3,	
  			NumInForm	Scram_G1_AC,
			Formation	SQD_RAFVIC_VIC,
			
			DUTYMIGCAP,

  			Posn	{Abs	HOTSHOT_G2_item, 
  					 Abs	{Y Scram_G1_Alt},
  					 Rel	{Intercept	{UID_NV_EASTGOODWIN,UID_IN_Faversham},
							 Bearing	{Random ANGLES_45Deg,45,ANGLES_1Deg},
							 Range		{Random	METRES3000,3,METRES1000},
							 Pitch	ANGLES_0Deg
							}
					},	

		   AirItem	
			{
				Home		UID_AF_NORTHWEALD,
				Scram_G1_Squad,
				NAT_RAF,
  				Scram_G1_Skill,
				Morale MORALE_HIGH
				
			}
		},
//Escort
		AirGroup //escort wave 1
		{	
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Leader	HOTSHOT_G2_item
			}
		},

//Escort
		AirGroup //escort for second wave  
		{	
			NumInWing	4,
  			NumInForm	Scram_G5_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_ABOVE,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Leader	HOTSHOT_G3_item
			}
		},
//FOLLOW UP Waves
		AirGroup   
		{	//Wave 1, Group 2

			NumInWing	3,
			NumInForm	9,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_VIC,

		   	AirItem	HOTSHOT_G2_item_b =
			{
				Scram_G2_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G2_Skill,
				Target	UID_FA_ShortsBros,
				Leader	HOTSHOT_G2_item
			}
		},
		AirGroup   
		{	//Wave 1, Group 3

			NumInWing	3,
			NumInForm	9,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_VIC2,

		   	AirItem	HOTSHOT_G2_item_c =
			{
				Scram_G2_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G2_Skill,
				Target	UID_FA_ShortsBros,
				Leader	HOTSHOT_G2_item
			}
		},
		AirGroup   
		{	//Wave 2, Group 2

			NumInWing	3,
			NumInForm	9,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_VIC,

		   	AirItem
			{
				Scram_G3_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G3_Skill,
				Target	UID_AF_EASTCHURCH,
				Leader	HOTSHOT_G3_item
			}
		},
		AirGroup   
		{	//Wave 2, Group 3

			NumInWing	3,
			NumInForm	9,

			Duty	DA_LEVEL,
			Formation	GRUP_LWVIC_VIC_VIC2,

		   	AirItem
			{
				Scram_G3_Squad,
				Home	UID_AF_AntwerpDeurne,
  				NAT_LUF,
				MORALE_HIGH,
  				Scram_G3_Skill,
				Target	UID_AF_EASTCHURCH,
				Leader	HOTSHOT_G3_item
			}
		},
//Follow Up escorts
		AirGroup //escort wave 1 pt 2
		{	
			NumInWing	4,
  			NumInForm	Scram_G4_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_RIGHT,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G4_Squad,
				NAT_LUF,
  				Scram_G4_Skill,
				MORALE_HIGH,
				Leader	HOTSHOT_G2_item_b
			}
		},
		AirGroup //escort wave 2 pt 2
		{	
			NumInWing	4,
  			NumInForm	Scram_G5_AC,

			Duty	DUTYESCORT,
			Formation	GRUP_FINGER_ASTERN_LEFT,

		   	AirItem
			{
				Home	UID_AF_Audembert,
				Scram_G5_Squad,
				NAT_LUF,
  				Scram_G5_Skill,
				MORALE_HIGH,
				Leader	HOTSHOT_G2_item_c
			}
		}
//DeadCode MS 25Jul00 //ARGGHHHHH More escorts
//DeadCode MS 25Jul00 		AirGroup 
//DeadCode MS 25Jul00 		{	
//DeadCode MS 25Jul00 			NumInWing	4,
//DeadCode MS 25Jul00   			NumInForm	Scram_G4_AC,
//DeadCode MS 25Jul00 
//DeadCode MS 25Jul00 			Duty	DUTYESCORT,
//DeadCode MS 25Jul00 			Formation	GRUP_FINGER_ASTERN_RIGHT,
//DeadCode MS 25Jul00 
//DeadCode MS 25Jul00 		   	AirItem
//DeadCode MS 25Jul00 			{
//DeadCode MS 25Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 25Jul00 				Scram_G4_Squad,	
//DeadCode MS 25Jul00 //DeadCode MS 25May00 				PT_JU87,
//DeadCode MS 25Jul00 				NAT_LUF,
//DeadCode MS 25Jul00   				Scram_G4_Skill,
//DeadCode MS 25Jul00 				MORALE_HIGH,
//DeadCode MS 25Jul00 				Leader	HOTSHOT_G2_item_b
//DeadCode MS 25Jul00 			}
//DeadCode MS 25Jul00 		},
//DeadCode MS 25Jul00 		AirGroup
//DeadCode MS 25Jul00 		{	
//DeadCode MS 25Jul00 			NumInWing	4,
//DeadCode MS 25Jul00   			NumInForm	Scram_G4_AC,
//DeadCode MS 25Jul00 
//DeadCode MS 25Jul00 			Duty	DUTYESCORT,
//DeadCode MS 25Jul00 			Formation	GRUP_FINGER_ASTERN_ABOVE,
//DeadCode MS 25Jul00 
//DeadCode MS 25Jul00 		   	AirItem
//DeadCode MS 25Jul00 			{
//DeadCode MS 25Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 25Jul00 				Scram_G4_Squad,
//DeadCode MS 25Jul00 //DeadCode MS 25May00 				PT_JU87,
//DeadCode MS 25Jul00 				NAT_LUF,
//DeadCode MS 25Jul00   				Scram_G4_Skill,
//DeadCode MS 25Jul00 				MORALE_HIGH,
//DeadCode MS 25Jul00 				Leader	HOTSHOT_G2_item_b
//DeadCode MS 25Jul00 			}
//DeadCode MS 25Jul00 		},
//DeadCode MS 25Jul00 //ARGGHHHHH More escorts 2
//DeadCode MS 25Jul00 		AirGroup 
//DeadCode MS 25Jul00 		{	
//DeadCode MS 25Jul00 			NumInWing	4,
//DeadCode MS 25Jul00   			NumInForm	Scram_G5_AC,
//DeadCode MS 25Jul00 
//DeadCode MS 25Jul00 			Duty	DUTYESCORT,
//DeadCode MS 25Jul00 			Formation	GRUP_FINGER_ASTERN_LEFT,
//DeadCode MS 25Jul00 
//DeadCode MS 25Jul00 		   	AirItem
//DeadCode MS 25Jul00 			{
//DeadCode MS 25Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 25Jul00 				Scram_G5_Squad,
//DeadCode MS 25Jul00 //DeadCode MS 25May00 				PT_JU87,
//DeadCode MS 25Jul00 				NAT_LUF,
//DeadCode MS 25Jul00   				Scram_G5_Skill,
//DeadCode MS 25Jul00 				MORALE_HIGH,
//DeadCode MS 25Jul00 				Leader	HOTSHOT_G2_item_c
//DeadCode MS 25Jul00 			}
//DeadCode MS 25Jul00 		},
//DeadCode MS 25Jul00 		AirGroup
//DeadCode MS 25Jul00 		{	
//DeadCode MS 25Jul00 			NumInWing	4,
//DeadCode MS 25Jul00   			NumInForm	Scram_G5_AC,
//DeadCode MS 25Jul00 
//DeadCode MS 25Jul00 			Duty	DUTYESCORT,
//DeadCode MS 25Jul00 			Formation	GRUP_FINGER_ASTERN_ABOVE,
//DeadCode MS 25Jul00 
//DeadCode MS 25Jul00 		   	AirItem
//DeadCode MS 25Jul00 			{
//DeadCode MS 25Jul00 				Home	UID_AF_Audembert,
//DeadCode MS 25Jul00 				Scram_G5_Squad,
//DeadCode MS 25Jul00 				NAT_LUF,
//DeadCode MS 25Jul00   				Scram_G5_Skill,
//DeadCode MS 25Jul00 				MORALE_HIGH,
//DeadCode MS 25Jul00 				Leader	HOTSHOT_G2_item_c
//DeadCode MS 25Jul00 			}
//DeadCode MS 25Jul00 		}
	};						
