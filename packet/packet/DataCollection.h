#ifndef _DATA_H_
#define _DATA_H_

#include "Comm.h"
#include <pcap/pcap.h>

/*回调函数类型*/
typedef void (*pPcapHandler_t)(u_char *, const struct pcap_pkthdr *, const u_char *);

class CDataCollection
{
public:
	/*构造函数*/
	CDataCollection();

	/*虚析构函数*/
	virtual ~CDataCollection(){};

	/*打开数据源，这里定义为一个纯虚函数，该函数将在其子类中实现*/
	virtual int OpenDataOrigin(const char path[]) = 0;	

	/*关闭数据源，并释放占用的资源*/
	void CloseDataOrigin();	

	/*构造一个过滤器*/
	int GetFilter(const char FiltratorStr[]);

	/*使用构造好的过滤器来设置程序中的过滤器*/
	int SetFilter();

	/*收集数据*/
	void DataCollection();
	
	/*设置回调函数*/
	void SetCall(pPcapHandler_t pCall);

	/*所有的设置都在这个函数里面*/
	int Analyze(const char path[], const char FiltratorStr[]);
	
protected:

	/*网口*/
	pcap_t *m_pHandle;

	/*过滤器结构体*/
	bpf_program m_bpf;

	/*解析使用的回调函数指针*/
	pPcapHandler_t pPcapHandler;
};

/*函数功能：设置回调函数
 *函数参数：想要使用的回调函数
 *函数返回值：无
 */
inline void CDataCollection::SetCall(pPcapHandler_t pCall)
{
	this->pPcapHandler = pCall;
}



#endif
