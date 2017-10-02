cmake_minimum_required(VERSION 2.8.3)
project(sooyoung_ros)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	std_msgs
)

catkin_package(

)

include_directories(
	${catkin_INCLUDE_DIRS}
)

add_executable(pub_setpoints_path src/pub_setpoints_path.cpp)
target_link_libraries(pub_setpoints_path ${catkin_LIBRARIES})
add_dependencies(pub_setpoints_path sooyoung_ros_generate_messages_cpp)


