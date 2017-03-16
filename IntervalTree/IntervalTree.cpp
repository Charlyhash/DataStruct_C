/*线段树*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#pragma warning(disable:4996)

#define MAXN 1000
#define MAX_INT 0x7fffffff

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int NextPow(int n)
{
	--n;
	n = n >> 1 | n;
	n = n >> 2 | n;
	n = n >> 4 | n;
	n = n >> 8 | n;
	n = n >> 16 | n;

	return ++n;
}

struct IntervalTreeNode
{
	int val;
	int addMask; //延迟标记使用
}intervalTree[MAXN]; //创建一个最大为1000的线段树。intervalTree[0]为根节点

/*
使用arr[]初始化线段树。root为根节点的位置。istart为数组起始位置，iend为数组结束位置
*/
void IntervalTreeBuilt(int root, int arr[], int istart, int iend)
{
	intervalTree[root].addMask = 0;
	if (istart == iend) //叶子节点，此时arr[istart]便是该节点的值
		intervalTree[root].val = arr[istart];
	else
	{
		//否则，递归
		int mid = (istart + iend) >> 1;
		IntervalTreeBuilt(root * 2 + 1, arr, istart, mid);// 构建左子树
		IntervalTreeBuilt(root * 2 + 2, arr, mid + 1, iend);//构建右子树
		//当前节点的值
		intervalTree[root].val = min(intervalTree[root * 2 + 1].val, intervalTree[root * 2 + 2].val);
	}
}


//辅助函数：向下传递标志，root为当前的节点
//pushdown函数的作用仅仅只是把addMask传给子节点，然后把当前节点的addMask设置为0
void PushDown(int root)
{
  
	if (intervalTree[root].addMask != 0)
	{
		intervalTree[root].addMask = 0;
		//更新子节点的addMask和val(因为所有的子节点都要加上addMask,因此这个区间的
		//最小值也要加上addMask)
		intervalTree[root * 2 + 1].addMask += intervalTree[root].addMask;
		intervalTree[root * 2 + 2].addMask += intervalTree[root].addMask;
		intervalTree[root * 2 + 1].val += intervalTree[root].addMask;
		intervalTree[root * 2 + 2].val += intervalTree[root].addMask;
	}
}

//查询操作：root为根节点，当前区间[nstart, nend],查询区间[qstart, qend].
//查询区间的最小值
int intervalTreeQuery(int root, int nstart, int nend, int qstart, int qend)
{
	//没有交集
	if (qstart > nend || qend < nstart)
		return MAX_INT;
	//当前区间包含在查询区间:返回当前节点的值
	if (qstart <= nstart && qend >= nend)
		return intervalTree[root].val;
	//分别从左右子树查询
	PushDown(root);//向下传递
	int mid = (nstart + nend) >> 1;
	return min(intervalTreeQuery(root * 2 + 1, nstart, mid, qstart, qend),
		intervalTreeQuery(root * 2 + 2, mid + 1, nend, qstart, qend));
}

//区间更新：把addMask加到root所代表的的区间并向下传递
//[nstart, nend]位当前节点所表示的区间
//[ustart, uend]为待更新的区间
//addVal为更新值
void intervalTreeUpdate(int root, int nstart, int nend, int ustart, int uend, int addVal)
{
	//没有交集
	if (ustart > nend || uend < nstart)
		return;
	//当前节点包含的区间在更新区间内
	if (ustart <= nstart && uend >= nend)
	{
		intervalTree[root].addMask += addVal;
		intervalTree[root].val += addVal;
		return;
	}
	//更新左右子树
	PushDown(root);
	int mid = (nstart + nend) >> 1;
	intervalTreeUpdate(root * 2 + 1, nstart, mid, ustart, uend, addVal);
	intervalTreeUpdate(root * 2 + 2, mid+1, nend, ustart, uend, addVal);
	//更新当前节点的val
	intervalTree[root].val = min(intervalTree[root * 2 + 1].val, intervalTree[root * 2 + 2].val);
}

void Print(int len)
{
	for (int i = 0; i < NextPow(len)-1; ++i)
		printf("(%d) ", intervalTree[i].val);
	printf("\n");
}

void test_interval_tree()
{
	int arr[6] = {2,5,1,4,3,9};
	//测试built函数
	IntervalTreeBuilt(0, arr, 0, 5);
	Print(12);
	//测试query函数
	printf("[1,3]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 1, 3));
	printf("[0,2]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 0, 4));
	printf("[3,5]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 3, 5));

	//测试updata
	intervalTreeUpdate(0, 0, 5, 1, 3, 2);
	Print(12);
	//测试query函数
	printf("[1,3]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 1, 3));
	printf("[0,2]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 0, 4));
	printf("[3,5]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 3, 5));


	intervalTreeUpdate(0, 0, 5, 0, 2, 1);
	Print(12);
	//测试query函数
	printf("[1,3]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 1, 3));
	printf("[0,2]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 0, 4));
	printf("[3,5]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 3, 5));


	intervalTreeUpdate(0, 0, 5, 3, 5, 2);
	Print(12);
	//测试query函数
	printf("[1,3]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 1, 3));
	printf("[0,2]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 0, 4));
	printf("[3,5]的最小值：%d\n", intervalTreeQuery(0, 0, 5, 3, 5));

}



int main()
{
	test_interval_tree();
	//printf("%d %d %d", NextPow(15), NextPow(16), NextPow(17));
	printf("down!\n");

	return 0;
}