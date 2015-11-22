extern "C" {
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

}
#include "dbHead.h"

//indexOpt.cpp
bool createIndexOn(struct dbSysHead *head, long fid, char* column);
bool deleteIndex(struct dbSysHead *head, long fid, char* column);
bool insertInIndex(struct dbSysHead *head, long fid, int position);
bool deleteInIndex(struct dbSysHead *head, long fid, int position);

int searchByColumnAndValue(struct dbSysHead *head, long fid, char* column, int value);

