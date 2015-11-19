#include "Config.h"
#include "zxDeBug.h"
#include <xmlmemory.h>
#include <parser.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LEN 128

CConfig* CConfig::pConfig = NULL;

/*类CCnofig的构造函数*/
CConfig::CConfig()
{
	this->m_cpNetPort = (char *)calloc(MAX_LEN, sizeof(char));//网口
	while(NULL == this->m_cpNetPort)
	{
		sleep(1);
		this->m_cpNetPort = (char *)calloc(MAX_LEN, sizeof(char));
	}
	
	this->m_cpFilter = (char *)calloc(2048, sizeof(char));
	while(NULL == this->m_cpFilter)
	{
		sleep(1);
		this->m_cpFilter = (char *)calloc(2048, sizeof(char));
	}
}

/*类CCnofig的析构函数*/
CConfig::~ CConfig()
{
	if(NULL != this->m_cpNetPort)
	{
		free(this->m_cpNetPort);
	}

	if(NULL != this->m_cpFilter)
	{
		free(this->m_cpFilter);
	}

	pConfig = NULL;
}

/*函数功能：读取配置文件
 *函数参数：配置文件的路径
 *函数返回值：无
 */
void CConfig::ReadConfig(const char cPath[])
{
	char szIp[MAX_LEN] = {0};
	char szProtocol[MAX_LEN] = {0};
	char szPort[MAX_LEN] = {0};
	
	xmlDocPtr Doc;
	int ret = CConfig::XmlParserFile(&Doc, cPath);//打开配置文件
	if(FAULT == ret)
	{
		cout << "open file error\n" << endl;
		return ;
	}

	xmlNodePtr Cur, Tc, Tcc;
	CConfig::GetRoot(Doc, &Cur);//获取根节点
	char cszBuf[128];

	xmlChar *key;

	ZXDEBUG();
	if(Cur != NULL)
	{
		bzero(szIp, MAX_LEN);
		bzero(szProtocol, MAX_LEN);
		bzero(szPort, MAX_LEN);
		Cur = Cur->xmlChildrenNode;//二级节点NetPort、Mainframe
		while(Cur != NULL)
		{
			ZXDEBUG();
			if((!xmlStrcmp(Cur->name, (const xmlChar *)"NetPort")))
			{
				if(0 == CConfig::GetNodeValue(Doc, Cur, &key, (char *)"NetPort"))
				{
					strcpy(this->m_cpNetPort, (const char *)key);
        			xmlFree(key);
				}
			}
			Tc = Cur->xmlChildrenNode;//三级节点Ip、协议、端口
			while(NULL != Tc)
			{
				if((!xmlStrcmp(Tc->name, (const xmlChar *)"Ip")))	//获取Ip
				{
					if(0 == CConfig::GetNodeValue(Doc, Tc, &key, (char *)"Ip"))
					{
						sprintf(szIp, "host %s", (char *)key);
	        			xmlFree(key);
					}
				}
				else if((!xmlStrcmp(Tc->name, (const xmlChar *)"Ports")))//获取端口信息
				{
					Tcc = Tc->xmlChildrenNode;
					while(NULL != Tcc)
					{
						ZXDEBUG();
						if((!xmlStrcmp(Tcc->name, (const xmlChar *)"Port")))
						{
							if(0 == CConfig::GetNodeValue(Doc, Tcc, &key, (char *)"Port"))
							{
								if('\0' == szPort[0])
								{
									sprintf(szPort, "port %s", (char *)key);
								}
								else
								{
									sprintf(cszBuf, " or %s", key);
									strcat(szPort, cszBuf);
								}
			        			xmlFree(key);
							}
						}
						
						Tcc = Tcc->next;
					}
				}
				else if((!xmlStrcmp(Tc->name, (const xmlChar *)"Protocols")))//获取协议信息
				{
					Tcc = Tc->xmlChildrenNode;
					while(NULL != Tcc)
					{
						ZXDEBUG();
						if((!xmlStrcmp(Tcc->name, (const xmlChar *)"Protocol")))
						{
							if(0 == CConfig::GetNodeValue(Doc, Tcc, &key, (char *)"Protocol"))
							{
								if('\0' == szProtocol[0])
								{
									strcpy(szProtocol, (const char *)key);
								}
								else
								{
									sprintf(cszBuf, " or %s", key);
									strcat(szProtocol, cszBuf);
								}
			        			xmlFree(key);
							}
						}
						Tcc = Tcc->next;
					}
				
				}
				Tc = Tc->next;
			}
			if((!xmlStrcmp(Cur->name, (const xmlChar *)"Mainframe")))
			{
				this->StructureFilter(szProtocol, szIp, szPort);//调用函数构造过滤器
			}
			Cur = Cur->next;
		}
		
	}
				
	xmlFreeDoc(Doc);//关闭打开的配置文件，并释放其占用的资源
	xmlCleanupParser();
}

