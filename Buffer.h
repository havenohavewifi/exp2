//
//  Buffer.h
//  loaddata
//
//  Created by IreneWu on 15/11/4.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#ifndef Buffer_h
#define Buffer_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "dbHead.h"

class Buffer{
public:
    Buffer(){};
    ~Buffer(){
        free(data_);
        std::cout<<"free Buffer"<<std::endl;
    };
    //initialize with data_ NULL
    Buffer(struct dbSysHead * head, int fid);
    //append one record per time
    bool AppendBuffer(const void * new_data, int new_size);
    //write one page to file(write from buffer to the disk)
    bool writeBuffer(struct dbSysHead * head, void * write_data, int write_size);
    bool writeBufferPage(struct dbSysHead * head,int buffer_id_,void * write_data, int write_size);
public:
    struct dbSysHead * filehead;
    //temporary is 1
    long fileID;
    //start at 0
    long pageID;
    //record content written in the form of char
    char * data_;
    //wirte pointer at current position
    char * pointer_;
    //current data length
    int current_size_;
    //set maxsize as SIZE_PER_PAGE
    int max_size_;
    
};

#endif 
