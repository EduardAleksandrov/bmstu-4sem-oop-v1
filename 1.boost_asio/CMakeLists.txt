# Запуск
# conan install path/to/conan/file --output-folder=build --build=missing
# 
# conan install /home/eduard/Projects/iu7/CPP_v1/2.cmake-conan/conanfile-example.txt -of /home/eduard/Projects/iu7/CPP_v1/2.cmake-conan/build-conan --build=missing
# cd build
# 
# source conanbuild.sh  - необязательный элемент
# 
# cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release        - .. значит что файл cmakelists.txt лежит на директорию выше
# cmake --build .
# 
# source deactivate_conanbuild.sh
# 
# ./timer

# vscode .vscode/c_cpp_properties.json    - чтобы vscode не подчеркивал
# {
#     "configurations": [
#         {
#             "name": "Linux",
#             "includePath": [
#                 "${workspaceFolder}/**",
#                 "~/.conan2/**"
#             ],
#             "intelliSenseMode": "linux-gcc-x64",
#             "compilerPath": "/usr/bin/g++"
#         }
#     ],
#     "version": 4
# }


cmake_minimum_required(VERSION 3.16)
project(FoundationBoost)
add_definitions("-std=c++17")
message("cl: ${CONAN_LIBS}")
message("cl: ${PROJECT_SOURCE_DIR}")

#compiler flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug) # Release
endif()

include(${PROJECT_SOURCE_DIR}/build-conan/build/Release/generators/conan_toolchain.cmake)
find_package(Boost REQUIRED)



add_executable(boost boost_asio.cpp)
target_link_libraries(boost boost::boost)
