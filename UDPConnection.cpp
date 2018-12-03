#include "UDPConnection.h"

UDPConnection::UDPConnection() :
	m_self_ip(SELF_IP),
	m_remote_ip(REMOTE_IP),
	m_self_port(SELF_PORT),
	m_remote_port(REMOTE_PORT)
{}

void UDPConnection::init()
{
	Ethernet.init(10);
	Ethernet.begin(m_mac, m_self_ip);
	m_udp.begin(m_self_port);
	delay(100);
	m_timer.start();
}

void UDPConnection::receivePacket()
{
	if (m_udp.parsePacket())
	{
		input_packet packet;
		char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
		m_udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
		memcpy(&packet, packetBuffer, sizeof(packetBuffer));
		Serial.println("Packet recieved");
	}
}

void UDPConnection::sendPacket()
{
	if (m_timer.elapsed() < 250)
	{
		output_packet packet;
		m_udp.beginPacket(m_udp.remoteIP(), m_udp.remotePort());
		m_udp.write((byte*)&packet, sizeof(packet));
		m_udp.endPacket();
		m_timer.start();
	}
}

