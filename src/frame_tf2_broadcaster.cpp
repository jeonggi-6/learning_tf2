#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf2_broadcaster");
  ros::NodeHandle node;

  tf2_ros::TransformBroadcaster tfb;
  geometry_msgs::TransformStamped transformStamped;

  //turtle1에서 y방향으로 2미터 떨어진 carrot1프레임 생성
  transformStamped.header.frame_id = "turtle1";
  transformStamped.child_frame_id = "carrot1";
  transformStamped.transform.translation.x = 0.0;
  transformStamped.transform.translation.y = 2.0;
  transformStamped.transform.translation.z = 0.0;
  tf2::Quaternion q;
        q.setRPY(0, 0, 0);
  transformStamped.transform.rotation.x = q.x();
  transformStamped.transform.rotation.y = q.y();
  transformStamped.transform.rotation.z = q.z();
  transformStamped.transform.rotation.w = q.w();

  ros::Rate rate(10.0);
  while (node.ok()){
    //헤더 기입
    transformStamped.header.stamp = ros::Time::now();

    //시간에 따라 동적인 프레임 생성
    // transformStamped.transform.translation.x = 2.0*sin(ros::Time::now().toSec());
    // transformStamped.transform.translation.y = 2.0*cos(ros::Time::now().toSec());
    
    tfb.sendTransform(transformStamped);
    rate.sleep();
    printf("sending\n");
  }

};