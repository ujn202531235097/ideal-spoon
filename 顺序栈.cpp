#include<bits/stdc++.h>
using namespace std;

const int maxStack=20;
const int stackIncreament=20;//栈溢出时扩展空间的增量 

template<class T>
class SeqStack
{
	
public:
	
	//建立一个最大尺寸为sz的空栈，若分配不成功则错误处理 
	SeqStack(int sz=50):top(-1),maxSize(sz)
	{
		elements=new T[maxSize];
		if(elements==NULL){cerr<<"存储分配失败！"<<endl;exit(1);}
	}
	
	~SeqStack(){delete[] elements;} 
	
	bool IsFull()const{return top==maxSize-1;}
	bool IsEmpty()const{return top==-1;}
	
	void Push(T& x)
	{
		if(IsFull())overflowProcess();
		elements[++top]=x;
	} 
	
	bool Pop(T& x)
	{
		if(IsEmpty())return 0;
		x=elements[top--];
		return 1;
	}
	
	bool GetTop(T& x)
	{
		if(IsEmpty())return 0;
		x=elements[top];return 1; 
	}
	
	int getSize(){return top+1;}
	void MakeEmpty(){top=-1;}
	
	//输出栈中元素的重载操作
	friend ostream& operator<<(ostream& os,SeqStack<T>&s)
	{
		int i; 
		os<<"top="<<s.top<<endl;//输出栈顶位置
		for(i=0;i<=s.top;i++)os<<s.elements[i]<<" ";
		os<<endl;
		return os;
	} 

private:
	T* elements;
	int top;//栈顶指针 
	int maxSize;//栈最大可容纳元素个数 
	
	//扩充栈的存储空间 
	void overflowProcess()//栈的溢出处理 
	{
		int i;
		T* newArray=new T[maxSize+stackIncreament];
		if(newArray==NULL){cerr<<"存储分配失败！"<<endl;exit(1);}
		for(i=0;i<=top;i++)newArray[i]=elements[i];
		maxSize+=stackIncreament;
		delete[] elements;
		elements=newArray; 
	}
	
};

//在双栈中插入x，d=0插在0号栈，d!=0插在1号栈 
//bool Push(DualStack& DS,T x,int d)
//{
//	if(DS.t[0]+1==DS.t[1])return 0;//栈满
//	if(d==0)DS.t[0]++;
//	else DS.t[1]--;
//	DS.Vector[DS.t[d]]=x;//进栈
//	return 1; 
//}

//弹出栈顶元素，通过x返回。d=0从0号栈退栈，d!=0从1号栈退栈
//bool Pop(DualStack& DS,T& x,int d)
//{
//	if(DS.t[d]==DS.b[d])return 0;//栈空
//	x=DS.Vector[DS.t[d]];
//	if(d==0)DS.t[0]--;
//	else DS.t[1]++;
//	return 1; 
//}

//圆括号匹配
const int maxLength=100;
bool Match(char* expression)
{
	int i;
	SeqStack<char>S(maxLength);char ch,x;int length=strlen(expression); 
	for(i=0;i<length;i++)
	{
		ch=expression[i];
		if(ch=='(')S.Push(ch);
		else if(ch==')')
		{
			if(!S.Pop(x)){cout<<"不匹配"<<endl;return 0;}
		}
	}
	if(S.IsEmpty()){cout<<"匹配成功！"<<endl;return 1;}
	else{cout<<"匹配失败"<<endl;return 0;}
} 

//后缀表达式 
class Calculator
{
private:
	SeqStack<double>s;
	
	//从栈中退出两个操作数 
	bool Get2Operands(double& left,double& right)
	{
		if(s.IsEmpty()){cerr<<"缺少右操作数！"<<endl;return 0;}
		s.Pop(right);
		if(s.IsEmpty()){cerr<<"缺少左操作数！"<<endl;return 0;}
		s.Pop(left);
		return 1; 
	}
	
	//取两个操作数，根据操作符op形成运算指令并计算 
	void DoOperator(char op)
	{
		double left,right,value;bool result;
		result=Get2Operands(left,right);//取两个操作数
		if(result)
		{
			switch(op)
			{
				case '+':value=left+right;s.Push(value);break;
				case '-':value=left-right;s.Push(value);break;
				case '*':value=left*right;s.Push(value);break;
				case '/'://若除以0，则报错清栈
					if(fabs(right)<0.0001){cout<<"除数为0\n";s.MakeEmpty();}
					else{value=left/right;s.Push(value);}
				 	break;
			}
		} 
		else s.MakeEmpty();
	}
	
public:
	Calculator(int sz):s(sz){}
	
	//执行表达式计算，读字符串并求一个后缀表达式的值。以字符'#'结束 
	void Run()
	{
		char ch;double newOperand;
		while(cin>>ch,ch!='#')
		{
			switch(ch)
			{
				//是操作符，执行计算
				case '+':case '-':case '*':case '/':DoOperator(ch);break;
				default:
					cin.putback(ch);//将字符放回输入流
					cin>>newOperand;//重新读操作数
					s.Push(newOperand);//将操作数放入栈中 
			}
		} 
		//s.output();
		s.MakeEmpty();
	}
	
};
//void main()//先建立计算器对象，再执行计算程序 
//{
//	Calculator CALC(10);
//	CALC.Run();//输入字符流，就能得到预期的结果 
//}

int main()
{
	return 0;
}
