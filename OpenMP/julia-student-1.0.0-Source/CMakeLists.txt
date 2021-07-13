
cmake_minimum_required(VERSION 3.0.2)
   
project(juliac LANGUAGES C)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")

find_package(OpenMP REQUIRED)
find_package(PNG REQUIRED)


if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")

option(ENABLE_ADMIN "enable admin mode" off)

if(ENABLE_ADMIN)

set(JULIAP_CODE
${SRC_DIR}/juliap_solution.c
)

set(FILTER_CODE
${SRC_DIR}/filter_solution.c
)

else(ENABLE_ADMIN)

set(JULIAP_CODE
${SRC_DIR}/juliap.c
)

set(FILTER_CODE
${SRC_DIR}/filter.c
)

endif(ENABLE_ADMIN)


add_executable(juliap_runner
${JULIAP_CODE}
${SRC_DIR}/juliap_runner.c
)

target_link_libraries(juliap_runner m)

include_directories(${PNG_INCLUDE_DIR})

add_executable(filter_runner
${FILTER_CODE}
${SRC_DIR}/filter_runner.c
${SRC_DIR}/png_utils.c
)

target_link_libraries(filter_runner m ${PNG_LIBRARY})

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_SOURCE_GENERATOR "TBZ2")


set(MY_IGNORE_FILES
"/CMakeFiles/"
"/_CPack_Packages/"
"/bin/"
"/Makefile"
"\\\\.tar\\\\.bz2$"
"/foo.*\\\\.png$"
"/\\\\.git/"
"/\\\\.settings/"
"/\\\\.DS_Store"
"cmake_install\\\\.cmake"
"CPackConfig\\\\.cmake"
"CPackSourceConfig\\\\.cmake"
"CMakeCache.txt"
"${CPACK_SOURCE_IGNORE_FILES}"
)

if(ENABLE_ADMIN)

SET(CPACK_SOURCE_IGNORE_FILES
${MY_IGNORE_FILES}
)

set(CPACK_PACKAGE_NAME "julia-admin")

else(ENABLE_ADMIN)

SET(CPACK_SOURCE_IGNORE_FILES
${MY_IGNORE_FILES}
"/src/.*_solution\\\\.c$"
)

set(CPACK_PACKAGE_NAME "julia-student")

endif(ENABLE_ADMIN)

INCLUDE(CPack)

