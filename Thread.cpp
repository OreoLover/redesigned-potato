*/
// connless.cpp : 从客户机收到数据后，回传一个ACK字符串.
//
#include "stdafx.h"
#include <winsock.h>
#include "mystruct.h"
#include "ui.h"

#pragma comment(lib,"wsock32.lib")

void exec_command(char * buf);

DWORD WINAPI child_thread( LPVOID lpParam );
void thread_test_insert_table(thread_command_t * pdu);
void thread_test_delete_table(thread_command_t * pdu);

//HANDLE hSemaphore;

/*******************************************************************************************
** Function name: thread_main()
** Descriptions	:	在多线程操作测试中，线程主体控制流程，启动，执行命令，
** Input:	
**          char *buf; 需要解析的命令报文
** Output:  NONE
**   return:  类型：void
*******************************************************************************************/
DWORD WINAPI thread_main( LPVOID lpParam ) 
{
	SOCKET s;
	sockaddr_in local;
	sockaddr_in remote;
	int len;
	char* buf;
	int retval;
	timeval timeout;
	fd_set readfds;
	WSAData wsa;
	unsigned long arg;
    DWORD dwThreadId, dwThrdParam; 
    HANDLE hThread; 

	WSAStartup(0x101,&wsa);
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s == INVALID_SOCKET){
		AddReport("实验者主线程因套接字创建错误，已停止");
		return 0;
	}
	
	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(6184);

	if(bind(s,(sockaddr*)&local,sizeof(local)) !=0){
		AddReport("实验者主线程因套接字绑定错误，已停止");
		closesocket(s);
		return 0;
	}

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	arg = 1;
	ioctlsocket(s,FIONBIO,&arg);

	FD_ZERO(&readfds);

	AddReport("实验者主线程启动");
	while(!stop_thread_flag){
		FD_SET(s,&readfds);
		retval = select(0,&readfds,NULL,NULL,&timeout);

		if( !FD_ISSET(s,&readfds)){
			continue;
		}
		//获取可读的信息量大小
		arg = 0;
		ioctlsocket( s, FIONREAD, &arg);
		if( arg <= 0){
			continue;
		}

		buf = (char *)malloc(arg);
		if(buf == NULL){
			continue;
		}

		len = sizeof(remote);
		retval = recvfrom(s,buf,arg,0,(sockaddr*)&remote,&len);
		if(retval <= 0 ){
			AddReport("主线程因套接字接收数据错误，已停止");
			closesocket(s);
			return 0;
		}

		//启动多线程，把数据交给他们处理
		dwThrdParam = (DWORD)buf;
		
		hThread = CreateThread(
					NULL,                        // no security attributes 
					0,                           // use default stack size  
					child_thread,                  // thread function 
					(DWORD *)dwThrdParam,                // argument to thread function 
					0,                           // use default creation flags 
					&dwThreadId);                // returns the thread identifier 
		
		FD_ZERO(&readfds);
	}
	AddReport("实验者主线程已结束");
	closesocket(s);
	WSACleanup();
	return 0;
} 

/*******************************************************************************************
** Function name: child_thread()
** Descriptions	:	具体执行命令的子线程，每个子线程执行一条操作命令
** Input:	
**          char *buf; 需要解析的命令报文
** Output:  NONE
**   return:  类型：void
*******************************************************************************************/
DWORD WINAPI child_thread( LPVOID lpParam )
{
	thread_command_t * pdu;
	CString csThread;
	char tmpbuf[48];

	pdu = (thread_command_t *)lpParam;

	if(pdu == NULL){
		return 0;
	}
	//取系统时间
	_strtime( tmpbuf );
	csThread.Format("实验者子线程%x，启动,%s",(unsigned long)pdu,tmpbuf);
	AddReport(csThread);

	//延时一段时间，模拟自己还有其它可并发的任务需要完成的情况
	
	Sleep(GetConcurrentSimTime()/2);

	//执行命令
	if(pdu == NULL){
		return 0;
	}
	//分析命令并执行
	switch(pdu->command){
	case MULTI_THREAD_INSERT:
		//在指定位置后插入元素
		thread_test_insert_table(pdu);
	break;
	case MULTI_THREAD_DELETE:
		//删除指定学号的元素
		thread_test_delete_table(pdu);
	break;

	}

	//延时一段时间，模拟自己还有其它可并发的任务需要完成的情况
	
	Sleep(GetConcurrentSimTime()/2);
    
	//取系统时间
	_strtime( tmpbuf );
	csThread.Format("实验者子线程%x，已完成%s",(unsigned long)pdu,tmpbuf);

	free(pdu);
	AddReport(csThread);
	return 0; 

}

