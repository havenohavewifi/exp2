//
//  project.cpp
//  
//
//  Created by mengxi on 15/11/14.
//  Copyright (c) 2015年 mengxi. All rights reserved.
//


#include <iostream>
#include <string.h>
#include "nestloop.h"
#include "cursor.h"
#include "cursorForTmptable.h"
#include "Buffer.h"
#include "file.h"
#include "dataDictionary.h"
#include "getaRecordbyCursor.h"

void merge_relation_quit(struct dbSysHead *head,relation datadic1,relation datadic2,relation *result, char* name){
	int a[20]={0};
	int length1=datadic1.getAttributeNum();
	int length2=datadic2.getAttributeNum();
	int signal=0;
	for(int j=0;j<length1;j++){
		signal=0;
		for(int k=0;k<length2;k++){
			if(strcmp(datadic1.getAttributeByNo(j).getName(),datadic2.getAttributeByNo(k).getName())==0){
				
			
				if(strcmp(datadic1.getAttributeByNo(j).getName(),name)!=0){
					a[k]=1;
					signal=1;
					break;
				}else{
					signal=2;
					break;
				}
			}
		}
		if(signal==2){
			(*result).insertAttribute(strcat(datadic1.getAttributeByNo(j).getName(),"_key"),
			datadic1.getAttributeByNo(j).getType(),
			datadic1.getAttributeByNo(j).getLength());
			continue;
		}
		if(signal==0){

			(*result).insertAttribute(datadic1.getAttributeByNo(j).getName(),
			datadic1.getAttributeByNo(j).getType(),
			datadic1.getAttributeByNo(j).getLength());
		}else{
			
			(*result).insertAttribute(strcat(datadic1.getAttributeByNo(j).getName(),"_1"),
			datadic1.getAttributeByNo(j).getType(),
			datadic1.getAttributeByNo(j).getLength());
		}
		
		
	}
	
	for(int j=0;j<length2;j++){
		if(strcmp(datadic2.getAttributeByNo(j).getName(),name)==0){
			continue;
		}
		if(a[j]==0){

			(*result).insertAttribute(datadic2.getAttributeByNo(j).getName(),
			datadic2.getAttributeByNo(j).getType(),
			datadic2.getAttributeByNo(j).getLength());
		}else{
			(*result).insertAttribute(strcat(datadic2.getAttributeByNo(j).getName(),"_2"),
			datadic2.getAttributeByNo(j).getType(),
			datadic2.getAttributeByNo(j).getLength());
		}
	}
	
}

void nestloop_equal(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name){
	int original_rec_length1 = temp_datadic1->getRecordLength(); //record_length in original table*
	int original_rec_length2 = temp_datadic2->getRecordLength();
	int original_attribute_length1=temp_datadic1->getAttributeNum();
	int original_attribute_length2=temp_datadic2->getAttributeNum();
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
		RecordCursorTmp scanTable1(head, temp_datadic1->fileID, original_rec_length1, -temp_datadic1->fileID, temp_datadic1->getRecordNum());
		
		cout << 1 << endl;
		char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
		char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
		char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
		Buffer t(head, -2); //to avoid positive number, no meaning
		int k = 0;
		while (true == scanTable1.getNextRecord(one_Row_1)) { //only scan
			
			RecordCursorTmp scanTable2(head, temp_datadic2->fileID, original_rec_length2, -temp_datadic2->fileID, temp_datadic2->getRecordNum());
		
			while(true == scanTable2.getNextRecord(one_Row_2)){
				int start1=0;
				int start2=0;
				int length=0;
				for(int i=0;i<original_attribute_length1;i++){
					if(strcmp(temp_datadic1->getAttributeByNo(i).getName(),name)==0){
						start1=temp_datadic1->getAttributeByNo(i).getRecordDeviation();
						length=temp_datadic1->getAttributeByNo(i).getLength();
						break;
					}
				}
				for(int i=0;i<original_attribute_length2;i++){
					if(strcmp(temp_datadic2->getAttributeByNo(i).getName(),name)==0){
						start2=temp_datadic2->getAttributeByNo(i).getRecordDeviation();
						break;
					}
				}
				int ssignal=0;
				for(int i=0,loc1=start1,loc2=start2;i<length;i++,loc1++,loc2++){
					if(one_Row_1[loc1]!=one_Row_2[loc2]){
						ssignal=1;
						break;
					}
				}
				if(ssignal==1){
					continue;
				}
				for(int i=0;i<original_rec_length1;i++)
					new_Row_[i]=one_Row_1[i];
				for(int i=0;i<original_rec_length2;i++)
					new_Row_[i+original_rec_length1]=one_Row_2[i];
					//cout<<endl;
				/*int order=0;
				for(int s=0;s<original_attribute_length2;s++){
					if(strcmp(temp_datadic2->getAttributeByNo(s).getName(),name)==0){
						order=s;
						break;
					}
				}
				int start=temp_datadic2->getAttributeByNo(order).getRecordDeviation();
				int stop=temp_datadic2->getAttributeByNo(order).getRecordDeviation()+temp_datadic2->getAttributeByNo(order).getLength();
				
				for(int i=0;i<start;i++){
					new_Row_[i+original_rec_length1]=one_Row_2[i];
				}
				int loc_new_row;
				for(int loc_new_row=original_rec_length1+start,i=stop;i<original_rec_length2;i++,loc_new_row++){
					new_Row_[loc_new_row]=one_Row_2[i];
				}
*/

				getOneRecord(new_Row_, result);
				
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

			

		}
		//write remainder
		t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
		result->fileID = -buffer_id_;
		free(one_Row_1);
		free(one_Row_2);
		free(new_Row_);
	
	}
}


