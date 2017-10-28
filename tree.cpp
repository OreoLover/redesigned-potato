/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           tree.cpp
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        各种二叉树操作，二叉树结构的定义在mystruct.h中，
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
** Function name: init_tree()
** Descriptions	:	初始化二叉树
**                  二叉树的是非线性结构，大多数情况下采用链接存储，采用动态申请内存的方式
**                  在需要的时候为链点申请空间。二叉树结构中最重要的是根节点指针，因此在初
**                  始化时，除了要申请二叉树结构空间外，还应将其中的根节点指针设置为空
** Input:	NONE
** Output:  NONE
**   return:  类型：tree_t *，返回链表的结构指针
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
** Descriptions	:	释放二叉树结构
**                  当程序结束时会通过本函数来释放二叉树空间，如果二叉树中有多个元素，则需要
**                  逐个将元素的空间予以释放。
** Input:	tree_t * t; 链表结构指针
** Output:  NONE
**   return:  类型：void
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
** Descriptions	:	释放二叉树的所有链点
**                  当程序结束时会通过本函数来释放二叉树空间，如果二叉树中有多个元素，则需要逐个将
**                  元素的空间予以释放，由于二叉树是非线性结构，可以考虑采用后根遍历递归框架释放
**                  各个链点，采用后根的原因是根节点的空间不能早于子树节点空间释放，否则无法继续
**                  继续遍历链表
** Input:	tnode_t * root; 二叉树根结点指针
** Output:  NONE
**   return:  类型：void
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
** Descriptions	:	向二叉排序树插入一个元素，以元素中的数据项——总分作为排序码
** Input:	
**          tree_t * tree; 二叉树指针
**          element data; 新元素
** Output:  NONE
**   return:  类型：int，0，表示成功插入；-1，表示插入失败，一般是因为没有足够的内存
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
** Descriptions	:	中序（根）遍历一棵二叉树,
**                  在访问节点内容时，调用ui.h中的ShowElement()来将元素内容显示在窗口内
**                  以供检查
** Input:	
**          tnode_t * root; 二叉树指针
** Output:  NONE
**
**   return:  类型：void
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
** Descriptions	:	先序（根）遍历一棵二叉树,
**                  在访问节点内容时，调用ui.h中的ShowElement()来将元素内容显示在窗口内
**                  以供检查
** Input:	
**          tnode_t * root; 二叉树指针
** Output:  NONE
**
**   return:  类型：void
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
** Descriptions	:	后序（根）遍历一棵二叉树,
**                  在访问节点内容时，调用ui.h中的ShowElement()来将元素内容显示在窗口内
**                  以供检查
** Input:	
**          tnode_t * root; 二叉树指针
** Output:  NONE
**
**   return:  类型：void
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
** Descriptions	:	在二叉树中，查询指定学号的元素，获得该元素的链点指针，以备进一步访问所需
**                  查询算法需要对二叉树进行遍历，可采用先序（根）遍历算法的框架,
** Input:	
**          tnode_t * root; 二叉树指针
**          double stuID; 学号
** Output:  NONE
**
**   return:  类型：tnode_t *; 返回具有指定学号的链点指针，如果没找到则返回值为NULL
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