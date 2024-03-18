cmake_minimum_required(VERSION 3.7)

# Let's set the target name as a variable so we can refer to it later
project(war LANGUAGES CXX)

file(GLOB SRC_LIST *.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

find_package(SDL2_image REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_IMAGE_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_TTF_INCLUDE_DIRS})

find_package(SDL2_mixer REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_MIXER_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC include)
# target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

# Copy assets
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/textures/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/textures/)
