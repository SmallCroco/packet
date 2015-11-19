/*
 * CAnalyzePacket.cpp
 *
 *  Created on: 2015年11月16日
 *      Author: smallcroco
 */

#include "CAnalyzePacket.h"
#include "CPacket.h"
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

////

CAnalyzePacket::CAnalyzePacket() {

}

CAnalyzePacket::~CAnalyzePacket() {

}

void CAnalyzePacket::analyze(u_char* user, const pcap_pkthdr* pcap_head, const u_char* packetContent) {

	CPacket* packet = new CPacket();

	// 以太网头
	struct ST_ethernet* ethernet = NULL;

	// ip包头
	struct ST_ip* ip = NULL;

	// tcp包头
	struct ST_tcp* tcp = NULL;

	// 数据包负载的数据
	const u_char* payload = NULL;

	// 数据包负载的数据大小
	int pay_size = 0;

	ethernet = (struct ST_ethernet*)(packetContent);

	ip = (struct ST_ip*)(packetContent + sizeof(struct ST_ethernet));

	tcp = (struct ST_tcp*)(packetContent + sizeof(struct ST_ethernet) + sizeof(struct ST_ip));

	payload = (u_char*)(packetContent + sizeof(struct ST_ethernet) + sizeof(struct ST_ip) + sizeof(struct ST_tcp));

	pay_size = ntohs(ip->len) - ntohs(ip->headerLen) - (tcp->headerLen);

	packet->setEthernet(ethernet);
	packet->setIp(ip);
	packet->setTcp(tcp);
	packet->setPacketData(payload, pay_size);

	printf("链路层\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("源地址:%x:%x:%x:%x:%x:%x\n",
			(ethernet->shost)[0],
			(ethernet->shost)[1],
			(ethernet->shost)[2],
			(ethernet->shost)[3],
			(ethernet->shost)[4],
			(ethernet->shost)[5]);

	printf("目的地址:%x:%x:%x:%x:%x:%x\n",
			(ethernet->dhost)[0],
			(ethernet->dhost)[1],
			(ethernet->dhost)[2],
			(ethernet->dhost)[3],
			(ethernet->dhost)[4],
			(ethernet->dhost)[5]);

	printf("帧类型：%d\n\n\n", ethernet->type);

	printf("网络层\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("源IP地址 : %s\n", inet_ntoa(ip->ipSrc));
	printf("目的IP地址 : %s\n", inet_ntoa(ip->ipDst));

	printf("运输层\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("源端口:%d\n", ntohs(tcp->sPort));
	printf("目的端口：%d\n", ntohs(tcp->dPort));

	delete packet;
}

