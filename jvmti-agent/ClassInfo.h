//
// Created by Sheldon Lobo on 2/22/21.
//

#ifndef JVMTI_AGENT_CLASSINFO_H
#define JVMTI_AGENT_CLASSINFO_H

#include <cstdint>
#include <string>

#include "jvmti.h"

class ClassInfo {
private:
    uint32_t    magic;
    uint16_t    minorVersion;
    uint16_t    majorVersion;
    uint16_t    constant_pool_count;
    //cp_info **constant_pool;
    std::string className;
    std::string superClassName;

public:
    ClassInfo(const uint8_t *classData, uint32_t classDataSize);
    ~ClassInfo();
};

#endif //JVMTI_AGENT_CLASSINFO_H
