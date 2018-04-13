/*********************************************************************
 *
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2018, University of Luxembourg
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of University of Luxembourg nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Maciej Zurad
 *********************************************************************/
#include <robot_process_tutorials/robot_process_tutorials.h>

namespace robot_process_tutorials
{

void RobotProcessTutorials::timerCallback()
{
  ROS_INFO_STREAM(getNamespace() << " " << counter);
  counter++;
}

void RobotProcessTutorials::heartbeatCallback(
  boost::shared_ptr<robot_process_msgs::State const> msg)
{
  ROS_INFO_STREAM(getNamespace() << " State: " << unsigned(msg->state));
}

bool RobotProcessTutorials::serviceCallback(
  std_srvs::Empty::Request& request,
  std_srvs::Empty::Response& response)
{
  ROS_INFO_STREAM(getNamespace() << " Service called, returning true");
  return true;
}

void RobotProcessTutorials::onManagedCreate()
{
  ROS_INFO("onManagedCreate");
  /*
    C++11 lambda as Timer's callback
    context is a local variable, which is **copied** ([=]) into lambda its
    state can be changed due to **mutable** keyword
    The lambda callback has access to the class object since ([=]) captures
    **this** by reference, therefore we can access **node_namespace_**,
    which resides in RobotProcess class
  */
  int context = 0;
  robot_process::IsolatedAsyncTimer::LambdaCallback cb = [ = ]() mutable
  {
    ROS_INFO_STREAM(getNamespace() << " " << context);
    context++;
  };

  /*
    registers the previous callback in timer at 1Hz, which is stoppable
    meaning that Timer will only be fired in RUNNING state
  */
  registerIsolatedTimer(cb, 1.0, true);


  /*
    registers timer with a member function of this class as a callback,
    which is std::bind'ed or boost:bind'ed
    This timer is unstoppable
  */
  registerIsolatedTimer(
    std::bind(&RobotProcessTutorials::timerCallback, this),
    1.0,
    false);

  subscriber_manager.subscribe("/heartbeat", 1, &RobotProcessTutorials::heartbeatCallback, this);
  service_manager.advertiseService("/test", &RobotProcessTutorials::serviceCallback, this);
}

void RobotProcessTutorials::onManagedTerminate()
{
  ROS_INFO("onManagedTerminate");
};

void RobotProcessTutorials::onManagedConfigure()
{
  ROS_INFO("onManagedConfigure");
}

void RobotProcessTutorials::onManagedUnconfigure()
{
  ROS_INFO("onManagedUnconfigure");
}

void RobotProcessTutorials::onManagedStart()
{
  ROS_INFO("onManagedStart");
}

void RobotProcessTutorials::onManagedStop()
{
  ROS_INFO("onManagedStop");
}

void RobotProcessTutorials::onManagedPause()
{
  ROS_INFO("onManagedPause");
}

void RobotProcessTutorials::onManagedResume()
{
  ROS_INFO("onManagedResume");
}

}  // namespace robot_process_tutorials
