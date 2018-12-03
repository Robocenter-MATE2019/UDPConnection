#pragma once

#include <Ethernet.h>
#include <SPI.h>
#include "Timer.h"

#define SELF_IP 192, 168, 1, 11
#define REMOTE_IP 192, 168, 1, 10
#define SELF_PORT 3020
#define REMOTE_PORT 3010
#define MAC 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED

struct input_packet
{
	int8_t axisX = 0; //! -100/100;    
	int8_t axisY = 0; //! -100/100;    
	int8_t axisZ = 0; //! -100/100;    
	int8_t axisW = 0; //! -100/100;
	int8_t cameraRotation[2] = { 0, 0 };
	//int8_t thrusterPower[6] = { 0, 0, 0, 0, 0, 0 };
	uint8_t debugFlag = 0;
	int8_t manipulatorRotation = 0; //! -100/100    
	int8_t manipulatorOpenClose = 0; //! -1 close/+1 open;
	uint8_t regulators = 0; //! 1st bit - depth;
	float desiredDepth = 0.0f;
};

struct output_packet
{
	float depth = 0.0f;
	float pitch = 0; //! -180/180;    
	float yaw = 0; //! 0 - 360;    
	float roll = 0; //! -180/180;
	float ammeter = 0.0f;
	float voltmeter = 0.0f;
	uint8_t regulatorsFeedback = 0;
	int8_t manipulatorAngle = 0; //! -100/100
	int8_t manipulatorState = 0; //! -1 close/+1 open;
};

class UDPConnection
{
public:
	UDPConnection();
	void init();
	void receivePacket();
	void sendPacket();
private:
	EthernetUDP m_udp;
	IPAddress m_self_ip;
	IPAddress m_remote_ip;
	uint16_t m_self_port;
	uint16_t m_remote_port;
	byte m_mac[6] = { MAC };
	Timer m_timer;
};
