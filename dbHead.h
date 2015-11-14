#ifndef DBHEAD_H_
#define DBHEAD_H_

#include "file.h"
#include "err.h"
#include "dataDictionary.h"

#define DBMS_DAT "./dbms.dat"
#define Customer_tbl "./customer.tbl"
#define Index_Path "./"
/*
struct dbSysHead
{
	struct SysDesc desc;
	struct buffSpace buff;
    
	unsigned long *bitMap;
    struct relationDefine redef[MAX_FILE_NUM];		//  √ø“ª∏ˆ±Ìµƒπÿœµ∂®“Â
//    struct relationDefine * redef;
	FILE *fpdesc;
};
*/
struct dbSysHead;   //在这里只是声明，具体的定义走dataDictionary头文件里，若在此处定义，编译不通过，因为其中的成员变量还未编译，还未初始化
//	bit.cpp
int setBit(unsigned long *num, int pos, int setValue);
int getBit(unsigned long num, int pos);

/*******************	buffManage.cpp   *******************/
// ≤È—Ø“≥query£®»´æ÷“≥∫≈£© «∑Ò‘⁄ª∫≥Â«¯÷–
int queryPage(struct dbSysHead *head, int bufferID, long query);
// ”√pageNo£®»´æ÷“≥∫≈£©“≥ÃÊªªª∫≥Â«¯÷–œ¬±ÍŒ™mapNoµƒ“≥
int replacePage(struct dbSysHead *head, int bufferID, int mapNo, long pageNo);
// ª∫≥Â«¯“≥√Êµ˜∂»À„∑®£¨ø…—°‘ÒLRUªÚ’ﬂFIFO
int scheBuff(struct dbSysHead *head, int bufferID);
// ª∫≥Â«¯“≥√Êµ˜∂»£∫LRU
int LRU(struct dbSysHead *head, int bufferID);
// ª∫≥Â«¯“≥√Êµ˜∂»£∫FIFO
int FIFO(struct dbSysHead *head, int bufferID);
// œÚª∫≥Â«¯÷–«Î«Ûquery“≥√Ê£¨∑µªÿ∆‰‘⁄ª∫≥Â«¯÷–µƒœ¬±Í
int reqPage(struct dbSysHead *head, int bufferID, long query);


//	diskOpt.cpp
long allocatePage(struct dbSysHead *head, int reqPageNum);//∑÷≈‰¡¨–¯µƒ“≥
int initSegment(struct Segment *newSegment, long startPage, long pageNum, long fd, long preAddr, long nextAddr);//≥ı ºªØ∂Œ
long creatFileSpace(struct dbSysHead *head);//Œ™“ª∏ˆŒƒº˛¥¥Ω®ø’º‰
int recyOnePage(struct dbSysHead *head, long pageNo);//∏˘æ›“≥∫≈ªÿ ’“ª∏ˆ“≥
int recyPage(struct dbSysHead *head, long segmentAddr);//ªÿ ’¥”ƒ≥“ª∏ˆ∂ŒÕ∑ø™ ºµƒÀ˘”–µƒ“≥
int recyFileSpace(struct dbSysHead *head, long fid);//ªÿ ’Œƒº˛ø’º‰
int queryFileID(struct dbSysHead *head, long fid);//≤È—Ø“ª∏ˆŒƒº˛±Í ∂ «∑Ò‘⁄œµÕ≥÷–
int getSegmentValue(struct dbSysHead *head, long segmentAddr, struct Segment *newSegment);//ªÒµ√“ª∏ˆ∂Œµƒƒ⁄»›
int writeSegmentValue(struct dbSysHead *head, long segmentAddr, struct Segment *newSegment);//Ω´ƒ⁄»›–¥µΩ∂Œ÷–
long getLastSegmentAddr(struct dbSysHead *head, long fid);//µ√µΩ◊Ó∫Û“ª∏ˆ∂Œµƒ∂ŒÕ∑
int extendFileSpace(struct dbSysHead *head, long fid, int extendPage);//¿©’π∂Œø’º‰


//	err.cpp
//  int isAvail(void *p, char *funcName, int type);

//	fileOpt.cpp
long mapPage(struct dbSysHead *head, long fid, long num);
int readInPage(struct dbSysHead *head, int bufferID, long pgID, long pos, long length, void *des);
int writeInPage(struct dbSysHead *head, int bufferID, long pgID, long pos, long length, void *des);
int rdFile(struct dbSysHead *head, int bufferID, long fid, long pos, long length, void *des);
int wtFile(struct dbSysHead *head, int bufferID, long fid, long pos, long length, void *des);

//	init.cpp
int initSys(struct dbSysHead *head);
int creaSysHead();

//	show.cpp
int showDesc(struct dbSysHead *head);
int showFileDesc(struct dbSysHead *head);
int showiNode(struct dbSysHead *head, long fid);
int showBitMap(struct dbSysHead *head, long start, long end);

//	update.cpp
int sysUpdate(struct dbSysHead *head);

#endif
