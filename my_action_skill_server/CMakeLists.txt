cmake_minimum_required(VERSION 2.8.3)
project(my_action_skill_server)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

#catkin packages
find_package(catkin
             REQUIRED COMPONENTS
             roscpp
             actionlib
             my_action_skill_msgs
             message_generation
             #rospy
             #std_msgs
             #geometry_msgs
             #tf
)

#External packages
find_package(OpenCV)
find_package(PCL REQUIRED)

#Headers
file(GLOB PROGRAM_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/${PROJECT_NAME}/*.h")

catkin_package(
               INCLUDE_DIRS
               include
               LIBRARIES
               ${PROJECT_NAME}
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(common
            src/common/verbosity_levels.cpp
            #src/common/math_common.cpp
            )

add_library(${PROJECT_NAME}
            src/my_action_skill_server.cpp
            #and all child classes.cpp
            )

## Set dependencies of the library
target_link_libraries(common
                      ${PCL_LIBRARIES}
                      ${catkin_LIBRARIES}
                      )

target_link_libraries(${PROJECT_NAME}
                      ${catkin_LIBRARIES}
                      ${OpenCV_LIBRARIES}
                      ${PCL_LIBRARIES}
                      common
                      )

## Define a executable
add_executable(${PROJECT_NAME}_node
               src/my_action_skill_server_node.cpp)

## Define the executable dependencies
target_link_libraries(${PROJECT_NAME}_node
                      common
                      ${catkin_LIBRARIES}
                      ${OpenCV_LIBRARIES}
                      ${PCL_LIBRARIES}
                      ${PROJECT_NAME})



 #add_executable(${PROJECT_NAME} src/my_action_skill_server.cpp src/my_action_skill_server_node.cpp ${PROGRAM_HEADERS})
 #target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
 #add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
