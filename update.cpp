


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dbHead.h"

/**
 * @brief 更新数据库，把内存中的数据写入到磁盘中
 *
 * @param [in] head  : struct dbSysHead *
 * @return  int 
 * @author tianzhenwu
 * @date 2015/10/20
 **/
int sysUpdate( struct dbSysHead *head )
{	
	int i, k;

	rewind( head->fpdesc );
	fwrite( &(head->desc), sizeof(struct SysDesc), 1, head->fpdesc );

	rewind( head->fpdesc );
	fseek( head->fpdesc, head->desc.bitMapAddr, SEEK_SET );
	fwrite( head->bitMap, sizeof(char), head->desc.sizeBitMap, head->fpdesc );
    
    rewind( head->fpdesc);
    fseek( head->fpdesc, head->desc.dataDictionaryAddr, SEEK_SET);
    for (i = 0; i < MAX_FILE_NUM; i++) {
        fwrite( &head->redef[i], sizeof(struct relationDefine) , head->desc.sizedataDictionary, head->fpdesc);
    }
    

	for (k=0; k<3; k++)
		for( i=0; i<SIZE_BUFF; i++ ) {
			if( P_EDIT == head->buff[k].map[i].edit ) {
				rewind( head->fpdesc );
				fseek( head->fpdesc, head->desc.dataAddr + SIZE_PER_PAGE * head->buff[k].map[i].pageNo, SEEK_SET );
				fwrite( head->buff[k].data[i], sizeof(char), SIZE_PER_PAGE, head->fpdesc);
				head->buff[k].map[i].edit = P_UNEDIT;
			}
		}
	return 0;
}