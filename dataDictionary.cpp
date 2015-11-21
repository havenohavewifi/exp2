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

attribute::attribute()
{
    
}

attribute::attribute(attribute& AA)
{
    strcpy(this->attributeName,AA.attributeName);
    this->length = AA.length;
    this->type = AA.type;
    this->recordDeviation = AA.recordDeviation;
}
attribute::~attribute()
{
    
}

relation::relation()
{
    
}

relation::relation(relation& RR)
{
    this->fileID = RR.fileID;
    strcpy(this->relationName, RR.relationName);
    strcpy(this->constructor, RR.constructor);
    this->attributeNum = RR.attributeNum;
    this->recordLength = RR.recordLength;
    this->recordNum = RR.recordNum;
    for (int i = 0; i < this->recordNum; i++) {
        this->atb[i] = RR.atb[i];
    }
}
relation::~relation()
{
    
}

int attribute::initAttribute(char *name, int type, int length, int deviation)
{
    strcpy(this->attributeName, name);
    this->type = type;
    this->length = length;
    this->recordDeviation = deviation;
    return 0;
}

char * attribute::getName()
{
    return this->attributeName;
}

int attribute::getLength()
{
    return this->length;
}

int attribute::getType()
{
    return this->type;
}

int attribute::getRecordDeviation()
{
    return this->recordDeviation;
}

int relation::initRelation(struct dbSysHead *head, int fid, char *relationName, char *constructorName)
{
    int n = queryFileID(head, fid);
    if (n == -1)
    {
        printf("can't find file!\n");
        return -1;
    }
    this->fileID = fid;
    strcpy(this->relationName, relationName);
    strcpy(this->constructor, constructorName);
    this->attributeNum = 0;
    this->recordLength = 0;
    this->recordNum = 0;
    return 0;
}

int relation::changeRecordNum(int num)
{
    this->recordNum = num;
    return 0;
}

int relation::insertAttribute(char *name, int type, int length)
{
    if (this->attributeNum >= ATTRIBUTENUM)
    {
        printf("too many attributes!\n");
        return -1;
    }
    if (this->attributeNum == 0)
    {
        this->atb[this->attributeNum].initAttribute(name, type, length, 0);
    }
    else
    {
        int deviation = this->atb[this->attributeNum - 1].getLength() + this->atb[this->attributeNum - 1].getRecordDeviation();
        this->atb[this->attributeNum].initAttribute(name, type, length, deviation);
    }
    this->attributeNum++;
    this->recordLength += length;
    return 0;
}

attribute relation::getAttributeByName(char *name)
{
    for (int i = 0; i < this->attributeNum; i++)
    {
        if (strcmp(this->atb[i].getName(), name) == 0)
        {
            return this->atb[i];
        }
    }
    /*	printf("can't find!\n");
     return;*/
}

attribute relation::getAttributeByNo(int no)
{
    /*	if (no > this->attributeNum - 1)
     {
     printf("wrong no!\n");
     return ;
     }*/
    return this->atb[no];
}

int relation::getAttributeNum()
{
    return this->attributeNum;
}

char* relation::getConstructor()
{
    return this->constructor;
}

int relation::getRecordLength()
{
    return this->recordLength;
}

int relation::getRecordNum()
{
    return this->recordNum;
}

char *relation::getRelationName()
{
    return this->relationName;
}

int initTable(struct dbSysHead *head, long fid)
{
    int n = queryFileID(head, fid);
    if (n == -1)
    {
        printf("can't find file!\n");
        return -1;
    }
    if (fid == 1) {
    
    head->redef[n].initRelation(head, fid, "customer", "TianzhenWu");
    head->redef[n].insertAttribute("custkey", 1, 4);
    head->redef[n].insertAttribute("name", 2, 64);
    head->redef[n].insertAttribute("address", 2, 64);
    head->redef[n].insertAttribute("nationkey", 1, 4);
    head->redef[n].insertAttribute("phone", 2, 64);
    head->redef[n].insertAttribute("acctbal", 2, 64);
    head->redef[n].insertAttribute("mktsegment", 2, 64);
    head->redef[n].insertAttribute("comment", 2, 128);
    }
    
    if (fid == 2) {
        head->redef[n].initRelation(head, fid, "nation", "IreneWu");
        head->redef[n].insertAttribute("nationkey", 1, 4);
        head->redef[n].insertAttribute("name", 2, 16);
        head->redef[n].insertAttribute("regionkey", 1, 4);
        head->redef[n].insertAttribute("comment", 2, 104);
    }
    return 0;
}

int showTable(struct dbSysHead *head, char* name)
{
    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        if (strcmp(name, head->redef[i].getRelationName()) == 0)
        {
            printf("dic id: %d\n", i);
            printf("TableName: %s\n", head->redef[i].getRelationName());
            printf("Constructor: %s\n", head->redef[i].getConstructor());
            printf("AttributeNum: %d\n", head->redef[i].getAttributeNum());
            for (int j = 0; j < head->redef[i].getAttributeNum(); j++)
            {
                printf("%d:%s\n", j + 1, head->redef[i].getAttributeByNo(j).getName());
            }
            printf("RecordLength: %d\n", head->redef[i].getRecordLength());
            return 0;
        }
    }
    return -1;
}

