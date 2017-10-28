/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           tree.cpp
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        ���ֶ������������������ṹ�Ķ�����mystruct.h�У�
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
** Function name: init_tree()
** Descriptions	:	��ʼ��������
**                  ���������Ƿ����Խṹ�����������²������Ӵ洢�����ö�̬�����ڴ�ķ�ʽ
**                  ����Ҫ��ʱ��Ϊ��������ռ䡣�������ṹ������Ҫ���Ǹ��ڵ�ָ�룬����ڳ�
**                  ʼ��ʱ������Ҫ����������ṹ�ռ��⣬��Ӧ�����еĸ��ڵ�ָ������Ϊ��
** Input:	NONE
** Output:  NONE
**   return:  ���ͣ�tree_t *����������Ľṹָ��
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
tree_t * init_tree()
{
	tree_t * t = (tree_t*)malloc(sizeof(tree_t));
	if(t == NULL)
		return NULL;
    t->root = NULL;
	t->num = 0;
	return t;
}
/*******************************************************************************************
** Function name: free_tree()
** Descriptions	:	�ͷŶ������ṹ
**                  ���������ʱ��ͨ�����������ͷŶ������ռ䣬������������ж��Ԫ�أ�����Ҫ
**                  �����Ԫ�صĿռ������ͷš�
** Input:	tree_t * t; ����ṹָ��
** Output:  NONE
**   return:  ���ͣ�void
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void free_tree(tree_t * tree)
{
	if(tree == NULL){
		return;
	}

	free_tree_nodes(tree->root);
	free(tree);
	return;
}
/*******************************************************************************************
** Function name: free_tree_nodes()
** Descriptions	:	�ͷŶ���������������
**                  ���������ʱ��ͨ�����������ͷŶ������ռ䣬������������ж��Ԫ�أ�����Ҫ�����
**                  Ԫ�صĿռ������ͷţ����ڶ������Ƿ����Խṹ�����Կ��ǲ��ú�������ݹ����ͷ�
**                  �������㣬���ú����ԭ���Ǹ��ڵ�Ŀռ䲻�����������ڵ�ռ��ͷţ������޷�����
**                  ������������
** Input:	tnode_t * root; �����������ָ��
** Output:  NONE
**   return:  ���ͣ�void
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void free_tree_nodes(tnode_t * root)
{
	if(root == NULL){
		return;
	}
	if(root->Lchild != NULL)
		free_tree_nodes(root->Lchild);
	if(root->Rchild != NULL)
		free_tree_nodes(root->Rchild);
	free(root);
	return;
}
/*******************************************************************************************
** Function name: insert_BS_tree()
** Descriptions	:	���������������һ��Ԫ�أ���Ԫ���е���������ܷ���Ϊ������
** Input:	
**          tree_t * tree; ������ָ��
**          element data; ��Ԫ��
** Output:  NONE
**   return:  ���ͣ�int��0����ʾ�ɹ����룻-1����ʾ����ʧ�ܣ�һ������Ϊû���㹻���ڴ�
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int insert_BS_tree(tree_t * tree, element_t data)
{
	int overall = data.overall;
    tnode_t *t,*p;
	t = (tnode_t*)malloc(sizeof(tnode_t));
	t->data = data;
	t->Lchild = NULL;
	t->Rchild = NULL;
	p = tree->root;
	if(p == NULL)
    {
		tree->root = t;
		tree->num++;
		return 0;
	}
	while((overall < p->data.overall && p->Lchild != NULL) ||
		(overall >= p->data.overall && p->Rchild != NULL))
	{
		if(overall < p->data.overall)
			p = p->Lchild;
		else if(overall > p->data.overall)
			p = p->Rchild;
	}
	if(overall < p->data.overall)
		p->Lchild = t;
	else if(overall >= p->data.overall)
		p->Rchild = t;
	tree->num++;
	return 0;
}
/*******************************************************************************************
** Function name: inorder_tree()
** Descriptions	:	���򣨸�������һ�ö�����,
**                  �ڷ��ʽڵ�����ʱ������ui.h�е�ShowElement()����Ԫ��������ʾ�ڴ�����
**                  �Թ����
** Input:	
**          tnode_t * root; ������ָ��
** Output:  NONE
**
**   return:  ���ͣ�void
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void inorder_tree(tnode_t * root)
{
	if(root == NULL)
		return;
	else
	{
		if(root->Lchild != NULL)
		{
			inorder_tree(root->Lchild);
			ShowElement(root->data);
		}
		if(root->Rchild != NULL)
			inorder_tree(root->Rchild);
	}
	return ;
}
/*******************************************************************************************
** Function name: preorder_tree()
** Descriptions	:	���򣨸�������һ�ö�����,
**                  �ڷ��ʽڵ�����ʱ������ui.h�е�ShowElement()����Ԫ��������ʾ�ڴ�����
**                  �Թ����
** Input:	
**          tnode_t * root; ������ָ��
** Output:  NONE
**
**   return:  ���ͣ�void
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void preorder_tree(tnode_t * root)
{
	if(root == NULL)
		return;
	else
	{
		ShowElement(root->data);
		if(root->Lchild != NULL)
			preorder_tree(root->Lchild);
		if(root->Rchild)
			preorder_tree(root->Rchild);
	}
	return ;
}
/*******************************************************************************************
** Function name: postorder_tree()
** Descriptions	:	���򣨸�������һ�ö�����,
**                  �ڷ��ʽڵ�����ʱ������ui.h�е�ShowElement()����Ԫ��������ʾ�ڴ�����
**                  �Թ����
** Input:	
**          tnode_t * root; ������ָ��
** Output:  NONE
**
**   return:  ���ͣ�void
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void postorder_tree(tnode_t * root)
{


	return ;
}
/*******************************************************************************************
** Function name: get_element_tree()
** Descriptions	:	�ڶ������У���ѯָ��ѧ�ŵ�Ԫ�أ���ø�Ԫ�ص�����ָ�룬�Ա���һ����������
**                  ��ѯ�㷨��Ҫ�Զ��������б������ɲ������򣨸��������㷨�Ŀ��,
** Input:	
**          tnode_t * root; ������ָ��
**          double stuID; ѧ��
** Output:  NONE
**
**   return:  ���ͣ�tnode_t *; ���ؾ���ָ��ѧ�ŵ�����ָ�룬���û�ҵ��򷵻�ֵΪNULL
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
tnode_t * get_element_tree(tnode_t * root, double stuID)
{
	tnode_t * ret = NULL;
	return ret;
}