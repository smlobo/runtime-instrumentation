//
// Created by Sheldon Lobo on 2/22/21.
//

#include <iostream>
#include <cassert>

#include "ClassInfo.h"

ClassInfo::ClassInfo(const uint8_t *classData, uint32_t classDataSize) {
    // The magic number
    magic = (*(classData+0) << 24) | (*(classData+1) << 16) | (*(classData+2) << 8) | (*(classData+3) << 0);
    assert(magic == 0xcafebabe);
    std::cout << "\tMagic: " << std::hex << magic << std::dec << std::endl;
    classData += 4;

    // Minor Version
    minorVersion = (*(classData+0) << 8) | (*(classData+1) << 0);
    std::cout << "\tMinor version: " << minorVersion << std::endl;
    classData += 2;

    // Minor Version
    majorVersion = (*(classData+0) << 8) | (*(classData+1) << 0);
    std::cout << "\tMajor version: " << majorVersion << std::endl;
    classData += 2;
}

ClassInfo::~ClassInfo() {}
