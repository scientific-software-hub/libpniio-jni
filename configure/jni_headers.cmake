set(JDK_HOME /usr/lib/jvm/java-7-openjdk-amd64)

if(NOT JDK_HOME)
    message(FATAL_ERROR "Could not find jdk!")
endif()

message("Proceeding with JDK_HOME=" ${JDK_HOME})

include_directories(${JDK_HOME}/include)
include_directories(${JDK_HOME}/include/linux)