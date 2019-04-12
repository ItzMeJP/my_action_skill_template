
/**\file my_action_skill_server.h
 * \brief File with my_action_skill class definition
 *
 * @version 1.0
 * @author João Pedro Carvalho de Souza
 */

#ifndef MY_ACTION_SKILL_SERVER
#define MY_ACTION_SKILL_SERVER

#pragma once

// ROS includes
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <my_action_skill_msgs/MyActionSkillAction.h>

// Std includes
//...

namespace my_action_skill {
    class MyActionSkill {
    public:
        typedef actionlib::SimpleActionServer<my_action_skill_msgs::MyActionSkillAction> MyActionSkillActionServer;

        MyActionSkill ();

        ~MyActionSkill (void);

        void start(); //start the server
        void executeCB (const my_action_skill_msgs::MyActionSkillGoalConstPtr &goal); // recognize the goal request
        bool executeProcess(); // execute the procedure after the goal request
        void feedback (float percentage);
        void setSucceeded (std::string outcome = "succeeded");
        void setAborted (std::string outcome = "aborted");
        bool checkPreemption ();

        bool setupSkillConfigurationFromParameterServer(ros::NodeHandlePtr &_node_handle,
                                                        ros::NodeHandlePtr &_private_node_handle);


    protected:

        ros::NodeHandlePtr node_handle_;
        ros::NodeHandlePtr private_node_handle_;

        std::shared_ptr<MyActionSkillActionServer>                               actionServer_; // to not init it in the constructor
        std::string                                                              action_server_name_;
        my_action_skill_msgs::MyActionSkillFeedback                              feedback_;
        my_action_skill_msgs::MyActionSkillResult                                result_;



    };
}
#endif // MY_ACTION_SKILL_SERVER
