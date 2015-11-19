#ifndef _ZXDEBUG_H_
#define _ZXDEBUG_H_

//#define ON_OFF 1

#ifdef ON_OFF
#define ZXDEBUG(...)do{\
	fprintf(stdout, "FILE:%s, FUNCTION:%s, LINE:%d \n",\
	__FILE__,__FUNCTION__,__LINE__);\
}while(0);
#else
#define ZXDEBUG(...)
#endif

#endif
