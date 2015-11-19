#include "Comm.h"
#include "DataFromFile.h"
#include "DataFromNetPort.h"
#include "CAnalyzePacket.h"
#include "Config.h"
#include <stdint.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "DataCollection.h"

#define READ_FILE 2

int main(int argc, char *argv[])
{
	
	CConfig *con = CConfig::CreateObject();
	con->ReadConfig("/root/zhangxin/workspace/packet/packet/packet/config.xml");//读取配置文件
	char *cpFilter = con->GetFilter();
	char *cpNetPort = con->GetNetPort();
	
	CDataCollection *p = NULL;
	char *cpPath;
	
	if(READ_FILE == argc)//如果输入的是两个参数，则默认以文件方式打开
	{
		p = new CDataFromFile();
		cpPath = argv[1];
	}
	else//以网口方式打开
	{
		p = new CDataFromNetPort();
		cpPath = cpNetPort;
	}

	cout << cpFilter << endl;
	p->SetCall(CAnalyzePacket::analyze);

	p->Analyze((const char *)cpPath, cpFilter);
	
	delete p;
	delete con;
	
	return 0;
}
