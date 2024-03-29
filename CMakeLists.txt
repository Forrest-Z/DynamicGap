cmake_minimum_required(VERSION 2.8.3)
project(dynamic_gap)

add_compile_options(-std=c++17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
  message(STATUS "OPENMP FOUND")
  set(OpenMP_FLAGS ${OpenMP_CXX_FLAGS})
  set(OpenMP_LIBS gomp)
endif()

find_package(catkin REQUIRED COMPONENTS
  base_local_planner
  pluginlib
  dynamic_reconfigure
  egocircle
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  std_msgs
  # benchmarking_tools
  pips_trajectory_msgs
  dynamic_reconfigure
  message_generation
)
find_package(Boost REQUIRED COMPONENTS system)
find_package(Eigen3 REQUIRED)

generate_dynamic_reconfigure_options(
  cfg/dg.cfg
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  SYSTEM ${EIGEN3_INCLUDE_DIRS}
  include
  ${catkin_INCLUDE_DIRS}
)

add_message_files(DIRECTORY msg
  FILES
  TrajPlan.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)

catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES dynamic_gap
  INCLUDE_DIRS ${EIGEN3_INCLUDE_DIRS}
  DEPENDS OpenMP 
  CATKIN_DEPENDS base_local_planner dynamic_reconfigure egocircle geometry_msgs nav_msgs roscpp rospy std_msgs sensor_msgs pips_trajectory_msgs message_runtime
)


add_library(dynamic_gap
  src/planner.cpp
  src/trajectory_follower.cpp
  src/dynamic_gap.cpp
  src/gap_utils.cpp
  
  src/dynamicgap_config.cpp
  src/visualization.cpp
  src/goal_selector.cpp
  src/trajectory_scoring.cpp
  src/gap_trajectory_generator.cpp
  src/gap_manip.cpp
  src/trajectory_controller.cpp
  src/gap_associator.cpp
  src/mp_model.cpp
  ) 

add_dependencies(dynamic_gap ${PROJECT_NAME}_gencfg)
add_dependencies(dynamic_gap custom_msg_generate_messages_cpp)
add_dependencies(dynamic_gap ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_compile_options(dynamic_gap PRIVATE ${OpenMP_FLAGS})
target_link_libraries(dynamic_gap
${catkin_LIBRARIES}
${OpenMP_LIBS}
)
