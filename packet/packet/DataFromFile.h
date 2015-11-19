#ifndef _DATAFROMFILE_H_
#define _DATAFROMFILE_H_


#include <pcap/pcap.h>
#include "Data.h"
#include "Comm.h"


class CDataFromFile:public CData
{
public:

	/*打开文件*/
	int OpenDataOrigin(const char path[]);
};


/*函数功能：打开文件
 *函数参数：path:文件路径
 *函数返回值：成功返回0， 失败返回-1
 */
inline int CDataFromFile::OpenDataOrigin(const char path[])
{
	printf("File!\n");
	char ebuf[256];
	this->m_pHandle = pcap_open_offline(path, ebuf);						// 打开文件
	if(NULL == this->m_pHandle)
	{
		return FAULT;
	}

	return TURE;
}

#endif
