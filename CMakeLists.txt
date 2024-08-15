cmake_minimum_required(VERSION 3.28)
project(Hebocontroller)

set(CMAKE_CXX_STANDARD 17)
set(BASH_COMMAND bash -c)

set(LIBNAME hebocontroller)
set(LIBRARIES_DIR "$ENV{HOMEPATH}/Documents/Arduino/libraries")
set(SOURCES src examples library.properties keywords.txt)

# Prepare
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR})
file(REMOVE_RECURSE ${LIBRARIES_DIR}/${PROJECT_NAME})
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/${LIBNAME})
foreach (FILE ${SOURCES})
    file(COPY ${CMAKE_SOURCE_DIR}/${FILE} DESTINATION ${CMAKE_BINARY_DIR}/${LIBNAME})
endforeach (FILE)

# Build
add_custom_target(Build ALL
                  COMMAND ${CMAKE_COMMAND} -E make_directory ${LIBRARIES_DIR}/${LIBNAME}
                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/${LIBNAME} ${LIBRARIES_DIR}/${LIBNAME}
                  COMMAND ${CMAKE_COMMAND} -E tar cf ${LIBNAME}.zip --format=zip ${LIBNAME})

