#ifndef dataDictionary_h
#define dataDictionary_h

//#include <cstdio>
extern "C"{
#include <stdio.h>
};
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
    attribute(attribute& AA);
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
    relation(relation& RR);
    ~relation();
    int initRelation(struct dbSysHead *head, int fid, char *relationName, char *constructorName);
    int init(char *relationName, char *constructorName);
    int changeRecordNum(int num);
    int insertAttribute(char *name, int type, int length);
    char *getRelationName();
    char *getConstructor();
    int getAttributeNum();
    int getRecordLength();
    int getRecordNum();
    attribute getAttributeByName(char *name);
    attribute getAttributeByNo(int no);
    
public:
    long fileID;
private:
//    long fileID;//文件标识
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

int initTable(struct dbSysHead *head, long fid);
int showTable(struct dbSysHead *head, char* name);
#endif
