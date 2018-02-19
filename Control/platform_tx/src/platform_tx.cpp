#include <ros/ros.h>
#include <serial/serial.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include "platform_rx_msg/platform_rx_msg.h"
#include <deque>


#define TX_PACKET_LENGTH 14
#define ackermannTopicName "whereeeeeeee"

//rx log variable
std::deque<platform_rx_msg::platform_rx_msg> rxMsgdeq(10);

//serial
serial::Serial *ser;
uint8_t packet[TX_PACKET_LENGTH] = {};

void createSerialPacket(const ackermann_msgs::AckermannDriveStamped::ConstPtr& msg){
    static uint8_t alive = 0;
    packet[0] = static_cast<uint8_t>(0x53);
    packet[1] = static_cast<uint8_t>(0x54);
    packet[2] = static_cast<uint8_t>(0x58);
    //manual OR auto. 0x00 - manual/0x01 - auto
    packet[3] = static_cast<uint8_t>(0x1);
    //estop ON. 0x01 - off/0x00 - on
    packet[4] = static_cast<uint8_t>(0x00);
    
    /*  gear
        0x00 : forward
        0x01 : neutral
        0x02 : backward
    */
    if(msg->drive.speed >= 0 )
        packet[5] = static_cast<uint8_t>(0x00);
    else packet[5] = static_cast<uint8_t>(0x02);

//  //speed. should put value (KPH * 10);
    //1 m/s = 3.6 kph
    uint16_t serialSpeed = msg->drive.speed * 3.6 * 10;
    *(uint16_t*)(packet + 6) = static_cast<uint16_t>(serialSpeed);

//  //steer. should put value (actual steering degree * 71)
    uint16_t serialSteeringAngle = msg->drive.steering_angle * 71;
    *(uint16_t*)(packet + 8) = static_cast<uint16_t>(serialSteeringAngle * 71);

//  //brake. low number is low braking. 1 ~ 33
    packet[10] = static_cast<uint8_t>(0x01);

    alive = (alive + 1) % 256;
    packet[11] = static_cast<uint8_t>(alive);//alive
    packet[12] = static_cast<uint8_t>(0x0D);//0x0D
    packet[13] = static_cast<uint8_t>(0x0A);//0x0A
}
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

void ackermannCallBack_(const ackermann_msgs::AckermannDriveStamped::ConstPtr& msg){
    createSerialPacket(msg);
    ser->write(packet,TX_PACKET_LENGTH);
}

int main(int argc, char *argv[]){
    ros::init(argc, argv, "platform_tx");
    ros::NodeHandle nh;

    //subscribe rx msg
    ros::Subscriber sub = nh.subscribe(ackermannTopicName, 100, &ackermannCallBack_);

    //open serial
    serial::Serial *ser = new serial::Serial();
    ser->setPort(argv[1]);
    ser->setBaudrate(115200);
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    ser->setTimeout(to);
    ser->open();
    if(!ser->isOpen()) throw serial::IOException("ser.isOpen() error!",__LINE__,"ser.isOpen() error!");

    //ros::spin();
    
    //for tx debuging
    ros::Rate loop_rate(10);
    while(true){
        ackermann_msgs::AckermannDriveStamped::ConstPtr msg;
        createSerialPacket(msg);
        ser->write(packet, TX_PACKET_LENGTH);    
        loop_rate.sleep();
    }
}