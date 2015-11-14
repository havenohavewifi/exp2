//
//  Buffer.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/4.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//
extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

};

#include "dbHead.h"
#include "file.h"
#include "Buffer.h"

#include <iostream>
#include <fstream>
#include <string>


Buffer:: Buffer(struct dbSysHead * head, int fID):filehead(head), fileID(fID),current_size_(0),max_size_(SIZE_PER_PAGE){
    pageID = 0;
    data_ = (char *)malloc(max_size_);
    pointer_ = data_;;
};
bool Buffer::AppendBuffer(const void * new_data, int new_size){
        if (new_size + current_size_ <= max_size_) {
            memcpy(pointer_, new_data, new_size);
            pointer_ = pointer_ + new_size;
            current_size_ += new_size;
            return true;
        }
        else{
            return false;
        }
    }
bool Buffer::writeBuffer(struct dbSysHead * head,void * write_data, int write_size){
        wtFile(head, 0, fileID, pageID * SIZE_PER_PAGE, write_size,write_data);
        return true;
    };

