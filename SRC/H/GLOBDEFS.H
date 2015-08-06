//////////////////////////////////////////////////////////////////////
//
// Module:      Globdefs.h
//
// Created:     04/02/00 by DAW
//
// Description: Very poorly named include file
//				This redefinition of the ON_MESSAGE macro protects
//				the system against the user procedures having the wrong 
//				number of parameters.
//				The system that MFC uses for it's own purposes makes 
//				this look high-tech!
//////////////////////////////////////////////////////////////////////
#pragma once
#ifndef Globdefs_DEFINED_4_2_2000
#define Globdefs_DEFINED_4_2_2000

#undef	ON_MESSAGE
#define ON_MESSAGE(message, memberFxn) \
	{ message, 0, 0, 0, AfxSig_lwl, \
		(AFX_PMSG)(AFX_PMSGW)(LRESULT (AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))&MSG2_##memberFxn },
#define ON_MESSAGE_CLASS(msg,type,routine)\
	{ msg, 0, 0, 0, AfxSig_lwl, \
		(AFX_PMSG)(AFX_PMSGW)(LRESULT (AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))(LRESULT (AFX_MSG_CALL type::*)(WPARAM, LPARAM))&MSG2_##routine },
#define MSG2_0(memberFxn)	LRESULT MSG2_##memberFxn(int,int) {return (int)memberFxn();}
#define MSG2_1(memberFxn)	LRESULT MSG2_##memberFxn(int a,int) {return (int)memberFxn(a);}
#define MSG2_2(memberFxn)	LRESULT MSG2_##memberFxn(int a,int b) {return (int)memberFxn(a,b);}
#define MSG2_0v(memberFxn)	LRESULT MSG2_##memberFxn(int,int) {memberFxn();return 0;}
#define MSG2_1v(memberFxn)	LRESULT MSG2_##memberFxn(int a,int) {memberFxn(a);return 0;}
#define MSG2_2v(memberFxn)	LRESULT MSG2_##memberFxn(int a,int b) {memberFxn(a,b);return 0;}
#define MSG2(memberFxn)		LRESULT MSG2_##memberFxn(int a,int b)

#endif define Globdefs_DEFINED_4_2_2000
