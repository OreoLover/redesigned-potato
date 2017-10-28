/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           mystruct.h
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        定义顺序表、链表、二叉树等数据结构类型和相关操作函数
**                      界面程序在完成相关控制后会在适当的时候调用这些操作函数
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
#ifndef MY_STRUCT_H
#define MY_STRUCT_H

/******************************************************************************************/
//  以下为各种结构类型定义
//
/******************************************************************************************/
#define MAX_NAME_SIZE	40
//定义成绩管理表元素类型
typedef struct element_t{
	double stuID;
	char stuName[MAX_NAME_SIZE];
	int sex;
	int pinshi;
	int qizhong;
	int shiyan;
	int qimo;
	int overall;
}element_t;

#define MAX_TABLE_SIZE	1024
//定义顺序表结构
typedef struct table_t{
	element_t data[MAX_TABLE_SIZE];
	int length;
}table_t;

//定义链点
typedef struct node_t{
	element_t data;
	struct node_t* next;
}node_t;

//定义链表
typedef struct link_t{
	node_t * head;
	//node_t * tail;
	int length;
}link_t;

//定义二叉树链点
typedef struct tnode_t{
	element_t data;
	struct tnode_t * Lchild;
	struct tnode_t * Rchild;
}tnode_t;

//定义二叉树
typedef struct tree_t{
	tnode_t * root;
	int num;
}tree_t;

//定义过滤规则树的每个过滤规则的结构
#pragma pack(1)
struct Parms{
	int Section;        //指示过滤数据元素的哪个字段
	bool MaxValid;      //指示过滤条件是否有最大值
	long Max;  //过滤条件最大值限度，即满足条件的数据值将小于这个限度
	bool MinValid;      //指示过滤条件是否有最小值
	long Min;  //过滤条件最小值限度，即满足条件的数据值将大于或等于这个限度
	bool Not;           //指示最终结果是否将以上条件取反，0表示不取反
};
#pragma pack()

//定义过滤规则树节点
typedef struct filter_tnode_t{
	int id;  //每个节点唯一的Id ，通过这个Id将帮助插入和删除函数找到对应的节点
	struct Parms rules;  //元素域，即一条过滤规则
	struct filter_tnode_t * Lchild; //左子树，实际对应于过滤规则之间的“与”关系
	struct filter_tnode_t * Rchild; //右子树，实际对应于过滤规则之间的"或"关系
}filter_tnode_t;
//定义过滤规则树
typedef struct filter_tree_t{
	filter_tnode_t * root;
	int num;
}filter_tree_t;
//定义过滤字段Section指示
#define FLT_SEX		0
#define FLT_PINSHI	1
#define FLT_QIZHONG	2
#define FLT_SHIYAN	3
#define FLT_QIMO	4
#define FLT_OVERALL	5

//定义多线程测试时的命令报文结构
#pragma pack(1)
typedef struct thread_command_t{
	unsigned long command;
	union {
		int location;
		double stuID;
	}arg;
	element_t data;
}thread_command_t;
//定义多线程测试命令
#define MULTI_THREAD_INSERT	0
#define MULTI_THREAD_DELETE 1

#pragma pack()
/******************************************************************************************/
//  以下为各种结构的操作函数定义，注意以extern作为前缀，便于界面模块使用
//
/******************************************************************************************/
	/******************************************************************************************/
	//  顺序表结构各操作函数
	//
	/******************************************************************************************/
extern table_t * init_table();
extern void free_table(table_t * t);
extern int get_table(table_t * table,int index, element_t * elem);
extern int add_table(table_t * table, element_t data);
extern int insert_table(table_t * table, element_t data, int location);
extern int insert_table_by_order(table_t * table, element_t data);
extern int delete_table(table_t * table, char * name);
extern void delete_table_below(table_t * table, int x);

	/******************************************************************************************/
	//  链表结构各操作函数
	//
	/******************************************************************************************/
extern link_t * init_link();
extern void free_link(link_t * t);
extern int add_link(link_t * link, element_t data);
extern int get_link(link_t * link,int index, element_t * elem);
extern int insert_link(link_t * link, element_t data, int location);
extern int insert_link_by_order(link_t * link, element_t data);
extern int delete_link(link_t * link, char * name);
extern void delete_link_below(link_t * link, int x);
	/******************************************************************************************/
	//  二叉树结构各操作函数
	//
	/******************************************************************************************/
