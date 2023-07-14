cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(playground VERSION 0.0.1 DESCRIPTION "C++11,14 playground" LANGUAGES C CXX)

set(DEFAULT_BUILD_TYPE "Debug")

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

#STNDARD STUFF
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")

if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lX11 -Wall" )
endif (UNIX)

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /O2 /MD" )
endif (WIN32)

set(TARGET_NAME "optimization")

if (WIN32)
	set(QT5_PATH  "C:\\Qt\\5.15.2\\msvc2019_64")
	list(APPEND CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\msvc2019_64\\lib\\cmake\\Qt5Core")
	list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH})
    list(APPEND CMAKE_PREFIX_PATH "C:\\repo\\opencv_build")
endif (WIN32)

if (UNIX)
    find_package(X11 REQUIRED)
endif (UNIX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
#find_package(OpenCV QUIET COMPONENTS core)

enable_testing()

include_directories( "gtest" )

macro(clone_build libname)
	configure_file(clone_build/${libname}.in ${libname}-download/CMakeLists.txt)
	execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/${libname}-download")
	execute_process(COMMAND "${CMAKE_COMMAND}" --build .
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/${libname}-download")
	add_subdirectory("${CMAKE_BINARY_DIR}/${libname}-src"
                 "${CMAKE_BINARY_DIR}/${libname}-build")
endmacro()

clone_build(spdlog)
clone_build(googletest)
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#add_library(utils_lib STATIC
#	${SRC_UTILS} ${HEADERS_UTILS})

set(SRC_GTEST
	gtest/gtest_smart_pointer.cc
	gtest/gtest_test.cc
	gtest/gtest.cc)

set(HEADERS_GTEST
	gtest/gtest_smart_pointer.h
    gtest/gtest_test.h)

add_executable(gtest_playground ${SRC_GTEST} ${HEADERS_GTEST})
target_link_libraries(gtest_playground gtest gmock spdlog Qt5::Core Threads::Threads)

if (WIN32)
	if(${CMAKE_BUILD_TYPE} STREQUAL  "Release")
		set(PREFIX_BUILD_TYPE "")
	endif()
	if(${CMAKE_BUILD_TYPE} STREQUAL  "Debug")
		set(PREFIX_BUILD_TYPE "d")
	endif()
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")

    add_custom_command(TARGET gtest_playground POST_BUILD
       COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:gtest_playground>)
endif(WIN32)

if (WIN32)
	add_custom_command(TARGET gtest_playground POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT5_PATH}/bin/Qt5Test${PREFIX_BUILD_TYPE}.dll   ${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT5_PATH}/bin/Qt5Gui${PREFIX_BUILD_TYPE}.dll   ${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT5_PATH}/bin/Qt5Core${PREFIX_BUILD_TYPE}.dll   ${CMAKE_BUILD_TYPE}/
	)
endif(WIN32)