# exp2
可运行的版本，实现了tablescan       
tablescan后生成了一个临时表和临时数据字典，临时表存放在3个buffer中的一个，bufferID记录在临时数据字典中。        
之后的select，project的传入参数是临时表和临时数据字典，同时会新生成一个临时表和临时数据字典，建好之后之前的临时表会被删除     

每次调试我的都把dbms.dat删除从新建
不然就注释掉createfilespace和loaddata这些重新读文件建表的过程
整体思路是：先找到哪个buffer为空（根据struct buffspace 的属性emptyOrnot），去使用该buffer，然后将其属性设为false
临时表的读写使用另一个curser，与之前的ReadCursor稍有不通，ReadCursor是从外存文件读取，cursorForTmptable用于读临时表
          
in test.cpp //Scan Table
struct relationDefine temp_data_dict[MAX_FILE_NUM];
TableScan(&head, FIRST_FID, temp_data_dict);
TableScan先从文件里扫描到内存缓冲区

后面的几行代码是测试从临时表读出来内容
