//
//  dataDictionary.cpp
//  exp2
//
//  Created by mengxi on 15/11/15.
//  Copyright (c) 2015年 mengxi. All rights reserved.
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

attribute::~attribute()
{

}

relation::relation()
{

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
<<<<<<< HEAD
	this->recordNum = num;
	return 0;
}

int relation::insertAttribute(char *name, int type, int length)
{
	if (this->attributeNum >= ATTRIBUTENUM)
=======
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
>>>>>>> 6935d6d5c26c9486420359d5298b7d1ad5e8c238
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
	head->redef[n].initRelation(head, fid, "customer", "TianzhenWu");
	head->redef[n].insertAttribute("custkey", 1, 4);
	head->redef[n].insertAttribute("name", 2, 64);
	head->redef[n].insertAttribute("address", 2, 64);
	head->redef[n].insertAttribute("nationkey", 1, 4);
	head->redef[n].insertAttribute("phone", 2, 64);
	head->redef[n].insertAttribute("acctbal", 2, 64);
	head->redef[n].insertAttribute("mktsegment", 2, 64);
	head->redef[n].insertAttribute("comment", 2, 128);
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


