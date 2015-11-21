#ifndef FILE_H_
#define FILE_H_

//  ˝æ›ø‚◊Ó∂‡»›ƒ…¡ø192M
//#define SIZE_DATA_SPACE (12*1024*1024)
// √ø“≥¥Û–°4K

// ¬†Àù√¶‚Ä∫√∏‚Äö‚óä√ì‚àÇ‚Ä°¬ª‚Ä∫∆í‚Ä¶¬°√∏192M
#define SIZE_DATA_SPACE (32*1024*1024)
// ‚àö√∏‚Äú‚â•¬•√õ‚Äì¬∞4K

#define SIZE_PER_PAGE (4*1024)
// BitMap≈í‚Ñ¢‚àÇÀõŒ©¬Ø√∑‚àÜ¬•√Ü¬£¬®‚àö√∏‚Äú¬™≈í¬™¬•Àô¬±√å‚àÇ‚Äò‚Äù¬∂‚Äú‚â•¬†¬´‚àë√í≈í‚Ñ¢√∏‚Äô
#define SIZE_BIT_MAP  (SIZE_DATA_SPACE/(SIZE_PER_PAGE*8))

// ‚ÄôÀö‚àèÀÜ¬†Àù√¶‚Ä∫√∏‚Äö¬•√ä‚Äò‚ÅÑ‚Äú¬™‚àèÀÜ≈í∆í¬∫ÀõDBMS_DAT¬µ¬±√∑‚Äì¬£¬®‚Äú¬ø¬•≈í√Ä‚â•‚Äì√ö≈í‚Ñ¢ ??≈í‚Ñ¢‚Äò‚Ä∫¬†¬±¬™œÄ‚àö¬™‚Äù‚Äì‚Äù‚àö¬µŒ©¬µ∆í
// (table description??, bitmap, data (pages), segment??)
#define TABLE_DESC_ADDR (0)
// BitMap‚Äò‚ÅÑ¬•√ä¬•¬¢≈í∆í¬∫Àõ√∑‚Äì¬µ∆í¬µ√ø√∑‚àë
#define BITMAP_ADDR (1024)
// ¬†Àù√¶‚Ä∫‚àÇ≈í‚Äò‚ÅÑ¬•√ä¬•¬¢≈í∆í¬∫Àõ√∑‚Äì¬µ∆í¬µ√ø√∑‚àë

#define DICTIONARY_ADDR  (BITMAP_ADDR+SIZE_BIT_MAP)
#define DICTIONARY_SIZE (8*1024)
#define DATA_ADDR	(DICTIONARY_ADDR+DICTIONARY_SIZE)
// ‚àÜ‚Ä∞√ÄÀö≈í∆í¬∫Àõ√∑‚Äì√Ä‚àÜ‚à´ƒ±‚àÇ¬∫‚àö¬™‚Äù‚Äì‚â•ÀÜ≈ì√∑¬£¬®‚Äù‚Äì‚Äù‚àö¬¨Ô£ø¬£√∏
#define SEGMENT_ADDR (DATA_ADDR+SIZE_DATA_SPACE)

/*
// √ø∏ˆ∂ŒµƒπÃ∂®“≥√Ê ˝
#define PAGE_PER_SEGMENT 28
// ◊Ó¥Û¥Ê¥¢µƒ±Ì∏ˆ ˝
#define MAX_FILE_NUM 64
// µ⁄“ª∏ˆ±Ìµƒ±‡∫≈£¨¥”1ø™ º
*/
// ‚àö√∏‚àèÀÜ‚àÇ≈í¬µ∆íœÄ√É‚àÇ¬Æ‚Äú‚â•‚àö√ä¬†Àù
#define PAGE_PER_SEGMENT (28)
// ‚óä√ì¬•√õ¬•√ä¬•¬¢¬µ∆í¬±√å‚àèÀÜ¬†Àù
#define MAX_FILE_NUM (8)
// ¬µ‚ÅÑ‚Äú¬™‚àèÀÜ¬±√å¬µ∆í¬±‚Ä°‚à´‚âà¬£¬®¬•‚Äù1√∏‚Ñ¢¬†¬∫

#define FIRST_FID	(1)

// ¬™‚à´‚â•√Ç¬´¬Ø√ÄÀò‚à´¬®‚Äú‚â•‚àö√ä‚àèÀÜ¬†Àù
#define SIZE_BUFF (32)
// Buffer√∑‚Äì‚â§¬™¬•√ä‚Äò‚ÅÑ‚â§√à‚Äî√ò‚Äú‚â•‚àö√ä¬†¬±¬µ∆í‚àë¬µ¬™√ø√∑¬µ
#define BUFF_NOT_HIT -1
// ‚àÇ‚Äò‚Äú‚â•‚àö√ä‚â§≈∏‚óäÀú¬µ∆í‚àö√ã¬†ÀÜ
#define P_AVAI		1
#define P_UNAVAI	0
#define P_EDIT		1
#define P_UNEDIT	0
#define ALLO_FAIL	-1


struct Segment
{
	long fid;					//	‚àè‚àöSegment¬†√ô‚Äù‚ÅÑ∆í∆í‚àèÀÜ≈í∆í¬∫Àõ¬£¬®¬∫¬•‚àö√∏‚àÇ≈í√∑¬™¬†√ô‚Äù‚ÅÑ‚Äú¬™‚àèÀÜ¬±√å¬£¬Æ¬•√ä‚Äò‚ÅÑŒ©≈ì¬•√õ√∏‚Äô¬∫‚Ä∞¬ø√Ä‚àë‚Äî¬£¬©
	long count;					//	‚àè‚àöSegment√∑‚Äì¬∫¬´¬¨¬∫¬°√Ä‚àÇ‚Ä°‚Ä¶≈∏‚àèÀÜ‚Äú‚â•
	long nextAddr;				//	≈ì¬¨‚Äú¬™‚àèÀÜSegment¬µ∆í√∑‚àè‚Äô√é
	long preAddr;				//	¬´‚àû‚Äú¬™‚àèÀÜSegment¬µ∆í√∑‚àè‚Äô√é
	long pageNo[PAGE_PER_SEGMENT];	//	¬∫¬´¬¨¬∫‚àö√∏‚Äú¬™‚àèÀÜ‚Äú‚â•¬µ∆í‚Äú‚â•‚à´‚âà
};


