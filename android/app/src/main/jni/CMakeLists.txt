cmake_minimum_required(VERSION 3.4.1)

project(unreal_notifications LANGUAGES CXX)

set(LIB_NAME unreal_notifications)

set(SOURCE_FILES
        src/UnrealNotifications.cpp
        src/TypeConverter.cpp)

add_library(${LIB_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${LIB_NAME} PRIVATE log)
target_include_directories(${LIB_NAME} PUBLIC include)