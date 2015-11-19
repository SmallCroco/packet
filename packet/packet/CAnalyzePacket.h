/*
 * CAnalyzePacket.h
 *
 *  Created on: 2015年11月16日
 *      Author: smallcroco
 *      Description: 包数据分析类
 */

#ifndef CANALYZEPACKET_H_
#define CANALYZEPACKET_H_

#include <pcap.h>

class CAnalyzePacket {
public:
	// 构造函数
	CAnalyzePacket();

	// 析构函数
	~CAnalyzePacket();

	// 数据包分析
	static void analyze(u_char* user, const struct pcap_pkthdr* pcap_head, const u_char* packet);
};

#endif /* CANALYZEPACKET_H_ */
