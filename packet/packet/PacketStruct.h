/*
 * PacketStruct.h
 *
 *  Created on: 2015年11月13日
 *      Author: smallcroco
 */

#ifndef PACKETSTRUCT_H_
#define PACKETSTRUCT_H_

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

// 链路层帧头
struct ST_ethernet {
	u_char dhost[6];	// 目的MAC地址
	u_char shost[6];	// 源MAC地址
	u_short type;		// 802.3表示长度，以太网帧表示类型
};

// IP头
struct ST_ip {
	u_char version:4;		// ４位版本号
	u_char headerLen:4;	// ４位首部长度
	u_char tos;				// ８位服务类型
	u_char len;				// 16 位总长度
	u_short id;				// 16 位标识
	u_short flag:3;		// 3 位标志
	u_short offset:13;	// 13 位片偏移
	u_char ttl;				// 8 位生存时间
	u_char protocol;		// 8 位协议
	u_short sum;			// 16 位首部检验和
	struct in_addr ipSrc;// 32 位源IP地址
	struct in_addr ipDst;// 32 位目的地址
};

// tcp头
struct ST_tcp {
	u_short	sPort;			// 16 位源端口号
	u_short	dPort;			// 16 位目的端口号
	u_int	seq;					// 32 位序号
	u_int ack;					// 32 位确认序号
	u_short headerLen:4;		// 4 位首部长度
	u_short retain:6;			// 6 位保留
	u_short URG:1;				// 1 位URG
	u_short ACK:1;				// 1 位ACK
	u_short PSH:1;				// 1 位PSH
	u_short RST:1;				// 1 位RST
	u_short SYN:1;				// 1 位SYN
	u_short FIN:1;				// 1 位FIN
	u_short winLen;			// 16 位窗口大小
	u_short sum;				// 16 位检验和
	u_short urp;				// 16 位紧急指针
};


#endif /* PACKETSTRUCT_H_ */
