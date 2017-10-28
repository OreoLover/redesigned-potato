/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           mystruct.h
** Last modified Date:  2012-12-19
** Last Version:        1.0
** Descriptions:        ����˳������������������ݽṹ���ͺ���ز�������
**                      ��������������ؿ��ƺ�����ʵ���ʱ�������Щ��������
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
#ifndef MY_STRUCT_H
#define MY_STRUCT_H

/******************************************************************************************/
//  ����Ϊ���ֽṹ���Ͷ���
//
/******************************************************************************************/
#define MAX_NAME_SIZE	40
//����ɼ������Ԫ������
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
//����˳���ṹ
typedef struct table_t{
	element_t data[MAX_TABLE_SIZE];
	int length;
}table_t;

//��������
typedef struct node_t{
	element_t data;
	struct node_t* next;
}node_t;

//��������
typedef struct link_t{
	node_t * head;
	//node_t * tail;
	int length;
}link_t;

//�������������
typedef struct tnode_t{
	element_t data;
	struct tnode_t * Lchild;
	struct tnode_t * Rchild;
}tnode_t;

//���������
typedef struct tree_t{
	tnode_t * root;
	int num;
}tree_t;

//������˹�������ÿ�����˹���Ľṹ
#pragma pack(1)
struct Parms{
	int Section;        //ָʾ��������Ԫ�ص��ĸ��ֶ�
	bool MaxValid;      //ָʾ���������Ƿ������ֵ
	long Max;  //�����������ֵ�޶ȣ�����������������ֵ��С������޶�
	bool MinValid;      //ָʾ���������Ƿ�����Сֵ
	long Min;  //����������Сֵ�޶ȣ�����������������ֵ�����ڻ��������޶�
	bool Not;           //ָʾ���ս���Ƿ���������ȡ����0��ʾ��ȡ��
};
#pragma pack()

//������˹������ڵ�
typedef struct filter_tnode_t{
	int id;  //ÿ���ڵ�Ψһ��Id ��ͨ�����Id�����������ɾ�������ҵ���Ӧ�Ľڵ�
	struct Parms rules;  //Ԫ���򣬼�һ�����˹���
	struct filter_tnode_t * Lchild; //��������ʵ�ʶ�Ӧ�ڹ��˹���֮��ġ��롱��ϵ
	struct filter_tnode_t * Rchild; //��������ʵ�ʶ�Ӧ�ڹ��˹���֮���"��"��ϵ
}filter_tnode_t;
//������˹�����
typedef struct filter_tree_t{
	filter_tnode_t * root;
	int num;
}filter_tree_t;
//��������ֶ�Sectionָʾ
#define FLT_SEX		0
#define FLT_PINSHI	1
#define FLT_QIZHONG	2
#define FLT_SHIYAN	3
#define FLT_QIMO	4
#define FLT_OVERALL	5

//������̲߳���ʱ������Ľṹ
#pragma pack(1)
typedef struct thread_command_t{
	unsigned long command;
	union {
		int location;
		double stuID;
	}arg;
	element_t data;
}thread_command_t;
//������̲߳�������
#define MULTI_THREAD_INSERT	0
#define MULTI_THREAD_DELETE 1

#pragma pack()
/******************************************************************************************/
//  ����Ϊ���ֽṹ�Ĳ����������壬ע����extern��Ϊǰ׺�����ڽ���ģ��ʹ��
//
/******************************************************************************************/
	/******************************************************************************************/
	//  ˳���ṹ����������
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
	//  ����ṹ����������
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
	//  �������ṹ����������
	//
	/******************************************************************************************/
extern tree_t * init_tree();
extern void free_tree(tree_t * tree);
extern void free_tree_nodes(tnode_t * root);
extern int insert_BS_tree(tree_t * tree, element_t data); //������������ķ�ʽ����Ԫ�أ��������ǡ��ܷ�-overall��
extern void inorder_tree(tnode_t * root);
extern void preorder_tree(tnode_t * root);
extern void postorder_tree(tnode_t * root);
extern tnode_t * get_element_tree(tnode_t * root, double stuID);

	/******************************************************************************************/
	//  ���ֹ������Ĳ�������
	//
	/******************************************************************************************/
