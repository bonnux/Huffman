#include<iostream>
using namespace std;

//赫夫曼树结点
struct node
{
    int lchild, rchild, parent;
    double weight;
    char ch;
};

//找权值最小的两个结点
void Select(node p[], int *a, int *b, int n)
{
    int i;
    double weight = 0;
    for(i = 0; i <n; i++)      //找权值最小的结点
    {
        if(p[i].parent != - 1) //如果有父结点的，不进行判断
            continue;
        else
        {
            if(weight == 0)
            {
                weight = p[i].weight;
                *a = i;
            }
            else
            {
                if(p[i].weight < weight)   //找出最小的权值
                {
                    weight = p[i].weight;
                    *a = i;
                }
            }
        }
    }

    weight = 0;
    for(i = 0; i < n; i++)    //找权值次小的结点
    {
        if(p[i].parent != -1 || (i == *a))
            continue;
        else
        {
            if(weight == 0)
            {
                weight = p[i].weight;
                *b = i;
            }
            else
            {
                if(p[i].weight < weight)
                {
                    weight = p[i].weight;
                    *b = i;
                }
            }
        }
    }
    int temp;
    if(p[*a].weight > p[*b].weight)//避免根结点的左右子树混淆
    {
        temp = *a;
        *a = *b;
        *b = temp;
    }
}

//建立赫夫曼树
void HuffmanTree(node p[], double w[], char ch[], int n)
{
    for(int i = 0; i < 2 * n - 1;i++) //构造空的赫夫曼树
    {
        p[i].parent = -1;	//双亲结点
        p[i].lchild = -1;	//左孩子结点
        p[i].rchild = -1;	//右孩子结点
    }
    for(int i = 0; i < n; i++)		//构造包含n棵二叉树的森林
    {
        p[i].weight = w[i];	    //给赫夫曼树赋权值
        p[i].ch = ch[i];		//赋字符值
    }
    for(int k = n; k < 2 * n - 1; k++)  //建立赫夫曼树
    {
        int i1 = 0;
        int i2 = 0;
        Select(p,&i1,&i2,k);	//在森林中找权值最小的两个结点
        p[i1].parent = k;	    //将两个最小的结点合并
        p[i2].parent = k;
        p[k].weight = p[i1].weight + p[i2].weight;
        p[k].lchild = i1;
        p[k].rchild = i2;
    }
}

//赫夫曼编码
void HuffmanCode(node p[], int n)
{
    int i, j,k;
    string s = "";
    for(i = 0; i < n; i++)	//在数组p中前n个元素是叶子结点，需要编码
    {
        s = "";			        //编码s初始化为空串
        j = i;					//暂存i
        while(p[j].parent != -1)	//结点j存在双亲
        {
            k = p[j].parent;
            if(j == p[k].lchild)	//结点j是左孩子，编码为0
            {
                s = s + "0";
            }
            else				    //结点j是右孩子，编码为1
            {
                s = s + "1";
            }
            j = p[j].parent;	   //遍历下一个结点
        }
        cout<<p[i].ch<<"：";
        for(int i =s.size() - 1; i >= 0; i--)	//将赫夫曼编码逆序输出
        {
            cout<<s.at(i)<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    const int n = 5;
    node treeNode[n];
    char ch[] = {'a','b','c','d','e'};
    double w[] = {10, 20, 25, 30, 15};
    HuffmanTree(treeNode,w,ch,n);
    HuffmanCode(treeNode,n);
    return 0;
}