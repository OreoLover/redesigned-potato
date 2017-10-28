*/
// connless.cpp : �ӿͻ����յ����ݺ󣬻ش�һ��ACK�ַ���.
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
** Descriptions	:	�ڶ��̲߳��������У��߳�����������̣�������ִ�����
** Input:	
**          char *buf; ��Ҫ�����������
** Output:  NONE
**   return:  ���ͣ�void
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
		AddReport("ʵ�������߳����׽��ִ���������ֹͣ");
		return 0;
	}
	
	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(6184);

	if(bind(s,(sockaddr*)&local,sizeof(local)) !=0){
		AddReport("ʵ�������߳����׽��ְ󶨴�����ֹͣ");
		closesocket(s);
		return 0;
	}

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	arg = 1;
	ioctlsocket(s,FIONBIO,&arg);

	FD_ZERO(&readfds);

	AddReport("ʵ�������߳�����");
	while(!stop_thread_flag){
		FD_SET(s,&readfds);
		retval = select(0,&readfds,NULL,NULL,&timeout);

		if( !FD_ISSET(s,&readfds)){
			continue;
		}
		//��ȡ�ɶ�����Ϣ����С
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
			AddReport("���߳����׽��ֽ������ݴ�����ֹͣ");
			closesocket(s);
			return 0;
		}

		//�������̣߳������ݽ������Ǵ���
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
	AddReport("ʵ�������߳��ѽ���");
	closesocket(s);
	WSACleanup();
	return 0;
} 

