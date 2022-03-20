cmake_minimum_required(VERSION 3.0.0)
project(Lab5_Chirea VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Lab5_Chirea App.cpp ExtendedTest.h ExtendedTest.cpp ShortTest.cpp ShortTest.h SMIterator.cpp SMIterator.h
                SortedMap.cpp SortedMap.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
