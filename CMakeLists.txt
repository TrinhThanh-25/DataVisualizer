cmake_minimum_required(VERSION 3.16)

# Đặt tên cho project
project(DATAVISUALIZER)




# Thêm tất cả file .cpp trong thư mục src/
file(GLOB_RECURSE SOURCES src/*.cpp)

# Thêm tất cả file .h trong thư mục inc/
include_directories(inc/)

# Tạo file thực thi từ các source file
add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory("raylib")
target_link_libraries(${PROJECT_NAME} raylib)

# Copy thư mục resources vào build để giữ hình ảnh, âm thanh...
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
