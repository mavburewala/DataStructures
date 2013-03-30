
/*
  This Program Creates Expression Tree For valid PostFix Equation
					Written By: Muhammad Nadeem Azam
							Reg#: 2009176
							Assignemnt: 3
							Date:03-12-2010
*/

#include<stdio.h>
#include<stdlib.h>
//typedef declarations for Tree Structure
typedef struct TreeNode *TPosition;
typedef struct TreeNode *Tree;
/*
typedef declarations for Stack Structure which is being used for building Expression Tree, for futher 
references, just "Expression Stack" term is used in short
*/
typedef struct Exp_StackNode *ExpStack;
typedef struct Exp_StackNode *PtrToExpSNode;
//typedef declarations for Stack Structure which is being used to check validity of the entered PostFix Equation
typedef struct StackNode *Stack;
typedef struct StackNode *PtrToStack;

struct TreeNode					//Tree Node
{
	char data;
	Tree Left;
	Tree Right;
};
struct Exp_StackNode			//Stack Node(being used for buliding Expression Tree
{
	Tree PtrToTreeNode;
	PtrToExpSNode next;
};
struct StackNode				//Stack Node(being used for Checking Validity of PostFix Equation 
{
	char data;
	PtrToStack next;
};
//Methods being used for building Tree
Tree createTreeNode(char x);
void InOrder(Tree Root);
void PostOrder(Tree Root);
void PreOrder(Tree Root);
//Methods being used for Expression Stack
ExpStack createExpStack(void);
void PushIntoExpStack(TPosition TreePos, ExpStack S);
int IsEmpty_ExpStack(ExpStack S);
TPosition Pop(ExpStack S);
//Methods being used for Stack
Stack createStack(void);
void PushIntoExpStack(char data, Stack S);
int IsEmpty_Stack(Stack S);
void Pop(Stack S);

int PostfixCheck(char equation[]);			//This methods Checks whether Postfix Equation is valid or Not
Tree BulidTree(char equation[]);			// This method creates Expression Tree for Valid PostFix Equation

int main()
{
	Tree T;
	printf("\t\t\t\tWelcome!!\n\tThis Program creates Expression tree For PostFix Equation\n\n");
	char equation[20];
    printf("Enter Expression:  ");
    scanf("%s",equation);
	printf("Your Entered Equation is\n");
	printf("\t\t\t\t%s\n",equation);
	if(PostfixCheck(equation)==1)			//Incase Equation is Valid
	{
		printf("\t\t\tIt is Valid PostFix Equation\n\tNow We can proceed further to build Exppress Tree for given equation\n\n\n");
		T=BulidTree(equation);				//Expression Tree Building Method is being called at this stage
		printf("\nInfix Equation by InOrder Traversal of Tree:\t\t");
		InOrder(T);
		printf("\nPostfix Equation by PostOrder Traversal of Tree:\t");
		PostOrder(T);
		printf("\nPrefix Equation by PreOrder Traversal of Tree:\t\t");
		PreOrder(T);
		printf("\n\t\t**********************************************\n\t\t\tThanks For Using Program\n\n");
	}
	else				//If Equation is Invalid, Program excuses to build expression Tree and stops
		printf("Equation is Invalid\nSorry!!!\n\t\tExpression Tree can't be built for Invalid Postfix Equation\n");
	return 0;
}

Tree createTreeNode(char x)		//This method creates Single Node for Tree and returns it's pointer
{
    Tree T;    
	T = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if( T == NULL )
		printf( "Out of space!!!");
    else
    {
		T->data = x;
		T->Left = T->Right = NULL;
    }
	return T;
}
void InOrder(Tree Root)		//InOrder Traversal
{
	if (Root !=NULL)
	{
		InOrder(Root->Left);
		printf("%c",Root->data);
		InOrder(Root->Right);
	}
}
void PostOrder(Tree Root)		//POstOrder Traversal
{
	if (Root !=NULL)
	{
		PostOrder(Root->Left);
		PostOrder(Root->Right);
		printf("%c",Root->data);
	}
}
void PreOrder(Tree Root)		//PreOrder Traversal
{
	if (Root !=NULL)
	{
		printf("%c",Root->data);
		PreOrder(Root->Left);
		PreOrder(Root->Right);
	}
}

