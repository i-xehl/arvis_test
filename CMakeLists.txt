cmake_minimum_required(VERSION 3.5)

project(arvis_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

set(DEPENDENCIES "aravis-0.10")
pkg_check_modules(DEPS REQUIRED IMPORTED_TARGET ${DEPENDENCIES})

find_package(OpenCV REQUIRED)

add_executable(arvis_test main.cpp)

include(GNUInstallDirs)
install(TARGETS arvis_test
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::DEPS ${OpenCV_LIBS})
