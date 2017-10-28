/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           filter_tree.cpp
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        各种过滤规则树的操作，过滤规则树也是一种过滤规则树，
**                      过滤规则树结构的定义在mystruct.h中，
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
** Function name: init_filter_tree()
** Descriptions	:	初始化过滤规则树
**                  过滤规则树也是过滤规则树，采用链接存储，动态申请内存的方式
**                  在需要的时候为链点申请空间。过滤规则树结构中最重要的是根节点指针，因此在初
**                  始化时，除了要申请过滤规则树结构空间外，还应将其中的根节点指针设置为空
** Input:	NONE
** Output:  NONE
**   return:  类型：filter_tree_t *，返回过滤规则树的结构指针
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
filter_tree_t * init_filter_tree()
{
	filter_tree_t * t = NULL;

	return t;
}
/*******************************************************************************************
** Function name: free_filter_tree()
** Descriptions	:	释放过滤树树结构
**                  当程序结束时会通过本函数来释放树空间，如果树中有多个元素，则需要
**                  逐个将元素的空间予以释放。
** Input:	filter_tree_t * t; 树结构指针
** Output:  NONE
**   return:  类型：void
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void free_filter_tree(filter_tree_t * tree)
{
	if(tree == NULL){
		return;
	}

	free_filter_tree_nodes(tree->root);
	free(tree);
	return;
}
/*******************************************************************************************
** Function name: free_filter_tree_nodes()
** Descriptions	:	释放过滤规则树树的所有链点
**                  当程序结束时会通过本函数来释放过滤规则树空间，如果过滤规则树中有多个元素，则需要逐个将
**                  元素的空间予以释放，由于过滤规则树是非线性结构，可以考虑采用后根遍历递归框架释放
**                  各个链点，采用后根的原因是根节点的空间不能早于子树节点空间释放，否则无法继续
**                  继续遍历链表
** Input:	filter_tnode_t * root; 过滤规则树根结点指针
** Output:  NONE
**   return:  类型：void
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
void free_filter_tree_nodes(filter_tnode_t * root)
{
	if(root == NULL){
		return;
	}
	if(root->Lchild != NULL)
		free_filter_tree_nodes(root->Lchild);
	if(root->Rchild != NULL)
		free_filter_tree_nodes(root->Rchild);
	free(root);
	return;
}
/*******************************************************************************************
** Function name: insert_filter_tree()
** Descriptions	:	向过滤规则树插入一个元素，插入在parent_id节点的type（0-左子或1-右子上），
**                  如果parent_id为0，则本节点作为整个树的根，而且type指示的是原来的树根做为本节点的左子或者右子。否则type指示的是本节点作为父节点的左子或右子。
**                  当本节点作为父节点的左子树插入时，父节点原来的左子树将作为本节点的左子树
**                  当本节点作为父节点的右子树插入时，父节点原来的右子树将作为本节点的右子树
** Input:	
**          filter_tree_t * tree; 过滤规则树指针
**          int my_id, 本节点id，即待插入节点的id
**          Parms rules, 过滤规则，作为过滤规则树节点主要的元素域
**          int parent_id, 指示应该在哪个父节点后插入，0表示本节点将作为根
**          int type, 指示本节点是作为父节点的左子树插入还是右子树插入，0表示左子树，1表示右子树
** Output:  NONE
**   return:  类型：int，0，表示成功插入；-1，表示插入失败，一般是因为没有足够的内存，-2表示找不到指定的父节点
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
filter_tnode_t * find_filter(filter_tnode_t * root, int id)
{
	filter_tnode_t * result = NULL;
	if(root == NULL){
		return NULL;
	}
	if(root->id == id){
		return root;
	}
	result = find_filter(root->Lchild, id);
	if(result == NULL){
		result = find_filter(root->Rchild,id);
	}
	return result;
}
int insert_filter_tree(filter_tree_t * tree, int my_id, Parms rules,int parent_id, int type)
{



	return 0;
}
/*******************************************************************************************
** Function name: delete_filter_tree()
** Descriptions	:	//按过滤规则树的方式删除指定id的元素，
**                  当本节点是树的根时，原左子树将作为新的树根，原右子树将作为新根的最右子树，即从根开始一直向右，到达尽头时插入,如果本节点没有左子，则直接将本节点右子作为根，结束
**                  当本节点作为父节点左子删除时，本节点原来的左子将作为父节点的左子树,本节点原来的右子树将作为本节点原左子树的最右子树，如果本节点没有左子，则直接将本节点右子作为父节点的左子，结束
**                  当本节点作为父节点右子删除时，本节点原来的左子将作为父节点的右子树,本节点原来的右子树将作为本节点原左子树的最右子树，如果本节点没有左子，则直接将本节点右子作为父节点的右子，结束
** Input:	
**          filter_tree_t * tree; 过滤规则树指针
**          int id;待删除节点的id
** Output:  NONE
**
**   return:  类型：int, 0表示正确删除，-1表示删除失败，因为没找到指定节点
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
filter_tnode_t * find_parent_filter(filter_tnode_t * root, int id)
{
	filter_tnode_t * result = NULL;

	if(root == NULL){
		return NULL;
	}
	if(root->id == id){
		return NULL;
	}

	if(root->Lchild != NULL){
		if(root->Lchild->id == id){
			return root;
		}
		result = find_filter(root->Lchild, id);

	}
	if(result == NULL){
		if(root->Rchild != NULL){
			if(root->Rchild->id == id){
				return root;
			}
			result = find_filter(root->Rchild, id);
		}
	}
	return result;

}
/*******************************************************************************************
** Function name: delete_filter_tree()
** Descriptions	:	//按过滤规则树的方式删除指定id的元素，
**                  当本节点是树的根时，原左子树将作为新的树根，原右子树将作为新根的最右子树，即从根开始一直向右，到达尽头时插入,如果本节点没有左子，则直接将本节点右子作为根，结束
**                  当本节点作为父节点左子删除时，本节点原来的左子将作为父节点的左子树,本节点原来的右子树将作为本节点原左子树的最右子树，如果本节点没有左子，则直接将本节点右子作为父节点的左子，结束
**                  当本节点作为父节点右子删除时，本节点原来的左子将作为父节点的右子树,本节点原来的右子树将作为本节点原左子树的最右子树，如果本节点没有左子，则直接将本节点右子作为父节点的右子，结束
** Input:	
**          filter_tree_t * tree; 过滤规则树指针
**          int id;待删除节点的id
** Output:  NONE
**
**   return:  类型：int, 0表示正确删除，-1表示删除失败，因为没找到指定节点
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int delete_filter_tree(filter_tree_t * tree, int id)
{




	return 0;
}
/*******************************************************************************************
** Function name: edit_filter_tnode()
** Descriptions	:	修改过滤规则树中指定id的节点的rules
** Input:	
**          tnode_t * root; 过滤规则树根指针
**          int id,  待修改过滤规则的id
**          Parms rules, 过滤规则
** Output:  NONE
**
**   return:  类型：int, 为0表示正确修改，为-1表示没有找到指定的节点
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
int edit_filter_tnode(filter_tnode_t * root, int id, Parms rules)
{
	filter_tnode_t * p;

	//先找到节点
	p = find_filter(root,id);
	if(p == NULL){
		return -1;
	}

	p->rules = rules;

	return 0;
}
/*******************************************************************************************
** Function name: check_rules()
** Descriptions	:	使用过滤规则树种节点的rules对输入的data进行过滤检查
**                  根据过滤规则树的原理，过滤算法将以先根遍历为框架，具有递归特点：
**                  首先检查树根条件，如果根判决结果（以下简称结果）为真，就继续检查其左子树（与条件），如果右子树查得的结果为真，则直接返回结果为真
**                  如果根结果为假或者根为真且继续检查左子树为假，才继续检查根的右子树（因为如果左子树为真则在上一部就直接返回了），如果右子树结果为真，则返回结果真，结束，如果右子树结果为假，则返回结果也是假，结束。
**                  如果根的左子或右子为空，则跳过相应步骤，以根的结果来决定下一步。如根的结果为假，又没有右子树，则最终结果为假。如果根结果为真，没有左子树，则结果直接为真，并结束。
** Input:	
**          filter_tnode_t * root; 过滤规则树指针
**          element_t data;  用于过滤检查的数据元素
** Output:  NONE
**
**   return:  类型：bool 过滤检查结果，0表示结果为假，1表示结果为真
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
bool check_rules(Parms * rules,element_t * data)
{
	BOOL minretval;
	BOOL maxretval;

	int check;
	switch(rules->Section){
	case FLT_SEX:
		check = data->sex;
	break;
	case FLT_PINSHI:
		check = data->pinshi;
	break;
	case FLT_QIZHONG:
		check = data->qizhong;
	break;
	case FLT_SHIYAN:
		check = data->shiyan;
	break;
	case FLT_QIMO:
		check = data->qimo;
	break;
	case FLT_OVERALL:
		check = data->overall;
	break;
	
	default:
		return FALSE;	
	}
	
	minretval = TRUE;
	maxretval = TRUE;

	if(rules->MinValid){
		if(check < rules->Min){
			minretval = FALSE;
		}
	}
	if(rules->MaxValid){
		if(check >= rules->Max){
			maxretval = FALSE;
		}
	}
	if(rules->Not){
		return !(minretval && maxretval);
	}else
		return minretval && maxretval;
}
/*******************************************************************************************
** Function name: do_filter()
** Descriptions	:	执行
** Input:	
**          filter_tree_t * tree; 过滤规则树指针
**          int id;待删除节点的id
** Output:  NONE
**
**   return:  类型：int, 0表示正确删除，-1表示删除失败，因为没找到指定节点
** Created by	: 
** Created Date	: 
**------------------------------------------------------------------------------------------
** Modified by	:
** Modified Date: 
**------------------------------------------------------------------------------------------
*******************************************************************************************/
BOOL do_filter(filter_tnode_t * root, element_t data)
{




	return 0;
}
