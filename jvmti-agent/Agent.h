//
// Created by Sheldon Lobo on 2/22/21.
//

#ifndef JVMTI_AGENT_AGENT_H
#define JVMTI_AGENT_AGENT_H

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *jvm, char *options, void *reserved);

class Agent {
private:
    const std::vector<std::string> DO_NOT_TRANSFORM {
            "java/util",
            "java/lang",
            "java/io",
            "java/nio",
            "java/security",
            "java/net",
            "sun/",
            "com/sun",
            "jdk/",
            "jre/",
            "["
    };
    bool doNotTransform(const char *className);

public:
    static void JNICALL callbackClassLoadHook(jvmtiEnv *jvmti_env,
                                       JNIEnv* jni_env,
                                       jclass class_being_redefined,
                                       jobject loader,
                                       const char* name,
                                       jobject protection_domain,
                                       jint class_data_len,
                                       const unsigned char* class_data,
                                       jint* new_class_data_len,
                                       unsigned char** new_class_data);

    void check_jvmti_errors(jvmtiEnv *jvmti, jvmtiError errnum, const char *str);
};

#endif //JVMTI_AGENT_AGENT_H