void nestloop_bigger(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name){
	int original_rec_length1 = temp_datadic1->getRecordLength(); //record_length in original table*
	int original_rec_length2 = temp_datadic2->getRecordLength();
	int original_attribute_length1=temp_datadic1->getAttributeNum();
	int original_attribute_length2=temp_datadic2->getAttributeNum();
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
		RecordCursorTmp scanTable1(head, temp_datadic1->fileID, original_rec_length1, -temp_datadic1->fileID, temp_datadic1->getRecordNum());
		
		cout << 1 << endl;
		char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
		char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
		char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
		Buffer t(head, -2); //to avoid positive number, no meaning
		int k = 0;
		while (true == scanTable1.getNextRecord(one_Row_1)) { //only scan
			
			RecordCursorTmp scanTable2(head, temp_datadic2->fileID, original_rec_length2, -temp_datadic2->fileID, temp_datadic2->getRecordNum());
		
			while(true == scanTable2.getNextRecord(one_Row_2)){
				int start1=0;
				int start2=0;
				int length=0;
				for(int i=0;i<original_attribute_length1;i++){
					if(strcmp(temp_datadic1->getAttributeByNo(i).getName(),name)==0){
						start1=temp_datadic1->getAttributeByNo(i).getRecordDeviation();
						length=temp_datadic1->getAttributeByNo(i).getLength();
						break;
					}
				}
				for(int i=0;i<original_attribute_length2;i++){
					if(strcmp(temp_datadic2->getAttributeByNo(i).getName(),name)==0){
						start2=temp_datadic2->getAttributeByNo(i).getRecordDeviation();
						break;
					}
				}
				int ssignal=0;
				for(int i=0,loc1=start1,loc2=start2;i<length;i++,loc1++,loc2++){
					if(one_Row_1[loc1]<one_Row_2[loc2]){
						ssignal=1;
						break;
					}else{
						if(one_Row_1[loc1]>one_Row_2[loc2]){
							ssignal=-1;
							break;
						}else{
							continue;
						}
						
					}
				}
				if(ssignal!=-1){
					continue;
				}
				for(int i=0;i<original_rec_length1;i++)
					new_Row_[i]=one_Row_1[i];
				for(int i=0;i<original_rec_length2;i++)
					new_Row_[i+original_rec_length1]=one_Row_2[i];
					//cout<<endl;
				/*int order=0;
				for(int s=0;s<original_attribute_length2;s++){
					if(strcmp(temp_datadic2->getAttributeByNo(s).getName(),name)==0){
						order=s;
						break;
					}
				}
				int start=temp_datadic2->getAttributeByNo(order).getRecordDeviation();
				int stop=temp_datadic2->getAttributeByNo(order).getRecordDeviation()+temp_datadic2->getAttributeByNo(order).getLength();
				
				for(int i=0;i<start;i++){
					new_Row_[i+original_rec_length1]=one_Row_2[i];
				}
				int loc_new_row;
				for(int loc_new_row=original_rec_length1+start,i=stop;i<original_rec_length2;i++,loc_new_row++){
					new_Row_[loc_new_row]=one_Row_2[i];
				}
*/

				getOneRecord(new_Row_, result);
				
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

			

		}
		//write remainder
		t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
		result->fileID = -buffer_id_;
		free(one_Row_1);
		free(one_Row_2);
		free(new_Row_);
	
	}
}

