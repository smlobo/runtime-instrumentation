# jvmti-agent
* Set JDK_HOME
* Build with `cmake`:
    - mkdir build
    - cd build
    - cmake ..
    - cmake --build .
* Run as:
    - java -agentpath:/Users/sheldon/repos/runtime-instrumentation/jvmti-agent/build/libjvmti_agent.dylib HelloWorld


