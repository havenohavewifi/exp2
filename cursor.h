//
//  cursor.h
//  loaddata
//
//  Created by IreneWu on 15/11/6.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#ifndef cursor_h
#define cursor_h

#include <stdio.h>
/*
extern "C" {
    // #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbHead.h"
};
extern "C" {
    extern int reqPage(struct  dbSysHead *head, long query);
    extern long mapPage(struct dbSysHead *head, long fid, long num);
}
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "dbHead.h"
using namespace std;

class RecordCursor
{
public:
    // construct function
    RecordCursor(struct dbSysHead *head, long fid, long recordLength, int bufferID) {
        int idx = queryFileID(head, fid);
        if(idx < 0) {
            cout << fid << "file doesn't exist!" << endl;
            exit(0);
        }
        this->head = head;
        this->fid = fid;
        this->recordLength = recordLength;
        this->cLogicPage = -1;
        this->cPhysicalPage = -1;
        this->bufferID = bufferID;
        this->cBufferPage = 0;
        this->bufferOffset = 0;
        this->start = true;
        this->filePageNum = head->desc.fileDesc[idx].filePageNum;
        cout<<idx<<":"<<this->filePageNum<<endl;
    }

    bool getNextRecord(void *des);
    long getcLogicLocation();
    long getcLogicPage();
    long getcBufferOffset();
    int getBufferID();
    
private:
    struct dbSysHead *head;     //
    long fid;                 // table ID
    long cLogicPage;          // current logical page ID in the table
    long cPhysicalPage;
    long filePageNum;         // the total number of pages in the table
    int bufferID;            // the current buffer block
    long cBufferPage;         // the current page in the buffer
    long bufferOffset;        // the current offset in the page
    long recordLength;        // record length
    bool start;               // is the first record

};




// int getNextPage(struct dbSysHead *head, long fid, long num) {

// 	int pageIdInDisk = mapPage(head, fid, num+1);

// 	return reqPage(head, pageIdInDisk);
// }

// int getNextRecord(struct dbSysHead *head, long mapNo, long offset, long recordLen) {

// 	return head->buff.data[mapNo][offset:offset+recordLen]
// }
#endif /* defined(__loaddata__cursor__) */
