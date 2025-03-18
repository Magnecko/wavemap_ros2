cmake_minimum_required(VERSION 3.8)
project(wavemap)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# include the wavemap repo with FetchContent
set(WAVEMAP_VERSION feature/cpp_api_yaml_support)  # Select a git branch, tag or commit
cmake_minimum_required(VERSION 3.18)
message(STATUS "Loading wavemap from GitHub (ref ${WAVEMAP_VERSION})")
include(FetchContent)
FetchContent_Declare(
  wavemap
  GIT_REPOSITORY https://github.com/ethz-asl/wavemap.git
  GIT_TAG ${WAVEMAP_VERSION}
  GIT_SHALLOW 1
  SOURCE_SUBDIR library/cpp
  )
FetchContent_MakeAvailable(wavemap)

# create the library as an interface target
add_library(${PROJECT_NAME} INTERFACE)

# link the wavemap targets to the library
target_link_libraries(${PROJECT_NAME} INTERFACE
  wavemap::wavemap_core
  wavemap::wavemap_io
  wavemap::wavemap_pipeline
)

ament_target_dependencies(${PROJECT_NAME} PUBLIC)

ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies()

install(
  TARGETS ${PROJECT_NAME}
  wavemap_core wavemap_io wavemap_pipeline
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()  

ament_package()