void nestloop_smaller(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name){
	int original_rec_length1 = temp_datadic1->getRecordLength(); //record_length in original table*
	int original_rec_length2 = temp_datadic2->getRecordLength();
	int original_attribute_length1=temp_datadic1->getAttributeNum();
	int original_attribute_length2=temp_datadic2->getAttributeNum();
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
		RecordCursorTmp scanTable1(head, temp_datadic1->fileID, original_rec_length1, -temp_datadic1->fileID, temp_datadic1->getRecordNum());
		
		cout << 1 << endl;
		char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
		char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
		char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
		Buffer t(head, -2); //to avoid positive number, no meaning
		int k = 0;
		while (true == scanTable1.getNextRecord(one_Row_1)) { //only scan
			
			RecordCursorTmp scanTable2(head, temp_datadic2->fileID, original_rec_length2, -temp_datadic2->fileID, temp_datadic2->getRecordNum());
		
			while(true == scanTable2.getNextRecord(one_Row_2)){
				int start1=0;
				int start2=0;
				int length=0;
				for(int i=0;i<original_attribute_length1;i++){
					if(strcmp(temp_datadic1->getAttributeByNo(i).getName(),name)==0){
						start1=temp_datadic1->getAttributeByNo(i).getRecordDeviation();
						length=temp_datadic1->getAttributeByNo(i).getLength();
						break;
					}
				}
				for(int i=0;i<original_attribute_length2;i++){
					if(strcmp(temp_datadic2->getAttributeByNo(i).getName(),name)==0){
						start2=temp_datadic2->getAttributeByNo(i).getRecordDeviation();
						break;
					}
				}
				int ssignal=0;
				for(int i=0,loc1=start1,loc2=start2;i<length;i++,loc1++,loc2++){
					if(one_Row_1[loc1]>one_Row_2[loc2]){
						ssignal=1;
						break;
					}else{
						if(one_Row_1[loc1]<one_Row_2[loc2]){
							ssignal=-1;
							break;
						}else{
							continue;
						}
						
					}
				}
				if(ssignal!=-1){
					continue;
				}
				for(int i=0;i<original_rec_length1;i++)
					new_Row_[i]=one_Row_1[i];
				for(int i=0;i<original_rec_length2;i++)
					new_Row_[i+original_rec_length1]=one_Row_2[i];
					//cout<<endl;
				/*int order=0;
				for(int s=0;s<original_attribute_length2;s++){
					if(strcmp(temp_datadic2->getAttributeByNo(s).getName(),name)==0){
						order=s;
						break;
					}
				}
				int start=temp_datadic2->getAttributeByNo(order).getRecordDeviation();
				int stop=temp_datadic2->getAttributeByNo(order).getRecordDeviation()+temp_datadic2->getAttributeByNo(order).getLength();
				
				for(int i=0;i<start;i++){
					new_Row_[i+original_rec_length1]=one_Row_2[i];
				}
				int loc_new_row;
				for(int loc_new_row=original_rec_length1+start,i=stop;i<original_rec_length2;i++,loc_new_row++){
					new_Row_[loc_new_row]=one_Row_2[i];
				}
*/

				getOneRecord(new_Row_, result);
				
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

			

		}
		//write remainder
		t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
		result->fileID = -buffer_id_;
		free(one_Row_1);
		free(one_Row_2);
		free(new_Row_);
	
	}
}
void nestloop_bigger_or_equal(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name){
	int original_rec_length1 = temp_datadic1->getRecordLength(); //record_length in original table*
	int original_rec_length2 = temp_datadic2->getRecordLength();
	int original_attribute_length1=temp_datadic1->getAttributeNum();
	int original_attribute_length2=temp_datadic2->getAttributeNum();
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
		RecordCursorTmp scanTable1(head, temp_datadic1->fileID, original_rec_length1, -temp_datadic1->fileID, temp_datadic1->getRecordNum());
		
		cout << 1 << endl;
		char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
		char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
		char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
		Buffer t(head, -2); //to avoid positive number, no meaning
		int k = 0;
		while (true == scanTable1.getNextRecord(one_Row_1)) { //only scan
			
			RecordCursorTmp scanTable2(head, temp_datadic2->fileID, original_rec_length2, -temp_datadic2->fileID, temp_datadic2->getRecordNum());
		
			while(true == scanTable2.getNextRecord(one_Row_2)){
				int start1=0;
				int start2=0;
				int length=0;
				for(int i=0;i<original_attribute_length1;i++){
					if(strcmp(temp_datadic1->getAttributeByNo(i).getName(),name)==0){
						start1=temp_datadic1->getAttributeByNo(i).getRecordDeviation();
						length=temp_datadic1->getAttributeByNo(i).getLength();
						break;
					}
				}
				for(int i=0;i<original_attribute_length2;i++){
					if(strcmp(temp_datadic2->getAttributeByNo(i).getName(),name)==0){
						start2=temp_datadic2->getAttributeByNo(i).getRecordDeviation();
						break;
					}
				}
				int ssignal=0;
				for(int i=0,loc1=start1,loc2=start2;i<length;i++,loc1++,loc2++){
					if(one_Row_1[loc1]<one_Row_2[loc2]){
						ssignal=1;
						break;
					}else{
						if(one_Row_1[loc1]>one_Row_2[loc2]){
							ssignal=-1;
							break;
						}else{
							continue;
						}
						
					}
				}
				if(ssignal==1){
					continue;
				}
				for(int i=0;i<original_rec_length1;i++)
					new_Row_[i]=one_Row_1[i];
				for(int i=0;i<original_rec_length2;i++)
					new_Row_[i+original_rec_length1]=one_Row_2[i];
					//cout<<endl;
				/*int order=0;
				for(int s=0;s<original_attribute_length2;s++){
					if(strcmp(temp_datadic2->getAttributeByNo(s).getName(),name)==0){
						order=s;
						break;
					}
				}
				int start=temp_datadic2->getAttributeByNo(order).getRecordDeviation();
				int stop=temp_datadic2->getAttributeByNo(order).getRecordDeviation()+temp_datadic2->getAttributeByNo(order).getLength();
				
				for(int i=0;i<start;i++){
					new_Row_[i+original_rec_length1]=one_Row_2[i];
				}
				int loc_new_row;
				for(int loc_new_row=original_rec_length1+start,i=stop;i<original_rec_length2;i++,loc_new_row++){
					new_Row_[loc_new_row]=one_Row_2[i];
				}
*/

				getOneRecord(new_Row_, result);
				
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

			

		}
		//write remainder
		t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
		result->fileID = -buffer_id_;
		free(one_Row_1);
		free(one_Row_2);
		free(new_Row_);
	
	}
}

