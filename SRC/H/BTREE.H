//------------------------------------------------------------------------------
//Filename       btree.h
//System         
//Author         Paul.   
//Date           Fri 13 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	BTREE_Included
#define	BTREE_Included

//#include	"display.h"											//ARM 05Aug96

typedef	struct 	Base_Obj3D 	BaseObj3D,	*BaseObj3DPtr;
typedef	struct	Land_Obj 	LandObj3D,	*LandObj3DPtr;
typedef struct	Obj_3D		Obj3D,		*Obj3DPtr;
//DEAD typedef struct	Vert_Ex	 	landvertex,	*landvertexptr;

enum	ObjectType;

 struct	Obj_3D : public Base_Obj3D	//moved from 3ddefs to cut dependency on worldinc//JIM 14May96
 {
 	itemptr		ItemPtr;
 	animptr		AnimPtr;
 	fpCOORDS3D	Body;
 	UWord		Shape;										//RJS 28Aug98	//RJS 26May00
 	ANGLES		AngH,
 				AngC,
 				AngR;
	UByte		copySize;												//RJS 26May00
	UByte		pad1;
	UByte		pad2;
	UByte		pad3;			//8 longs

 };


class	ViewPoint;
#define	DEFAULT_BTREE 0

class	btree
		{
			Obj3DPtr		*item_list_header;					//PD 12Mar96
//DEADCODE PD 06/12/99 			LandObj3DPtr	*land_list_header;					//PD 13Mar96

			ANGLES	hdgBuffet,pitchBuffet,rollBuffet;			//PD 29Oct98

			SLong	farobj,
					objcount;									//PD 15Oct96

			BaseObj3DPtr	start_index;						//PD 12Mar96

			CLib3D *g_lpLib3d;
			ViewPoint* View_Point;
			SWord	item_list_index,
					item_list_size;	//, //PD 06/12/99
//DEADCODE PD 06/12/99 					land_list_index,
//DEADCODE PD 06/12/99 					land_list_size;

			public:
				CON				btree(SLong, SLong );			//PD 12Mar96
				DES				~btree();						//PD 12Mar96

				BaseObj3DPtr 	Get3DArea(ObjectType);			//PD 12Mar96
				void			SetupBTree(CLib3D *lib3d,ViewPoint* v)
								{g_lpLib3d=lib3d;View_Point=v;}
				void 			insert_object(BaseObj3DPtr );	//PD 12Mar96
				void 			insert_object2(BaseObj3DPtr );	//PD 11Oct96
				void			draw_object(CLib3D *,ViewPoint* vp);			//PD 12Mar96
				void			nz_draw_object(CLib3D *,ViewPoint* vp);			//PD 12Mar96
				void  			Clear3DArea();					//PD 12Mar96
				void			PreparePossMoveCycle();			//PD 15Oct96

				void SetHPRBuffet(ANGLES,ANGLES,ANGLES);

			struct ObjectRec
			{
				enum {MAX_OBJECTS=4096};

				ULong	numItems;
				bool	somethingvisible;						//RJS 07Feb00
//DeadCode RJS 07Feb00 				item *itemList[MAX_OBJECTS];
				D3DVECTOR pos[MAX_OBJECTS];
				D3DVALUE rad[MAX_OBJECTS];
				ULong itemFlag[MAX_OBJECTS];
				ULong range[MAX_OBJECTS];
				Obj_3D	obj3d[MAX_OBJECTS];					//RJS 07Feb00
			};
			static ObjectRec objectRec;

			private:
				void  			recurse(BaseObj3DPtr );			//PD 12Mar96
				void  			nz_recurse(BaseObj3DPtr );			//PD 12Mar96
				void  			drw_obj(BaseObj3DPtr );			//PD 12Mar96
				void			drw_static(BaseObj3DPtr );		//PD 13Mar96
				void			drw_shadeoverride(BaseObj3DPtr );		//PD 4Apr99
				void			drw_mobile(BaseObj3DPtr );		//PD 13Mar96
//DEADCODE PD 03/12/99 				void			drw_land(BaseObj3DPtr );		//PD 13Mar96
//DEADCODE PD 03/12/99 				void			drw_special_land(BaseObj3DPtr );
//DEAD				void			drw_nrland(BaseObj3DPtr );		//PD 18Mar96
//DEAD				void			drw_sky(BaseObj3DPtr );			//PD 13Mar96
//DEAD				void			drw_horizon(BaseObj3DPtr );		//PD 13Mar96
				void			drw_shadow(BaseObj3DPtr );		//RJS 07May97
				void			drw_cockpit(BaseObj3DPtr );
				BaseObj3DPtr	RecycleObj3D();					//RDH 26Jul96
				void			drw_map(BaseObj3DPtr );			//RJS 08Sep98

			protected:

		};

#endif
