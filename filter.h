extern "C"{
#include <stdio.h>
};
#include "dbHead.h"
#include "file.h"
#include "tableScan.h"
#include "cursor.h"
#include "Buffer.h"
#include "dataDictionary.h"

#define LESS_THAN 0
#define NOT_LESS_THAN 1
#define MORE_THAN 2
#define NOT_MORE_THAN 3
#define NOT_EQUAL 4

bool tableScanEqualFilter(struct dbSysHead * head, int fileID, relation * temp_datadic, char* attributeName, char * value,relation * new_temp_datadic);

bool indexScanEqualFilter(struct dbSysHead * head, int fileID, char* attributeName, char* value,relation * new_temp_datadic);

bool tableScanSemiscopeFilter(struct dbSysHead * head, int fileID, relation * temp_data_dict, char* attributeName, char* value,int sign,relation * new_temp_datadic);
bool tableScanScopeFilter(struct dbSysHead * head, int fileID, relation * temp_data_dict, char* attributeName, char* value1,int sign1,char* value2,int sign2,relation * new_temp_datadic);
