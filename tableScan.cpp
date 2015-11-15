//
//  tableScan.cpp
//  exp2
//
//  Created by IreneWu on 15/11/14.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#include "tableScan.h"
#include "cursor.h"
#include "Buffer.h"
#include "file.h"
#include "dataDictionary.h"
#include <iostream>
void TableScan(struct dbSysHead * head,int fileID, struct relationDefine * temp_datadic){
    int fid = queryFileID(head, fileID);
    int dictID = fid;
    int original_rec_length = head->redef[dictID].recordLength; //record_length in original table
    int size_per_record = original_rec_length;   //each record length in new temp table, in case SPJ use
    //look up which buffer is empty
    int buffer_id_ ;
    int i;
    for (i = 0 ; i < 3; i++) {
        if (head->buff[i].emptyOrnot == true) {
            buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout<<"bufferID: "<<i<<std::endl;
            break;
        }
    }
    if (i == 3) {
        cout<<"No Buffer Can be Used!"<<endl;
    }
    else{
        cout<<"fileid: "<<fileID<<endl;
        RecordCursor scanTable(head, fileID, original_rec_length, 0); //0 for readin data buffer
        char * one_Row_ = (char *)malloc(sizeof(char) * size_per_record);
        Buffer t(head, -2); //to avoid positive number, no meaning
        int k = 0;
        while (true == scanTable.getNextRecord(one_Row_)) { //only scan
            k++;
            //if more than one page, write to file and reset Buffer t
            if(false == t.AppendBuffer(one_Row_, size_per_record))
            {
                t.writeBufferPage(t.filehead,buffer_id_ ,t.data_, t.current_size_);
                t.pageID++;
                if (t.pageID == SIZE_BUFF) {
                    std::cout<<"this buffer full"<<std::endl;
                    break;
                }
                memset(t.data_, 0, SIZE_PER_PAGE);
                memcpy(t.data_, one_Row_, size_per_record);
                t.pointer_ = t.data_+size_per_record;
                t.current_size_ = size_per_record;
            }

        }
        //write remainder
        t.writeBufferPage(t.filehead,buffer_id_ ,t.data_, t.current_size_);
        free(one_Row_);
        temp_datadic[dictID] = head->redef[0]; //wrong, need to wait class copy
        temp_datadic[dictID].fileID = -buffer_id_; //negative number for temp datadict, value is for which buffer
        temp_datadic[dictID].recordNum = k;
        temp_datadic[dictID].recordLength = size_per_record;
        strcpy(temp_datadic[dictID].relationName ,"temp datadict 1");
    }
}
