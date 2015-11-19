/*
 * CQueue.h
 *
 *  Created on: 2015年11月19日
 *      Author: smallcroco
 *      Description: 队列类
 */

#ifndef CQUEUE_H_
#define CQUEUE_H_

#include <iostream>
#include <cstdlib>

using namespace std;

struct ST_PacketData {
	int len;
	char* data;
};

class CQueue {
public:
	CQueue();
	~CQueue();

private:
	ST_PacketData*	m_pstFront;		// 队列头
	ST_PacketData*	m_pstRear;		// 队列尾
};

#endif /* CQUEUE_H_ */
