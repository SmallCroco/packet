/*
 * CAnalyzePacket.h
 *
 *  Created on: 2015年11月13日
 *      Author: smallcroco
 *      Dscription:	网络包分析类
 */

#ifndef CPACKET_H_
#define CPACKET_H_

#include "PacketStruct.h"

class CPacket {
public:
	// 构造函数
	CPacket();

	// 析构函数
	~CPacket();

	void setEthernet(const ST_ethernet* pstEthernet);
	const ST_ethernet* getEthernet();

	void setIp(const ST_ip* pstIp);
	const ST_ip* getIp();

	void setTcp(const ST_tcp* pstTcp);
	const ST_tcp* getTcp();

	void setPacketData(const u_char* pszPacketData, const int iPacketDataLen);
	const u_char* getPacketData();
	const int getPacketDataLen();

private:
	ST_ethernet* 	m_pstEthernet;				// 链路层帧头
	ST_ip* 		 	m_pstIp;						// IP头
	ST_tcp*			m_pstTcp;					// TCP头
	u_char* 			m_pszPacketData;			// 包内容
	int				m_iPacketDataLen;			// 包内容长度
};

#endif /* CPACKET_H_ */
