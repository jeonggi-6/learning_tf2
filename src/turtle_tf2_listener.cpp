#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf2_listener");

  ros::NodeHandle node;

  //turtle2 생성?
  ros::service::waitForService("spawn");
  ros::ServiceClient spawner =
    node.serviceClient<turtlesim::Spawn>("spawn");
  turtlesim::Spawn turtle;
  turtle.request.x = 4;
  turtle.request.y = 2;
  turtle.request.theta = 0;
  turtle.request.name = "turtle2";
  spawner.call(turtle);

  //pub 광고
  ros::Publisher turtle_vel = node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

  //listener를 위한 버퍼, listener 생성
  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  ros::Rate rate(10.0);

  while (node.ok()){
    geometry_msgs::TransformStamped transformStamped;
    try{
        //현재 시간
        ros::Time now = ros::Time::now(); 
        //5초전 시간
        ros::Time past = now - ros::Duration(5.0);

        //turtle1에 대한 turtle2의 좌표 변환, 최신 tf 변환
        // transformStamped = tfBuffer.lookupTransform("turtle2", "turtle1", ros::Time(0));

        //carrot1에 대한 turtle2의 좌표 변환, 최신 tf 변환
        // transformStamped = tfBuffer.lookupTransform("turtle2", "carrot1", ros::Time(0));

        //turtle1의 5초 전 좌표에 대해 turtle2의 지금 좌표 변환, 계산을 위해 시간에 따라 변하지 않는 프레임 'world', 대기 1초
        transformStamped = tfBuffer.lookupTransform("turtle2", now, "turtle1", past, "world", ros::Duration(1.0));
    }
    catch (tf2::TransformException &ex) {
      ROS_WARN("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }

    geometry_msgs::Twist vel_msg;

    //좌표 차이만큼 turtle2의 속도와 방향을 조정
    vel_msg.angular.z = 4.0 * atan2(transformStamped.transform.translation.y,
                                    transformStamped.transform.translation.x);
    vel_msg.linear.x = 0.5 * sqrt(pow(transformStamped.transform.translation.x, 2) +
                                  pow(transformStamped.transform.translation.y, 2));
    //turtle2 속도 pub
    turtle_vel.publish(vel_msg);

    rate.sleep();
  }

  return 0;
};