ExpStack createExpStack(void)		//This method creates Expression Stack	
{
	PtrToExpSNode NewNode;
	NewNode=(struct Exp_StackNode*)malloc(sizeof(struct Exp_StackNode));
	NewNode->PtrToTreeNode=NULL;
	NewNode->next=NULL;
	return NewNode;
 }
void PushIntoExpStack(TPosition TreePos, ExpStack S)		// This Method pushes TreeNode pointer into Expression Stack
{
		PtrToExpSNode TmpCell;
		TmpCell=(struct Exp_StackNode*)malloc(sizeof(struct Exp_StackNode));
		if (TmpCell== NULL)
		{
			printf("Out of Space!");
		}
		else
		{
			TmpCell->PtrToTreeNode=TreePos;
			TmpCell->next= S->next;
			S->next= TmpCell;
		}
}
int IsEmpty_ExpStack(ExpStack S)			//This Method returns 0 if Expression Stack is empty otherwise 1
{
	if(S->next== NULL)
	{
		return 0;
	}
	else
		return 1;
}
TPosition Pop_ExpStack(ExpStack S)		//This Method Pops out TreeNode pointer at Top of Expression Stack
{
	PtrToExpSNode TmpCell;
	TmpCell= S->next;
	if (IsEmpty_ExpStack(S)!=1)
	{
		printf("Empty Stack");
		return NULL;
	}
	else
	{
		S->next= S->next->next;
		return TmpCell->PtrToTreeNode;
	}
	free(TmpCell);		//freeing the space
}


Stack createStack(void)		//creates stack
{
	PtrToStack NewNode;
	NewNode=(struct StackNode*)malloc(sizeof(struct StackNode));
	NewNode->data=NULL;
	NewNode->next=NULL;
	return NewNode;
 }
void PushIntoStack(char data, Stack S)			//pushes character data into stack
{
		PtrToStack TmpCell;
		TmpCell=(struct StackNode*)malloc(sizeof(struct StackNode));
		if (TmpCell== NULL)
		{
			printf("Out of Space!");
		}
		else
		{
			TmpCell->data=data;
			TmpCell->next= S->next;
			S->next= TmpCell;
		}
}
int IsEmpty_Stack(Stack S)		//returns 0 incase stack is empty otherwise 1
{
	if(S->next== NULL)
	{
		return 0;
	}
	else
		return 1;
}
void Pop_Stack(Stack S)			//Just deletes node at top, without returning anything
{
	PtrToStack TmpCell;
	TmpCell= S->next;
	if (IsEmpty_Stack(S)!=1)
	{
		printf("Empty Stack");
	}
	else
	{
		S->next= S->next->next;
	}
	free(TmpCell);
}


int PostfixCheck(char equation[])	//This method checks either Postfix Equation is valid or not, incase of valid, it returns 1
{
	int i;
	Stack S;
	S=createStack();
	for(i=0;equation[i]!='\0';i++)
	{
		if(equation[i]!='+' && equation[i]!='-'  && equation[i]=='/'  && equation[i]=='*')
		{
			PushIntoStack(equation[i],S);
		}
		else if(equation[i]=='+' || equation[i]=='-'  || equation[i]=='/'  || equation[i]=='*')
		{
			Pop_Stack(S);
			Pop_Stack(S);
			PushIntoStack(equation[i],S);
		}
		else
			PushIntoStack(equation[i],S);
	}
	Pop_Stack(S);
	if(IsEmpty_Stack(S)==0)
		return 1;
	else
		return 0;
}


Tree BulidTree(char equation[])		//Builds Expression Tree
{
	Tree T[20];
	int i;
	ExpStack S;
	S=createExpStack();
	for(i=0;equation[i]!='\0';i++)
        {
                if(equation[i]!='+' && equation[i]!='-'  && equation[i]!='/'  && equation[i]!='*')
                {
                        T[i]=createTreeNode(equation[i]);
						PushIntoExpStack(T[i],S);
                }
                else if(equation[i]=='+' || equation[i]=='-'  || equation[i]=='/'  || equation[i]=='*')
                {
					T[i]=createTreeNode(equation[i]);
					T[i]->Right=Pop_ExpStack(S);
                    T[i]->Left=Pop_ExpStack(S);
					PushIntoExpStack(T[i],S);
                }
				else
				{
					T[i]=createTreeNode(equation[i]);
					PushIntoExpStack(T[i],S);
				}

        }
	printf("Expression Tree has been successfully built!!!\n"); 
	return Pop_ExpStack(S);	//returns Root of newly built Expression Tree
}