extern tree_t * init_tree();
extern void free_tree(tree_t * tree);
extern void free_tree_nodes(tnode_t * root);
extern int insert_BS_tree(tree_t * tree, element_t data); //按排序二叉树的方式插入元素，排序码是“总分-overall”
extern void inorder_tree(tnode_t * root);
extern void preorder_tree(tnode_t * root);
extern void postorder_tree(tnode_t * root);
extern tnode_t * get_element_tree(tnode_t * root, double stuID);

	/******************************************************************************************/
	//  各种过滤树的操作函数
	//
	/******************************************************************************************/
extern filter_tree_t * init_filter_tree();
extern void free_filter_tree(filter_tree_t * tree);
extern void free_filter_tree_nodes(filter_tnode_t * root);
extern int insert_filter_tree(filter_tree_t * tree, int my_id, Parms rules,int parent_id, int type); //按过滤规则树的方式插入元素，
//插入在parent_id节点的type（0-左子或1-右子上），
//如果parent_id为0，则本节点作为整个树的根，而且type指示的是原来的树根做为本节点的左子或者右子。否则type指示的是本节点作为父节点的左子或右子。
//当本节点作为父节点的左子树插入时，父节点原来的左子树将作为本节点的左子树
//当本节点作为父节点的右子树插入时，父节点原来的右子树将作为本节点的右子树
extern int delete_filter_tree(filter_tree_t *tree, int id); //按过滤规则树的方式删除指定id的元素，
//当本节点是树的根时，原左子树将作为新的树根，原右子树将作为新根的最右子树，即从根开始一直向右，到达尽头时插入,如果本节点没有左子，则直接将本节点右子作为根，结束
//当本节点作为父节点左子删除时，本节点原来的左子将作为父节点的左子树,本节点原来的右子树将作为本节点左子树的最右子树，如果本节点没有左子，则直接将本节点右子作为父节点的左子，结束
//当本节点作为父节点右子删除时，本节点原来的左子将作为父节点的右子树,本节点原来的右子树将作为本节点左子树的最右子树，如果本节点没有左子，则直接将本节点右子作为父节点的右子，结束
extern int edit_filter_tnode(filter_tnode_t * root, int id, Parms rules);  //修改过滤规则树中指定id的节点的rules
extern BOOL do_filter(filter_tnode_t * root, element_t data);  //使用过滤规则树种节点的rules对输入的data进行过滤检查
//根据过滤规则树的原理，过滤算法将以先根遍历为框架，具有递归特点：
//首先检查树根条件，如果根判决结果（以下简称结果）为真，就继续检查其左子树（与条件），如果右子树查得的结果为真，则直接返回结果为真
//如果根结果为假或者根为真且继续检查左子树为假，才继续检查根的右子树（因为如果左子树为真则在上一部就直接返回了），如果右子树结果为真，则返回结果真，结束，如果右子树结果为假，则返回结果也是假，结束。
//如果根的左子或右子为空，则跳过相应步骤，以根的结果来决定下一步。如根的结果为假，又没有右子树，则最终结果为假。如果根结果为真，没有左子树，则结果直接为真，并结束。

	/******************************************************************************************/
	//  各种检索操作函数
	//
	/******************************************************************************************/
extern int sequence_search(table_t * table, double Num, element_t * elem);
extern int binary_search(table_t * table, double Num, element_t * elem);

#define MAX_HASH_TABLE_SIZE 32
extern int hash(char * stu_name);
extern int hash_search(table_t * table, char* stu_name, element_t * elem);
extern int hash_insert(table_t *table, element_t elem);

	/******************************************************************************************/
	//  各种排序操作函数
	//
	/******************************************************************************************/
extern void simple_select_sort(table_t * table);
extern void simple_insert_sort(table_t * table);
extern void bubble_sort(table_t * table);
extern void quick_sort(table_t * table,int first,int last);

	/******************************************************************************************/
	//  各种多线程同步函数
	//
	/******************************************************************************************/
extern DWORD WINAPI thread_main(LPVOID lpParam);

#endif //MY_STRUCT_H