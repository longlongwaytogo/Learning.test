﻿CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(HELLO)
MESSAGE(STATUS "THIS PROJECT IS SHOW HOW TO USE CMAKE MODULE FINDHELLO.CMAKE")

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMAKE)
ADD_SUBDIRECTORY(SRC)