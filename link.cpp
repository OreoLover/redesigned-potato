/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           link.cpp
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        各种链表操作，链表结构的定义在mystruct.h中，
**                      函数中使用的与界面显示有关接口的说明在ui.h
**                      本文件基于C语言风格
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
** Descriptions	:	初始化链表
**                  链表的特点是利用内存离散空间存放各个元素，因此不必事先为链表准备足够大
**                  的内存空间，只是在需要插入新元素时，才申请必要的链点空间。因此在初始化
**                  链表时，只需要为链表申请少量结构所需的空间即可。
**                  关键是要将其中的头指针设置为空
** Input:	NONE
** Output:  NONE
**   return:  类型：link_t *，返回链表的结构指针
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
** Descriptions	:	释放链表空间
**                  当程序结束时会通过本函数来释放链表空间，如果链表中还有元素，则需要逐个将
**                  元素的空间予以释放
** Input:	link_t * t; 链表结构指针
** Output:  NONE
**   return:  类型：void
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
	//如果链表中有链点，则需要逐个释放各链点空间，不能只是free(t);
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
** Descriptions	:	将指定元素放入到链表的末尾
** Input:	
**        link_t * link; 链表结构指针
**        element_t data; 待放入的元素
** Output:
**        link_t * link; 添加新元素后的链表指针
**   return:  类型：int; 为-1表示放入失败，一般是因为申请不到链点空间，为0表示正确放入
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
** Descriptions	:	查询链表
**                  查询链表中第i个元素
** Input:	
**        link_t * link; 顺序表指针
**        int index;  查询位置，即第i个元素
** Output:  
**        element_t * elem; 元素域指针，用来存放被查询到的元素内容，
**                      （注意，需要将元素全部内容拷贝到该指针所记录的空间中，即，使用memcpy()）
**   return:  类型：int，返回查询是否成功，为0表示找到指定元素，为-1表示没有找到，一般是因为
**                       index指示的位置超出了顺序表的范围
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
** Descriptions	:	将指定元素插入到链表的指定位置之前
** Input:	
**        link_t * link; 链表结构指针
**        element_t data; 待放入的元素
**        int location;  插入位置，语义是：第X个元素前，当location大于链表元素总数时，该元素
**                       将插入到表尾。
** Output:
**        link_t * link; 插入新元素后的链表结构指针	
**   return:  类型：int; 为-1表示插入失败，一般是因为没有申请到空间而无法生成链点
                         为0表示正确插入
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
** Descriptions	:	将指定元素按照学号从小到大顺序插入到链表中
** Input:	
**        link_t * link; 链表指针
**        element_t data; 待放入的元素
** Output:
**        link_t * link; 插入新元素后的链表指针	
**   return:  类型：int; 为-1表示插入失败，一般是因为没有申请到空间而无法生成链点,
                         为0表示正确插入
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
** Descriptions	:	删除链表中指定姓名作为关键字的元素
** Input:	
**        link_t * link; 链表指针
**        char * name; 以该姓名为关键字的元素将被删除，其链点空间也需要被释放
** Output:
**        link_t * link; 删除指定元素后的链表指针	
**   return:  类型：int; 为-1表示删除失败，一般是因为在链表中没有找到指定元素，
                         为0表示正确删除
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
** Descriptions	:	删除链表中总分小于某个指定值的所有元素，本算法的特点是
**                  希望一趟能在链表中删除多个元素
** Input:	
**        link_t * link; 链表指针
**        int x; 删除范围，即被删除的元素总分小于这个值
** Output:
**        link_t * link; 删除元素后的链表结构指针	
**   return:  类型：void; 
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
