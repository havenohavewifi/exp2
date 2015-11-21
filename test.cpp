
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "dbHead.h"
#include "loaddata.h"
#include "cursor.h"
#include "getaRecordbyCursor.h"
#include "b_plus_tree.h"
#include "insertOneRecord.h"
#include "recorder_char_general.h"
#include "indexOpt.h"
#include "dataDictionary.h"
#include "file.h"
#include "tableScan.h"
#include "cursorForTmptable.h"

int init_database(struct dbSysHead *head)
{
	initSys(head);
	head->fpdesc = fopen(DBMS_DAT, "rb+");
	isAvail(head->fpdesc, "main", FOPEN);
	return 0;
}

int exit_database(struct dbSysHead *head)
{
	sysUpdate(head);
	fclose(head->fpdesc);
	free(head->bitMap);
	return 0;
}

int main()
{
	struct dbSysHead head;
	long fid1, fid2;

	/*
	≥ı ºªØ£¨»ª∫Û¥Ú”°≥ˆµ±«∞œµÕ≥µƒ–≈œ¢
	*/
	init_database(&head);
	showDesc(&head);

//	printf("create file1...\n");
	fid1 = creatFileSpace(&head);//Œ™Œƒº˛“ª∑÷≈‰ø’º‰
    fid2 = creatFileSpace(&head);
//	showFileDesc(&head);
/*	printf("extend 10 pages for file1...\n");
	extendFileSpace(&head, fid1, 10);//¿©’π Æ“≥
	showFileDesc(&head);
	printf("extend 10 pages for file1...\n");
	extendFileSpace(&head, fid1, 10);//‘Ÿ¿©’π Æ“≥
	showFileDesc(&head);

	printf("create file2...\n");
	fid2 = creatFileSpace(&head);
	showFileDesc(&head);
	printf("extend 10 pages for file2...\n");
	extendFileSpace(&head, fid2, 10);
	showFileDesc(&head);
	printf("extend 10 pages for file2...\n");
	extendFileSpace(&head, fid2, 10);
	showFileDesc(&head);

	printf("delete file1...\n");
	recyFileSpace(&head, fid1);
	showFileDesc(&head);
	printf("delete file2...\n");
	recyFileSpace(&head, fid2);
	showFileDesc(&head);*/

//	if(initTable(&head, fid1) == 0)
    if(initTable(&head, FIRST_FID) == 0)
		printf("1 initTable: customer.tbl\n");
	if(showTable(&head, "customer") == -1 )
		printf("2 showTable: customer\n");
    
    if(initTable(&head, FIRST_FID+1) == 0)
        printf("1 initTable: nation.tbl\n");
    if(showTable(&head, "nation") == -1 )
        printf("2 showTable: nation\n");
    //read customer.tbl and write into our file1, 一次性
    loaddata(&head, FIRST_FID);
    loaddata(&head, FIRST_FID + 1);
    //use dictID to scan file1
/*
    int dictID = 1;
    int scanPointer = 0;
    int rec_length = head.redef[dictID].getRecordLength();
	printf("attributeName::%s", head.redef[dictID].getAttributeByNo(0).getName());
    RecordCursor scanTable(&head, 1, rec_length, 0);
    char * one_Row_ = (char *)malloc(sizeof(char)*rec_length);
    while (true == scanTable.getNextRecord(one_Row_)) { //only scan
        scanPointer ++;
        if(scanPointer > 230)
            getOneRecord(one_Row_, head.redef[dictID]); //get each attribute value and print
    }
    free(one_Row_);
*/
    //Scan Table
    relation * temp_data_dict = new relation[MAX_FILE_NUM];
    TableScan(&head, FIRST_FID, temp_data_dict);
    //get the output of tablescan, temporarily according to datadict1, other than temp_data_dict[1]
    int buffer_ID_ = - temp_data_dict[0].fileID;   //find which buffer
    int record_num_ = temp_data_dict[0].getRecordNum();
    int record_len_ = temp_data_dict[0].getRecordLength();
    RecordCursorTmp t1(&head,1,record_len_,buffer_ID_,record_num_);
    cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    int scanPointer = 0;
    int dictID = queryFileID(&head, FIRST_FID);
    char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
    while (true == t1.getNextRecord(one_Row_)) { //only scan
        scanPointer ++;
        if(scanPointer < 20)
            getOneRecord(one_Row_, &head.redef[dictID]); //get each attribute value and print
    }
    free(one_Row_);
    // create index
/*
    printf("recordNum:%d\n",head.redef[dictID].recordNum);
	if(true == createIndexOn(&head, 1, "custkey")){
		char* index_filename= "b_plus_tree_index_1custkey.dat";
		
		FILE* fp = fopen(index_filename,"rb+");
		printf("search(fp,-10):%d\n",search(fp,-10));
		printf("search(fp,1):%d\n",search(fp,1));
		printf("search(fp,2):%d\n",search(fp,2));
		printf("search(fp,50):%d\n",search(fp,50));
		display(fp);
		fclose(fp);
	}
	
    // insert one record
	relationDefine dic = head.redef[0];
    int size_per_record = dic.recordLength;
    char *oneRec = (char *)malloc(sizeof(char)*size_per_record);
        
	char * insertTest = (char *)malloc(sizeof(char)* 256);
    strcpy(insertTest,"501|Customer#000000001|IVhzIApeRb ot,c,E|15|25-989-741-2988|711.56|BUILDING|to the even, regular platelets. regular, ironic epitaphs nag eHHHHHH|");
    parserOneLineFromFile(insertTest, oneRec, dic);
    insertOneRecord(&head, 1, oneRec);//≤Â»Î“ªÃı ˝æ›£¨◊‘∂Ø∏¸–¬À˜“˝
	free(insertTest);
    free(oneRec);
    
    // look up key in index
	char* index_filename= "b_plus_tree_index_1custkey.dat";
	FILE* fp = fopen(index_filename,"rb+");
	int pos = search(fp,501);
	printf("pos:::%d\n",pos);
	fclose(fp);
	
	
	one_Row_ = (char *)malloc(sizeof(char)*rec_length);
	rdFile( &head, 0, 1, pos, rec_length,one_Row_);
	printf("reading from index:\n");
	getOneRecord(one_Row_, dic);
*/    
    
    showFileDesc(&head);
    exit_database(&head);
	system("pause");
	return 0;
}

