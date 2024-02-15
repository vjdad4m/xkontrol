cmake_minimum_required(VERSION 3.10)
project(XKontrol)
set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCE_FILES "src/*.h" "src/*.cpp")

add_executable(xkontrol ${SOURCE_FILES})

if (WIN32)
  find_package(ZeroMQ CONFIG REQUIRED)
  set(CMAKE_LIBS "Xinput.lib libzmq libzmq-static")
endif (WIN32)

if (UNIX)
  set(CMAKE_LIBS "zmq")
endif (UNIX)

target_link_libraries(xkontrol ${CMAKE_LIBS})
