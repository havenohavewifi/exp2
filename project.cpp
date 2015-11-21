//
//  project.cpp
//  
//
//  Created by mengxi on 15/11/14.
//  Copyright (c) 2015Äê mengxi. All rights reserved.
//

#include "project.h"
#include "cursor.h"
#include "cursorForTmptable.h"
#include "Buffer.h"
#include "file.h"
#include "dataDictionary.h"
#include <iostream>

void project(struct dbSysHead *head, relation *temp_datadic, relation *result){
	int original_rec_length = temp_datadic->getRecordLength(); //record_length in original table
	int new_rec_length = result->getRecordLength();   //each record length in new temp table, in case SPJ use
	//look up which buffer is empty
	int buffer_id_;
	int i;
	for (i = 0; i < 3; i++) {
		if (head->buff[i].emptyOrnot == true) {
			buffer_id_ = i;
			head->buff[i].emptyOrnot = false;   // ready for writein
			std::cout << "bufferID: " << i << std::endl;
			break;
		}
	}
	if (i == 3) {
		cout << "No Buffer Can be Used!" << endl;
	}
	else{
		//RecordCursor scanTable(head, temp_datadic->fileID, original_rec_length, -temp_datadic->fileID);
		RecordCursorTmp scanTable(head, temp_datadic->fileID, original_rec_length, -temp_datadic->fileID, temp_datadic->getRecordNum());
		cout << 1 << endl;
		char * one_Row_ = (char *)malloc(sizeof(char) * original_rec_length);
		char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
		Buffer t(head, -2); //to avoid positive number, no meaning
		int k = 0;
		while (true == scanTable.getNextRecord(one_Row_)) { //only scan
			k++;
			for (int ptr1 = 0, ptr2 = 0; ptr1 < temp_datadic->getAttributeNum() && ptr2 < result->getAttributeNum();){
				int offset1 = temp_datadic->getAttributeByNo(ptr1).getRecordDeviation();
				int offset2 = result->getAttributeByNo(ptr2).getRecordDeviation();
				if (strcmp(temp_datadic->getAttributeByNo(ptr1).getName(), result->getAttributeByNo(ptr2).getName()) == 0)
				{
					strncpy(new_Row_ + offset2, one_Row_ + offset1, result->getAttributeByNo(ptr2).getLength());
					if (result->getAttributeByNo(ptr2).getType() == 1){
						int value = *((int *)(new_Row_ + offset2));
						cout << ptr2 << ":" << value << endl;
					}
					if (result->getAttributeByNo(ptr2).getType() == 2){
						char * valuechar = (char *)malloc(sizeof(char)*result->getAttributeByNo(ptr2).getLength());
						memcpy(valuechar, new_Row_ + offset2, result->getAttributeByNo(ptr2).getLength());
						cout << ptr2 << ":" << valuechar << endl;
						free(valuechar);
					}
					ptr1++;
					ptr2++;
				}
				else
				{
					ptr1++;
				}
			}
			//if more than one page, write to file and reset Buffer t
			if (false == t.AppendBuffer(new_Row_, new_rec_length))
			{
				t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
				t.pageID++;
				if (t.pageID == SIZE_BUFF) {
					std::cout << "this buffer full" << std::endl;
					break;
				}
				memset(t.data_, 0, SIZE_PER_PAGE);
				memcpy(t.data_, new_Row_, new_rec_length);
				t.pointer_ = t.data_ + new_rec_length;
				t.current_size_ = new_rec_length;
			}

		}
		//write remainder
		t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
		result->fileID = -buffer_id_;
		free(one_Row_);
		free(new_Row_);
		//        temp_datadic[dictID].recordLength = size_per_record;
		//        strcpy(temp_datadic[dictID].relationName ,"temp datadict 1");
	}
}
