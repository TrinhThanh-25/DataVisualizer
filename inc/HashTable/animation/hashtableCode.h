#pragma once

#include <string>


const std::string hashinsertCode = {
    "bucket = key % size\n"
    "for(int i = 0; i < table[bucket].size(); i++)\n"
    "    cur = cur->next;\n"
    "Insert to tail\n"
};

const std::string hashremoveCode = {
    "bucket = key % size\n"
    "for(int i = 0; i < table[bucket].size(); i++)\n"
    "    if(not found) cur = cur->next\n"
    "Remove key\n"
    "NOT FOUND KEY\n"
};

const std::string hashfindCode = {
    "bucket = key % size\n"
    "for(int i = 0; i < table[bucket].size(); i++)\n"
    "    if(not found) cur = cur->next\n"
    "FOUND\n"
    "NOT FOUND\n"
};