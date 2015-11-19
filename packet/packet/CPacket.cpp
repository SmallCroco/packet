/*
 * CAnalyzePacket.cpp
 *
 *  Created on: 2015年11月13日
 *      Author: smallcroco
 */

#include "CPacket.h"

#include <iostream>
#include <string.h>

using namespace std;

/*
 * @Function Name	: CAnalyzePacket
 * @Description	: 构造函数
 */
CPacket::CPacket() {

	this->m_pstEthernet = NULL;
	this->m_pstIp = NULL;
	this->m_pstTcp = NULL;
	this->m_pszPacketData = NULL;
	this->m_iPacketDataLen = 0;
}

/*
 * @Function Name	: ~CAnalyzePacket
 * @Description	: 析构函数
 */
CPacket::~CPacket() {

	if (NULL != m_pstEthernet) {
		delete m_pstEthernet;
	}

	if (NULL != m_pstIp) {
		delete m_pstIp;
	}

	if (NULL != m_pstTcp) {
		delete m_pstTcp;
	}

	if (NULL != m_pszPacketData) {
		delete[] m_pszPacketData;
	}

	m_iPacketDataLen = 0;
}

/*
 * @Function Name	: setEthernet
 * @Parameter [in] const ST_ethernet* : pstEthernet --- 链路层帧头
 * @Description		: 设置链路层帧头
 */
void CPacket::setEthernet(const ST_ethernet* pstEthernet) {

	if (NULL != pstEthernet) {
		this->m_pstEthernet = new ST_ethernet();

		memset(m_pstEthernet->dhost, 0, sizeof(u_char)*6);
		memset(m_pstEthernet->shost, 0, sizeof(u_char)*6);

		memcpy(m_pstEthernet->dhost, pstEthernet->dhost, sizeof(u_char)*6);
		memcpy(m_pstEthernet->shost, pstEthernet->shost, sizeof(u_char)*6);
		m_pstEthernet->type = pstEthernet->type;
	}
}

/*
 * @Function Name	: getEthernet
 * @Description		: 获取链路层帧头
 * @Return Value	: 返回帧头部结构
 */
const ST_ethernet* CPacket::getEthernet() {

	return this->m_pstEthernet;
}

/*
 * @Function Name	: setIp
 * @Parameter [in] const ST_ip* : pstIp --- IP包头部
 * @Description	: 设置IP包头部
 */
void CPacket::setIp(const ST_ip* pstIp) {

	if (NULL != pstIp) {
		this->m_pstIp = new ST_ip();
		m_pstIp->flag = pstIp->flag;
		m_pstIp->headerLen = pstIp->headerLen;
		m_pstIp->id = pstIp->id;
		m_pstIp->ipDst = pstIp->ipDst;
		m_pstIp->ipSrc = pstIp->ipSrc;
		m_pstIp->len = pstIp->len;
		m_pstIp->offset = pstIp->offset;
		m_pstIp->protocol = pstIp->protocol;
		m_pstIp->sum = pstIp->sum;
		m_pstIp->tos = pstIp->tos;
		m_pstIp->ttl = pstIp->ttl;
		m_pstIp->version = pstIp->version;
	}
}

/*
 * @Function Name	: getIp
 * @Description	: 获取IP包头部结构
 * @Return Value	: IP包头部结构
 */
const ST_ip* CPacket::getIp() {
	return this->m_pstIp;
}

/*
 * @Function Name : setTcp
 * @Parameter [in] const ST_tcp* : pstTcp ---
 * @Description	: 设置Tcp头部
 */
void CPacket::setTcp(const ST_tcp* pstTcp) {
	if (NULL != pstTcp) {
		this->m_pstTcp = new ST_tcp();

		m_pstTcp->ACK = pstTcp->ACK;
		m_pstTcp->FIN = pstTcp->FIN;
		m_pstTcp->PSH = pstTcp->PSH;
		m_pstTcp->RST = pstTcp->RST;
		m_pstTcp->SYN = pstTcp->SYN;
		m_pstTcp->URG = pstTcp->URG;
		m_pstTcp->ack = pstTcp->ack;
		m_pstTcp->dPort = pstTcp->dPort;
		m_pstTcp->headerLen = pstTcp->headerLen;
		m_pstTcp->retain = pstTcp->retain;
		m_pstTcp->sPort = pstTcp->sPort;
		m_pstTcp->seq = pstTcp->seq;
		m_pstTcp->sum = pstTcp->sum;
		m_pstTcp->urp = pstTcp->urp;
		m_pstTcp->winLen = pstTcp->winLen;
	}
}

/*
 * @Function Name	: getTcp
 * @Description	: 获取Tcp头部
 * @Return Value	: Tcp头部结构
 */
const ST_tcp* CPacket::getTcp() {
	return this->m_pstTcp;
}

/*
 * @Function Name	: setPacketData
 * @Parameter [in] const u_char* : pszPacketData --- 数据包内容
 * @Parameter [in] const int : iPacketDataLen --- 数据包内容长度
 * @Description	: 设置网络负载的实际内容和内容长度
 */
void CPacket::setPacketData(const u_char* pszPacketData, const int iPacketDataLen) {

	if (NULL != pszPacketData && iPacketDataLen > 0) {
		m_pszPacketData = new u_char[iPacketDataLen + 1];
		memset(m_pszPacketData, 0, sizeof(char)*(iPacketDataLen + 1));
		memcpy(m_pszPacketData, pszPacketData, iPacketDataLen);

		m_iPacketDataLen = iPacketDataLen;
	}
}

/*
 * @Function Name	: getPacketData
 * @Description	: 获取数据包内容
 * @Return Value	: 数据包内容
 */
const u_char* CPacket::getPacketData() {
	return this->m_pszPacketData;
}

/*
 * @Function Name	: getPacketDataLen
 * @Description 	: 获取数据包内容长度
 * @Return Value	: 数据包内容长度
 */
const int CPacket::getPacketDataLen() {
	return this->m_iPacketDataLen;
}
