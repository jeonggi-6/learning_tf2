cmake_minimum_required(VERSION 3.0.2)
project(learning_tf2)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf2
  tf2_ros
  turtlesim
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES learning_tf2
#  CATKIN_DEPENDS roscpp rospy tf2 tf2_ros turtlesim
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
add_executable(static_turtle_tf2_broadcaster src/static_turtle_tf2_broadcaster.cpp)
target_link_libraries(static_turtle_tf2_broadcaster  ${catkin_LIBRARIES} )


add_executable(turtle_tf2_broadcaster src/turtle_tf2_broadcaster.cpp)
target_link_libraries(turtle_tf2_broadcaster ${catkin_LIBRARIES} )

add_executable(turtle_tf2_listener src/turtle_tf2_listener.cpp)
target_link_libraries(turtle_tf2_listener ${catkin_LIBRARIES} )

add_executable(frame_tf2_broadcaster src/frame_tf2_broadcaster.cpp)
target_link_libraries(frame_tf2_broadcaster ${catkin_LIBRARIES} )

install(FILES
 start_demo.launch
 DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)