void nestloop_smaller_or_equal(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name){
	int original_rec_length1 = temp_datadic1->getRecordLength(); //record_length in original table*
	int original_rec_length2 = temp_datadic2->getRecordLength();
	int original_attribute_length1=temp_datadic1->getAttributeNum();
	int original_attribute_length2=temp_datadic2->getAttributeNum();
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
		RecordCursorTmp scanTable1(head, temp_datadic1->fileID, original_rec_length1, -temp_datadic1->fileID, temp_datadic1->getRecordNum());
		
		cout << 1 << endl;
		char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
		char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
		char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
		Buffer t(head, -2); //to avoid positive number, no meaning
		int k = 0;
		while (true == scanTable1.getNextRecord(one_Row_1)) { //only scan
			
			RecordCursorTmp scanTable2(head, temp_datadic2->fileID, original_rec_length2, -temp_datadic2->fileID, temp_datadic2->getRecordNum());
		
			while(true == scanTable2.getNextRecord(one_Row_2)){
				int start1=0;
				int start2=0;
				int length=0;
				for(int i=0;i<original_attribute_length1;i++){
					if(strcmp(temp_datadic1->getAttributeByNo(i).getName(),name)==0){
						start1=temp_datadic1->getAttributeByNo(i).getRecordDeviation();
						length=temp_datadic1->getAttributeByNo(i).getLength();
						break;
					}
				}
				for(int i=0;i<original_attribute_length2;i++){
					if(strcmp(temp_datadic2->getAttributeByNo(i).getName(),name)==0){
						start2=temp_datadic2->getAttributeByNo(i).getRecordDeviation();
						break;
					}
				}
				int ssignal=0;
				for(int i=0,loc1=start1,loc2=start2;i<length;i++,loc1++,loc2++){
					if(one_Row_1[loc1]>one_Row_2[loc2]){
						ssignal=1;
						break;
					}else{
						if(one_Row_1[loc1]<one_Row_2[loc2]){
							ssignal=-1;
							break;
						}else{
							continue;
						}
						
					}
				}
				if(ssignal==1){
					continue;
				}
				for(int i=0;i<original_rec_length1;i++)
					new_Row_[i]=one_Row_1[i];
				for(int i=0;i<original_rec_length2;i++)
					new_Row_[i+original_rec_length1]=one_Row_2[i];
					//cout<<endl;
				/*int order=0;
				for(int s=0;s<original_attribute_length2;s++){
					if(strcmp(temp_datadic2->getAttributeByNo(s).getName(),name)==0){
						order=s;
						break;
					}
				}
				int start=temp_datadic2->getAttributeByNo(order).getRecordDeviation();
				int stop=temp_datadic2->getAttributeByNo(order).getRecordDeviation()+temp_datadic2->getAttributeByNo(order).getLength();
				
				for(int i=0;i<start;i++){
					new_Row_[i+original_rec_length1]=one_Row_2[i];
				}
				int loc_new_row;
				for(int loc_new_row=original_rec_length1+start,i=stop;i<original_rec_length2;i++,loc_new_row++){
					new_Row_[loc_new_row]=one_Row_2[i];
				}
*/

				getOneRecord(new_Row_, result);
				
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

			

		}
		//write remainder
		t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
		result->fileID = -buffer_id_;
		free(one_Row_1);
		free(one_Row_2);
		free(new_Row_);
	
	}
}

