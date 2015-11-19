#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <xmlmemory.h>
#include <parser.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Comm.h"

class CConfig
{
public:
	~CConfig();

	/*创建一个对象*/
	static CConfig* CreateObject();

	/*读取文件*/
	void ReadConfig(const char * path);

	/*获取网口信息指针*/
	char *GetNetPort();

	/*获取过滤器信息指针*/
	char *GetFilter();
private:

	/*这里使用了单例模式，因此构造函数声明为私有的*/
	CConfig();

	/*构造过滤器字符串*/
	void StructureFilter(char szProtocol[], char szIp[], char szPort[]);
	
	/*获取节点的值*/
	static int GetNodeValue(xmlDocPtr doc, xmlNodePtr cur, 
		xmlChar **key, char *name);
	
	/*获取跟节点*/
	static void GetRoot(xmlDocPtr doc, xmlNodePtr *cur);
	
	/*打开配置文件*/
	static int XmlParserFile(xmlDocPtr *doc, const char *fileName);

private:

	/*创建对象的指针，在创建时将为其赋值*/
	static CConfig *pConfig;

	/*网口信息*/
	char *m_cpNetPort;

	/*过滤器信息*/
	char *m_cpFilter;
};


#endif
