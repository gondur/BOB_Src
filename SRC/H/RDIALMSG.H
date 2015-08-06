//////////////////////////////////////////////////////////////////////
//
// Module:      rdialmsg.h
//
// Created:     02/11/99 by RDH
//
// Description: Windows message component interface
//				rdialog, rmdldlg, rtoolbar, AND cmigview 
//				should all respond to all these messages.
//////////////////////////////////////////////////////////////////////
	afx_msg LRESULT OnCommandHelp(WPARAM, LPARAM lParam);
	virtual afx_msg FileNum OnGetArt();
	afx_msg long OnGetXYOffset();
	afx_msg CFont* OnGetGlobalFont(int fontnum);
	afx_msg BYTE* OnGetFile(int filenum);
	afx_msg void OnReleaseLastFile();
	afx_msg BOOL OnGetX2Flag();
	afx_msg CDC* OnGetOffScreenDC();
	afx_msg CHintBox* OnGetHintBox();
	afx_msg CListBx* OnGetComboDialog();
	afx_msg CRListBox* OnGetComboListbox();
	afx_msg void OnActiveXScroll(int scrollpos, BOOL horzalign);
	afx_msg int OnGetString(int resourceID,char* workbuffer);
public:
	afx_msg static void OnPlaySound(int filenum);
private:
	MSG2(OnGetString)	{return OnGetString(a,(char*)b);}
	MSG2_0(OnGetArt);
	MSG2_0(OnGetXYOffset);
	MSG2_1(OnGetGlobalFont);
	MSG2_1(OnGetFile);
	MSG2_0v(OnReleaseLastFile);
	MSG2_0(OnGetX2Flag);
	MSG2_0(OnGetOffScreenDC);
	MSG2_0(OnGetHintBox);
	MSG2_1v(OnPlaySound);
	MSG2_0(OnGetComboListbox);
	MSG2_0(OnGetComboDialog);
	MSG2_2v(OnActiveXScroll);
	MSG2_2(OnCommandHelp);