struct FileDesc
{
    long fileID;				//	≈í∆í¬∫Àõ¬µ∆í¬±√ç¬†‚àÇ
    long fileAddr;				//	≈í∆í¬∫Àõ¬µ∆íSegment¬µ√ø√∑‚àë√∑¬µ¬£¬ÆSegment‚Äù‚àö¬°¬•¬±√å¬•√Ü¬°¬®¬£¬©
    long filePageNum;			//	≈í∆í¬∫Àõ‚Äô¬∫‚Äù‚àö‚àÇ‚Ä°‚Ä¶≈∏‚Äú‚â•
    long filePageEndPos;        //  mark the end position in the final page
};

struct SysDesc
{
	long sizeOfFile;			//	¥Ê¥¢Œƒº˛÷–£¨ ˝æ›«¯µƒ¥Û–°£¨ƒ¨»œ…ËŒ™196M
	long sizePerPage;           //	√ø“ª∏ˆ“≥µƒ¥Û–°
	long totalPage;				//	◊‹π≤µƒ“≥ ˝
	long pageAvai;				//	µ±«∞”–∂‡…Ÿø…”√µƒ“≥

	long bitMapAddr;			//	bitMap‘⁄¥Ê¥¢Œƒº˛÷–µƒµÿ÷∑
	long sizeBitMap;			//	bitMapµƒ¥Û–°,“‘◊÷Ω⁄Œ™µ•Œª
    long dataDictionaryAddr;    //  datadictionary start address
    long sizedataDictionary;    //  datadictionary size
	long dataAddr;				//	¥Ê¥¢Œƒº˛÷– ˝æ›«¯µƒ¥Û–°
	long segmentNum;			//	Segmentµƒ ˝¡ø
	long segmentAddr;			//	Segment‘⁄¥Ê¥¢Œƒº˛µƒµÿ÷∑
	long segmentCur;			//	ƒø«∞ π”√π˝µƒSegment ˝¡ø

	long curfid;				//	ƒø«∞ø…“‘∑÷≈‰µƒfid∫≈
	long curFileNum;			//	ƒø«∞”–∂‡…Ÿ∏ˆŒƒº˛£¨◊Ó∂‡Œ™ MAX_FILE_NUM
    
	struct FileDesc fileDesc[MAX_FILE_NUM];			//	∂‘√ø“ª∏ˆŒƒº˛Ω¯––√Ë ˆ

};

struct buffMap
{
	long pageNo;					//	∏√ª∫≥Â«¯øÈ÷–¥Ê¥¢µƒ ˝æ›Œƒº˛µƒ“≥∫≈
	long loadTime;					//	∂¡»Îª∫≥Â«¯µƒ ±º‰
	long vstTime;					//	∑√Œ ∏√ª∫≥Â«¯øÈµƒ ±º‰
	int edit;
    
};

struct buffSpace
{
	/*
	”¶∏√∂ØÃ¨∑÷≈‰ª∫≥Â«¯ ˝æ›µƒø’º‰
	“ÚŒ™’‚—˘æ≤Ã¨∑÷≈‰ƒ‹∑÷≈‰µΩµƒø’º‰Ã´–°
=======
	 /*
		‚Äù¬∂‚àè‚àö‚àÇ√ò√É¬®‚àë√∑‚âà‚Ä∞¬™‚à´‚â•√Ç¬´¬Ø¬†Àù√¶‚Ä∫¬µ∆í√∏‚Äô¬∫‚Ä∞
		‚Äú√ö≈í‚Ñ¢‚Äô‚Äö‚ÄîÀò√¶‚â§√É¬®‚àë√∑‚âà‚Ä∞∆í‚Äπ‚àë√∑‚âà‚Ä∞¬µŒ©¬µ∆í√∏‚Äô¬∫‚Ä∞√É¬¥‚Äì¬∞
>>>>>>> Stashed changes
	*/
	char data[SIZE_BUFF][SIZE_PER_PAGE];	//	¬™‚à´‚â•√Ç¬´¬Ø¬†Àù√¶‚Ä∫√∏√à¬£¬®∆í√∏¬´‚àû‚Ä¶√ã√∑‚àöSIZE_BUFF√∏√à¬£¬®‚àö√∏‚Äú¬™√∏√à¬µ∆í¬•√õ‚Äì¬∞≈í‚Ñ¢‚Äú‚â•¬µ∆í¬•√õ‚Äì¬∞	
	struct buffMap map[SIZE_BUFF];			//	¬∫¬´¬¨¬∫‚àö√∏‚Äú¬™‚àèÀÜ¬™‚à´‚â•√Ç¬´¬Ø√∏√à¬µ∆í‚Äì‚âà≈ì¬¢
	long curTimeStamp;						//	∆í√∏¬´‚àû¬µ∆í≈ì‚Ä°‚àÇ‚Äò¬†¬±¬∫‚Ä∞¬•¬°
    bool emptyOrnot; //true for empty, false for in use
};

typedef struct
{
	int year;
	int month;
	int day;
} date;//»’∆⁄–Õ
#endif
