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

//------------------------------------------------------------------------------
//Filename       Cd_BOB.cpp
//System         
//Author         Craig Beeston
//Date           Wed 22 Sep 1999
//Description    Battle of Britain COMMON Flight Model Curve Data
//------------------------------------------------------------------------------

#include "dosdefs.h"
#include "modvec.h"
#include "curves.h"

void LoadCurvesBOB()
{

// ****  COMM  WingCl  **** //

CURVEPNT COMM_WingCl[18] = {				
	0.2618	,	1.1883	,
	0.3491	,	1.4734	,
	0.3752	,	1.3261	,
	0.4800	,	1.1500	,
	0.6109	,	0.7250	,
	0.9599	,	0.6250	,
	1.5708	,	0.0000	,
	2.6180	,	0.5000	,
	2.9234	,	0.9665	,
	3.3598	,	-0.9665	,
	3.6652	,	-0.5000	,
	4.7124	,	0.0000	,
	5.3233	,	-0.6250	,
	5.6723	,	-0.7250	,
	5.9341	,	-1.1500	,
	5.9079	,	-1.3261	,
	5.9341	,	-1.4734	,
	6.0214	,	-1.1883	
};				
new CURVE ("COMM", "WingCl", 18, 0.0, 6.2832, 1, COMM_WingCl);


// ****  COMM  POWER0  **** //

CURVEPNT COMM_Power0[11] = {				
	0.00	,	0.0000	,
	0.20	,	-0.0200	,
	0.40	,	-0.0410	,
	0.60	,	-0.0678	,
	0.80	,	-0.1128	,
	1.00	,	-0.2000	,
	1.20	,	-0.3688	,
	1.40	,	-0.6778	,
	1.60	,	-1.2086	,
	1.80	,	-2.0696	,
	2.00	,	-3.4000	
};				
new CURVE ("COMM", "Power0", 11, 0.0, 2.0, 2, COMM_Power0);


// ****  COMM  POWER1  **** //

CURVEPNT COMM_Power1[13] = {				
	0.0	,	0.0000	,
	0.4	,	0.4390	,
	0.6	,	0.6522	,
	0.8	,	0.8472	,
	1.0	,	1.0000	,
	1.1	,	1.0489	,
	1.2	,	1.0712	,
	1.3	,	1.0587	,
	1.4	,	1.0022	,
	1.5	,	0.8906	,
	1.6	,	0.7114	,
	1.8	,	0.0904	,
	2.0	,	-1.0000	
};				
new CURVE ("COMM", "Power1", 13, 0.0, 2.0, 2, COMM_Power1);


// ****  COMM  TailCd  **** //

CURVEPNT COMM_TailCd [24] = {
	0.0000	,	0.000	,
	0.0436	,	0.003	,
	0.0873	,	0.012	,
	0.1309	,	0.026	,
	0.1745	,	0.046	,
	0.2182	,	0.072	,
	0.2618	,	0.104	,
	0.3491	,	0.342	,
	0.6981	,	0.643	,
	1.0472	,	0.866	,
	1.5708	,	1.000	,
	2.0944	,	0.866	,
	3.1416	,	0.000	,
	4.1888	,	0.866	,
	4.7124	,	1.000	,
	5.2360	,	0.866	,
	5.5851	,	0.643	,
	5.9341	,	0.342	,
	6.0214	,	0.104	,
	6.0650	,	0.072	,
	6.1087	,	0.046	,
	6.1523	,	0.026	,
	6.1959	,	0.012	,
	6.2396	,	0.003	
};

new CURVE ("COMM", "TailCd", 24, 0.0, 6.2832, 1, COMM_TailCd);

}
// End.
