#include "ros/ros.h"
#include "package_lab1/Roulette_bet.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>

ros::ServiceServer service;
ros::Publisher roulette_publisher;
ros::Subscriber result_subscriber;

bool win_lose(package_lab1::Roulette_bet::Request  &req,
         package_lab1::Roulette_bet::Response &res)
{
  srand(time(0));
 
  if (time(0) % 2 == 0) 
  {    
    res.result = std::string("win").c_str();
  }
  else
  {
    res.result = std::string("lose").c_str();
  }
  ROS_INFO("Sending back response: ",res.result);
  std_msgs::String result;
  result.data = res.result;
  roulette_publisher.publish(result);
  return true;
}

void result_callback(const std_msgs::String::ConstPtr& msg)
{
  std::string answer = msg-> data;
  if (answer == "win")
  {
    ROS_INFO("CONGRATULATIONS!!!");
  }
  else
  {
    int check = time(0) % 3;
    if (check == 0) 
    {
      ROS_INFO("Don't be upset, next time you will win");
    }
     if (check == 2) 
     {
        ROS_INFO("Don't worry, you will win next time");
     }
     if (check == 3) 
     {
       ROS_INFO("Cheer up!Next time you will definitely win");
     }
   }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "roulette_server");
  ros::NodeHandle n;

  service = n.advertiseService("result_roulette_bet", win_lose);
  roulette_publisher = n.advertise<std_msgs::String>("result", 1000);
  result_subscriber = n.subscribe("result", 1000, result_callback);

  ROS_INFO("Ready to play roulette.");
  ros::spin();

  return 0;
}
