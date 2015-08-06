//------------------------------------------------------------------------------
//Filename       gameset.h
//System         
//Author         Paul.   
//Date           Thu 25 Jun 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	GAMESET_Included
#define	GAMESET_Included

#define	DEFAULT_GAMESET 0

struct GameSettings
{
	bool	m_bBorder;		//Always border the UI
 	bool 	m_bUse16;			//force the use of 16-bit textures
	bool 	m_bBypassMemCheck;	//ignore video RAM check
	bool 	m_bFullScreenMode;	//force 3D to full screen mode
	bool	m_bDoTimerDiags;	//do the timer diagnstics for the AI	//JON 21/03/01
	ULong 	m_dwWidth;			//width for full screen mode
	ULong 	m_dwHeight;			//height for full screen mode
	SLong	m_dwTimerBufferSize;//size of the timer buffer			//JON 21/03/01
	GameSettings()
	{
		//default values for command line switches
		m_bDoTimerDiags=false;		// -DIAGS
		m_bBorder=false;			// -BORDER
		m_bUse16=false;				// -USE16
		m_bBypassMemCheck=false;	// -NOMEM
		m_bFullScreenMode=true;		// -F640X480
		m_dwWidth=640;
		m_dwHeight=480;
		m_dwTimerBufferSize=1;		// will default to 500 if -DIAGS is used, use -DIAGS[n] to set		//JON 21/03/01
	}
};

extern struct GameSettings gameSettings;

#endif
