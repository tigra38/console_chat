cmake_minimum_required(VERSION 3.14)

project(Chat LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Chat
  main.cpp
  Sha1.cpp
  Sha1.h
  Message.h
  Chat.h
  Chat.cpp
)