void merge_relation(struct dbSysHead *head,relation datadic1,relation datadic2,relation *result){
	int a[20]={0};
	int length1=datadic1.getAttributeNum();
	int length2=datadic2.getAttributeNum();
	int signal=0;
	for(int j=0;j<length1;j++){
		signal=0;
		for(int k=0;k<length2;k++){
			if(strcmp(datadic1.getAttributeByNo(j).getName(),datadic2.getAttributeByNo(k).getName())==0){
				a[k]=1;
				signal=1;
				break;
			}
		}
		if(signal==0){
			(*result).insertAttribute(datadic1.getAttributeByNo(j).getName(),
			datadic1.getAttributeByNo(j).getType(),
			datadic1.getAttributeByNo(j).getLength());
		}else{
			(*result).insertAttribute(strcat(datadic1.getAttributeByNo(j).getName(),"_1"),
			datadic1.getAttributeByNo(j).getType(),
			datadic1.getAttributeByNo(j).getLength());
		}
		
		
	}
	
	for(int j=0;j<length2;j++){
		if(a[j]==0){
		(*result).insertAttribute(datadic2.getAttributeByNo(j).getName(),
			datadic2.getAttributeByNo(j).getType(),
			datadic2.getAttributeByNo(j).getLength());
		}else{
			(*result).insertAttribute(strcat(datadic2.getAttributeByNo(j).getName(),"_2"),
			datadic2.getAttributeByNo(j).getType(),
			datadic2.getAttributeByNo(j).getLength());
		}
	}
	
}

void nestloop_cp(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result){
	int original_rec_length1 = temp_datadic1->getRecordLength(); //record_length in original table*
	int original_rec_length2 = temp_datadic2->getRecordLength();
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
		RecordCursorTmp scanTable1(head, temp_datadic1->fileID, original_rec_length1, -temp_datadic1->fileID, temp_datadic1->getRecordNum());
		
		cout << 1 << endl;
		char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
		char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
		char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
		Buffer t(head, -2); //to avoid positive number, no meaning
		int k = 0;
		while (true == scanTable1.getNextRecord(one_Row_1)) { //only scan
			
			RecordCursorTmp scanTable2(head, temp_datadic2->fileID, original_rec_length2, -temp_datadic2->fileID, temp_datadic2->getRecordNum());
		
			while(true == scanTable2.getNextRecord(one_Row_2)){
				for(int i=0;i<original_rec_length1;i++)
					new_Row_[i]=one_Row_1[i];
					//cout<<endl;
				for(int i=0;i<original_rec_length2;i++)
					new_Row_[i+original_rec_length1]=one_Row_2[i];

				getOneRecord(new_Row_, result);
				
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

			

		}
		//write remainder
		t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
		result->fileID = -buffer_id_;
		free(one_Row_1);
		free(one_Row_2);
		free(new_Row_);
	
	}
}

