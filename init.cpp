extern "C" {
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
};
#include"dbHead.h"

/**
* @brief 初始化系统，从文件中读入相关的信息完成初始化；如果文件不存在，则重新创建文件，并进行初始化。
*
* @param [in/out] head  : struct dbSysHead *
* @return  int
*
* @author tianzhenwu
* @date 2015/10/20
**/
int initSys(struct dbSysHead *head)
{
	FILE *fp;
	int i, k;

	fp = fopen(DBMS_DAT, "rb");
	if (NULL == fp) {
		creaSysHead();
		fp = fopen(DBMS_DAT, "rb");
	}
	isAvail(fp, "initSys", FOPEN);
	rewind(fp);
	fread(&(head->desc), sizeof(struct  SysDesc), 1, fp);

	head->bitMap = (unsigned long *)malloc(head->desc.sizeBitMap);
	isAvail(head->bitMap, "initSys", MALLOC);
	rewind(fp);
	fseek(fp, head->desc.bitMapAddr, SEEK_SET);
	fread(head->bitMap, 1, head->desc.sizeBitMap, fp);

	for (k=0; k<3; k++) {
		for (i = 0; i<SIZE_BUFF; i++) {
			head->buff[k].map[i].pageNo = -1;
			head->buff[k].map[i].vstTime = 0;
			head->buff[k].map[i].edit = P_UNEDIT;
		}
		head->buff[k].curTimeStamp = 0;
        head->buff[k].emptyOrnot = true;
	}
    
	fclose(fp);
	return 0;
}



/**
* @brief 若第一次运行程序，则初始化系统，并把初始化的信息写入到文件中。
*
* @return  int
*
* @author tianzhenwu
* @date 2015/10/20
**/
int creaSysHead()
{
	FILE *fp;
	struct dbSysHead sysHead;
	char ch;

	fp = fopen(DBMS_DAT, "wb");
	isAvail(fp, "creaSysHead", FOPEN);
	rewind(fp);
//	fseek(fp, BITMAP_ADDR + SIZE_BIT_MAP + SIZE_DATA_SPACE, SEEK_SET);
    fseek(fp, DICTIONARY_ADDR +DICTIONARY_SIZE +SIZE_DATA_SPACE, SEEK_SET);
    ch = '\0';
	fwrite(&ch, sizeof(char), 1, fp);

	/*
	这里把参数写死了，其实用配置文件的方式初始化更好。
	*/
	sysHead.desc.sizeOfFile = SIZE_DATA_SPACE;
	sysHead.desc.sizePerPage = SIZE_PER_PAGE;
	sysHead.desc.totalPage = (SIZE_DATA_SPACE) / (SIZE_PER_PAGE);

	sysHead.desc.bitMapAddr = BITMAP_ADDR;
	sysHead.desc.sizeBitMap = sysHead.desc.totalPage / 8;	//byte
	sysHead.desc.pageAvai = (SIZE_DATA_SPACE) / (SIZE_PER_PAGE);
    
    sysHead.desc.dataAddr = DICTIONARY_ADDR;
    sysHead.desc.dataDictionaryAddr = DICTIONARY_SIZE;
	sysHead.desc.dataAddr = DATA_ADDR;
	sysHead.desc.segmentNum = 0;
	sysHead.desc.segmentAddr = SEGMENT_ADDR;
	sysHead.desc.segmentCur = 0;

	sysHead.desc.curfid = FIRST_FID;
	sysHead.desc.curFileNum = 0;
	memset(sysHead.desc.fileDesc, 0, sizeof(struct FileDesc)*MAX_FILE_NUM);

	rewind(fp);
	fwrite(&(sysHead.desc), sizeof(struct SysDesc), 1, fp);

/*    sysHead.redef = (struct relationDefine *)malloc(sizeof(struct relationDefine)* MAX_FILE_NUM);
    memset(sysHead.redef, 0 , sizeof(struct relationDefine)* MAX_FILE_NUM);
    rewind(fp);
    fseek(fp, sysHead.desc.dataDictionaryAddr, SEEK_SET);
    fwrite(&(sysHead.redef), sizeof(relation)* MAX_FILE_NUM, 1, fp);
*/
    
	sysHead.bitMap = (unsigned long *)malloc(sysHead.desc.sizeBitMap);
	memset(sysHead.bitMap, -1, sysHead.desc.sizeBitMap);
	rewind(fp);
	fseek(fp, sysHead.desc.bitMapAddr, SEEK_SET);
	fwrite(sysHead.bitMap, 1, sysHead.desc.sizeBitMap, fp);
	free(sysHead.bitMap);
    
	fclose(fp);

	return 0;
}