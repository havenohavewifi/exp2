
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "nestloop.h"
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
int showRelation(relation *r)
{
	printf("TableName: %s\n", r->getRelationName());
	printf("Constructor: %s\n", r->getConstructor());
	printf("AttributeNum: %d\n", r->getAttributeNum());
	for (int j = 0; j < r->getAttributeNum(); j++)
	{
		printf("%d:%s\n", j + 1, r->getAttributeByNo(j).getName());
	}
	printf("RecordLength: %d\n", r->getRecordLength());
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

	
	init_database(&head);
	showDesc(&head);

	fid1 = creatFileSpace(&head);//Œ™Œƒº˛“ª∑÷≈‰ø’º‰
    fid2 = creatFileSpace(&head);

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
    

    //Scan Table
    relation * temp_data_dict = new relation[MAX_FILE_NUM];
    TableScan(&head, FIRST_FID, temp_data_dict);
   
    
    loaddata(&head, FIRST_FID + 1);
    
    TableScan(&head, FIRST_FID + 1, temp_data_dict);
  
	//nestloop_cp
	relation result;
	result.init("cus_nation", "zhangwenhui");
	/*merge_relation_cp(&head,temp_data_dict[0],temp_data_dict[1],&result);
	showRelation(&result);
	
	nestloop_cp(&head, &temp_data_dict[0],&temp_data_dict[1], &result);*/
	
	//nestloop_equal
	merge_relation(&head,temp_data_dict[0],temp_data_dict[1],&result);
	//nestloop_equal(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");
	nestloop_bigger(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");
	nestloop_smaller(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");
	nestloop_smaller_or_equal(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");
	nestloop_bigger_or_equal(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");
	showRelation(&result);
    showFileDesc(&head);
    exit_database(&head);
	system("pause");
	return 0;
}

