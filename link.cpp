/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           link.cpp
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        �����������������ṹ�Ķ�����mystruct.h�У�
**                      ������ʹ�õ��������ʾ�йؽӿڵ�˵����ui.h
**                      ���ļ�����C���Է��
**------------------------------------------------------------------------------------------
** Created by:          Duan Jingshan
** Created date:        2012-12-19
**------------------------------------------------------------------------------------------
** Modified by:   
** Modified date: 
** Version:    
** Descriptions:  
**
*******************************************************************************************/
#include "stdafx.h"
#include "mystruct.h"
#include "ui.h"
/*******************************************************************************************
** Function name: init_link()
** Descriptions	:	��ʼ������
**                  ������ص��������ڴ���ɢ�ռ��Ÿ���Ԫ�أ���˲�������Ϊ����׼���㹻��
**                  ���ڴ�ռ䣬ֻ������Ҫ������Ԫ��ʱ���������Ҫ������ռ䡣����ڳ�ʼ��
**                  ����ʱ��ֻ��ҪΪ�������������ṹ����Ŀռ伴�ɡ�
**                  �ؼ���Ҫ�����е�ͷָ������Ϊ��
** Input:	NONE
** Output:  NONE
**   return:  ���ͣ�link_t *����������Ľṹָ��
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
link_t * init_link()
{
	link_t * p;
	p = (link_t*)malloc(sizeof(link_t));
	if(p == NULL)
		return NULL;
	p->head = NULL;
	p->length = 0;
	return p;
}
/*******************************************************************************************
** Function name: free_link()
** Descriptions	:	�ͷ�����ռ�
**                  ���������ʱ��ͨ�����������ͷ�����ռ䣬��������л���Ԫ�أ�����Ҫ�����
**                  Ԫ�صĿռ������ͷ�
** Input:	link_t * t; ����ṹָ��
** Output:  NONE
**   return:  ���ͣ�void
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void free_link(link_t * t)
{	
	node_t * p;
	if(t == NULL){
		return;
	}
	//��������������㣬����Ҫ����ͷŸ�����ռ䣬����ֻ��free(t);
	p = t->head;
	while(t->head != NULL){
		p = t->head;
		t->head = t->head->next;
		free(p);
	}

	t->head = NULL;
	t->length = 0;
	free(t);

}
/*******************************************************************************************
** Function name: add_link()
** Descriptions	:	��ָ��Ԫ�ط��뵽�����ĩβ
** Input:	
**        link_t * link; ����ṹָ��
**        element_t data; �������Ԫ��
** Output:
**        link_t * link; �����Ԫ�غ������ָ��
**   return:  ���ͣ�int; Ϊ-1��ʾ����ʧ�ܣ�һ������Ϊ���벻������ռ䣬Ϊ0��ʾ��ȷ����
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int add_link(link_t * link, element_t data)
{
	node_t * p, * t;
	t = (node_t*)malloc(sizeof(node_t));
	if(t == NULL)
		return -1;
	t->data = data;
	t->next = NULL;

	if(link->head == NULL)
	{
		link->head = t;
		link->length = 1;
	}

	else
	{
		p = link->head;
		while(p->next != NULL)
			p = p->next;
		p->next = t;
		link->length++;
	}
	return 0;
}
/*******************************************************************************************
** Function name: get_link()
** Descriptions	:	��ѯ����
**                  ��ѯ�����е�i��Ԫ��
** Input:	
**        link_t * link; ˳���ָ��
**        int index;  ��ѯλ�ã�����i��Ԫ��
** Output:  
**        element_t * elem; Ԫ����ָ�룬������ű���ѯ����Ԫ�����ݣ�
**                      ��ע�⣬��Ҫ��Ԫ��ȫ�����ݿ�������ָ������¼�Ŀռ��У�����ʹ��memcpy()��
**   return:  ���ͣ�int�����ز�ѯ�Ƿ�ɹ���Ϊ0��ʾ�ҵ�ָ��Ԫ�أ�Ϊ-1��ʾû���ҵ���һ������Ϊ
**                       indexָʾ��λ�ó�����˳���ķ�Χ
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int get_link(link_t * link,int index, element_t * elem)
{
	int j;
	node_t * p = link->head;
	if(index > link->length || index<=0)
		return -1;
	
	for(j=0; j<index-1; j++)
		p = p->next;

	memcpy(elem, &p->data, sizeof(element_t));
	return 0;
	
}
/*******************************************************************************************
** Function name: insert_link()
** Descriptions	:	��ָ��Ԫ�ز��뵽�����ָ��λ��֮ǰ
** Input:	
**        link_t * link; ����ṹָ��
**        element_t data; �������Ԫ��
**        int location;  ����λ�ã������ǣ���X��Ԫ��ǰ����location��������Ԫ������ʱ����Ԫ��
**                       �����뵽��β��
** Output:
**        link_t * link; ������Ԫ�غ������ṹָ��	
**   return:  ���ͣ�int; Ϊ-1��ʾ����ʧ�ܣ�һ������Ϊû�����뵽�ռ���޷���������
                         Ϊ0��ʾ��ȷ����
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int insert_link(link_t * link, element_t data, int location)
{
	int i = 1;
	node_t *p, *t;
	p= link->head;
	t = (node_t*)malloc(sizeof(node_t));
	if(t == NULL)
		return -1;
	t->data = data;

	if(location == 1)
	{
		t->next = p;
		link->head = t;
	}
	else
	{
		while(i<location-1 && i<link->length)
		{
			p = p->next;
			i++;
		}
		t->next = p->next;
		p->next = t;
	}
	link->length++;
	return 0;
}
/*******************************************************************************************
** Function name: insert_link_by_order()
** Descriptions	:	��ָ��Ԫ�ذ���ѧ�Ŵ�С����˳����뵽������
** Input:	
**        link_t * link; ����ָ��
**        element_t data; �������Ԫ��
** Output:
**        link_t * link; ������Ԫ�غ������ָ��	
**   return:  ���ͣ�int; Ϊ-1��ʾ����ʧ�ܣ�һ������Ϊû�����뵽�ռ���޷���������,
                         Ϊ0��ʾ��ȷ����
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int insert_link_by_order(link_t * link, element_t data)
{
	node_t *t, *p;
	t = (node_t*)malloc(sizeof(node_t));
	t->data = data;
	p = link->head;

	if(link->head->data.stuID > data.stuID)
	{
		t->next = link->head;
		link->head = t;
	}
	else
	{
		while(p->next != NULL && p->next->data.stuID < data.stuID)
			p = p->next;
		t->next = p->next;
		p->next = t;
	}
	link->length++;
	return 0;
}
/*******************************************************************************************
** Function name: delete_link()
** Descriptions	:	ɾ��������ָ��������Ϊ�ؼ��ֵ�Ԫ��
** Input:	
**        link_t * link; ����ָ��
**        char * name; �Ը�����Ϊ�ؼ��ֵ�Ԫ�ؽ���ɾ����������ռ�Ҳ��Ҫ���ͷ�
** Output:
**        link_t * link; ɾ��ָ��Ԫ�غ������ָ��	
**   return:  ���ͣ�int; Ϊ-1��ʾɾ��ʧ�ܣ�һ������Ϊ��������û���ҵ�ָ��Ԫ�أ�
                         Ϊ0��ʾ��ȷɾ��
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int delete_link(link_t * link, char * name)
{
	node_t *p, *t;
	p = link->head;
	if(strcmp(p->data.stuName, name) == 0)
	{
		t = p;
		p = p->next;
		free(t);
		link->length--;
		return 0;
	}

	while(p->next != NULL && strcmp(p->next->data.stuName, name) != 0)
		p = p->next;
	if(p->next != NULL)
	{
		t = p->next;
		p->next = t->next;
		free(t);
		link->length--;
		return 0;
	}
	else
		return -1;
}
/*******************************************************************************************
** Function name: delete_link_below()
** Descriptions	:	ɾ���������ܷ�С��ĳ��ָ��ֵ������Ԫ�أ����㷨���ص���
**                  ϣ��һ������������ɾ�����Ԫ��
** Input:	
**        link_t * link; ����ָ��
**        int x; ɾ����Χ������ɾ����Ԫ���ܷ�С�����ֵ
** Output:
**        link_t * link; ɾ��Ԫ�غ������ṹָ��	
**   return:  ���ͣ�void; 
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void delete_link_below(link_t * link, int x)
{
	node_t *p,*t;

    p = link->head;
	while(p->next != NULL)
	{
		if(p->next->data.overall <= x)
		{
			t = p->next;
			p->next = t->next;
			free(t);
			link->length--;
		}
		else
			p = p->next;
	}

	if(link->head->data.overall <= x)
	{
		t = link->head;
		link->head = t->next;
		free(t);
		link->length--;
	}
}
