#ifndef __LIST_H__
#define __LIST_H__

/*
实现一个循环单链表
STL的list很难用啊
*/


#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
	int val;
	ListNode* next;

	ListNode(int val_ = 0) : val(val_), next(NULL) {}
};

struct List
{
	ListNode* head;
	List(ListNode* node = NULL) : head(node) {}
};


//使用vector创建一个循环链表，返回链表的头
List* createList(vector<int>& v)
{
	List* l = new List();
	if (v.size() == 0)
	{
		l->head = NULL;
		l->head->next = NULL;
	}
	else
	{
		l->head = new ListNode(v[0]);
		l->head->next = l->head;
		ListNode* cur = l->head;
		for (int i = 1; i < v.size(); ++i)
		{
			ListNode* tmp = new ListNode(v[i]);
			cur->next = tmp;
			tmp->next = l->head;
			cur = cur->next;
		}
	}

	return l;
}
//遍历链表并将结果存放在数组中
void traverseList(List* l, vector<int>& v)
{
	ListNode* cur = l->head;
	if (cur == NULL)
		return;
	while (cur->next != l->head)
	{
		v.push_back(cur->val);
		cur = cur->next;
	}
	v.push_back(cur->val);
}
//插入一个元素
List* insertList(List* l, int val)
{
	if (l->head == NULL)
	{
		l->head = new ListNode(val);
		l->head->next = l->head;
	}
	else
	{
		ListNode* cur = l->head;
		while (cur->next != l->head)
			cur = cur->next;
		ListNode* tmp = new ListNode(val);
		cur->next = tmp;
		tmp->next = l->head;
	}

	return l;
}

//删除一个元素
List* deleteList(List* l, int val)
{
	if (l->head == NULL)
		return NULL;
	ListNode* cur = l->head;
	//处理头结点删除
	if (l->head->val == val)
	{
		if (l->head->next == l->head)
		{
			ListNode* tmp = l->head;
			delete tmp;
			l->head = NULL;
		}
		else
		{
			ListNode* cur = l->head;
			while (cur->next != l->head)
				cur = cur->next;
			ListNode* tmp = cur->next;
			cur->next = tmp->next;
			l->head = cur->next;
		}
	}
	else
	{
		ListNode* cur = l->head;
		while (cur->next->val != val && cur->next != l->head)
			cur = cur->next;
		if (cur->next->val == val)
		{
			ListNode* tmp = cur->next;
			cur->next = tmp->next;
			delete tmp;
		}
	}

	return l;
}

#endif