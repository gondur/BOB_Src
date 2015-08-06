//------------------------------------------------------------------------------
//Filename       impact.h
//System         
//Author         Robert Slater
//Date           Thu 25 Nov 1999
//Description    
//				Designed by Jim! Handles balloons....
//------------------------------------------------------------------------------
#ifndef	IMPACT_Included
#define	IMPACT_Included

#define	DEFAULT_IMPACT 0






//DeadCode RJS 14Mar00 class OctGrid
//DeadCode RJS 14Mar00 {
//DeadCode RJS 14Mar00 	int recsize;
//DeadCode RJS 14Mar00 	typedef UByte	BaseDataType;
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 	BaseDataType*	FindRecord(int x,int y);		//convert coords and find
//DeadCode RJS 14Mar00 	BaseDataType*	FindRecordIndex(int& x,int& y);	//returns x3,y3
//DeadCode RJS 14Mar00 	virtual BaseDataType*	FindRecord(int x1,int y1,int x2,int y2);
//DeadCode RJS 14Mar00 	virtual BaseDataType*	FindMakeRecord(int x1,int y1,int x2,int y2);
//DeadCode RJS 14Mar00 	void	ConvertOrdinate(int x,int& x1,int& x2,int& x3)
//DeadCode RJS 14Mar00 	{
//DeadCode RJS 14Mar00 		x3=(x>>=17)&7;
//DeadCode RJS 14Mar00 		x2=(x>>=3)&7;
//DeadCode RJS 14Mar00 		x1=(x>>3);
//DeadCode RJS 14Mar00 	}
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 	int GetValue(int x,int y)
//DeadCode RJS 14Mar00  	{
//DeadCode RJS 14Mar00  		BaseDataType t=FindRecordIndex(x,y);
//DeadCode RJS 14Mar00  		
//DeadCode RJS 14Mar00 		return GetValue(t,x,y);		
//DeadCode RJS 14Mar00  	};
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 	virtual	int GetValue(BaseDataType* record,int x3,int y3)=0;
//DeadCode RJS 14Mar00 	int SetValue(int x,int y,int v);
//DeadCode RJS 14Mar00 	virtual	int SetValue(BaseDataType* record,int x3,int y3,int v);
//DeadCode RJS 14Mar00 };
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 class HighSparseOctGrid
//DeadCode RJS 14Mar00 {
//DeadCode RJS 14Mar00 	//Use when no sparsity optimisation is possible
//DeadCode RJS 14Mar00 	//or only 80km level sparsity optimisation is practical
//DeadCode RJS 14Mar00 	//This scheme costs 4 bytes per 4K of data points.
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 	BaseDataType*	subrecords[10][10];
//DeadCode RJS 14Mar00 	BaseDataType* FindRecord(x1,y1,x2,y2)	//should not be inline
//DeadCode RJS 14Mar00 	{
//DeadCode RJS 14Mar00 		BaseDataType* rv=subrecords[y1][x1];
//DeadCode RJS 14Mar00 		if (rv)
//DeadCode RJS 14Mar00 			rv+=recsize*(y2+x2*8);
//DeadCode RJS 14Mar00 		return rv;
//DeadCode RJS 14Mar00 	}
//DeadCode RJS 14Mar00 	BaseDataType* FindMakeRecord(x1,y1,x2,y2)	//should not be inline
//DeadCode RJS 14Mar00 	{
//DeadCode RJS 14Mar00 		BaseDataType* rv=subrecords[y1][x1];
//DeadCode RJS 14Mar00 		if (!rv)
//DeadCode RJS 14Mar00  		{
//DeadCode RJS 14Mar00  			rv=subrecords[y1][x1]=new BaseDataType[recsize*64];
//DeadCode RJS 14Mar00  			memset(rv,0, recsize*64);
//DeadCode RJS 14Mar00  		}
//DeadCode RJS 14Mar00 		rv+=recsize*(y2+x2*8);
//DeadCode RJS 14Mar00 		return rv;
//DeadCode RJS 14Mar00 	}
//DeadCode RJS 14Mar00 };
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 class	BitOctGrid
//DeadCode RJS 14Mar00 {
//DeadCode RJS 14Mar00 	//1 bit per data value. Not worth optimising at 10km level
//DeadCode RJS 14Mar00  	BitOctGrid()		{recsize=8;}
//DeadCode RJS 14Mar00 	
//DeadCode RJS 14Mar00 	int GetValue(BaseDataType* record,int x3,int y3)
//DeadCode RJS 14Mar00  	{
//DeadCode RJS 14Mar00 		if (record)
//DeadCode RJS 14Mar00 			return BT(record,x3*8+y3);
//DeadCode RJS 14Mar00 		else
//DeadCode RJS 14Mar00 			return 0;
//DeadCode RJS 14Mar00 	}
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 	int SetValue(BaseDataType* record,int x3,int y3,int v)
//DeadCode RJS 14Mar00  	{
//DeadCode RJS 14Mar00 		if (v)
//DeadCode RJS 14Mar00 			return BTS(record,x3*8+y3);
//DeadCode RJS 14Mar00 		else
//DeadCode RJS 14Mar00 			return BTC(record,x3*8+y3);
//DeadCode RJS 14Mar00 	}
//DeadCode RJS 14Mar00 };
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 class LowSparseOctGrid
//DeadCode RJS 14Mar00 {
//DeadCode RJS 14Mar00 	//Use when low level is quite large (64 bytes)
//DeadCode RJS 14Mar00  	//and some sparsity optimisation may be possible
//DeadCode RJS 14Mar00  	//This scheme costs 4 bytes per 64 data points
//DeadCode RJS 14Mar00 	char*	subrecords[10][10][8][8];	
//DeadCode RJS 14Mar00 	char* FindRecord(x1,y1,x2,y2)	//should not be inline
//DeadCode RJS 14Mar00 	{
//DeadCode RJS 14Mar00 		char* rv=subrecords[x1][y1][x2][y2];
//DeadCode RJS 14Mar00 		return rv;
//DeadCode RJS 14Mar00 	}
//DeadCode RJS 14Mar00 };
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 class	ByteOctGrid
//DeadCode RJS 14Mar00 {
//DeadCode RJS 14Mar00 	//1 bit per data value. Not worth optimising at 10km level
//DeadCode RJS 14Mar00  	BitOctGrid()		{recsize=64;}
//DeadCode RJS 14Mar00 	int GetValue(BaseDataType* record,int x3,int y3)
//DeadCode RJS 14Mar00  	{
//DeadCode RJS 14Mar00 		return record[x3*8+y3];
//DeadCode RJS 14Mar00 	}
//DeadCode RJS 14Mar00 };
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00 class DoubleSparseOctGrid
//DeadCode RJS 14Mar00 {
//DeadCode RJS 14Mar00 	//Use when low level is quite large (64 bytes)
//DeadCode RJS 14Mar00  	//and some sparsity optimisation may be possible
//DeadCode RJS 14Mar00  	//at both low level (10km) and high level (80km) levels
//DeadCode RJS 14Mar00  	//This scheme costs 4 bytes per 64 data points
//DeadCode RJS 14Mar00  	struct	SubGrid
//DeadCode RJS 14Mar00  	{
//DeadCode RJS 14Mar00  		char* subrecords[8][8];
//DeadCode RJS 14Mar00  	};
//DeadCode RJS 14Mar00 	SubGrid*	subrecords[10][10];	
//DeadCode RJS 14Mar00 	char* FindRecord(x1,y1,x2,y2)	//should not be inline
//DeadCode RJS 14Mar00  	{
//DeadCode RJS 14Mar00   		SubGrid* sg= subrecords[x1][y1];
//DeadCode RJS 14Mar00   		if (!sg)
//DeadCode RJS 14Mar00 			return NULL;
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00  		char* rv= sg[0][x2][y2];
//DeadCode RJS 14Mar00 
//DeadCode RJS 14Mar00  		return rv;
//DeadCode RJS 14Mar00  	}
//DeadCode RJS 14Mar00 };



class	Impact
{
private:

	bool	CheapCol(ItemPtr, ItemPtr);									//RJS 12Sep00


public:

	SLong 	GetDamageLoc(ShapeNum, animptr&);
	void	CollideAircraft(AirStrucPtr, AirStrucPtr);
	void	HitGroupElement(ItemPtr,ItemPtr,SLong index=-1, SLong amount=8, SLong damagetype=0);//RJS 05Apr00
	bool	HitGroup(ItemPtr,ItemPtr,SLong amount=24, SLong damagetype=0);	//RJS 11Aug00
	void	HitAircraft(ItemPtr,ItemPtr, SLong amount=8, SLong damagetype=0);	//RJS 30/05/00
	void	TestForBalloon(ItemPtr);									//RJS 12Sep00



};

extern	Impact	Fake_Damage;									//RJS 05Apr00



#endif
