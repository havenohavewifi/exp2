//
//  cursorForTmptable.h
//  exp2
//
//  Created by IreneWu on 15/11/15.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#ifndef cursorForTmptable_h
#define cursorForTmptable_h

#include <stdio.h>
#include <iostream>
#include "dbHead.h"
class RecordCursorTmp
{
public:
    // construct function
    RecordCursorTmp(struct dbSysHead *head, long fid, long recordLength, int bufferID, int rowNum) {
        this->head = head;
        this->tmptableid = fid;
        this->recordLength = recordLength;
        this->bufferID = bufferID;
//        head->buff[bufferID].emptyOrnot = false;
        this->cBufferPage = -1;
        this->bufferOffset = 0;
        this->recordNum = rowNum;
        this->recordCurrent = 0;
        this->start = true;
        std::cout<<"Init cursorForTmptable:"<<std::endl;
    }
    
    bool getNextRecord(void *des);
    long getcLocation();
    long getBufferPageNum();
    long getBufferPage();
    int getBufferID();
    
private:
    struct dbSysHead *head;     //
    long tmptableid;                 // table ID
    long bufferPageNum;         // the total number of pages in the table
    int bufferID;            // the current buffer block
    long cBufferPage;         // the current page in the buffer
    long bufferOffset;        // the current offset in the page
    long recordLength;        // record length
    long recordNum;
    long recordCurrent;
    bool start;               // is the first record
    
};
#endif
