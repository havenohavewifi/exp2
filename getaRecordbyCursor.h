//
//  getaRecordbyCursor.h
//  loaddata
//
//  Created by IreneWu on 15/11/6.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#ifndef getaRecordbyCursor_h
#define getaRecordbyCursor_h

#include <stdio.h>
#include "file.h"
#include "dataDictionary.h"
//according to datadictionary, analyze each attribute value, need to be rewritten to get a certain attriute value and modify the return type
void getOneRecord(char *oneRec, relationDefine dic);
#endif /* defined(__loaddata__getaRecordbyCursor__) */
