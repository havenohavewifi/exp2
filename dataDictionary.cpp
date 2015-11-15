//
//  dataDictionary.cpp
//  exp2
//
//  Created by IreneWu on 15/11/11.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

// 1. change into the C++
// 2. add the functions that can find one attribute
    // just return the attribute struct, 
    // find the attribute type and offset according to attribute name
// 3. change the length of attribute into then number of byte

extern "C" {
    #include <string.h>
};
 
#include <string>
#include <cstdio>
#include <iostream>
#include "dataDictionary.h"
int initTable(struct dbSysHead *head, long fid)
{
    initRelation(head, fid, "customer", "TianzhenWu");
    initAttribute(head, fid, "custkey", 1, 1);
    initAttribute(head, fid, "name", 2, 64);
    initAttribute(head, fid, "address", 2, 64);
    initAttribute(head, fid, "nationkey", 1, 1);
    initAttribute(head, fid, "phone", 2, 64);
    initAttribute(head, fid, "acctbal", 2, 64);
    initAttribute(head, fid, "mktsegment", 2, 64);
    initAttribute(head, fid, "comment", 2, 128);
    return 0;
}

int showTable(struct dbSysHead *head, char* name)
{
    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        if (strcmp(name, head->redef[i].relationName) == 0)
        {
            printf("dic id: %d\n",i);
            printf("TableName: %s\n", head->redef[i].relationName);
            printf("Constructor: %s\n", head->redef[i].constructor);
            printf("AttributeNum: %d\n", head->redef[i].attributeNum);
            for (int j = 0; j < head->redef[i].attributeNum; j++)
            {
                printf("%d:%s\n", j+1, head->redef[i].attribute[j].attributeName);
            }
            printf("RecordLength: %d\n",head->redef[i].recordLength);
            return 0;
        }
    }
    return -1;
}



/*
 * @brief ≥ı ºªØπÿœµ
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid   : long  Œƒº˛±Í ∂
 * @param [in] relationName  : char* πÿœµ√˚
 * @param [in] constructorName :char* Ω®¡¢’ﬂ√˚
 * @return int
 *
 * @author mengxi
 * @date 2015/11/4
 **/
int initRelation(struct dbSysHead *head, long fid, const char *relationName, const char *constructorName)
{
    int n;
    n = queryFileID(head, fid);
    std::cout<<"datadict: "<<n<<std::endl;
    if ( n == -1)
    {
        printf("can't find file!\n");
        return -1;
    }
    head->redef[n].fileID = fid;
    strcpy(head->redef[n].relationName, relationName);
    strcpy(head->redef[n].constructor, constructorName);
    head->redef[n].attributeNum = 0;
    head->redef[n].recordLength = 0;
    changeRecordNum(head, fid, 0);
    return 0;
}

/*
 * @brief ∏¸∏ƒº«¬º◊‹ ˝
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid   : long  Œƒº˛±Í ∂
 * @param [in] num   : int  º«¬º◊‹ ˝
 * @return int
 *
 * @author mengxi
 * @date 2015/11/4
 **/
int changeRecordNum(struct dbSysHead *head, long fid, int num)
{
    int n;
    
    if ((n = queryFileID(head, fid)) == -1)
    {
        printf("can't find file!\n");
        return -1;
    }
    head->redef[n].recordNum = num;
    return 0;
}

/*
 * @brief ≥ı ºªØ“ª∏ˆ Ù–‘±Ì
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid   : long  Œƒº˛±Í ∂
 * @param [in] name  : char*  Ù–‘√˚
 * @param [in] type  : int   Ù–‘¿‡–Õ
 * @param [in] length: int   Ù–‘≥§∂»
 * @return int
 *
 * @author mengxi
 * @date 2015/11/4
 **/
 // change the diao yong de length
int initAttribute(struct dbSysHead *head, long fid, const char *name, int type, int length)
{
    
    int n = queryFileID(head, fid);
    int pos;
    
    if (n == -1)
    {
        printf("can't find file!\n");
        return -1;
    }
    if (head->redef[n].attributeNum == ATTRIBUTENUM)
    {
        printf("too many attributes!\n");
        return -1;
    }
    pos = head->redef[n].attributeNum;
    strcpy(head->redef[n].attribute[pos].attributeName, name);
    head->redef[n].attribute[pos].type = type;
    head->redef[n].attribute[pos].length = length;  // the length should be the number of byte
    if (pos == 0)
    {
        head->redef[n].attribute[pos].recordDeviation = 0;
        // can simplify
        switch (head->redef[n].attribute[pos].type)
        {
            case 1:head->redef[n].recordLength += sizeof(int);  break;
            case 2:head->redef[n].recordLength += length*sizeof(char); break;
            case 3:head->redef[n].recordLength += sizeof(date); break;
        }
    }
    else
    {
        switch (head->redef[n].attribute[pos].type)
        {
            case 1:head->redef[n].attribute[pos].recordDeviation = head->redef[n].recordLength;
                head->redef[n].recordLength += sizeof(int);  break;
            case 2:head->redef[n].attribute[pos].recordDeviation = head->redef[n].recordLength;
                head->redef[n].recordLength += length*sizeof(char); break;
            case 3:head->redef[n].attribute[pos].recordDeviation = head->redef[n].recordLength;
                head->redef[n].recordLength += sizeof(date); break;
        }
    }
    head->redef[n].attributeNum++;
    return 0;
    
}
/*
 * @brief …æ≥˝“ª∏ˆ Ù–‘±Ì
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid   : long  Œƒº˛±Í ∂
 * @param [in] name  : char*  Ù–‘√˚
 * @return int
 *
 * @author mengxi
 * @date 2015/11/4
 **/
/*
 int deleteAttribute(struct dbSysHead *head, long fid, char *name)
 {
	int n;
	int num;
 
	if (n = queryFileID(head, fid) == -1)
	{
 printf("can't find file!\n");
 return -1;
	}
	num = (head->desc).fileDesc[n].relationDef.attributeNum;
	for (int i = 0; i < num; i++)
	{
 if (strcmp(name, (head->desc).fileDesc[n].relationDef.attribute[i].attributeName) == 0)
 {
 switch ((head->desc).fileDesc[n].relationDef.attribute[i].type)
 {
 case 1:changeRecordLength(head, fid, (head->desc).fileDesc[n].relationDef.attribute[i].length - sizeof(int)); break;
 case 2:changeRecordLength(head, fid, (head->desc).fileDesc[n].relationDef.attribute[i].length - sizeof(char)); break;
 case 3:changeRecordLength(head, fid, (head->desc).fileDesc[n].relationDef.attribute[i].length - sizeof(date)); break;
 default:
 break;
 }
 (head->desc).fileDesc[n].relationDef.attributeNum--;
 for (int j = i; j < num-1; j++)
 {
 strcpy((head->desc).fileDesc[n].relationDef.attribute[j].attributeName, (head->desc).fileDesc[n].relationDef.attribute[j+1].attributeName);
 (head->desc).fileDesc[n].relationDef.attribute[j].length = (head->desc).fileDesc[n].relationDef.attribute[j+1].length;
 (head->desc).fileDesc[n].relationDef.attribute[j].type = (head->desc).fileDesc[n].relationDef.attribute[j+1].type;
 (head->desc).fileDesc[n].relationDef.attribute[j].recordDeviation = (head->desc).fileDesc[n].relationDef.attribute[j+1].recordDeviation;
 }
 break;
 }
	}
 }
 
 */

