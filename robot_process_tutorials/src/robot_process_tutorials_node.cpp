#include "robot_process_tutorials/robot_process_tutorials.h"

int main(int argc, char *argv[]) {

  using namespace robot_process_tutorials;

  RobotProcessTutorials rbt(argc, argv);
  rbt.run();

  ros::spin();

  return 0;
}
