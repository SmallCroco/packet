
#ifndef _CDATAFROMNETPORT_H_
#define _CDATAFROMNETPORT_H_
#include "DataCollection.h"
#include "Comm.h"

class CDataFromNetPort:public CDataCollection
{
public:
	/*打开网口*/
	int OpenDataOrigin(const char path[]);
};

/*函数功能：打开网口
 *函数参数：path:网口名称
 *函数返回值：成功返回0， 失败返回-1
 */
inline int CDataFromNetPort::OpenDataOrigin(const char cPath[])
{
	printf("NewPort!\n");
	char cErrBuf[256];
	this->m_pHandle = pcap_open_live(cPath, 1024 * 1024, 1, 1000, cErrBuf);//打开网口
	if(NULL == this->m_pHandle)
	{
		printf("OpenDataOrigin error\n");
		return FAULT;
	}

	return TURE;
}

#endif

