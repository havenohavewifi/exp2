//
//  recorder_char_general.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/7.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//
extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbHead.h"
};

#include <string>
#include <iostream>
#include "recorder_char_general.h"


void parserOneLineFromFile(char * row, char *rec, relationDefine dict_id){
    int rec_length = dict_id.recordLength;
    const char split[] = "|";
    char * current;
    int offset = 0;
    int tmp;
    current = strtok(row, split);
    if (1 == dict_id.attribute[0].type) {
        tmp = atoi(current);
        memcpy(rec , (char *)&tmp, dict_id.attribute[0].length*sizeof(int));
    }
    else memcpy(rec + offset, current, dict_id.attribute[0].length);
   
    for (int i = 1; i < dict_id.attributeNum; i++) {
        current = strtok(NULL, split);
        offset = dict_id.attribute[i].recordDeviation;
        if (1 == dict_id.attribute[i].type) {
            tmp = atoi(current);
            memcpy(rec + offset, (char *)&tmp, dict_id.attribute[i].length*sizeof(int));
        }
        else memcpy(rec + offset, current, dict_id.attribute[i].length);
    }
}