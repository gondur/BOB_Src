//////////////////////////////////////////////////////////////////////
//
// Module:      propdial.h
//
// Created:     02/11/99 by RDH
//
// Description: 
//
//////////////////////////////////////////////////////////////////////
#define PROJDIR	"\\BOB"
#ifndef	PROPDIAL_H
#define	PROPDIAL_H
class	ComboTexts
{
  int		maxlistlen;
  int		listlen;
  char*		filebuffer;
  char** 	linebuffer;
public:
  ComboTexts(char* filename,int reqmaxlistlen);
  ~ComboTexts();
  SetComboList(CComboBox*);
};
inline ComboTexts::ComboTexts(char* filename,int reqmaxlistlen)
{
	maxlistlen=reqmaxlistlen;
	filebuffer=filename;
	linebuffer=NULL;
}
inline ComboTexts::~ComboTexts()
{
	if (linebuffer)
	{
		delete[]filebuffer;
		delete[]linebuffer;
	}
}
inline ComboTexts::SetComboList(CComboBox* combo)
{
	if (!linebuffer)
	{
		FILE* f=fopen(filebuffer,"rt");
		fseek(f,0,SEEK_END);
		int filesize=ftell(f)+1;
		fseek(f,0,SEEK_SET);
		filebuffer=new char[filesize];
		linebuffer=new char*[maxlistlen];
		filesize=fread(filebuffer,1,filesize,f);
		filebuffer[filesize]='!';
		fclose(f);
		char** ep=linebuffer;
		if (filebuffer[0]=='/')
			ep--;
		else
			*ep=filebuffer;
		for (int i=0;i<filesize;i++)
			if (filebuffer[i]=='\n')
			{
				filebuffer[i]=0;
				if (filebuffer[i+1]!='/')
					*++ep=filebuffer+i+1;
			}
		*ep=NULL;
		listlen=ep-linebuffer;
	}
		combo->ResetContent();
		for (char** fp=linebuffer;*fp;fp++)
			combo->AddString(*fp); 
}











#endif