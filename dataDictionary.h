//
//  dataDictionary.h
//  exp2
//
//  Created by mengxi on 15/11/15.
//  Copyright (c) 2015年 mengxi. All rights reserved.
//

#ifndef dataDictionary_h
#define dataDictionary_h

//#include <cstdio>
#include "dbHead.h"

#define NAMELENGTH  32
#define ATTRIBUTENUM  10
#define INT 1
#define CHAR 2
#define DATE 3

class attribute
{
public:
	attribute();
	~attribute();

	int initAttribute(char *name, int type, int length, int deviation);
	char *getName();
	int getType();
	int getLength();
	int getRecordDeviation();

private:
	char attributeName[NAMELENGTH];//属性名
	int type;//属性类型
	int length;//属性长度
	int recordDeviation;//记录内偏移
};


class relation
{
public:
	relation();
	~relation();
	int initRelation(struct dbSysHead *head, int fid, char *relationName, char *constructorName);
	int changeRecordNum(int num);
	int insertAttribute(char *name, int type, int length);
	char *getRelationName();
	char *getConstructor();
	int getAttributeNum();
	int getRecordLength();
	int getRecordNum();
	attribute getAttributeByName(char *name);
	attribute getAttributeByNo(int no);


private:
	long fileID;//文件标识
	char relationName[NAMELENGTH];//关系名
	char constructor[NAMELENGTH];//建立者
	int attributeNum;//属性个数
	int recordLength;//记录长度
	int recordNum;//记录个数
	attribute atb[ATTRIBUTENUM];//属性表
};

struct dbSysHead
{
    struct SysDesc desc;
    struct buffSpace buff[3];   // 3 buffers for SPJ operations
    
    unsigned long *bitMap;
    relation redef[MAX_FILE_NUM];		//关系数据字典
    FILE *fpdesc;
};

<<<<<<< HEAD
=======
int initRelation(struct dbSysHead *head, long fid, const char *relationName, const char *constructorName);//≥ı ºªØπÿœµ
int changeRecordNum(struct dbSysHead *head, long fid, int num);//∏¸∏ƒº«¬º◊‹ ˝
int initAttribute(struct dbSysHead *head, long fid, const char *name, int type, int length);//≥ı ºªØ“ª∏ˆ Ù–‘±Ì
>>>>>>> 6935d6d5c26c9486420359d5298b7d1ad5e8c238
int initTable(struct dbSysHead *head, long fid);
int showTable(struct dbSysHead *head, char* name);

#endif /* defined(__exp2__dataDictionary__) */