/*******************************************************************************************
** Function name: child_thread()
** Descriptions	:	����ִ����������̣߳�ÿ�����߳�ִ��һ����������
** Input:	
**          char *buf; ��Ҫ�����������
** Output:  NONE
**   return:  ���ͣ�void
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
	//ȡϵͳʱ��
	_strtime( tmpbuf );
	csThread.Format("ʵ�������߳�%x������,%s",(unsigned long)pdu,tmpbuf);
	AddReport(csThread);

	//��ʱһ��ʱ�䣬ģ���Լ����������ɲ�����������Ҫ��ɵ����
	
	Sleep(GetConcurrentSimTime()/2);

	//ִ������
	if(pdu == NULL){
		return 0;
	}
	//�������ִ��
	switch(pdu->command){
	case MULTI_THREAD_INSERT:
		//��ָ��λ�ú����Ԫ��
		thread_test_insert_table(pdu);
	break;
	case MULTI_THREAD_DELETE:
		//ɾ��ָ��ѧ�ŵ�Ԫ��
		thread_test_delete_table(pdu);
	break;

	}

	//��ʱһ��ʱ�䣬ģ���Լ����������ɲ�����������Ҫ��ɵ����
	
	Sleep(GetConcurrentSimTime()/2);
    
	//ȡϵͳʱ��
	_strtime( tmpbuf );
	csThread.Format("ʵ�������߳�%x�������%s",(unsigned long)pdu,tmpbuf);

	free(pdu);
	AddReport(csThread);
	return 0; 

}

/*******************************************************************************************
** Function name: thread_test_insert_table()
** Descriptions	: ��ָ��λ�ò���Ķ��̲߳����㷨��
**                �㷨������ͨ�����㷨��ܣ�����һЩ���溯����ģ����߳��µĲ���Ч������ʾ���������ͳ��
**                  
** Input:	
**        thread_command_t * pdu; ���������������λ�ú�Ԫ������
** Output:
**        
**   return:  ���ͣ�NONE
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

	//ȡ��˳�����
	table_length = thread_get_table_length();

	location = pdu->arg.location;
	if(table_length >= MAX_TABLE_SIZE ||  location< 0){
		return ;
	}
	if( location > table_length + 1){
		location = table_length + 1;
	}

	//����Ԫ�أ��ڿ�λ��
	for(i = table_length - 1; i >= location; i --){
		//table->data[i+1] = table->data[i];
		tmp_data = thread_get_table_element(i);
		thread_put_table_element(tmp_data, i+1 );
	}

	//������Ԫ��
	thread_put_table_element(pdu->data,location);
	//table->data[location] = data;

	//������
	table_length ++;
	thread_set_table_length(table_length);

	//table->length ++;

	return ;

}
/*******************************************************************************************
** Function name: thread_test_delete_table()
** Descriptions	: ��ָ��Ԫ��ɾ���Ķ��̲߳����㷨��
**                �㷨������ͨɾ���㷨��ܣ�����һЩ���溯����ģ����߳��µĲ���Ч������ʾ���������ͳ��
**                  
** Input:	
**        thread_command_t * pdu; �����������ɾ��Ԫ�ص�ѧ�š�����ָ��ѧ��ɾ��
** Output:
**        
**   return:  ���ͣ�NONE
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

	//ȡ��˳�����
	table_length = thread_get_table_length();

	if(table_length <= 0){
		return;
	}

	//��ǰ������ж��Ƿ�Ϊ��Ҫɾ����Ԫ��
	i = 0;
	while(i < table_length ){
		//ȡ��Ԫ��
		tmp_data = thread_get_table_element(i);

		if(pdu->arg.stuID == tmp_data.stuID ){
			break;
		}
		i ++;
	}
	//�ж��Ƿ��ҵ�
	if(i >= table_length){

		return ;
	}
	//ɾ����i+1��Ԫ��(��0��ʼ������i��Ԫ�ؾ��ǵ�i+1��Ԫ�أ���ǰ��������ǰ�ƶ�Ԫ��
	for( ; i < table_length - 1; i ++){
		tmp_data = thread_get_table_element(i + 1);
		thread_put_table_element(tmp_data, i);

		//table->data[i] = table->data[i+1];
	}

	//������
	table_length --;
	thread_set_table_length(table_length);

	return ;

}
/**********************************
//С��ʾ��Windowsͬ������
/***********************************
CriticalSection:
CRITICAL_SECTION g_csA;
InitializeCriticalSection(&g_csA);
EnterCriticalSection(&g_csA);
LeaveCriticalSection(&g_csA);
DeleteCriticalSection(&g_csA);

�������:
HANDLE hMutex;
hMutex=CreateMutex(NULL,TRUE,LPCTSTR("tickets"));
WaitForSingleObject(hMutex,INFINITE);
ReleaseMutex(hMutex);
CloseHandle(hMutex);

�¼�����
HANDLE g_hEvent;
g_hEvent=CreateEvent(NULL,FALSE,FALSE,LPCTSTR("tickets"));
OpenEvent(),��һ���¼������õ���
ResetEvent(g_hEvent);
SetEvent(g_hEvent);�����¼�
WaitForSingleObject(g_hEvent,IFINITE)
WaitForMultipleObjects()

�ź���
CreateSemaphore() ����һ���ź��� 
OpenSemaphore() ��һ���ź��� 
ReleaseSemaphore() �ͷ��ź��� 
WaitForSingleObject() �ȴ��ź��� 

HANDLE global_Semephore;
global_Semephore= CreateSemaphore(NULL, 1, 1, NULL); 
WaitForSingleObject(global_Semephore, INFINITE); 
ReleaseSemaphore(global_Semephore, 1, NULL); 
1�� ���������ٽ��������÷ǳ����ƣ����������ǿ��������ģ�Ҳ����˵�����Կ�Խ����ʹ�á����Դ�����������Ҫ����Դ���࣬�������ֻΪ���ڽ����ڲ����õĻ�ʹ���ٽ���������ٶ��ϵ����Ʋ��ܹ�������Դռ��������Ϊ�������ǿ���̵Ļ�����һ�����������Ϳ���ͨ�����ִ�����
2�� ��������Mutex�����źŵƣ�Semaphore�����¼���Event�������Ա���Խ����ʹ��������ͬ�����ݲ������������Ķ���������ͬ�������޹أ������ڽ��̺��߳�������������̺��߳�������״̬��Ϊ���ź�״̬�����˳���Ϊ���ź�״̬�����Կ���ʹ��WaitForSingleObject���ȴ����̺��߳��˳���
3�� ͨ������������ָ����Դ����ռ�ķ�ʽʹ�ã������������һ�����ͨ�����������޷�������������һλ�û�������һ����������������ɵ����ݿ�ϵͳ�����Ը����û�����ķ�����������������ж��ٸ��߳�/������ͬʱ�������ݿ��������ʱ��������û�������û�а취������Ҫ���źŵƶ������˵��һ����Դ������

***********************************/