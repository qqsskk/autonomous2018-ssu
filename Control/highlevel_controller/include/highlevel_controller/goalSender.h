#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_broadcaster.h>
#include <string>
#include "HybridAutomata.h"

class GoalSender{
private:
    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
public:
    /*
        STATE_PENDING : no goal is set.
        STATE_ACTIVE : not reached to the current goal.
        STATE_SUCCEEDED : reached the current goal
    */
    enum class GoalStates : int {STATE_SUCCEEDED, STATE_PENDING, STATE_ACTIVE,
                                STATE_LOST, STATE_PREEMPTED, STATE_ABORTED};
public:
    
    GoalStates getState();
    void sendGoal();
    void setGoal(double x, double y, double ori_x, double ori_w, std::string goal_type);

    //teb_local_planner fails to planning when current speed suddenly decrease.
    //then we must set the goal one more, so we decided to use the default thread.
    //it sends the goal to the server periodically
    void auto_goal_sender();

    //singletone
public:
    static GoalSender* getInstancePtr();
private:
    GoalSender();
    static GoalSender* objptr;

    //members
private:
    MoveBaseClient ac;
    move_base_msgs::MoveBaseGoal goal;
    std::string goal_type;
};