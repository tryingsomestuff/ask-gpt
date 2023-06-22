cmake_minimum_required(VERSION 3.13)

project(ask-gpt)
set(CMAKE_CXX_STANDARD 20)

include_directories("lib/openai/include/openai")

add_executable(ask-gpt main.cpp)

# get curl (for openai ...)
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(ask-gpt ${CURL_LIBRARIES})

# get fmt
include(FetchContent)
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)
target_link_libraries(ask-gpt fmt::fmt)
