/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           shadow.h
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        ����Ӱ��˳�����������������ز�������
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
#ifndef SHADOW_H
#define SHADOW_H

#include "mystruct.h"

#define MAX_XING 30
#define MAX_MING 48
	//����������������
extern void AddHelp(CString csHelp);
	//�������һ��Ԫ��
extern element_t rand_element();
/******************************************************************************************/
//  ����Ϊ���ֽṹ�Ĳ����������壬ע����extern��Ϊǰ׺�����ڽ���ģ��ʹ��
//
/******************************************************************************************/
	/******************************************************************************************/
	//  ˳���ṹ����������
	//
	/******************************************************************************************/
extern table_t * shd_init_table();
extern void shd_free_table(table_t * t);
extern int shd_get_table(table_t * table,int index, element_t * elem);
extern int shd_add_table(table_t * table, element_t data);
extern int shd_insert_table(table_t * table, element_t data, int location);
extern int shd_insert_table_by_order(table_t * table, element_t data);
extern int shd_delete_table(table_t * table, char * name);
extern void shd_delete_table_below(table_t * table, int x);
extern int shd_delete_table_by_index(table_t * table, int index);

	/******************************************************************************************/
	//  ����ṹ����������
	//
	/******************************************************************************************/
extern link_t * shd_init_link();
extern void shd_free_link(link_t * t);
extern int shd_add_link(link_t * link, element_t data);
extern int shd_get_link(link_t * link,int index, element_t * elem);
extern int shd_insert_link(link_t * link, element_t data, int location);
extern int shd_insert_link_by_order(link_t * link, element_t data);
extern int shd_delete_link(link_t * link, char * name);
extern void shd_delete_link_below(link_t * link, int x);

	/******************************************************************************************/
	//  �������ṹ����������
	//
	/******************************************************************************************/
extern tree_t * shd_init_tree();
extern void shd_free_tree(tree_t * tree);
extern void shd_free_tree_nodes(tnode_t * root);
extern int shd_insert_BS_tree(tree_t * tree, element_t data);
extern void shd_inorder_tree(tnode_t * root);
extern void shd_preorder_tree(tnode_t * root);
extern void shd_postorder_tree(tnode_t * root);
extern tnode_t * shd_get_element_tree(tnode_t * root, double stuID);

	/******************************************************************************************/
	//  ���ּ�����������
	//
	/******************************************************************************************/
extern int shd_sequence_search(table_t * table, double Num, element_t * elem);
extern int shd_binary_search(table_t * table, double Num, element_t * elem);

extern int shd_hash(char * stu_name);
extern int shd_hash_search(table_t * table, char* stu_name, element_t * elem);
extern int shd_hash_insert(table_t *table, element_t elem);

	/******************************************************************************************/
	//  �������������
	//
	/******************************************************************************************/
extern void shd_bubble_sort_byid(table_t * table);
extern void shd_simple_select_sort(table_t * table);
extern void shd_simple_insert_sort(table_t * table);
extern void shd_bubble_sort(table_t * table);
extern void shd_quick_sort(table_t * table,int first,int last);

	/******************************************************************************************/
	//  ���̲߳����е��̵߳ĸ���������
	//
	/******************************************************************************************/
		//��1����ִ�к���
extern DWORD WINAPI sha_thread_main( LPVOID lpParam );
extern void solo_server(char * buf);
		//��2˳����㷨����
extern void sha_thread_test_insert_table(thread_command_t * pdu);
extern void sha_thread_test_delete_table(thread_command_t * pdu);
		//��3˳����д�Ȳ������溯��
extern int shtt_get_table_length();
extern element_t shtt_get_table_element(int i);
extern void shtt_put_table_element(element_t data,int i);
extern void shtt_set_table_length(int len);
		//������صĺ���
extern BOOL IsShaThreadSolo();

extern DWORD WINAPI main_server(LPVOID lpParam);

#endif //SHADOW_H