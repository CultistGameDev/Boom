cmake_minimum_required(VERSION 3.29.6)

project(BoomHeadshot
  LANGUAGES CXX
  VERSION 0.0.1)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

add_subdirectory(external)

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
# Our Project
add_executable(${PROJECT_NAME})
add_subdirectory(src)

include_directories(include ${GLFW3_INCLUDE_DIR} ${GLM_INCLUDE_DIR}
  ${Vulkan_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE
  include ${GLWF3_INCLUDE_DIR} ${glm_INCLUDE_DIR}
  ${Vulkan_INCLUDE_DIRS})

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if ("${PLATFORM}" STREQUAL "Web")
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/../data
    )
else ()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
    )
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE glfw Vulkan::Vulkan)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file data)
endif ()
