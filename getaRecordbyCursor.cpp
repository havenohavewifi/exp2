//
//  getaRecordbyCursor.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/6.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#include "getaRecordbyCursor.h"
#include "cursor.h"
#include "file.h"
#include "dataDictionary.h"
void getOneRecord(char *oneRec, relationDefine dic){
    int size_per_record = dic.recordLength;
    int offset;
    for(int i = 0; i < dic.attributeNum; i++){
        offset = dic.attribute[i].recordDeviation;
        if(dic.attribute[i].type == 1){
            int value= *((int *)(oneRec + offset));
            cout<<i<<":"<<value<<endl;
        }
        if(dic.attribute[i].type == 2){
            char * valuechar = (char *)malloc(sizeof(char)*dic.attribute[i].length);
            memcpy(valuechar, oneRec + offset ,dic.attribute[i].length);
            cout<<i<<":"<<valuechar<<endl;
        }
    }
}


