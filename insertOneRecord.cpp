//
//  insertOneRecord.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/8.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#include "insertOneRecord.h"
#include "file.h"
#include "dbHead.h"
#include "indexOpt.h"
#include "dataDictionary.h"
#include <iostream>

long insertOneRecord(struct dbSysHead *head , int fileID, char * oneRow){
    int fPhysicalID = queryFileID(head , fileID);
//did this make change??
    relation dic = head->redef[fPhysicalID];
    long pos = (head->desc.fileDesc[fPhysicalID].filePageNum - 1) * SIZE_PER_PAGE + head->desc.fileDesc[fPhysicalID].filePageEndPos;
    wtFile(head, 0, 1, pos, dic.getRecordLength(), oneRow);
    head->desc.fileDesc[fPhysicalID].filePageEndPos += dic.getRecordLength();
    dic.changeRecordNum(dic.getRecordNum()+1);
	
	if(true==insertInIndex(head, fileID, pos))
        std::cout<<"insert in index true"<<std::endl;
	return pos;
}