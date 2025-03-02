cmake_minimum_required (VERSION 3.8)
project(playground VERSION 0.0.1 DESCRIPTION "C++11,14 playground" LANGUAGES C CXX)

set(TARGET_NAME "playground")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)
	set(QT5_PATH  "D:\\Qt5\\5.15.2\\msvc2019_64")
    list(APPEND CMAKE_PREFIX_PATH ${QT5_PATH})
    set(OpenCV_DIR "D:\\repo\\opencv-4.10.0-build")
    set(QMAKE_EXE  "D:\\Qt5\\5.15.2\\msvc2019_64\\bin\\qmake.exe")
endif (WIN32)

if (UNIX)
    find_package(X11 REQUIRED)
endif (UNIX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Multimedia Network)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

include_directories( "gtest" )
MESSAGE(STATUS "CMAKE_CONFIGURATION_TYPES: ${CMAKE_CONFIGURATION_TYPES}")
add_subdirectory(googletest)
if("${CMAKE_CONFIGURATION_TYPES}" STREQUAL "Release")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

set(SRC
	src/main.cc)

set(HEADERS)

set(SRC_GTEST
	gtest/gtest_smart_pointer.cc
	gtest/gtest_move.cc
	gtest/gtest_test.cc
    gtest/gtest_padding.cc
	gtest/gtest_virtual_destructor.cc
	gtest/gtest_cast.cc
	gtest/gtest.cc)

set(HEADERS_GTEST
	gtest/gtest_smart_pointer.h
	gtest/gtest_move.h
    gtest/gtest_test.h
    gtest/gtest_padding.h
	gtest/gtest_virtual_destructor.h
	gtest/gtest_cast.h)





add_library(${PROJECT_NAME}_lib STATIC
    ${SRC} ${HEADERS})

target_link_libraries(${PROJECT_NAME}_lib Qt::Core Threads::Threads)

install(TARGETS ${PROJECT_NAME}_lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
install(TARGETS ${PROJECT_NAME}_lib EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

MESSAGE(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
MESSAGE(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")

add_executable(g_test ${SRC_GTEST} ${HEADERS_GTEST})
target_link_libraries(g_test ${PROJECT_NAME}_lib gtest gmock)


if (WIN32)
    get_target_property(QMAKE_EXE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${QMAKE_EXE}" DIRECTORY)
    message(STATUS "QT_BIN_DIR" ${QT_BIN_DIR} )
    find_program(WINDEPLOYQT_ENV_SETUP qtenv2.bat HINTS "${QT_BIN_DIR}")
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")
endif(WIN32)

if (WIN32)
    set(PREFIX_BUILD_TYPE "")
    if("${CMAKE_CONFIGURATION_TYPES}" STREQUAL "Debug")
		set(PREFIX_BUILD_TYPE "d")
    endif()
    set(OPENCV_VERSION_WINDOWS "4100")

    MESSAGE(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
    MESSAGE(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")

    set(QT5_CORE ${QT5_PATH}/bin/Qt5Core${PREFIX_BUILD_TYPE}.dll)
    MESSAGE(STATUS "QT5_CORE ${QT5_CORE}")
    add_custom_command ( TARGET g_test
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT5_PATH}/bin/Qt5Test${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT5_PATH}/bin/Qt5Gui${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT5_PATH}/bin/Qt5Multimedia${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT5_PATH}/bin/Qt5Network${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${QT5_CORE} ${CMAKE_CONFIGURATION_TYPES}

        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_stitching${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_bgsegm${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_tracking${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_videoio${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_video${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_imgcodecs${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_imgproc${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_core${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_calib3d${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_features2d${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_flann${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_dnn${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_highgui${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_stitching${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_gapi${OPENCV_VERSION_WINDOWS}${PREFIX_BUILD_TYPE}.dll   ${CMAKE_CONFIGURATION_TYPES}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}/opencv_videoio_ffmpeg${OPENCV_VERSION_WINDOWS}_64.dll   ${CMAKE_CONFIGURATION_TYPES}
    )
endif(WIN32)