#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


/* 定义ElemType为int类型 */
typedef int ElemType;
void        input(ElemType& s);
void        output(ElemType s);
int         equals(ElemType a, ElemType b);

/* 单链表类型定义 */
typedef struct LNnode
{
    ElemType       data;
    struct LNnode* next;
} LNnode, *LinkList;
void InitList(LinkList& L);
int  ListInsert(LinkList& L, int i, int e);
void ListTraverse(LinkList L, void (*vi)(ElemType));
int  LocateElem(LinkList L, ElemType e, int (*compare)(ElemType, ElemType));
int
main() // main() function
{
    LinkList A;
    ElemType e;
    InitList(A);
    int n, i;
    // cout<<"Please input the list number ";
    cin >> n;
    for(i = 1; i <= n; i++)
    {
        cin >> e;
        ListInsert(A, i, e);
    }
    // cout<<"请输入查找的元素："<<endl;
    cin >> e;
    i = LocateElem(A, e, equals);
    if(i)
    {
        cout << "查找成功！" << endl;
        output(e);
        cout << "是单链表第" << i << "个元素" << endl;
    }
    else
        cout << "查找失败！" << endl;
}


/*****ElemType类型元素的基本操作*****/
void
input(ElemType& s)
{
    cin >> s;
}
void
output(ElemType s)
{
    cout << s << " ";
}
int
equals(ElemType a, ElemType b)
{
    if(a == b)
        return 1;
    else
        return 0;
}

/*****单链表的基本操作*****/
void
InitList(LinkList& L)
{                                         // 操作结果：构造一个空的单链表L
    L = (LinkList)malloc(sizeof(LNnode)); // 产生头结点，并使L指向此头结点
    if(!L)                                // 存储分配失败
        return;
    L->next = NULL; // 指针域为空
}

int
ListInsert(LinkList& L, int i, ElemType e)
{ // 在带头结点的单链线性表L的第i个元素之前插入元素e
    LinkList p, s;
    p     = L;
    int j = 0;
    while(p && j < i - 1)
    { // 寻找第i-1个结点
        p = p->next;
        ++j;
    }
    if(!p || j > i - 1)
        return 0;                               // i小于1或者大于表长
    s       = (LinkList)malloc(sizeof(LNnode)); // 生成新结点
    s->data = e;
    s->next = p->next; // 插入L中
    p->next = s;
    return 1;
}

void
ListTraverse(LinkList L, void (*vi)(ElemType))
{ // 初始条件：单链表L已存在。
    // 操作结果：依次对L的每个数据元素调用函数vi()
    LinkList p = L->next;
    while(p)
    {
        vi(p->data);
        p = p->next;
    }
    printf("\n");
}

int
LocateElem(LinkList L, ElemType e, int (*equal)(ElemType, ElemType))
{
    // 初始条件: 单链表L已存在，equal()是数据元素判定函数(满足为1，否则为0)
    // 操作结果: 返回L中第1个与e满足关系equal()的数据元素的位序，若这样的数据元素不存在，则返回值为0
    /********** Begin **********/

    LinkList p = L->next;
    int      i = 1;

    while(p)
    {
        if(equal(p->data, e))
            return i;
        p = p->next;
        i++;
    }

    return 0;
}