/*函数功能：构造过滤器
 *函数参数：szProtocol:使用的协议	szIp:通信的Ip	szPort:通信的端口号
 *函数返回值：无
 */
void CConfig::StructureFilter(char szProtocol[], char szIp[], char szPort[])
{
	char szBuf[512] = {0};
	char szBuffer[512] = {0};

	strcat(szBuf, szIp);

	/*当配置文件中限制了ip和协议时，应该用and连接*/
	if(0 != szBuf[0] && 0 != szProtocol[0])
	{
		strcat(szBuf, " and ");
	}
	strcat(szBuf, szProtocol);

	/*当配置文件中限制了端口号时，并且还加上了其它限制条件时，用and连接*/
	if(0 != szBuf[0] && 0 != szPort[0])
	{
		strcat(szBuf, " and ");
	}
	strcat(szBuf, szPort);

	/*当过滤器中还没有限制时，中间不需要and连接*/
	if(0 == this->m_cpFilter[0] && 0 != szBuf[0])
	{
		sprintf(szBuffer, "(%s)", szBuf);
	}
	else if(0 != szBuf[0])
	{
		/*当过滤器字符串中已经加过限制时，应该用or连接*/
		sprintf(szBuffer, " or (%s)", szBuf);
	}

	strcat(this->m_cpFilter, szBuffer);
}

/*函数功能：获取xml节点的值
 *函数参数：doc:打开的xml文件句柄	cur:当前节点	key:用于指向存放内容的指针	name:节点名称
 *函数返回值：成功返回0 失败返回-1
 */
inline int CConfig::GetNodeValue(xmlDocPtr doc, xmlNodePtr cur, xmlChar **key, char *name)
{
	if(cur == NULL || doc == NULL)
		return FAULT;

	if ((!xmlStrcmp(cur->name, (const xmlChar *)name))){ 
		if((*key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1)) != NULL){
			return TURE;
		}
    } 

	return FAULT;
}

/*函数功能：获取xml文件的根节点的值
 *函数参数：doc:打开的xml文件句柄	pCur:节点指针
 *函数返回值：成功返回0 失败返回-1
 */
inline void CConfig::GetRoot(xmlDocPtr doc, xmlNodePtr *pCur)
{
	*pCur = xmlDocGetRootElement(doc); 
	if (pCur == NULL) 
	{ 
		fprintf(stderr,"empty document\n");
		return; 
	}   
}

/*函数功能：打开xml文件
 *函数参数：doc:打开xml文件存放的句柄 	cPath:文件路径
 *函数返回值：成功返回0 失败返回-1
 */
inline int CConfig::XmlParserFile(xmlDocPtr *doc, const char cPath[])
{
	LIBXML_TEST_VERSION
	xmlKeepBlanksDefault(0);
	
	*doc = xmlParseFile(cPath); 
	if (*doc == NULL ) { 
		fprintf(stderr,"Document not parsed successfully. \n"); 
		return FAULT; 
	}
	return TURE;
}

/*函数功能：创建一个唯一的对象
 *函数参数：无
 *函数返回值：成功返回一个对象 失败返回NULL
 */
CConfig* CConfig::CreateObject()
{
	if(NULL == pConfig)
	{
		pConfig = new CConfig();
		return pConfig;
	}
	return NULL;
}

/*函数功能：获取网口信息
 *函数参数：无
 *函数返回值：网口信息的指针
 */
char *CConfig::GetNetPort()
{
	return this->m_cpNetPort;
}

/*函数功能：获取过滤器信息
 *函数参数：无
 *函数返回值：过滤器信息的指针
 */
char *CConfig::GetFilter()
{
	return this->m_cpFilter;
}
