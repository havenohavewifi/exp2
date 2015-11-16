//
//  recorder_char_general.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/7.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//
extern "C" {
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include "dbHead.h"
};

#include <string>
#include <iostream>
#include "recorder_char_general.h"


void parserOneLineFromFile(char * row, char *rec, relation dict_id){
    int rec_length = dict_id.getRecordLength();
    const char split[] = "|";
    char * current;
    int offset = 0;
    int tmp;
    current = strtok(row, split);
    if (1 == dict_id.getAttributeByNo(0).getType()) {
        tmp = atoi(current);
        memcpy(rec, (char *)&tmp, dict_id.getAttributeByNo(0).getLength()*sizeof(int));
    }
    else memcpy(rec + offset, current, dict_id.getAttributeByNo(0).getLength());
    
    for (int i = 1; i < dict_id.getAttributeNum(); i++) {
        current = strtok(NULL, split);
        offset = dict_id.getAttributeByNo(i).getRecordDeviation();
        if (1 == dict_id.getAttributeByNo(i).getType()) {
            tmp = atoi(current);
            memcpy(rec + offset, (char *)&tmp, dict_id.getAttributeByNo(i).getLength()*sizeof(int));
        }
        else memcpy(rec + offset, current, dict_id.getAttributeByNo(i).getLength());
    }
}