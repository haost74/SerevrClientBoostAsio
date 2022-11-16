cmake_minimum_required(VERSION 3.2...3.5)
set (PROJECT_NAME "app" CXX)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(Boost_NO_WARN_NEW_VERSIONS 1)

if(WIN32)
  add_definitions(-D_WIN32_WINNT=0x0501)
ENDIF(WIN32)

# -----------------------------------------------------

  #  vc143

  # The following directory should be added to compiler include paths:                                                                                                                                                                                  
  # C:\Boost\boost_1_80_0                                                                                                                                                                                                                       
  # C:\Boost\boost_1_80_0 
  # The following directory should be added to linker library paths:                                                                                                                                                                                    
  # C:\Boost\boost_1_80_0\stage\x64\lib 
  # C:\Boost\boost_1_80_0\stage\lib 

  # cmake .. -DBOOST_ROOT="C:\Boost\boost_1_80_0" -DBOOST_LIBRARYDIR="C:\Boost\boost_1_80_0\stage\x64\lib"


  # b2 -j8 toolset=msvc address-model=64 architecture=x86 link=static threading=multi runtime-link=shared --build-type=complete stage

  # b2 -j8 toolset=msvc address-model=64 architecture=x86 link=shared threading=multi runtime-link=shared --with-thread --build-type=minimal stage

  # C:/Program Files/CMake/bin

# -----------------------------------------------------

#set(Boost_DEBUG 1)

set(CMAKE_CXX_STANDARD 20)
# set(Boost_NO_WARN_NEW_VERSIONS 1)

# -----------------------------------------------------

set (PROJECT_SOURCE_DECLARATION_DIRECTORY ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DEFINITION_DIRECTORY ${PROJECT_SOURCE_DIR}/src)

# -----------------------------------------------------


set(BOOST_ROOT "C:/Boost/boost_1_80_0/stage")
# set(ENV{BOOST_ROOT} "C:/Boost/boost_1_80_0")
# set(Boost_DIR "C:/Boost/boost_1_80_0")
# set(BOOST_LIBRARYDIR "C:/Boost/boost_1_80_0/stage/lib")
# set(ENV{BOOST_LIBRARYDIR} "C:/Boost/boost_1_80_0/stage/lib")
# set(BOOST_INCLUDEDIR "C:/Boost/boost_1_80_0")
# set(Boost_NO_SYSTEM_PATHS TRUE)
# set(Boost_USE_STATIC_RUNTIME FALSE)
# set(Boost_USE_STATIC_LIBS TRUE)
# set(Boost_USE_MULTITHREADED TRUE)
# set(THREAD_LIBRARY_DEBUG TRUE)
# set(Boost_USE_DEBUG_RUNTIME FALSE)
set(Boost_COMPILER "vc143")
# set(Boost_DEBUG 1) 

# SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Boost/boost_1_80_0")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/win32libs/boost/lib")

find_package(Boost COMPONENTS system filesystem regex thread context json)

message(STATUS ${Boost_FOUND})

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found ---------------- == ---------------------")
endif()


#include_directories (${Boost_INCLUDE_DIR})



# -----------------------------------------------------

add_executable(${PROJECT_NAME} 
         main.cpp
         src/server/asio/synserver.cpp
         src/msg/chat_message.hpp
         src/msg/msg.hpp
         src/msg/msg_server.cpp
         src/msg/msg_client.cpp)         

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++20 standard compliance
    CXX_STANDARD 20
)

target_include_directories(${PROJECT_NAME}  PUBLIC ${Boost_INCLUDE_DIRS}) 

target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})