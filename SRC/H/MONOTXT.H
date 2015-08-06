//------------------------------------------------------------------------------
//Filename       monotxt.h
//System         
//Author         Paul.   
//Date           Wed 16 Oct 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	MONOTXT_Included
#define	MONOTXT_Included

/////////////////////////////////////////////////////////
//just comment your own equate in when you take a version
//make sure any mono debugs you put in are removed when
//your #define is removed
/////////////////////////////////////////////////////////

//#define PAULS_DEBUG
//#define DAVES_DEBUG
//#define JIMS_DEBUG
//#define ROBS_DEBUG
//#define CRAIGS_DEBUG
//#define RODS_DEBUG
//#define MACCAS_DEBUG

#ifdef NDEBUG
	#undef PAULS_DEBUG
	#undef DAVES_DEBUG
	#undef JIMS_DEBUG
	#undef ROBS_DEBUG
	#undef CRAIGS_DEBUG
	#undef RODS_DEBUG
	#undef MACCAS_DEBUG
#else
	#define	ENABLE_MONO_TEXT
#endif

//#define NO_MONO_DATA "no PrintVar"

/////////////////////////////////////////////////
//put any #defines or #undefs in your own section
/////////////////////////////////////////////////

#ifdef PAULS_DEBUG
#define SHOW_FRAMERATE
#endif

#ifdef DAVES_DEBUG

#endif

#ifdef JIMS_DEBUG

#endif

#ifdef ROBS_DEBUG

#endif

#ifdef CRAIGS_DEBUG
	#define DISPLAY_MONO_DATA
	#undef NO_MONO_DATA
#endif

#ifdef RODS_DEBUG
	#define DISPLAY_MONO_DATA
	#undef NO_MONO_DATA
#endif

#ifdef MACCAS_DEBUG

#endif

/////////////////////////////////////////////////
/////////////////////////////////////////////////

class	MonoText
{
	SLong	cx,cy;	//cursor pos

	public:

		CON		MonoText()	{ClsMono();};
		DES		~MonoText() {};

		void ClsMono();
		void SetCursor(SLong rx=0,SLong ry=0);
		void StartTimer(SLong& );
		void StopTimer(SLong& );
		void StopTimer(SLong& ,UByte* );
		void Print(SLong val, UByte* text)
			 {
#ifdef	ENABLE_MONO_TEXT
			 	UByte	ltstring[] = "1234567890 \n";

			 	UByte*	tstring = ltstring;

			 	TextOutMono(text);

			 	BinToASCII(val,tstring);

			 	TextOutMono(tstring);
#endif
			 }
		void Prin(SLong val, UByte* text)
			 {
#ifdef	ENABLE_MONO_TEXT
			 	UByte	ltstring[] = "1234567890";

			 	UByte*	tstring = ltstring;

			 	TextOutMono(text);

			 	BinToASCII(val,tstring);

			 	TextOutMono(tstring+7);
#endif
			 }
		void Print(UByte* text)
			 {
#ifdef	ENABLE_MONO_TEXT
			 	TextOutMono(text);
#endif
			 }
		void Print(UByte* text,SLong length);

		void PrintAt(SLong x,SLong y,SLong& val, UByte* text)
			 {
#ifdef	ENABLE_MONO_TEXT
			 	SetCursor(x,y);
			 	Print(val,text);
#endif
			 }
		void PrintAt(SLong x,SLong y,UByte* text)
			 {
#ifdef	ENABLE_MONO_TEXT
			 	SetCursor(x,y);
				Print(text);
#endif

			 }

		void PrintHexAt(SLong x,SLong y,SLong h,SLong digits)
		{
#ifdef	ENABLE_MONO_TEXT
			SetCursor(x,y);
			UByte lstring[9];
			BinToHEX(h,lstring);
			for (int i=0;i<8-digits;i++)
				if (lstring[i]!='0')
				{
					Print(lstring);
					return;
				}
			Print(lstring+8-digits);
#endif
		}

	private:

		void	BinToASCII(SLong ,UByte* );
		void	BinToHEX(SLong,UByte*);

		void	TextOutMono(UByte* );
};

extern class MonoText Mono_Text;

struct	ProbeTime
{
	static int colcounts[80];
	static float	coltimes[80];
	static int		colinsts[80];
	static int divfactor;
	static bool	timergo;
	__int64	ticker;
	int	col;
	char* str;

	ProbeTime(int x,char* s);	//="%5i")		
	~ProbeTime();
	operator bool()	{return true;}

};

#endif
