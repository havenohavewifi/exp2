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
void getOneRecord(char *oneRec, relation dic){
    int size_per_record = dic.getRecordLength();
    int offset;
    for(int i = 0; i < dic.getAttributeNum(); i++){
        offset = dic.getAttributeByNo(i).getRecordDeviation();
        if(dic.getAttributeByNo(i).getType() == 1){
            int value= *((int *)(oneRec + offset));
            cout<<i<<":"<<value<<endl;
        }
        if(dic.getAttributeByNo(i).getType() == 2){
            char * valuechar = (char *)malloc(sizeof(char)*dic.getAttributeByNo(i).getLength());
            memcpy(valuechar, oneRec + offset ,dic.getAttributeByNo(i).getLength());
            cout<<i<<":"<<valuechar<<endl;
        }
    }
}


