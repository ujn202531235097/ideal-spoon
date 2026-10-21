#include<bits/stdc++.h>
using namespace std;

template<class T>
class SeqQueue
{
protected:
	int rear,front;//队尾与队头指针
	T* elements;
	int maxSize;//队列最大容量
	
public:
	
	SeqQueue(int sz=10):rear(0),front(0),maxSize(sz)
	{
		elements=new T[maxSize];
		if(elements==NULL){cerr<<"存储分配失败！"<<endl;exit(1);}
	}
	
	~SeqQueue(){delete[] elements;}
	
	bool EnQueue(T x)
	{
		if(IsFull())return 0;
		elements[rear]=x;
		rear=(rear+1)%maxSize;
		return 1; 
	}
	
	bool DeQueue(T& x)
	{
		if(IsEmpty())return 0;
		x=elements[front];
		front=(front+1)%maxSize;
		return 1;
	}
	
	bool getFront(T& x)const
	{
		if(IsEmpty())return 0;
		x=elements[front];return 1;
	}
	
	void makeEmpty(){front=rear=0;}
	bool IsEmpty()const{return front==rear;}
	bool IsFull()const{return (rear+1)%maxSize==front;} 
	int getSize()const{return (rear-front+maxSize)%maxSize;}
	
	//输出队列中元素的重载操作
	friend ostream& operator<<(ostream& os,SeqQueue<T>&Q)
	{
		int i;
		os<<"front="<<Q.front<<",rear="<<Q.rear<<endl;
		for(i=Q.front;i!=Q.rear;i=(i+1)%Q.maxSize)os<<Q.elements[i]<<" ";
		os<<endl;
		return os;
	} 
};

//打印杨辉三角形
void YangHvi(int n)
{
	int i,j;
	SeqQueue<int>A(n+1);A.EnQueue(1);
	int s=0,t;
	for(i=0;i<n;i++)//逐行计算 
	{
		A.EnQueue(0);//各行间插入一个0 
		for(j=1;j<=i+2;j++)//处理第i行的i+2个系数(包括一个0) 
		{
			A.DeQueue(t);//读取一个系数 
			A.EnQueue(s+t);//计算下一行系数，并进队列 
			s=t;
			if(j!=i+2)cout<<s<<" ";//打印一个系数，第i+2个是0 
		}
		cout<<endl;
	}
} 

//打印杨辉三角形(改进输出) 
void YANGHVI(int n)
{
	int i,j,k;
	SeqQueue<int>A(n+1);A.EnQueue(1);
	int s=0,t;
	for(i=0;i<n;i++)//逐行计算 
	{
		for(k=0;k<n-i-1;k++)cout<<setw(3)<<" ";
		A.EnQueue(0);//各行间插入一个0 
		for(j=1;j<=i+2;j++)//处理第i行的i+2个系数(包括一个0) 
		{
			A.DeQueue(t);//读取一个系数 
			A.EnQueue(s+t);//计算下一行系数，并进队列 
			s=t;
			if(j!=i+2)cout<<setw(6)<<s;//打印一个系数，第i+2个是0 
		}
		cout<<endl;
	}
} 

int main()
{
	YANGHVI(8);
	return 0;
}
