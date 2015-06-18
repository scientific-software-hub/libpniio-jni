# README #

### How to setup? ###

As any JNI project this one consists of cpp and java parts. cpp part is located under jni_cpp folder and managed by a cmake script. Java part defines native interface and a NxFile class. Java part managed by maven.

### How to develop? ###

1. Setup cpp part (a number of dependencies have to be resolved: boost, pni-libraries etc)
2. To update cpp part build it and install (a new libpniio-jni.so file will be copied to {PRJ_ROOT}/src/main/resources/lib/native/x86_64-linux-gnu folder) 
3. When being packaged java part embeds native library into the target jar file.