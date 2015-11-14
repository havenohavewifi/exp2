//
//  dataDictionary.h
//  exp2
//
//  Created by IreneWu on 15/11/11.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#ifndef dataDictionary_h
#define dataDictionary_h

//#include <cstdio>
#include "dbHead.h"

#define NAMELENGTH  32
#define ATTRIBUTENUM  10

struct attributeDefine
{
    char attributeName[NAMELENGTH];//Â±ûÊÄßÂêç
    int type;//Êï¥Âûã„ÄÅÂ≠óÁ¨¶Âûã„ÄÅÊó•ÊúüÂûã
    int length;//Â±ûÊÄßÈïøÂ∫¶
    int recordDeviation;//ËÆ∞ÂΩïÂÜÖÂÅèÁßª
};

struct relationDefine
{
    long fileID;//文件标识
    char relationName[NAMELENGTH];//ÂÖ≥Á≥ªÂêç
    char constructor[NAMELENGTH];//Âª∫Á´ãËÄÖ
    int attributeNum;//Â±ûÊÄß‰∏™Êï∞
    int recordLength;//ËÆ∞ÂΩïÈïøÂ∫¶
    int recordNum;//ËÆ∞ÂΩïÊÄªÊï∞
    struct attributeDefine attribute[ATTRIBUTENUM];//Â±ûÊÄßÂÆö‰πâÊåáÈíà
};

struct dbSysHead
{
    struct SysDesc desc;
    struct buffSpace buff[3];   // 3 buffers for SPJ operations
    
    unsigned long *bitMap;
    struct relationDefine redef[MAX_FILE_NUM];		//  √ø“ª∏ˆ±Ìµƒπÿœµ∂®“Â
    //    struct relationDefine * redef;
    FILE *fpdesc;
};

int initRelation(struct dbSysHead *head, long fid, char *relationName, char *constructorName);//≥ı ºªØπÿœµ
int changeRecordNum(struct dbSysHead *head, long fid, int num);//∏¸∏ƒº«¬º◊‹ ˝
int initAttribute(struct dbSysHead *head, long fid, char *name, int type, int length);//≥ı ºªØ“ª∏ˆ Ù–‘±Ì
int initTable(struct dbSysHead *head, long fid);
int showTable(struct dbSysHead *head, char* name);

#endif /* defined(__exp2__dataDictionary__) */
