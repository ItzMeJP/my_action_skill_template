
/**\file my_action_skill_server.cpp
 * \brief File with my_action_skill_server class definition
 *
 * @version 1.0
 * @author João Pedro Carvalho de Souza
 */

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <my_action_skill_server/my_action_skill_server.h>

namespace my_action_skill {

    MyActionSkill::MyActionSkill (){}

    MyActionSkill::~MyActionSkill (){}

    void MyActionSkill::start() {

        actionServer_ = std::make_shared<MyActionSkillActionServer>(*node_handle_, action_server_name_,
                                                                          boost::bind(&MyActionSkill::executeCB,
                                                                                      this, _1));
        actionServer_->start();
    }

    void MyActionSkill::executeCB (const my_action_skill_msgs::MyActionSkillGoalConstPtr &goal) {
        executeProcess()?setSucceeded():setAborted();
    }

    void MyActionSkill::setSucceeded (std::string outcome) {
        result_.percentage  = 100;
        result_.skillStatus = action_server_name_;
        result_.skillStatus += ": Succeeded";
        result_.outcome     = outcome;
        ROS_INFO_STREAM(action_server_name_ << ": Succeeded");
        actionServer_->setSucceeded(result_);
    }
    void MyActionSkill::setAborted (std::string outcome) {
        result_.percentage  = 0;
        result_.skillStatus = action_server_name_;
        result_.skillStatus += ": Aborted";
        result_.outcome     = outcome;
        ROS_INFO_STREAM(action_server_name_ << ": Aborted");
        actionServer_->setAborted(result_);
    }
    void MyActionSkill::feedback (float percentage) {
        feedback_.percentage  = percentage;
        feedback_.skillStatus = action_server_name_;
        feedback_.skillStatus += " Executing";
        ROS_INFO_STREAM(action_server_name_ << ": Executing. Percentage" << percentage);
        actionServer_->publishFeedback(feedback_);
    }
    bool MyActionSkill::checkPreemption () {
        if (actionServer_->isPreemptRequested() || !ros::ok()) {
            result_.percentage  = 0;
            result_.skillStatus = action_server_name_;
            result_.skillStatus += ": Preempted";
            result_.outcome     = "preempted";
            ROS_INFO_STREAM(action_server_name_ << ": Preempted");
            actionServer_->setPreempted(result_);
            return true;
        } else {
            return false;
        }
    }

    bool MyActionSkill::setupSkillConfigurationFromParameterServer(ros::NodeHandlePtr &_node_handle,
                                                                   ros::NodeHandlePtr &_private_node_handle){
        this->node_handle_ = _node_handle;
        this->private_node_handle_ = _private_node_handle;
        private_node_handle_->param<std::string>("action_server_name", action_server_name_, "MyActionSkill");
        return true;

    }
    bool MyActionSkill::executeProcess()
    {
        //start he procedure after goal acquisition
        return true;
    }

    void MyActionSkill::publisher()
    {
        pub_ = private_node_handle_->advertise<std_msgs::String>("my_pub_topic", 100);
        pub_.publish("data");
    }

}
