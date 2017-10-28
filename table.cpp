/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           table.cpp
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        ����˳��������˳���ṹ�Ķ�����mystruct.h�У�
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
** Function name: init_table()
** Descriptions	:	��ʼ��˳���
**                  ˳�������������Ϊ���������ص�����Ҫ���Ȼ��ȫ��Ԫ�ؿռ䣬��˱���������Ҫ
**                  ���ܾ�����ϵͳ�����㹻�Ŀռ���Ϊ˳���Ĵ洢�ռ䡣�漰��ϵͳ����Ϊ��
**                  malloc()
**                  ���⣬���õ�ϰ���ǽ��ռ��ڵĸ������ݽ����ʵ��ĳ�ʼ��
** Input:	NONE
** Output:  NONE
**   return:  ���ͣ�table_t *������˳���Ľṹָ��
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
** Descriptions	:	�ͷ�˳���ռ�
**                  ���������ʱ��ͨ�����������ͷ�ͨ��malloc��õ�˳���ռ�
** Input:	table_t * t; ˳���ָ��
** Output:  NONE
**   return:  ���ͣ�void
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
** Descriptions	:	��ѯ˳���
**                  ��ѯ˳����е�i��Ԫ��
** Input:	
**        table_t * table; ˳���ָ��
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
int get_table(table_t * table,int index, element_t * elem)
{
	//�ж�index�Ƿ񳬳�˳���Χ
	if(index <= 0 || index > table->length){
		return -1;
	}
	
	//����Ԫ�����ݵ�ָ���ռ���;
	memcpy(elem,&(table->data[index-1]),sizeof(element_t));//error
	return 0;
}
/*******************************************************************************************
** Function name: add_table()
** Descriptions	:	��ָ��Ԫ�ط��뵽˳����ĩβ
** Input:	
**        table_t * table; ˳���ָ��
**        element_t data; �������Ԫ��
** Output:
**        table_t * table; �����Ԫ�غ��˳���ָ��
**   return:  ���ͣ�int; Ϊ-1��ʾ����ʧ�ܣ�һ������Ϊ˳����Ѿ�������Ϊ0��ʾ��ȷ����
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
** Descriptions	:	��ָ��Ԫ�ز��뵽˳����ָ��λ��֮ǰ
** Input:	
**        table_t * table; ˳���ָ��
**        element_t data; �������Ԫ��
**        int location;  ����λ�ã������ǣ���X��Ԫ��ǰ������location��������Ԫ������ʱ����Ԫ��
**                       �����뵽��β��
** Output:
**        table_t * table; ������Ԫ�غ��˳���ָ��	
**   return:  ���ͣ�int; Ϊ-1��ʾ����ʧ�ܣ�һ������Ϊ˳����Ѿ��������߲���λ�ò���ȷ��
                         Ϊ0��ʾ��ȷ����
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
** Descriptions	:	��ָ��Ԫ�ذ���ѧ�Ŵ�С����˳����뵽˳�����
** Input:	
**        table_t * table; ˳���ָ��
**        element_t data; �������Ԫ��
** Output:
**        table_t * table; ������Ԫ�غ��˳���ָ��	
**   return:  ���ͣ�int; Ϊ-1��ʾ����ʧ�ܣ�һ������Ϊ˳����Ѿ��������߲���λ�ò���ȷ��
                         Ϊ0��ʾ��ȷ����
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
** Descriptions	:	ɾ��˳�����ָ��������Ϊ�ؼ��ֵ�Ԫ��
** Input:	
**        table_t * table; ˳���ָ��
**        char * name; �Ը�����Ϊ�ؼ��ֵ�Ԫ�ؽ���ɾ��
** Output:
**        table_t * table; ɾ��ָ��Ԫ�غ��˳���ָ��	
**   return:  ���ͣ�int; Ϊ-1��ʾɾ��ʧ�ܣ�һ������Ϊ˳���û���ҵ�ָ��Ԫ�أ�
                         Ϊ0��ʾ��ȷɾ��
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
** Descriptions	:	ɾ��˳������ܷ�С��ĳ��ָ��ֵ������Ԫ�أ����㷨���ص���
**                  ϣ��һ������˳�����ɾ�����Ԫ��
** Input:	
**        table_t * table; ˳���ָ��
**        int x; ɾ����Χ������ɾ����Ԫ���ܷ�С�����ֵ
** Output:
**        table_t * table; ɾ��Ԫ�غ��˳���ָ��	
**   return:  ���ͣ�void; 
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

