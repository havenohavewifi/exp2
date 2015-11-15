# exp2
re-organized experiment 2
整体思路是：先找到哪个buffer为空（根据struct buffspace 的属性emptyOrnot），去使用该buffer，然后将其属性设为false      
临时表的读写使用另一个curser，与之前的ReadCursor稍有不通，ReadCursor是从外存文件读取，cursorForTmptable用于读临时表     
//Scan Table    
    struct relationDefine temp_data_dict[MAX_FILE_NUM];   
    TableScan(&head, FIRST_FID, temp_data_dict);    
TableScan先从文件里扫描到内存缓冲区   
后面的是测试从临时表读出来内容    
//get the output of tablescan, temporarily according to datadict1, other than temp_data_dict[1]   
    int buffer_ID_ = - temp_data_dict[0].fileID;   //find which buffer
    int record_num_ = temp_data_dict[0].recordNum;
    int record_len_ = temp_data_dict[0].recordLength;
    RecordCursorTmp t1(&head,1,record_len_,buffer_ID_,record_num_);
    cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    int scanPointer = 0;
    int dictID = queryFileID(&head, FIRST_FID);
    char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
    while (true == t1.getNextRecord(one_Row_)) { //only scan
        scanPointer ++;
        if(scanPointer < 20)
            getOneRecord(one_Row_, head.redef[dictID]); //get each attribute value and print
    }
    free(one_Row_);
