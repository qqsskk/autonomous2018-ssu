#include <ros/ros.h>
#include <serial/serial.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <deque>


#define TX_PACKET_LENGTH 14
#define ACKERMANN_TOPIC_NAME "platform_tx_test"

//#define TX_DEBUG
//#define RX_SUBSCRIBE

static double angleToSerialValue;
static double maxSteeringAngle;
static double minSteeringAngle;
static int alignmentBias;

static double maxSpeed;//m/s
static double m_s2serial;

static int frequency;

uint8_t packet[TX_PACKET_LENGTH] = {};

//serial
serial::Serial *ser;

void initTx(const ros::NodeHandle& nh){
    packet[0] = static_cast<uint8_t>(0x53);
    packet[1] = static_cast<uint8_t>(0x54);
    packet[2] = static_cast<uint8_t>(0x58);
    //manual OR auto. 0x00 - manual/0x01 - auto
    packet[3] = static_cast<uint8_t>(0x01);
    //estop. 0x00 - off/0x01 - on
    packet[4] = static_cast<uint8_t>(0x00);

    packet[12] = static_cast<uint8_t>(0x0D);//0x0D
    packet[13] = static_cast<uint8_t>(0x0A);//0x0A

    //steering member
    nh.param("/platform_tx/angleToSerialValue", angleToSerialValue, 71.0);
    nh.param("/platform_tx/maxSteeringAngle", maxSteeringAngle, 24.0);
    nh.param("/platform_tx/minSteeringAngle", minSteeringAngle, -24.0);
    nh.param("/platform_tx/alignmentBias", alignmentBias, 160);

    //speed member
    nh.param("/platform_tx/maxSpeed", maxSpeed, 10.0);
    nh.param("/platform_tx/m_s2serial", m_s2serial, 36.0);

    //frequency
    nh.param("/platform_tx/frequency", frequency, 50);
}

//rx log variable
#ifdef RX_SUBSCRIBE
#include "platform_rx_msg/platform_rx_msg.h"
std::deque<platform_rx_msg::platform_rx_msg> rxMsgdeq(10);
//for pid. I'm not sure but maybe this will be needed in the future
void rxMsgCallBack(const platform_rx_msg::platform_rx_msg::ConstPtr& msg){
    platform_rx_msg::platform_rx_msg temp;
    temp.speed = msg->steer;
    temp.steer = msg->steer;
    temp.brake = msg->brake;
    rxMsgdeq.push_front(temp);
    rxMsgdeq.pop_back();
    ROS_INFO("rxMsgSubscribing Done!");
}
#endif

inline void checkSpeedBound(double& speed){
    speed = (speed <= maxSpeed) ? speed : maxSpeed;
    return;
}

inline void checkBrakeBound(double& brake_percent){
    brake_percent = (brake_percent <= 100) ? brake_percent : 100;
}

inline void checkSteeringBound(double& steeringAngle){
    if(steeringAngle > maxSteeringAngle)
        steeringAngle = maxSteeringAngle;
    else if(steeringAngle < minSteeringAngle)
        steeringAngle = minSteeringAngle;
}

void createSerialPacket(const ackermann_msgs::AckermannDriveStamped::ConstPtr& msg){
    static uint8_t alive = 0;
    /*  gear
        0x00 : forward
        0x01 : neutral
        0x02 : backward
    */
    packet[5] = (msg->drive.speed >= 0) ?
         static_cast<uint8_t>(0x00) : static_cast<uint8_t>(0x02);

//  //speed. should put value (KPH * 10);
    //1 m/s = 3.6 kph
    double speed = abs(msg->drive.speed);
    checkSpeedBound(speed);
    uint16_t serialSpeed = speed * m_s2serial;
    *(uint16_t*)(packet + 7) = static_cast<uint16_t>(serialSpeed);
    
//  //steer. should put value (actual steering degree * 71)
    double angle = -msg->drive.steering_angle;
    checkSteeringBound(angle);
    int16_t serialSteeringAngle = angle * angleToSerialValue + alignmentBias;
    *(int8_t*)(packet + 8) = *((int8_t*)(&serialSteeringAngle) + 1);
    *(int8_t*)(packet + 9) = *(int8_t*)(&serialSteeringAngle);
    
//  //brake. low number is low braking. 1 ~ 200
    packet[10] = static_cast<uint8_t>(1);
    //checkBrakeBound()

    packet[11] = static_cast<uint8_t>(alive);//alive
    alive = (alive + 1) % 256;
}

void ackermannCallBack_(const ackermann_msgs::AckermannDriveStamped::ConstPtr& msg){
    createSerialPacket(msg);
    ser->write(packet,TX_PACKET_LENGTH);
}

int main(int argc, char *argv[]){
    if(argc < 2){
        ROS_ERROR("give me [path]");
        return -1;
    }
    ros::init(argc, argv, "platform_tx");
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe(ACKERMANN_TOPIC_NAME, 100, &ackermannCallBack_);
    
    initTx(nh);

    //open serial
    ser = new serial::Serial();
    ser->setPort(argv[1]);
    ser->setBaudrate(115200);
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    ser->setTimeout(to);
    ser->open();
    if(!ser->isOpen()) throw serial::IOException("ser.isOpen() error!",__LINE__,"ser.isOpen() error!");
    ROS_INFO("serial setting done");

    ros::Rate loop_rate(frequency);
#ifndef TX_DEBUG
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
#else
    //5hz->9.75
    //10hz->9.95
    //15hz->9.56
    //20hz->9.68
    //50hz->9.02
    while(true){
        ackermann_msgs::AckermannDriveStamped::ConstPtr msg;
        createSerialPacket(msg);
        ser->write(packet, TX_PACKET_LENGTH);
        for(int i = 0 ; i < TX_PACKET_LENGTH;++i)
            ROS_INFO("[%d] : %#x",i,packet[i]);
        loop_rate.sleep();
    }
#endif
}