/*******************************************************************************************
** Function name: thread_test_insert_table()
** Descriptions	: 按指定位置插入的多线程测试算法，
**                算法保持普通插入算法框架，调用一些仿真函数来模拟多线程下的操作效果，演示结果及进行统计
**                  
** Input:	
**        thread_command_t * pdu; 操作命令，包括插入位置和元素内容
** Output:
**        
**   return:  类型：NONE
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void thread_test_insert_table(thread_command_t * pdu)
{
	int i;
	int table_length;
	int location;
	element_t tmp_data;

	//取得顺序表长度
	table_length = thread_get_table_length();

	location = pdu->arg.location;
	if(table_length >= MAX_TABLE_SIZE ||  location< 0){
		return ;
	}
	if( location > table_length + 1){
		location = table_length + 1;
	}

	//搬移元素，腾空位置
	for(i = table_length - 1; i >= location; i --){
		//table->data[i+1] = table->data[i];
		tmp_data = thread_get_table_element(i);
		thread_put_table_element(tmp_data, i+1 );
	}

	//插入新元素
	thread_put_table_element(pdu->data,location);
	//table->data[location] = data;

	//表长增加
	table_length ++;
	thread_set_table_length(table_length);

	//table->length ++;

	return ;

}
/*******************************************************************************************
** Function name: thread_test_delete_table()
** Descriptions	: 按指定元素删除的多线程测试算法，
**                算法保持普通删除算法框架，调用一些仿真函数来模拟多线程下的操作效果，演示结果及进行统计
**                  
** Input:	
**        thread_command_t * pdu; 操作命令，包括删除元素的学号——按指定学号删除
** Output:
**        
**   return:  类型：NONE
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void thread_test_delete_table(thread_command_t * pdu)
{
	int i;
	int table_length;
	element_t tmp_data;

	//取得顺序表长度
	table_length = thread_get_table_length();

	if(table_length <= 0){
		return;
	}

	//从前向后，逐判断是否为需要删除的元素
	i = 0;
	while(i < table_length ){
		//取得元素
		tmp_data = thread_get_table_element(i);

		if(pdu->arg.stuID == tmp_data.stuID ){
			break;
		}
		i ++;
	}
	//判断是否找到
	if(i >= table_length){

		return ;
	}
	//删除第i+1个元素(从0开始，所以i号元素就是第i+1个元素，从前向后，逐个向前移动元素
	for( ; i < table_length - 1; i ++){
		tmp_data = thread_get_table_element(i + 1);
		thread_put_table_element(tmp_data, i);

		//table->data[i] = table->data[i+1];
	}

	//表长减少
	table_length --;
	thread_set_table_length(table_length);

	return ;

}
/**********************************
//小提示：Windows同步操作
/***********************************
CriticalSection:
CRITICAL_SECTION g_csA;
InitializeCriticalSection(&g_csA);
EnterCriticalSection(&g_csA);
LeaveCriticalSection(&g_csA);
DeleteCriticalSection(&g_csA);

互斥对象:
HANDLE hMutex;
hMutex=CreateMutex(NULL,TRUE,LPCTSTR("tickets"));
WaitForSingleObject(hMutex,INFINITE);
ReleaseMutex(hMutex);
CloseHandle(hMutex);

事件对象
HANDLE g_hEvent;
g_hEvent=CreateEvent(NULL,FALSE,FALSE,LPCTSTR("tickets"));
OpenEvent(),打开一个事件——用的少
ResetEvent(g_hEvent);
SetEvent(g_hEvent);回置事件
WaitForSingleObject(g_hEvent,IFINITE)
WaitForMultipleObjects()

信号量
CreateSemaphore() 创建一个信号量 
OpenSemaphore() 打开一个信号量 
ReleaseSemaphore() 释放信号量 
WaitForSingleObject() 等待信号量 

HANDLE global_Semephore;
global_Semephore= CreateSemaphore(NULL, 1, 1, NULL); 
WaitForSingleObject(global_Semephore, INFINITE); 
ReleaseSemaphore(global_Semephore, 1, NULL); 
1． 互斥量与临界区的作用非常相似，但互斥量是可以命名的，也就是说它可以跨越进程使用。所以创建互斥量需要的资源更多，所以如果只为了在进程内部是用的话使用临界区会带来速度上的优势并能够减少资源占用量。因为互斥量是跨进程的互斥量一旦被创建，就可以通过名字打开它。
2． 互斥量（Mutex），信号灯（Semaphore），事件（Event）都可以被跨越进程使用来进行同步数据操作，而其他的对象与数据同步操作无关，但对于进程和线程来讲，如果进程和线程在运行状态则为无信号状态，在退出后为有信号状态。所以可以使用WaitForSingleObject来等待进程和线程退出。
3． 通过互斥量可以指定资源被独占的方式使用，但如果有下面一种情况通过互斥量就无法处理，比如现在一位用户购买了一份三个并发访问许可的数据库系统，可以根据用户购买的访问许可数量来决定有多少个线程/进程能同时进行数据库操作，这时候如果利用互斥量就没有办法完成这个要求，信号灯对象可以说是一种资源计数器

***********************************/