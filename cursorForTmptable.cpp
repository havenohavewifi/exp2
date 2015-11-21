//
//  cursorForTmptable.cpp
//  exp2
//
//  Created by IreneWu on 15/11/15.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//
extern "C" {
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

}
#include <string>
#include "cursorForTmptable.h"
bool RecordCursorTmp::getNextRecord(void *des) {
    // all the data is read
    if(this->recordCurrent >= this->recordNum) {
        return false;
    }
    // if the next record is out of the buffer page
    // then read the next page into buffer
    if(this->start==true || (this->bufferOffset+recordLength)>SIZE_PER_PAGE) {
        this->cBufferPage += 1;
        this->bufferOffset = 0;
        this->start = false;
    }
    // read the record into des
    memcpy(des, this->head->buff[this->bufferID].data[this->cBufferPage]+bufferOffset, sizeof(char)*recordLength);
    this->recordCurrent++;
    this->bufferOffset += recordLength;
    return true;
}

long RecordCursorTmp::getcLocation() {
    return this->cBufferPage*SIZE_PER_PAGE+this->bufferOffset;
}

long RecordCursorTmp::getBufferPageNum() {
    return this->bufferPageNum;
}

long RecordCursorTmp::getBufferPage() {
    return this->cBufferPage;
}

int RecordCursorTmp::getBufferID() {
    return this->bufferID;
}
