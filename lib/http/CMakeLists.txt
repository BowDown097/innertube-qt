cmake_minimum_required(VERSION 3.16)
project(http VERSION 1.0 LANGUAGES C CXX)
add_library(http)

set_target_properties(http
    PROPERTIES
        AUTOMOC ON
        AUTORCC ON
        AUTOUIC ON
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED true)

option(HTTP_DEBUG "Logs for debugging the library and requests." OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

target_sources(http
    PRIVATE
        src/cachedhttp.cpp
        src/http.cpp
        src/localcache.cpp
        src/networkhttpreply.cpp
        src/throttledhttp.cpp
    PUBLIC
        FILE_SET HEADERS FILES
            src/cachedhttp.h
            src/http.h
            src/httpreply.h
            src/httprequest.h
            src/localcache.h
            src/networkhttpreply.h
            src/throttledhttp.h)

if(HTTP_DEBUG)
    target_compile_definitions(http PUBLIC HTTP_DEBUG)
endif()

target_include_directories(http PUBLIC src)
target_link_libraries(http PUBLIC Qt::Core Qt::Network)
