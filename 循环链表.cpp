#include<bits/stdc++.h>
using namespace std;

template<class T>
struct CircLinkNode
{
	T data;
	CircLinkNode<T>*next;
	CircLinkNode(CircLinkNode<T>*n=NULL){next=n;}
	CircLinkNode(T d,CircLinkNode<T>*n=NULL){data=d;next=n;}
};

template<class T>
class CircList
{
public:
	CircList(const T&x);
	CircList(CircList<T>&L);
	~CircList();
	int Length()const;
	bool IsEmpty(){return first->next==first;}
	bool IsHead(CircLinkNode<T>*p){return p==first;}
	CircLinkNode<T>*getHead()const{return first;}
	CircLinkNode<T>*getNext(CircLinkNode<T>*p){return p->next;}
	void setHead(CircLinkNode<T>*p){first=p;}
	
	//循环链表的搜索算法 
	CircLinkNode<T>*Search(T x)
	{
		CircLinkNode<T>*current=first->next;
		while(current!=first&&current->data!=x)current=current->next;
		return current;
	}
	
	CircLinkNode<T>*Locate(int i);
	T* getData(int i);
	void setData(int i,T& x);
	bool Insert(int i,T& x);
	bool Remove(int i,T& x);
	
private:
	CircLinkNode<T>*first,*last;
};

//约瑟夫环问题
template<class T>
void Josephus(CircList<T>&Js,int n,int m)
{
	CircLinkNode<T>*p=Js.Locate(1),*pre=NULL;
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=1;j<m;j++){pre=p;p=p->next;}
		cout<<"出列的人是"<<p->data<<endl;
		pre->next=p->next;
		delete p;
		p=pre->next; 
	}
} 

int main()
{
	return 0;
} 
