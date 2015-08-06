//------------------------------------------------------------------------------
//Filename       imagemap.h
//System         
//Author         Martin Alderton
//Date           Mon 9 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	imageMap_Included
#define	imageMap_Included

//DEADCODE MS 31/01/00 	#include	"3DDefs.h"										//PD 30Oct95
	#include	"FileMan.h"										//PD 06Nov95

	#include	"bitfield.h"									//PD 25Aug96

#define MaxNumberOfImageMaps 512								//RJS 11Jul97
#define MaxMapDirs 			16									//DAW 27Oct98

#ifndef	__BCPLUSPLUS__
enum	ImageMapNumber;
#else
typedef	int	ImageMapNumber;
#endif
typedef ImageMapNumber *ImageMapListPtr;
struct 	ImageMap_Desc;
typedef ImageMap_Desc									//PD 01Aug96
				ImageMapDesc,									//PD 01Aug96
				*ImageMapDescPtr;								//PD 01Aug96

MINMAX		(ImageMapBit,0,512);								//DAW 27Oct98
MAKEFIELD 	(ImageMapBit,ImageMapBitMIN,ImageMapBitMAX);		//DAW 27Oct98
//DeadCode DAW 27Oct98 MAKEFIELD 	(ImageMapNumber,ImageMapNumberMIN,ImageMapNumberMAX);//PD 25Aug96


class	 ImageMap
{
	struct	SuperMap											//DAW 27Oct98
	{															//DAW 27Oct98
		UWord				offset_8bit;						//DAW 03Nov98
		UWord				offset_16bit;						//DAW 03Nov98
		SWord				nomaps;								//DAW 27Oct98
		ImageMapBitField	imbf;								//DAW 27Oct98
		ImageMapDescPtr		*imagemaptable;						//DAW 27Oct98
	};															//DAW 27Oct98
																//DAW 27Oct98
	SuperMap		superimagemaptable[MaxMapDirs];				//DAW 27Oct98
	SWord			supercnt;									//DAW 27Oct98
	
	friend	class	fileblock;
	
//DeadCode DAW 27Oct98 	ImageMapDesc	*imagemaptable;

	SLong			total_image_mem;							//PD 06Jun96
	SLong			total_ac_mem;								//RJS 24Jun98
	SLong			total_piloted_ac_mem;								//RJS 24Jun98
	SLong			total_cockpit_mem;							//RJS 24Jun98

	UWord			list_size,
					list_index;

	SLong			failedcnt;									//RJS 13Jun99

//DeadCode DAW 27Oct98 	ImageMapNumberField	imnf;									//PD 25Aug96

	public:
//DeadCode DAW 27Oct98 			SLong		*imagemaptable2;						//PD 10Mar97
			Bool		DoingAC,DoingCock;						//RJS 24Jun98
			bool		DoingPilotedAC;

			ImageMap();											//DAW 27Oct98
   			~ImageMap(void );

			void	AddImageMapToGlbList(UWord );				//PD 03Nov98
			void 	UnLoadImageMapPtrs(void);
			void 	LoadImageMapPtrs();
 			ImageMapDescPtr	GetImageMapPtrDontLoad(ImageMapNumber imagemap_number)
			{	//Returns NULL if not loaded							//JIM 15Dec00
				UWord	real_imagemap_number = imagemap_number & 0x7FFF; 
				UWord	file_no = real_imagemap_number & 0xFF;
				UWord	dir_no = real_imagemap_number >> 8; 
				return	superimagemaptable[dir_no].imagemaptable[file_no];
			}

 			ImageMapDescPtr	GetImageMapPtr(ImageMapNumber,Bool	skipmap=FALSE);//RJS 15Dec96

			SLong	ImageMapMemUsed()	{return total_image_mem;};//PD 06Jun96
			void	InitImageMaps();							//DAW 27Oct98
			void 	UnLoadImageMaps();							//RJS 14Jun99
		
	private:
			Bool 	LoadImageMap(SuperMap*,UWord,Bool,Bool	skipmap=FALSE);//DAW 27Oct98
			void 	UnLoadImageMap(ImageMapNumber);
			static  void 	FixupImageMap(void*	&dataarea,ULong&	datalengthin);
			void 	UnLoadImageMapPtr(SuperMap*,UWord);			//DAW 27Oct98

	protected:

};

extern ImageMap  Image_Map;										//PD 29Nov95

#endif


