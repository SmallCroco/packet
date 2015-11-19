#include "DataCollection.h"

/*类CDataCollection的构造函数*/
CDataCollection::CDataCollection()
{
	this->m_pHandle = NULL;
	this->pPcapHandler = NULL;
}

/*函数功能：构造一个过滤器
 *函数参数：设置过滤器使用的字符串
 *函数返回值：成功返回0， 失败返回-1
 */
inline int CDataCollection::GetFilter(const char FiltratorStr[])
{
	int ret = pcap_compile(this->m_pHandle, &(this->m_bpf), FiltratorStr, 1, 0);//构造过滤器
	if(-1 == ret)
	{
		return FAULT;
	}
	
	return TURE;
}

/*函数功能：设置过滤器过滤器
 *函数参数：无
 *函数返回值：成功返回0， 失败返回-1
 */
inline int CDataCollection::SetFilter()
{
	int ret = pcap_setfilter(this->m_pHandle, &(this->m_bpf));				//设置过滤器
	if(ret < 0)
	{
		return FAULT;
	}

	return TURE;
}

/*函数功能：关闭文件
 *函数参数：无
 *函数返回值：无
 */
inline void CDataCollection::CloseDataOrigin()
{
	pcap_close(this->m_pHandle);		//关闭文件
}


/*函数功能：数据采集
 *函数参数：无
 *函数返回值：无
 */
void CDataCollection::DataCollection()
{
	if(NULL == this->pPcapHandler)
	{
		return ;
	}
	pcap_loop(this->m_pHandle, -1, this->pPcapHandler, NULL);
}


/*函数功能：数据采集模块的接口函数
 *函数参数：path:数据来源	FiltratorStr:过滤器字符串
 *函数返回值：成功该函数不会返回  失败或者结束数据采集返回-1
 */
int CDataCollection::Analyze(const char path[], const char FiltratorStr[])
{
	int iRet = this->OpenDataOrigin(path);	//打开数据源
	if(FAULT == iRet)
	{
		printf("OpenDataOrigin error!\n");
		return FAULT;
	}

	iRet = this->GetFilter((char *)FiltratorStr);	//构造过滤器
	if(FAULT == iRet)
	{
		printf("GetFilter error\n");
		return FAULT;
	}

	iRet = this->SetFilter();		//设置过滤器
	if(FAULT == iRet)
	{
		printf("SetFilter error \n");
		return FAULT;
	}

	printf("start---------------------------------------\n");
	this->DataCollection();//开始采集数据，该函数只有在采集出错才会返回

	this->CloseDataOrigin();//采集出错，关闭数据源，并释放相应资源

	return FAULT;
}

