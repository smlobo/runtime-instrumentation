//
// Created by Sheldon Lobo on 2/22/21.
//

#include <iostream>
#include <vector>
#include <cstring>

#include "jvmti.h"

#include "Agent.h"
#include "ClassInfo.h"

// Global definition
Agent agent;

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *jvm, char *options, void *reserved) {
    std::cout << "Agent loaded" << std::endl;

    jvmtiError error;

    // Get the JVMTI environment
    jvmtiEnv *jvmti;
    jint result = jvm->GetEnv((void **) &jvmti, JVMTI_VERSION_1_0);
    if (result != JNI_OK || jvmti == NULL) {
        std::cout << "Unable to get access to JVMTI version 1.0";
    }

    // Set the ClassFileLoadHook Event capability
    jvmtiCapabilities capabilities;
    memset(&capabilities, 0, sizeof(jvmtiCapabilities));
    capabilities.can_generate_all_class_hook_events = 1;
    error = jvmti->AddCapabilities(&capabilities);
    agent.check_jvmti_errors(jvmti, error, "Error while setting the ClassFileLoadHook Event capability");

    // Enable the event
    error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK,
                                            (jthread) NULL);
    agent.check_jvmti_errors(jvmti, error, "Unable to set the ClassFileLoadHook event notification");

    // Setup the callback
    jvmtiEventCallbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.ClassFileLoadHook = &agent.callbackClassLoadHook;
    error = jvmti->SetEventCallbacks(&callbacks, sizeof(callbacks));
    agent.check_jvmti_errors(jvmti, error, "Unable to set the ClassFileLoadHook event callbacks");

    return JNI_OK;
}

void JNICALL Agent::callbackClassLoadHook(jvmtiEnv *jvmti_env,
                                   JNIEnv* jni_env,
                                   jclass class_being_redefined,
                                   jobject loader,
                                   const char* name,
                                   jobject protection_domain,
                                   jint class_data_len,
                                   const unsigned char* class_data,
                                   jint* new_class_data_len,
                                   unsigned char** new_class_data) {
    if (agent.doNotTransform(name))
        return;

    std::cout << "Class loaded: " << name << std::endl;

    ClassInfo classInfo(class_data, class_data_len);
}

void Agent::check_jvmti_errors(jvmtiEnv *jvmti, jvmtiError errnum, const char *str) {
    if (errnum != JVMTI_ERROR_NONE) {
        char *errnum_str;
        errnum_str = NULL;
        jvmti->GetErrorName(errnum, &errnum_str);
        std::cout << "ERROR: JVMTI: " << errnum << " "  << (errnum_str == NULL ? "Unknown": errnum_str) << " - " <<
                  (str == NULL? "" : str);
    }
}

bool Agent::doNotTransform(const char *className) {
    for (int i = 0; i < DO_NOT_TRANSFORM.size(); i++) {
        if (DO_NOT_TRANSFORM[i].compare(0, DO_NOT_TRANSFORM[i].length(), className, DO_NOT_TRANSFORM[i].length()) == 0)
            return true;
    }
    return false;
}
