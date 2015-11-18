# exp2
re-organized experiment 2
tablescan后生成了一个临时表和临时数据字典，临时表存放在3个buffer中的一个，bufferID记录在临时数据字典中。        
之后的select，project的传入参数是临时表和临时数据字典，同时会新生成一个临时表和临时数据字典，建好之后之前的临时表会被删除