extern filter_tree_t * init_filter_tree();
extern void free_filter_tree(filter_tree_t * tree);
extern void free_filter_tree_nodes(filter_tnode_t * root);
extern int insert_filter_tree(filter_tree_t * tree, int my_id, Parms rules,int parent_id, int type); //�����˹������ķ�ʽ����Ԫ�أ�
//������parent_id�ڵ��type��0-���ӻ�1-�����ϣ���
//���parent_idΪ0���򱾽ڵ���Ϊ�������ĸ�������typeָʾ����ԭ����������Ϊ���ڵ�����ӻ������ӡ�����typeָʾ���Ǳ��ڵ���Ϊ���ڵ�����ӻ����ӡ�
//�����ڵ���Ϊ���ڵ������������ʱ�����ڵ�ԭ��������������Ϊ���ڵ��������
//�����ڵ���Ϊ���ڵ������������ʱ�����ڵ�ԭ��������������Ϊ���ڵ��������
extern int delete_filter_tree(filter_tree_t *tree, int id); //�����˹������ķ�ʽɾ��ָ��id��Ԫ�أ�
//�����ڵ������ĸ�ʱ��ԭ����������Ϊ�µ�������ԭ����������Ϊ�¸����������������Ӹ���ʼһֱ���ң����ﾡͷʱ����,������ڵ�û�����ӣ���ֱ�ӽ����ڵ�������Ϊ��������
//�����ڵ���Ϊ���ڵ�����ɾ��ʱ�����ڵ�ԭ�������ӽ���Ϊ���ڵ��������,���ڵ�ԭ��������������Ϊ���ڵ�������������������������ڵ�û�����ӣ���ֱ�ӽ����ڵ�������Ϊ���ڵ�����ӣ�����
//�����ڵ���Ϊ���ڵ�����ɾ��ʱ�����ڵ�ԭ�������ӽ���Ϊ���ڵ��������,���ڵ�ԭ��������������Ϊ���ڵ�������������������������ڵ�û�����ӣ���ֱ�ӽ����ڵ�������Ϊ���ڵ�����ӣ�����
extern int edit_filter_tnode(filter_tnode_t * root, int id, Parms rules);  //�޸Ĺ��˹�������ָ��id�Ľڵ��rules
extern BOOL do_filter(filter_tnode_t * root, element_t data);  //ʹ�ù��˹������ֽڵ��rules�������data���й��˼��
//���ݹ��˹�������ԭ�������㷨�����ȸ�����Ϊ��ܣ����еݹ��ص㣺
//���ȼ������������������о���������¼�ƽ����Ϊ�棬�ͼ�������������������������������������õĽ��Ϊ�棬��ֱ�ӷ��ؽ��Ϊ��
//��������Ϊ�ٻ��߸�Ϊ���Ҽ������������Ϊ�٣��ż�������������������Ϊ���������Ϊ��������һ����ֱ�ӷ����ˣ���������������Ϊ�棬�򷵻ؽ���棬������������������Ϊ�٣��򷵻ؽ��Ҳ�Ǽ٣�������
//����������ӻ�����Ϊ�գ���������Ӧ���裬�Ը��Ľ����������һ��������Ľ��Ϊ�٣���û���������������ս��Ϊ�١���������Ϊ�棬û��������������ֱ��Ϊ�棬��������

	/******************************************************************************************/
	//  ���ּ�����������
	//
	/******************************************************************************************/
extern int sequence_search(table_t * table, double Num, element_t * elem);
extern int binary_search(table_t * table, double Num, element_t * elem);

#define MAX_HASH_TABLE_SIZE 32
extern int hash(char * stu_name);
extern int hash_search(table_t * table, char* stu_name, element_t * elem);
extern int hash_insert(table_t *table, element_t elem);

	/******************************************************************************************/
	//  ���������������
	//
	/******************************************************************************************/
extern void simple_select_sort(table_t * table);
extern void simple_insert_sort(table_t * table);
extern void bubble_sort(table_t * table);
extern void quick_sort(table_t * table,int first,int last);

	/******************************************************************************************/
	//  ���ֶ��߳�ͬ������
	//
	/******************************************************************************************/
extern DWORD WINAPI thread_main(LPVOID lpParam);

#endif //MY_STRUCT_H