
/*
  	 Written By: Muhammad Nadeem Azam
				Reg#: 2009176
				Assignemnt: 2
				Date:22-10-2010
*/



#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

struct node
{
	char data;
	struct node* next;
};
struct node* createHeaderOfList(void);				//Will create header of link list used to store output 
void insert_endOfList(struct node* L,char value);	//will be inserting nodes at end of Output link list
struct node* createstack(void);						//will create stack which will be used for infix to postfix conversion
void push(struct node* s,char ch);					//will push new element in stack
char popAndTop(struct node *s);						//will pop out top element from stack and move the pointer on seoond top
char top(struct node* s);							//will return the element at top
int isempty(struct node *s);						// will check whether stack is empty or not
int expression(char exp[20]);						//will check wthether equation is valid or not
void print(struct node *s);							//will print output link list
int CheckPrecedence(char x,char y);					//will check precedence of operators
void infixToPostfix(char exp[20]);					//will convert from infix to postfix

int main()
{
	char exp[20];
	printf("enter the expression you want to check\n");
	scanf("%s",exp);
	
	if(expression(exp)==0)			//This condition will check whether equation is valid w.r.t. brackets or not
	{
		printf("Congratulation, Now hopefully result will be 100% correct\n");
	}
	else
		printf("Sorry man, your entered equation is not valid,Now there are uncertain chances for result to be correct unless you didn't use brackets in your eqaution\n");
	
	printf("PostFix form of your Infix Equation is:\n");
	infixToPostfix(exp);
	printf("Thanks for using Program\nHit Any key to quiet\n");
	getch();
	printf("\n");
	return 0;
}
struct node* createHeaderOfList(void)
{
     struct node* L; 
     L = (struct node*)malloc(sizeof(struct node));
     L -> data = NULL;
     L -> next = NULL;
     return L;     
}
void insert_endOfList(struct node* L,char value)
{
	struct node* p=L;
	struct node* newNode;
	newNode=(struct node*)malloc(sizeof(struct node));
	while(p->next!=NULL)
	{
		p=p->next;
	}
	newNode->data=value;
	newNode->next=NULL;
	p->next=newNode;
}



struct node* createstack(void)
{

	struct node* head=(struct node*)malloc(sizeof(struct node));

	head->next=NULL;
	return head;
}
void push(struct node* s,char ch)
{
	struct node *newnode=(struct node *)malloc(sizeof(struct node));
	newnode->next=s->next;
	s->next=newnode;
	newnode->data=ch;

}

char popAndTop(struct node *s)
{
	char ch;
	struct node *temp=s->next;
	ch=temp->data;
	s->next=temp->next;
	free(temp);
	return ch;
	
}
char top(struct node* s)
{
	struct node* p=s->next;
	return p->data;
}
int isempty(struct node *s)				//will return '0' if stack is empty otherwise '1'
{
	if(s->next==NULL)
		return 0;
	else
		return 1;
}
int expression(char exp[20])			//will return '0' if equation is valid otherwise '1'
{
	struct node* s=createstack();
	int flag=0;
	int i=0;

	while(exp[i]!='\0')
	{
		if(exp[i]=='(')
			push(s,exp[i]);
		else if(exp[i]=='{')
			push(s,exp[i]);
		else if(exp[i]=='[')
			push(s,exp[i]);

		if(exp[i]==')')
		{
			

			if(exp[i]==')'&&isempty(s)&&popAndTop(s)=='(')
			{
				i++;
				flag=1;
				continue;
			}
			else
			{
				
				flag=0;
				break;
			}
			
		}

	i++;
	}
	if(flag==1&&!isempty(s)){
		printf("Entered Equation is Valid\n");
		return 0;
	}

	else
	{
		printf("\nNot valid w.r.t. brackets\n");
		return 1;
	}
}
void print(struct node *s)
{
	struct node *p=s;
	while(p->next!=NULL)
	{
		printf("%c",popAndTop(p));
	}
	printf("\n\n");

}

int CheckPrecedence(char x,char y)			//will return 0 if former has higher precedence than later otherwise '1'
{
	if(x=='/')
		return 0;
	else if(x=='*'&&y!='/')
		return 0;
	else if((x=='+'||x=='-')&&y!='*'&&y!='/')
		return 0;
	else if((x=='+'||x=='-')&&(y=='+'||y=='-'))
		return 0;
	else
		return 1;
}
void infixToPostfix(char exp[20])			
{
	struct node* s1=createHeaderOfList();			//s1: it is a link list, will be used to store output
	struct node* s2=createstack();					//s2: it is dynamic stack used for conversion
	int i=0;
	while(exp[i]!='\0')
	{
		if(exp[i]!='+'&&exp[i]!='-'&&exp[i]!='*'&&exp[i]!='/'&&exp[i]!='('&&exp[i]!=')')
		{
			insert_endOfList(s1,exp[i]);
		}
		else if(isempty(s2)==0)
		{
			push(s2,exp[i]);
		}
		else if((exp[i]=='+'||exp[i]=='-'||exp[i]=='*'||exp[i]=='/')&&isempty(s2)!=0)   
		{
			if(CheckPrecedence(exp[i],top(s2))!=0)
			{
				insert_endOfList(s1,popAndTop(s2));
				if(exp[i]==top(s2)&&isempty(s2)!=0)
				{
					push(s2,exp[i]);
					insert_endOfList(s1,popAndTop(s2));
					
				}
				else
					push(s2,exp[i]);

			}
			else
			{
				push(s2,exp[i]);
			}

		}
		else if(exp[i]=='(')
		{

			push(s2,exp[i]);
		}
		else if(exp[i]==')')
		{
			while(top(s2)!='(')
			{
				insert_endOfList(s1,popAndTop(s2));
			}
			char temp=popAndTop(s2);
		}
			i++;
	}
	if(isempty(s2)!=0)
	{
		while(isempty(s2)!=0)
		{				
			insert_endOfList(s1,popAndTop(s2));
		}
	}
	print(s1);			//printing output link list
	
}




