#ifndef __LIST_H__
#define __LIST_H__

/*
ʵ��һ��ѭ��������
STL��list�����ð�
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


//ʹ��vector����һ��ѭ���������������ͷ
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
//������������������������
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
//����һ��Ԫ��
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

//ɾ��һ��Ԫ��
List* deleteList(List* l, int val)
{
	if (l->head == NULL)
		return NULL;
	ListNode* cur = l->head;
	//����ͷ���ɾ��
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