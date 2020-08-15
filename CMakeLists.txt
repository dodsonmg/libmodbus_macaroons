cmake_minimum_required(VERSION 3.5)
project(libmodbus_macaroons)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(libmodbus REQUIRED)
find_package(libmacaroons REQUIRED)

add_library(modbus_macaroons SHARED
            src/modbus_macaroons.c
            )

target_include_directories(modbus_macaroons PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

ament_target_dependencies(modbus_macaroons libmodbus libmacaroons)

ament_export_interfaces(export_modbus_macaroons HAS_LIBRARY_TARGET)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS modbus_macaroons
  EXPORT export_modbus_macaroons
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

ament_export_include_directories(include)
ament_export_libraries(modbus_macaroons)

ament_package()