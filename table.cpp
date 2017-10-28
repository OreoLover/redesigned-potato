/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           table.cpp
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        各种顺序表操作，顺序表结构的定义在mystruct.h中，
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
** Function name: init_table()
** Descriptions	:	初始化顺序表
**                  顺序表利用数组作为基础，其特点是需要事先获得全部元素空间，因此本函数的主要
**                  功能就是向系统申请足够的空间作为顺序表的存储空间。涉及的系统函数为：
**                  malloc()
**                  此外，良好的习惯是将空间内的各项数据进行适当的初始化
** Input:	NONE
** Output:  NONE
**   return:  类型：table_t *，返回顺序表的结构指针
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
table_t * init_table()
{
	table_t *t;
	t = (table_t *)malloc(sizeof(table_t));
    t->length = 0;
    return t;
}
/*******************************************************************************************
** Function name: free_table()
** Descriptions	:	释放顺序表空间
**                  当程序结束时会通过本函数来释放通过malloc获得的顺序表空间
** Input:	table_t * t; 顺序表指针
** Output:  NONE
**   return:  类型：void
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void free_table(table_t * t)
{
	free(t);
}
/*******************************************************************************************
** Function name: get_table()
** Descriptions	:	查询顺序表
**                  查询顺序表中第i个元素
** Input:	
**        table_t * table; 顺序表指针
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
int get_table(table_t * table,int index, element_t * elem)
{
	//判断index是否超出顺序表范围
	if(index <= 0 || index > table->length){
		return -1;
	}
	
	//复制元素内容到指定空间中;
	memcpy(elem,&(table->data[index-1]),sizeof(element_t));//error
	return 0;
}
/*******************************************************************************************
** Function name: add_table()
** Descriptions	:	将指定元素放入到顺序表的末尾
** Input:	
**        table_t * table; 顺序表指针
**        element_t data; 待放入的元素
** Output:
**        table_t * table; 添加新元素后的顺序表指针
**   return:  类型：int; 为-1表示放入失败，一般是因为顺序表已经放满，为0表示正确放入
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int add_table(table_t * table, element_t data)
{
	if(table->length == MAX_TABLE_SIZE)
		return -1;
	else
	{
		table->length++;
		table->data[table->length-1] = data;
	}
	return 0;
}
/*******************************************************************************************
** Function name: insert_table()
** Descriptions	:	将指定元素插入到顺序表的指定位置之前
** Input:	
**        table_t * table; 顺序表指针
**        element_t data; 待放入的元素
**        int location;  插入位置，语义是：第X个元素前，，当location大于链表元素总数时，该元素
**                       将插入到表尾。
** Output:
**        table_t * table; 插入新元素后的顺序表指针	
**   return:  类型：int; 为-1表示插入失败，一般是因为顺序表已经放满或者插入位置不正确，
                         为0表示正确插入
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int insert_table(table_t * table, element_t data, int location)
{
	int i,temp;
	temp = table->length;
	if(location<0 || location>MAX_TABLE_SIZE || temp>=MAX_TABLE_SIZE)
		return -1;
	else if(location>temp)
		table->data[temp] = data;
	else
	{
		for(i=temp;i>=location;i--)
		{
			
			table->data[i] = table->data[i-1];
		}
		table->data[location-1] = data;
    }
	table->length++;
	return 0;
}//
/*******************************************************************************************
** Function name: insert_table_by_order()
** Descriptions	:	将指定元素按照学号从小到大顺序插入到顺序表中
** Input:	
**        table_t * table; 顺序表指针
**        element_t data; 待放入的元素
** Output:
**        table_t * table; 插入新元素后的顺序表指针	
**   return:  类型：int; 为-1表示插入失败，一般是因为顺序表已经放满或者插入位置不正确，
                         为0表示正确插入
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int insert_table_by_order(table_t * table, element_t data)
{
    int i,j;
	for(i=0;i<table->length;i++)
	{
		if(table->data[i].stuID > data.stuID)
		{
			break;
		}
	}

    for(j=table->length;j>i;j--)
	{
		table->data[j] = table->data[j-1];
	}
	table->data[j] = data;
	table->length++;
	return 0;
}//
/*******************************************************************************************
** Function name: delete_table()
** Descriptions	:	删除顺序表中指定姓名作为关键字的元素
** Input:	
**        table_t * table; 顺序表指针
**        char * name; 以该姓名为关键字的元素将被删除
** Output:
**        table_t * table; 删除指定元素后的顺序表指针	
**   return:  类型：int; 为-1表示删除失败，一般是因为顺序表没有找到指定元素，
                         为0表示正确删除
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int delete_table(table_t * table, char * name)
{
	int i;
	for(i=0;i<table->length;i++)
	{
		if(strcmp(table->data[i].stuName,name) == 0)
			break;
	}

	for(;i<table->length-1;i++)
	{
		table->data[i] = table->data[i+1];
	}
	table->length--;
	return 0;
}//
/*******************************************************************************************
** Function name: delete_table_below()
** Descriptions	:	删除顺序表中总分小于某个指定值的所有元素，本算法的特点是
**                  希望一趟能在顺序表中删除多个元素
** Input:	
**        table_t * table; 顺序表指针
**        int x; 删除范围，即被删除的元素总分小于这个值
** Output:
**        table_t * table; 删除元素后的顺序表指针	
**   return:  类型：void; 
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void delete_table_below(table_t * table, int x)
{
    int i,j=0;
	int init_length = table->length;
	for(i=0;i<init_length;i++)
	{
		if(table->data[i].overall >= x)
		{
			table->data[j++] = table->data[i];
		}
		else
			table->length--;
	}
}

