//
//  recorder_char_general.h
//  loaddata
//
//  Created by IreneWu on 15/11/7.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#ifndef recorder_char_general_h
#define recorder_char_general_h


#include <stdio.h>
#include "dataDictionary.h"
//根据数据字典，把源数据文件的内容转换为相应格式的一行记录
void parserOneLineFromFile(char * row, char *rec, relation * dict_id);
#endif 
