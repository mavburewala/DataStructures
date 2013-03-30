#include <iostream>
#include <fstream>
#include <iomanip>
#include<sstream>
#include<conio.h>
#include<string.h>
using namespace std;
using std::cout;
using std::endl;

const int CellNoLength=14;
typedef struct ptrNode* FileList;
typedef struct message* Messg;
struct ptrNode
{
  Messg FileNode;
	FileList next;
};

FileList createHeaderNodeOfFileList(void);
FileList insertAtEndOfFileList(FileList L);
void printLinkedFileList(FileList L);

typedef struct node* ptrToNode;
typedef ptrToNode SimpleList;
typedef ptrToNode Position;

struct node						// Simple Link List Node
{
  char element;
  struct node* next;            
};

SimpleList createHeaderNodeOfSimpleList(void);
void insertAtEndOfSimpleList(char value, SimpleList L);
void printLinkedSimpleList(SimpleList L);

struct message
{
	char CellNo[CellNoLength];
	int year,month,day,hour,minutes;
	SimpleList content;
};

void printMessage(Messg L);
Messg createNullMessage(void);


FileList createHeaderNodeOfFileList(void)
{
	FileList L; 
     L = (struct ptrNode*)malloc(sizeof(struct ptrNode));
	 L ->FileNode = createNullMessage();
     L -> next = NULL;
     return L;
}
FileList insertAtEndOfFileList(FileList L)
{
	FileList P=L;
	while(P->next!=NULL)
	{
		P=P->next;
	}

	FileList newNode;
 
     newNode = (struct ptrNode*)malloc(sizeof(struct ptrNode));
	 newNode->FileNode=createNullMessage();
     newNode -> next = P -> next;
     P -> next = newNode;
	 return newNode;
 }

void printLinkedFileList(FileList L)
{
	FileList P=L;
	if(P->next==NULL)
		cout << "List is Empty" <<endl;
     
	while (P->next!=NULL)
     {
		 printMessage(P->FileNode);
		 P = P->next;
	 }
}

/////////////////////////////////////////////////////////////////////////
//////////////////////////Data ReadingWriting////////////////////////////
/////////////////////////////////////////////////////////////////////////

void printLinkedSimpleList(SimpleList L)		//Prints All content of Link List
{
     
	Position P = L->next;
     
     while (P!=NULL)
     {
         cout <<  P->element;
         P = P->next;
	 }       
}     
SimpleList createHeaderNodeOfSimpleList(void)			//Creates New Link List by establishing Header Node with NULL values
{
     SimpleList L; 
     L = (struct node*)malloc(sizeof(struct node));
     L -> element = NULL;
     L -> next = NULL;
     return L;     
}
void insertAtEndOfSimpleList(char value, SimpleList L)		//Creates NewNode with given character element at End Of The Link List
{
	Position P=L;
	while(P->next!=NULL)
	{
		P=P->next;
	}

	Position newNode;
 
     newNode = (struct node*)malloc(sizeof(struct node));
     newNode -> element = value;
     newNode -> next = P -> next;
     P -> next = newNode;
 }

void printMessage(Messg L)
{
	cout << "Cell No is:"<< L->CellNo<<endl;
	cout << "Year is:"<< L->year <<endl;
	cout << "Months is:"<<L->month <<endl ;
	cout << "Day is:" <<setw(2) << L->day<<endl;
	cout << "Hour is:"<<L->hour <<endl;
	cout << "Minutes are:"<<L->minutes <<endl;
	cout << "Message is:"<<endl;
	printLinkedSimpleList(L->content);
	cout << "\n" << endl;
}

Messg createNullMessage(void)
{
	Messg P;
	P=(struct message*)malloc(sizeof(struct message));
	P->content=createHeaderNodeOfSimpleList();
	return P;
}


FileList csvFileParsing(void)
{
	cout << "Welcome!!! Welcome to CSV File Parsing Module"<<endl;
	FileList COMPLETE;
	FileList L;
	COMPLETE=createHeaderNodeOfFileList();
	L=COMPLETE;
	char csv[15];
	char tempo,ch,ch1,ch2,ch3;
	ifstream File;
	while(1)
	{
	cout << "Enter CSV File Name:-";
	cout << "Make sure, You have added .csv extension at the end"<< endl;
	cout << "Press E to Exit .csv File Parsing Module" << endl;
	tempo=cin.peek();
	if (tempo=='E'||tempo=='e')
	{
		cin >> tempo;
		cout << "Module is Exiting" <<endl;
		break;
	}
	else 
	{
		cin >> csv;
		File.open(csv,ios::in);
		if(!File.fail())
		{
			cout <<"File Successfully Opens"<<endl;
			do
			{
				File.ignore(13,'"');
				File.getline(L->FileNode->CellNo,CellNoLength,'"');
				File.ignore(8);
				File >> L->FileNode->year;
				File.ignore(1,'.');
				File >> L->FileNode->month;
				File.ignore(1,'.');
				File >> L->FileNode->day;
				File.ignore(1,' ');
				File >> L->FileNode->hour;
				File.ignore(1,'.');
				File >> L->FileNode->minutes;
				File.ignore(6);
				L->FileNode->content=createHeaderNodeOfSimpleList();
				ch=File.get();
				ch1='a';
				while(1)
				{
					if(ch=='"')
					{
						ch1=File.peek();
						if(ch1==EOF || ch1=='\n')
							break;
					}
					insertAtEndOfSimpleList(ch, L->FileNode->content);
					ch=File.get();
				}
				File.ignore(2,'\n');
				ch2=File.get();
				L=insertAtEndOfFileList(COMPLETE);
				ch3=File.peek();
				if(ch3==EOF)
					break;
			}
			while(File.good());
			File.close();
			break;
		}
		else
		{
			cout << "Sorry!!! File couldn't be locate, You need to Enter File Name again" <<endl;
		}
	}
	
	}
	return COMPLETE;
}
void csvFileWriting(FileList L)
{
	cout << "Welcome!!! Welcome to CSV File Writing Module"<<endl;
	FileList P=L;
	ofstream File;
	File.open("temp.csv",ios::out);
	if (File.is_open())
	{
		while (P->next!=NULL)
		 {
			  File << "sms;deliver;\""
				<< P->FileNode->CellNo
				<<"\";\"\";\"\";\""
				<<P->FileNode->year
				<<"."
				<<P->FileNode->month
				<<"."
				<<P->FileNode->day
				<<" "
				<<P->FileNode->hour
				<<":"
				<<P->FileNode->hour
				<<"\";\"\";\"";
			Position M =P->FileNode->content->next;
			while (M!=NULL)
			 {
				 File <<  M->element;
				 M = M->next;
			} 
			File <<"\"\n";
			P = P->next;
		 }
		
		cout<<".csv File Has Been Successfully Written"<<endl;
		File.close();
	}
	else
	{
		cout << "Error opening file";
	}
}

void xmlWriter(FileList L)
{
	FileList P=L;
	ofstream File;
	File.open("temp.xml",ios::out);
	if (File.is_open())
	{
		int i=1;
		File << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n ";
		File << "<FILE>\n";
		while (P->next!=NULL)
		 {
			 File << "<MESSAGE>\n"
				 << "<SENDER>"
				<< P->FileNode->CellNo
				<< "</SENDER>\n"
				<< "<TIME>"
				<< "<HOUR>" << P->FileNode->hour << "</HOUR>\n"
				<< "<MINUTES>" << P->FileNode->minutes << "</MINUTES>\n"
				<< "</TIME>"
				<< "<DATE>\n"
				<< "<DAY>" << P->FileNode->day << "</DAY>\n"
				<< "<MONTH>" << P->FileNode->month << "</MONTH>\n"
				<< "<YEAR>" << P->FileNode->year << "</YEAR>\n"
				<< "</DATE>\n"
				<< "<CONTENT>";
			Position M =P->FileNode->content->next;
			while (M!=NULL)
			 {
				 if(M->element=='<')
					 File << "&lt;";
				 else if(M->element=='>')
					 File <<  "&gt;";
				 else if(M->element=='&')
					 File <<  "&amp;";
				 else if(M->element=='\'')
					File <<  "&apos;"; 
				 else if(M->element=='"')
					File <<  "&quot;";
				 else
					 File <<  M->element;
				 M = M->next;
			} 
			File << "</CONTENT>\n";
			File << "</MESSAGE>\n\n";
			P = P->next;
			i++;
		 }
		File << "</FILE>\n";
		cout<<"XML File Has Been Successfully Written"<<endl;
		File.close();
	}
	else
	{
		cout << "Error opening file";
	}
}


int lengthOfSimpleLinkList(SimpleList L)
{
	Position P=L;
	int i=0;
	while(L->next!=NULL)
	{
		i++;
		L=L->next;
	}
	return i;
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////Encryption//////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void encipher(char key[],SimpleList L)
{
    Position P=L; 
	unsigned int i,j;
     int length=lengthOfSimpleLinkList(P);
	 char value;
    for(i=0,j=0;i<length;i++,j++)
     {
		 if(P->element==' ')
		 {
			 cout << " " ;
			 P=P->next;
			 continue;
		 }

          if(j>=strlen(key))
          {
               j=0;
          }
		  value = 65+(((toupper(P->element)-65)+(toupper(key[j])-65))%26);
		  P->element=value;
		  P=P->next;
	}

}

void decipher(char key[],SimpleList L)
{
     Position P=L; 
	unsigned int i,j;
     int length=lengthOfSimpleLinkList(P);
	 char value;
	 for(i=0,j=0;i<length;i++,j++)
     {
		 if(P->element==' ')
		 {
			 cout << " " ;
			 P=P->next;
			 continue;
		 }

          if(j>=strlen(key))
          {
               j=0;
          }
          value = (toupper(P->element)-64)-(toupper(key[j])-64);
          if( value < 0)
          {
               value = 26 + value;
          }   
		  value=65+(value%26);
		  P->element=value;
		  P=P->next;
	 }
}
void encrypt(char key[],FileList L)
{
	FileList P=L;
	while(P->next!=NULL)
	{
		encipher(key,P->FileNode->content);
		P=P->next;
	}
}

void decrypt(char key[],FileList L)
{
	FileList P=L;
	while(P->next!=NULL)
	{
		decipher(key,P->FileNode->content);
		P=P->next;
	}
}
/////////////////////////////////////////////////////////////////////////
//////////////Computation for Key manipulation///////////////////////////
/////////////////////////////////////////////////////////////////////////
unsigned int KeyGenerator(int year,int month,int day,int hour,int minutes)
{
	unsigned int Key;
	year=year%100;
	Key=(year*100000000)+(month*1000000)+(day*10000)+(hour*100)+(minutes);
	return Key;
}
int MinutesExtractor(unsigned int Key)
{
	return Key%100;
}
int HourExtractor(unsigned int Key)
{
	return (Key%10000)/100;
}
int DayExtractor(unsigned int Key)
{
	return ((Key%1000000)/10000);
}
int MonthExtractor(unsigned int Key)
{
	return (Key%100000000)/1000000;
}
int YearExtractor(unsigned int Key)
{
	int x=Key/100000000;
	x=x+2000;
	return x;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////AVL Tree////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

typedef struct AvlNode* AvlTree;
struct AvlNode
{
	unsigned int data;

	int height;
	Messg Message;
	AvlTree right;
	AvlTree left;
};

struct queue
{
        AvlTree tptr;
        struct queue* next;
};
struct queue* createqueue();
struct queue* enqueue(AvlTree ,struct queue*);
void traversequeue(struct queue *,struct queue *);
void printqueue(struct queue*);
int isempty(struct queue *);


void breadthtraversal(AvlTree T);
void inorderprint(AvlTree t);
int Height(AvlTree T);
AvlTree Delete(int x, AvlTree T, Messg M);
AvlTree LeftRotation(AvlTree K2);
AvlTree RightRotation(AvlTree K2);
AvlTree LeftRightRotation(AvlTree K3);
AvlTree RightLeftRotation(AvlTree K3);
AvlTree AvlTreeInsert(unsigned int x, AvlTree T,Messg M);
AvlTree FindMin(AvlTree X);
AvlTree establishTree(unsigned int x,Messg M);

AvlTree createAvlTree(FileList L)
{
	AvlTree T;
	unsigned int x;
	if(L==NULL)
		cout << "record is empty" <<endl;
	else
		{
			x=KeyGenerator(L->FileNode->year,L->FileNode->month,L->FileNode->day,L->FileNode->hour,L->FileNode->minutes);
			T=establishTree(x,L->FileNode);
			L=L->next;
			while(L->next!=NULL)
			{
				x=KeyGenerator(L->FileNode->year,L->FileNode->month,L->FileNode->day,L->FileNode->hour,L->FileNode->minutes);
				T=AvlTreeInsert(x,T, L->FileNode);
				L=L->next;
			}
	}
	return T;
}
AvlTree establishTree(unsigned int x,Messg M)
{
	AvlTree T;
	T = (struct AvlNode*)malloc(sizeof(struct AvlNode));
	T->Message= M;
	T->data=x;
	T->height= 0;
	T->left= NULL;
	T->right= NULL;
	return T;
}

int Height(AvlTree T)
{
	int LeftHeight, RightHeight;
	LeftHeight = RightHeight = 0;
	if(T==NULL)
		return -1;
	LeftHeight = Height(T->left);
	RightHeight = Height(T->right);
	return (max(LeftHeight,RightHeight) + 1);
}

AvlTree LeftRotation(AvlTree K2)
{
	AvlTree K1 = K2->right;
	K2->right = K1->left;
	K1->left = K2;
	K2->height = max(Height(K2->right), Height(K2->left))+1;
	K1->height = max(Height(K1->right), K2->height) + 1;
	return K1;
}

AvlTree RightRotation(AvlTree K2)
{
	AvlTree K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(Height(K2->left), Height(K2->right))+1;
	K1->height = max(Height(K1->left), Height(K2->right)) + 1;
	return K1;
}
AvlTree LeftRightRotation(AvlTree K3)
{
	K3->left= LeftRotation(K3->left);
	return RightRotation(K3);
}
AvlTree RightLeftRotation(AvlTree K3)
{
	K3->right= RightRotation(K3->right);
	return LeftRotation(K3);
}

AvlTree AvlTreeInsert(unsigned int x, AvlTree T,Messg M)
{
	if(T== NULL)
	{
		T = (struct AvlNode*)malloc(sizeof(struct AvlNode));
		T->data= x;
		T->Message=M;
		T->height= 0;
		T->left= NULL;
		T->right= NULL;
	}
	if (x<T->data)
	{
		T->left= AvlTreeInsert(x,T->left,M);
		if (Height(T->left)-Height(T->right) == 2)
		{	
			if (x<T->left->data)
				T = RightRotation(T);
			else
				T = RightLeftRotation(T);
		}
	}
	if (x > T->data)
	{
		T->right= AvlTreeInsert(x,T->right,M);
		if (Height(T->right)-Height(T->left) == 2)
		{
			if (x>T->right->data)
				T = LeftRotation(T);
			else
				T = LeftRightRotation(T);
		}
	}
	T->height= max(Height(T->left),Height(T->right))+1;
	return T;
}

AvlTree FindMin(AvlTree X)
{
	AvlTree P=X;
	if(X!=NULL)
		P=FindMin(X->left);
	return P;
}

AvlTree Delete(unsigned int X, AvlTree T,Messg M)
{
	AvlTree TmpCell;
	if (T == NULL)
	{
		cout << "Element Not Found" <<endl;
	}
	else
	if (X < T->data)
	{
		T->left = Delete(X,T->left,M);
		if(Height(T->right) - Height(T->left)==2)
			if(Height(T->right->right) > Height(T->right->left))
				LeftRotation(T);
		else
			RightLeftRotation(T);
	}
	else if (X > T->data)
	{
		T->right = Delete(X,T->right,M);
		if(Height(T->left) - Height(T->right)==2)
			if(Height(T->left->left) > Height(T->left->right))
				RightRotation(T);
		else
			LeftRightRotation(T);
	}
	else if (T->left && T->right) // left and right child //
	{
		TmpCell = FindMin(T->right);
		T->data = TmpCell->data;
		T->right = Delete(T->data, T->right,M);
	}
	else
	{
		TmpCell = T;
		if (T->left == NULL) // leaves , no children //
		{
			T = T->right;
		}
		else if (T->right == NULL)
		{
			T = T->left;
		}
		free(TmpCell);
		}
	return T;
}

void breadthtraversal(AvlTree T)
{
	struct queue* front,*rear;
	cout << "tree print" <<endl;
	inorderprint(T);
    struct queue* q=createqueue();
    front=rear=q;
    rear=enqueue(T,rear);
    traversequeue(q,rear);
    cout << "New Order\n";
    while(q->next!=NULL)
    {
		q=q->next;
        cout << q->tptr->data <<endl;
     }
}
void inorderprint(AvlTree T)
{
        if(T!=NULL)

        {
                cout << T->data << endl;;
                inorderprint(T->left);
                inorderprint(T->right);
        }

}

/////////////////////////////////////////////////////////////////////////
///////////////////////////////Queue/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

struct queue* createqueue()
{
        struct queue *q=(struct queue *)malloc(sizeof(struct queue));
        q->next=NULL;
        return q;

}

struct queue* enqueue(AvlTree t,struct queue *rear)
{
        if(t!=NULL)
        {
        struct queue *newnode=(struct queue*)malloc(sizeof(struct queue));
        newnode->tptr=t;

        newnode->next=NULL;
        rear->next=newnode;
        rear=newnode;
        return rear;
        }
        return rear;
}

void traversequeue(struct queue* q,struct queue* rear)
{
        while(q->next!=NULL)
        {
                q=q->next;
        rear=enqueue(q->tptr->left,rear);
        rear=enqueue(q->tptr->right,rear);

        }
}
int isempty(struct queue* q)
{
        if(q->next!=NULL)
                return 0;
        else
                return 1;
} 

/////////////////////////////////////////////////////////////////////////
////////////////////////Content Searching////////////////////////////////
/////////////////////////////////////////////////////////////////////////
void appendInNewCSVFile(Messg M,char FileName[]);
int FoundIndicator(char word[],SimpleList L);


void contentSearching(char word[],FileList L)
{
	FileList temp=L;
	char FileName[15];
	cout << "Enter File Name for Searched Data to Save," <<endl;
	cout << "Don't Forget to add .csv Extension at last, as data will be stored in .csv File" <<endl;
	cin >> FileName;
	int flag=0;
	while(temp->next!=NULL)
	{	
		
		if(FoundIndicator(word,temp->FileNode->content)==1)
		{
			appendInNewCSVFile(temp->FileNode,FileName);
			flag=1;
		}
		temp=temp->next;
	}
	cout << "Searching Completes" << endl; 
	if(flag==1)
		cout << ".csv File containing Searched Result Has Been Saved in Default Directory";
	else
		cout << "Provided word can't be searched, so no file is being created";


}
void appendInNewCSVFile(Messg M,char FileName[])
{
	Messg P=M;
	ofstream File;
	File.open(FileName,ios::app);
	if (File.is_open())
	{
		File << "sms;deliver;\""
			<< P->CellNo
			<<"\";\"\";\"\";\""				
			<<P->year
			<<"."
			<<P->month
			<<"."
			<<P->day
			<<" "
			<<P->hour
			<<":"
			<<P->hour
			<<"\";\"\";\"";
			Position M =P->content->next;
			while (M!=NULL)
			 {
				 File <<  M->element;
				 M = M->next;
			} 
			File <<"\"\n";
	cout<<"searched.csv File Has Been Successfully Written"<<endl;
	File.close();
	}
	else
	{
		cout << "Error opening file";
	}
}
int FoundIndicator(char word[],SimpleList L)
{
	SimpleList temp=L;
	int a=0,i=0;
	while(temp->next!=NULL)
	{
		if(i==strlen(word))
		{
			a=1;
			break;
		}
		if(temp->element==word[i])
			i++;
		else
			i=0;
		temp=temp->next;
	}
	return a;
}

/////////////////////////////////////////////////////////////////////////
////////////////////Searching By Date And Time///////////////////////////
/////////////////////////////////////////////////////////////////////////

AvlTree YearFind( int year, AvlTree T )
{
	if( T == NULL )
		return NULL;
	if( year < YearExtractor(T->data) )
		return YearFind( year, T->left );
	else if( year > YearExtractor(T->data))
		return YearFind( year, T->right );
	else
		return T;
}
AvlTree MonthFind( int month, AvlTree T )
{
	if( T == NULL )
		return NULL;
	if( month < MonthExtractor(T->data) )
		return MonthFind( month, T->left );
	else if( month > MonthExtractor(T->data))
		return MonthFind( month, T->right );
	else
		return T;
}
AvlTree DayFind( int day, AvlTree T )
{
	if( T == NULL )
		return NULL;
	if( day < DayExtractor(T->data) )
		return DayFind( day, T->left );
	else if( day > DayExtractor(T->data))
		return DayFind( day, T->right );
	else
		return T;
}
void HourFind( int hour, AvlTree T,char FileName[] )
{
	
	while(T!=NULL)
	{
		if(hour==HourExtractor(T->data))
		{
			appendInNewCSVFile(T->Message,FileName);
			HourFind( hour, T->left,FileName );
			HourFind( hour, T->right ,FileName);
		}
		if( hour < HourExtractor(T->data) )
			 HourFind( hour, T->left,FileName );
		if( hour > HourExtractor(T->data))
			 HourFind( hour, T->right ,FileName);
	}
}
AvlTree MinutesFind( int minutes, AvlTree T )
{
	if( T == NULL )
		return NULL;
	if( minutes < MinutesExtractor(T->data) )
		return MinutesFind( minutes, T->left );
	else if( minutes > MinutesExtractor(T->data))
		return MinutesFind(minutes, T->right );
	else
		return T;
}

/////////////////////////////////////////////////////////////////////////
////////////////////Searching By Date And Time///////////////////////////
/////////////////////////////////////////////////////////////////////////
typedef struct YearNode* YearPosition;
typedef struct YearNode* YearTree;
typedef struct MonthNode* MonthPosition;
typedef struct MonthNode* MonthTree;
typedef struct DayNode* DayPosition;
typedef struct DayNode* DayTree;
typedef struct HourNode* HourPosition;
typedef struct HourNode* HourTree;
typedef struct MinutesNode* MinutesPosition;
typedef struct MinutesNode* MinutesTree;
///////////////////////////////////////////////////////////////////////
struct YearNode
{
	int year;
	MonthTree MTree;
	int height;
	YearPosition right;
	YearPosition left;
};
//////////////////////////////////////////////////////////////////////////
struct MonthNode
{
	int Month;
	DayTree DTree;
	int height;
	MonthPosition right;
	MonthPosition left;
};
///////////////////////////////////////////////////////////////////////////
struct DayNode
{
	int Day;
	HourTree HTree;
	int height;
	DayPosition right;
	DayPosition left;
};
///////////////////////////////////////////////////////////////////////////
struct HourNode
{
	int Hour;
	MinutesTree MinTree;
	int height;
	HourPosition right;
	HourPosition left;
};
///////////////////////////////////////////////////////////////////////////
struct MinutesNode
{
	int Minutes;
	Messg Message;
	int height;
	MinutesPosition right;
	MinutesPosition left;
};
///////////////////////////////////////////////////////////////////////////


void inorderprint(YearTree t);


int YearHeight(YearTree T);
YearTree YearDelete(int X, YearTree T);
YearPosition YearLeftRotation(YearPosition K2);
YearPosition YearRightRotation(YearPosition K2);
YearPosition YearLeftRightRotation(YearPosition K3);
YearPosition YearRightLeftRotation(YearPosition K3);
YearTree YearTreeInsert(int x, YearTree T,MonthTree M);
YearPosition YearFindMin(YearPosition X);

YearTree createYearTree(int x,MonthTree M)
{
	YearTree T;
	T = (struct YearNode*)malloc(sizeof(struct YearNode));
	T->year= x;
	T->MTree=M;
	T->height= 0;
	T->left= NULL;
	T->right= NULL;
	return T;
}
YearPosition YearFind( int X, YearTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->year )
		return YearFind( X, T->left );
	else if( X > T->year )
		return YearFind( X, T->right );
	else
		return T;
}

int YearHeight(YearTree T)
{
	int LeftHeight, RightHeight;
	LeftHeight = RightHeight = 0;
	if(T==NULL)
		return -1;
	LeftHeight = YearHeight(T->left);
	RightHeight = YearHeight(T->right);
	return (max(LeftHeight,RightHeight) + 1);
}

YearPosition YearLeftRotation(YearPosition K2)
{
	YearPosition K1 = K2->right;
	K2->right = K1->left;
	K1->left = K2;
	K2->height = max(YearHeight(K2->right), YearHeight(K2->left))+1;
	K1->height = max(YearHeight(K1->right), YearHeight(K2->left)) + 1;
	return K1;
}

YearPosition YearRightRotation(YearPosition K2)
{
	YearPosition K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(YearHeight(K2->left), YearHeight(K2->right))+1;
	K1->height = max(YearHeight(K1->left), YearHeight(K2->right)) + 1;
	return K1;
}
YearPosition YearLeftRightRotation(YearPosition K3)
{
	K3->left= YearLeftRotation(K3->left);
	return YearRightRotation(K3);
}
YearPosition YearRightLeftRotation(YearPosition K3)
{
	K3->right= YearRightRotation(K3->right);
	return YearLeftRotation(K3);
}

YearTree YearTreeInsert(int x, YearTree T,MonthTree M)
{
	if(T== NULL)
	{
		T = (struct YearNode*)malloc(sizeof(struct YearNode));
		T->year= x;
		T->MTree=M;
		T->height= 0;
		T->left= NULL;
		T->right= NULL;
	}
	if (x<T->year)
	{
		T->left= YearTreeInsert(x,T->left,M);
		if (YearHeight(T->left)-YearHeight(T->right) == 2)
		{	
			if (x<T->left->year)
				T = YearRightRotation(T);
			else
				T = YearRightLeftRotation(T);
		}
	}
	if (x > T->year)
	{
		T->right= YearTreeInsert(x,T->right,M);
		if (YearHeight(T->right)-YearHeight(T->left) == 2)
		{
			if (x>T->right->year)
				T = YearLeftRotation(T);
			else
				T = YearLeftRightRotation(T);
		}
	}
	T->height= max(YearHeight(T->left),YearHeight(T->right))+1;
	return T;
}

YearPosition YearFindMin(YearPosition X)
{
	YearTree P=X;
	if(X!=NULL)
		P=YearFindMin(P->left);
	return P;
}
YearTree YearDelete(int X, YearTree T)
{
	YearPosition TmpCell;
	if (T == NULL)
	{
		cout << "Element Not Found" <<endl;
	}
	else
	if (X < T->year)
	{
		T->left = YearDelete(X,T->left);
		if(YearHeight(T->right) - YearHeight(T->left)==2)
			if(YearHeight(T->right->right) > YearHeight(T->right->left))
				YearLeftRotation(T);
		else
			YearRightLeftRotation(T);
	}
	else if (X > T->year)
	{
		T->right = YearDelete(X,T->right);
		if(YearHeight(T->left) - YearHeight(T->right)==2)
			if(YearHeight(T->left->left) > YearHeight(T->left->right))
				YearRightRotation(T);
		else
			YearLeftRightRotation(T);
	}
	else if (T->left && T->right) // left and right child //
	{
		TmpCell = YearFindMin(T->right);
		T->year = TmpCell->year;
		T->right = YearDelete(T->year, T->right);
	}
	else
	{
		TmpCell = T;
		if (T->left == NULL) // leaves , no children //
		{
			T = T->right;
		}
		else if (T->right == NULL)
		{
			T = T->left;
		}
		free(TmpCell);
		}
	return T;
}
///////////////////////////////////////////////////////////////////////

void inorderprint(MonthTree t);


int MonthHeight(MonthTree T);
MonthTree MonthDelete(int X, MonthTree T);
MonthPosition MonthLeftRotation(MonthPosition K2);
MonthPosition MonthRightRotation(MonthPosition K2);
MonthPosition MonthLeftRightRotation(MonthPosition K3);
MonthPosition MonthRightLeftRotation(MonthPosition K3);
MonthTree MonthTreeInsert(int x, MonthTree T,DayTree D);
MonthPosition MonthFindMin(MonthPosition X);

MonthTree createMonthTree(int x,DayTree D)
{
	MonthTree T;
	T = (struct MonthNode*)malloc(sizeof(struct MonthNode));
	T->Month= x;
	T->DTree=D;
	T->height= 0;
	T->left= NULL;
	T->right= NULL;
	return T;
}

MonthPosition MonthFind( int X, MonthTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->Month )
		return MonthFind( X, T->left );
	else if( X > T->Month )
		return MonthFind( X, T->right );
	else
		return T;
}


int MonthHeight(MonthTree T)
{
	int LeftHeight, RightHeight;
	LeftHeight = RightHeight = 0;
	if(T==NULL)
		return -1;
	LeftHeight = MonthHeight(T->left);
	RightHeight = MonthHeight(T->right);
	return (max(LeftHeight,RightHeight) + 1);
}

MonthPosition MonthLeftRotation(MonthPosition K2)
{
	MonthPosition K1 = K2->right;
	K2->right = K1->left;
	K1->left = K2;
	K2->height = max(MonthHeight(K2->right), MonthHeight(K2->left))+1;
	K1->height = max(MonthHeight(K1->right), MonthHeight(K2->left)) + 1;
	return K1;
}

MonthPosition MonthRightRotation(MonthPosition K2)
{
	MonthPosition K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(MonthHeight(K2->left), MonthHeight(K2->right))+1;
	K1->height = max(MonthHeight(K1->left), MonthHeight(K2->right)) + 1;
	return K1;
}
MonthPosition MonthLeftRightRotation(MonthPosition K3)
{
	K3->left= MonthLeftRotation(K3->left);
	return MonthRightRotation(K3);
}
MonthPosition MonthRightLeftRotation(MonthPosition K3)
{
	K3->right= MonthRightRotation(K3->right);
	return MonthLeftRotation(K3);
}

MonthTree MonthTreeInsert(int x, MonthTree T,DayTree D)
{
	if(T== NULL)
	{
		T = (struct MonthNode*)malloc(sizeof(struct MonthNode));
		T->Month= x;
		T->DTree=D;
		T->height= 0;
		T->left= NULL;
		T->right= NULL;
	}
	if (x<T->Month)
	{
		T->left= MonthTreeInsert(x,T->left,D);
		if (MonthHeight(T->left)-MonthHeight(T->right) == 2)
		{	
			if (x<T->left->Month)
				T = MonthRightRotation(T);
			else
				T = MonthRightLeftRotation(T);
		}
	}
	if (x > T->Month)
	{
		T->right= MonthTreeInsert(x,T->right,D);
		if (MonthHeight(T->right)-MonthHeight(T->left) == 2)
		{
			if (x>T->right->Month)
				T = MonthLeftRotation(T);
			else
				T = MonthLeftRightRotation(T);
		}
	}
	T->height= max(MonthHeight(T->left),MonthHeight(T->right))+1;
	return T;
}

MonthPosition MonthFindMin(MonthPosition X)
{
	MonthTree P=X;
	if(X!=NULL)
		P=MonthFindMin(P->left);
	return P;
}

MonthTree MonthDelete(int X, MonthTree T)
{
	MonthPosition TmpCell;
	if (T == NULL)
	{
		cout << "Element Not Found" <<endl;
	}
	else
	if (X < T->Month)
	{
		T->left = MonthDelete(X,T->left);
		if(MonthHeight(T->right) - MonthHeight(T->left)==2)
			if(MonthHeight(T->right->right) > MonthHeight(T->right->left))
				MonthLeftRotation(T);
		else
			MonthRightLeftRotation(T);
	}
	else if (X > T->Month)
	{
		T->right = MonthDelete(X,T->right);
		if(MonthHeight(T->left) - MonthHeight(T->right)==2)
			if(MonthHeight(T->left->left) > MonthHeight(T->left->right))
				MonthRightRotation(T);
		else
			MonthLeftRightRotation(T);
	}
	else if (T->left && T->right) // left and right child //
	{
		TmpCell = MonthFindMin(T->right);
		T->Month = TmpCell->Month;
		T->right = MonthDelete(T->Month, T->right);
	}
	else
	{
		TmpCell = T;
		if (T->left == NULL) // leaves , no children //
		{
			T = T->right;
		}
		else if (T->right == NULL)
		{
			T = T->left;
		}
		free(TmpCell);
		}
	return T;
}


//////////////////////////////////////////////////////////////////////////

void inorderprint(DayTree t);


int DayHeight(DayTree T);
DayTree DayDelete(int X, DayTree T);
DayPosition DayLeftRotation(DayPosition K2);
DayPosition DayRightRotation(DayPosition K2);
DayPosition DayLeftRightRotation(DayPosition K3);
DayPosition DayRightLeftRotation(DayPosition K3);
DayTree DayTreeInsert(int x, DayTree T,HourTree H);
DayPosition DayFindMin(DayPosition X);

DayTree createDayTree(int x,HourTree H)
{
	DayTree T;
	T = (struct DayNode*)malloc(sizeof(struct DayNode));
	T->Day= x;
	T->HTree=H;
	T->height= 0;
	T->left= NULL;
	T->right= NULL;
	return T;
}
DayPosition DayFind( int X, DayTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->Day )
		return DayFind( X, T->left );
	else if( X > T->Day )
		return DayFind( X, T->right );
	else
		return T;
}



int DayHeight(DayTree T)
{
	int LeftHeight, RightHeight;
	LeftHeight = RightHeight = 0;
	if(T==NULL)
		return -1;
	LeftHeight = DayHeight(T->left);
	RightHeight = DayHeight(T->right);
	return (max(LeftHeight,RightHeight) + 1);
}

DayPosition DayLeftRotation(DayPosition K2)
{
	DayPosition K1 = K2->right;
	K2->right = K1->left;
	K1->left = K2;
	K2->height = max(DayHeight(K2->right), DayHeight(K2->left))+1;
	K1->height = max(DayHeight(K1->right), DayHeight(K2->left)) + 1;
	return K1;
}

DayPosition DayRightRotation(DayPosition K2)
{
	DayPosition K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(DayHeight(K2->left), DayHeight(K2->right))+1;
	K1->height = max(DayHeight(K1->left), DayHeight(K2->right)) + 1;
	return K1;
}
DayPosition DayLeftRightRotation(DayPosition K3)
{
	K3->left= DayLeftRotation(K3->left);
	return DayRightRotation(K3);
}
DayPosition DayRightLeftRotation(DayPosition K3)
{
	K3->right= DayRightRotation(K3->right);
	return DayLeftRotation(K3);
}

DayTree DayTreeInsert(int x, DayTree T,HourTree H)
{
	if(T== NULL)
	{
		T = (struct DayNode*)malloc(sizeof(struct DayNode));
		T->Day= x;
		T->HTree=H;
		T->height= 0;
		T->left= NULL;
		T->right= NULL;
	}
	if (x<T->Day)
	{
		T->left= DayTreeInsert(x,T->left,H);
		if (DayHeight(T->left)-DayHeight(T->right) == 2)
		{	
			if (x<T->left->Day)
				T = DayRightRotation(T);
			else
				T = DayRightLeftRotation(T);
		}
	}
	if (x > T->Day)
	{
		T->right= DayTreeInsert(x,T->right,H);
		if (DayHeight(T->right)-DayHeight(T->left) == 2)
		{
			if (x>T->right->Day)
				T = DayLeftRotation(T);
			else
				T = DayLeftRightRotation(T);
		}
	}
	T->height= max(DayHeight(T->left),DayHeight(T->right))+1;
	return T;
}

DayPosition DayFindMin(DayPosition X)
{
	DayTree P=X;
	if(X!=NULL)
		P=DayFindMin(P->left);
	return P;
}

DayTree DayDelete(int X, DayTree T)
{
	DayPosition TmpCell;
	if (T == NULL)
	{
		cout << "Element Not Found" <<endl;
	}
	else
	if (X < T->Day)
	{
		T->left = DayDelete(X,T->left);
		if(DayHeight(T->right) - DayHeight(T->left)==2)
			if(DayHeight(T->right->right) > DayHeight(T->right->left))
				DayLeftRotation(T);
		else
			DayRightLeftRotation(T);
	}
	else if (X > T->Day)
	{
		T->right = DayDelete(X,T->right);
		if(DayHeight(T->left) - DayHeight(T->right)==2)
			if(DayHeight(T->left->left) > DayHeight(T->left->right))
				DayRightRotation(T);
		else
			DayLeftRightRotation(T);
	}
	else if (T->left && T->right) // left and right child //
	{
		TmpCell = DayFindMin(T->right);
		T->Day = TmpCell->Day;
		T->right = DayDelete(T->Day, T->right);
	}
	else
	{
		TmpCell = T;
		if (T->left == NULL) // leaves , no children //
		{
			T = T->right;
		}
		else if (T->right == NULL)
		{
			T = T->left;
		}
		free(TmpCell);
		}
	return T;
}



///////////////////////////////////////////////////////////////////////////

void inorderprint(HourTree t);

int HourHeight(HourTree T);
HourTree HourDelete(int X, HourTree T);
HourPosition HourLeftRotation(HourPosition K2);
HourPosition HourRightRotation(HourPosition K2);
HourPosition HourLeftRightRotation(HourPosition K3);
HourPosition HourRightLeftRotation(HourPosition K3);
HourTree HourTreeInsert(int x, HourTree T,MinutesTree Min);
HourPosition HourFindMin(HourPosition X);

HourTree createHourTree(int x,MinutesTree Min)
{
	HourTree T;
	T = (struct HourNode*)malloc(sizeof(struct HourNode));
	T->Hour= x;
	T->MinTree=Min;
	T->height= 0;
	T->left= NULL;
	T->right= NULL;
	return T;
}
HourPosition HourFind( int X, HourTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->Hour )
		return HourFind( X, T->left );
	else if( X > T->Hour )
		return HourFind( X, T->right );
	else
		return T;
}



int HourHeight(HourTree T)
{
	int LeftHeight, RightHeight;
	LeftHeight = RightHeight = 0;
	if(T==NULL)
		return -1;
	LeftHeight = HourHeight(T->left);
	RightHeight = HourHeight(T->right);
	return (max(LeftHeight,RightHeight) + 1);
}

HourPosition HourLeftRotation(HourPosition K2)
{
	HourPosition K1 = K2->right;
	K2->right = K1->left;
	K1->left = K2;
	K2->height = max(HourHeight(K2->right), HourHeight(K2->left))+1;
	K1->height = max(HourHeight(K1->right), HourHeight(K2->left)) + 1;
	return K1;
}

HourPosition HourRightRotation(HourPosition K2)
{
	HourPosition K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(HourHeight(K2->left), HourHeight(K2->right))+1;
	K1->height = max(HourHeight(K1->left), HourHeight(K2->right)) + 1;
	return K1;
}
HourPosition HourLeftRightRotation(HourPosition K3)
{
	K3->left= HourLeftRotation(K3->left);
	return HourRightRotation(K3);
}
HourPosition HourRightLeftRotation(HourPosition K3)
{
	K3->right= HourRightRotation(K3->right);
	return HourLeftRotation(K3);
}

HourTree HourTreeInsert(int x, HourTree T,MinutesTree Min)
{
	if(T== NULL)
	{
		T = (struct HourNode*)malloc(sizeof(struct HourNode));
		T->Hour= x;
		T->MinTree=Min;
		T->height= 0;
		T->left= NULL;
		T->right= NULL;
	}
	if (x<T->Hour)
	{
		T->left= HourTreeInsert(x,T->left,Min);
		if (HourHeight(T->left)-HourHeight(T->right) == 2)
		{	
			if (x<T->left->Hour)
				T = HourRightRotation(T);
			else
				T = HourRightLeftRotation(T);
		}
	}
	if (x > T->Hour)
	{
		T->right= HourTreeInsert(x,T->right,Min);
		if (HourHeight(T->right)-HourHeight(T->left) == 2)
		{
			if (x>T->right->Hour)
				T = HourLeftRotation(T);
			else
				T = HourLeftRightRotation(T);
		}
	}
	T->height= max(HourHeight(T->left),HourHeight(T->right))+1;
	return T;
}

HourPosition HourFindMin(HourPosition X)
{
	HourTree P=X;
	if(X!=NULL)
		P=HourFindMin(P->left);
	return P;
}

HourTree HourDelete(int X, HourTree T)
{
	HourPosition TmpCell;
	if (T == NULL)
	{
		cout << "Element Not Found" <<endl;
	}
	else
	if (X < T->Hour)
	{
		T->left = HourDelete(X,T->left);
		if(HourHeight(T->right) - HourHeight(T->left)==2)
			if(HourHeight(T->right->right) > HourHeight(T->right->left))
				HourLeftRotation(T);
		else
			HourRightLeftRotation(T);
	}
	else if (X > T->Hour)
	{
		T->right = HourDelete(X,T->right);
		if(HourHeight(T->left) - HourHeight(T->right)==2)
			if(HourHeight(T->left->left) > HourHeight(T->left->right))
				HourRightRotation(T);
		else
			HourLeftRightRotation(T);
	}
	else if (T->left && T->right) // left and right child //
	{
		TmpCell = HourFindMin(T->right);
		T->Hour = TmpCell->Hour;
		T->right = HourDelete(T->Hour, T->right);
	}
	else
	{
		TmpCell = T;
		if (T->left == NULL) // leaves , no children //
		{
			T = T->right;
		}
		else if (T->right == NULL)
		{
			T = T->left;
		}
		free(TmpCell);
		}
	return T;
}


///////////////////////////////////////////////////////////////////////////

void inorderprint(MinutesTree t);


int MinutesHeight(MinutesTree T);
MinutesTree MinutesDelete(int X, MinutesTree T);
MinutesPosition MinutesLeftRotation(MinutesPosition K2);
MinutesPosition MinutesRightRotation(MinutesPosition K2);
MinutesPosition MinutesLeftRightRotation(MinutesPosition K3);
MinutesPosition MinutesRightLeftRotation(MinutesPosition K3);
MinutesTree MinutesTreeInsert(int x, MinutesTree T,Messg M);
MinutesPosition MinutesFindMin(MinutesPosition X);

MinutesTree createMinutesTree(int x,Messg M)
{
	MinutesTree T;
	T = (struct MinutesNode*)malloc(sizeof(struct MinutesNode));
	T->Minutes= x;
	T->Message=M;
	T->height= 0;
	T->left= NULL;
	T->right= NULL;
	return T;
}
MinutesPosition MinutesFind( int X, MinutesTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->Minutes )
		return MinutesFind( X, T->left );
	else if( X > T->Minutes )
		return MinutesFind( X, T->right );
	else
		return T;
}



int MinutesHeight(MinutesTree T)
{
	int LeftHeight, RightHeight;
	LeftHeight = RightHeight = 0;
	if(T==NULL)
		return -1;
	LeftHeight = MinutesHeight(T->left);
	RightHeight = MinutesHeight(T->right);
	return (max(LeftHeight,RightHeight) + 1);
}

MinutesPosition MinutesLeftRotation(MinutesPosition K2)
{
	MinutesPosition K1 = K2->right;
	K2->right = K1->left;
	K1->left = K2;
	K2->height = max(MinutesHeight(K2->right), MinutesHeight(K2->left))+1;
	K1->height = max(MinutesHeight(K1->right), MinutesHeight(K2->left)) + 1;
	return K1;
}

MinutesPosition MinutesRightRotation(MinutesPosition K2)
{
	MinutesPosition K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(MinutesHeight(K2->left), MinutesHeight(K2->right))+1;
	K1->height = max(MinutesHeight(K1->left), MinutesHeight(K2->right)) + 1;
	return K1;
}
MinutesPosition MinutesLeftRightRotation(MinutesPosition K3)
{
	K3->left= MinutesLeftRotation(K3->left);
	return MinutesRightRotation(K3);
}
MinutesPosition MinutesRightLeftRotation(MinutesPosition K3)
{
	K3->right= MinutesRightRotation(K3->right);
	return MinutesLeftRotation(K3);
}

MinutesTree MinutesTreeInsert(int x, MinutesTree T,Messg M)
{
	if(T== NULL)
	{
		T = (struct MinutesNode*)malloc(sizeof(struct MinutesNode));
		T->Minutes= x;
		T->Message=M;
		T->height= 0;
		T->left= NULL;
		T->right= NULL;
	}
	if (x<T->Minutes)
	{
		T->left= MinutesTreeInsert(x,T->left,M);
		if (MinutesHeight(T->left)-MinutesHeight(T->right) == 2)
		{	
			if (x<T->left->Minutes)
				T = MinutesRightRotation(T);
			else
				T = MinutesRightLeftRotation(T);
		}
	}
	if (x > T->Minutes)
	{
		T->right= MinutesTreeInsert(x,T->right,M);
		if (MinutesHeight(T->right)-MinutesHeight(T->left) == 2)
		{
			if (x>T->right->Minutes)
				T = MinutesLeftRotation(T);
			else
				T = MinutesLeftRightRotation(T);
		}
	}
	T->height= max(MinutesHeight(T->left),MinutesHeight(T->right))+1;
	return T;
}

MinutesPosition MinutesFindMin(MinutesPosition X)
{
	MinutesTree P=X;
	if(X!=NULL)
		P=MinutesFindMin(P->left);
	return P;
}

MinutesTree MinutesDelete(int X, MinutesTree T)
{
	MinutesPosition TmpCell;
	if (T == NULL)
	{
		cout << "Element Not Found" <<endl;
	}
	else
	if (X < T->Minutes)
	{
		T->left = MinutesDelete(X,T->left);
		if(MinutesHeight(T->right) - MinutesHeight(T->left)==2)
			if(MinutesHeight(T->right->right) > MinutesHeight(T->right->left))
				MinutesLeftRotation(T);
		else
			MinutesRightLeftRotation(T);
	}
	else if (X > T->Minutes)
	{
		T->right = MinutesDelete(X,T->right);
		if(MinutesHeight(T->left) - MinutesHeight(T->right)==2)
			if(MinutesHeight(T->left->left) > MinutesHeight(T->left->right))
				MinutesRightRotation(T);
		else
			MinutesLeftRightRotation(T);
	}
	else if (T->left && T->right) // left and right child //
	{
		TmpCell = MinutesFindMin(T->right);
		T->Minutes = TmpCell->Minutes;
		T->right = MinutesDelete(T->Minutes, T->right);
	}
	else
	{
		TmpCell = T;
		if (T->left == NULL) // leaves , no children //
		{
			T = T->right;
		}
		else if (T->right == NULL)
		{
			T = T->left;
		}
		free(TmpCell);
		}
	return T;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void inorderYprint(YearTree t);
void inorderMprint(MonthTree t);
void inorderDprint(DayTree t);
void inorderHprint(HourTree t);
void inorderMinprint(MinutesTree t);


void inorderYprint(YearTree t)
{
	if(t!=NULL)
	{
		inorderMprint(t->MTree);
        inorderYprint(t->left);
		inorderYprint(t->right);
     }
}


void inorderMprint(MonthTree t)
{
	if(t!=NULL)
	{
		inorderDprint(t->DTree);
        inorderMprint(t->left);
		inorderMprint(t->right);
     }
}
void inorderDprint(DayTree t)
{
	if(t!=NULL)
	{
		inorderHprint(t->HTree);
        inorderDprint(t->left);
		inorderDprint(t->right);
     }
}
void inorderHprint(HourTree t)
{
	if(t!=NULL)
	{
		inorderMinprint(t->MinTree);
        inorderHprint(t->left);
		inorderHprint(t->right);
     }
}
void inorderMinprint(MinutesTree t)
{
	if(t!=NULL)
	{
		printMessage(t->Message);
        inorderMinprint(t->left);
		inorderMinprint(t->right);
     }
}
YearTree createTree(FileList L)
{
	YearTree T,ptr;
	MonthTree M;
	DayTree D;
	HourTree H;
	MinutesTree Min;
	unsigned int x;
	if(L==NULL)
		cout << "record is empty" <<endl;
	else
		{
			Min=createMinutesTree(L->FileNode->minutes,L->FileNode);
			H=createHourTree(L->FileNode->hour,Min);
			D=createDayTree(L->FileNode->day,H);
			M=createMonthTree(L->FileNode->month,D);
			T=createYearTree(L->FileNode->year,M);
			ptr=T;
			
			L=L->next;
			while(L->next!=NULL)
			{
				if(YearFind(L->FileNode->year,T)!=NULL)
				{
					if(MonthFind(L->FileNode->month,M)!=NULL)
					{
						if(DayFind(L->FileNode->day,D)!=NULL)
						{
							if(HourFind(L->FileNode->hour,H)!=NULL)
							{
								
								
								Min=MinutesTreeInsert(L->FileNode->minutes,Min,L->FileNode);
								HourFind(L->FileNode->hour,H)->MinTree=Min;
							}
							else
							{
								Min=createMinutesTree(L->FileNode->minutes,L->FileNode);
								H=HourTreeInsert(L->FileNode->hour,H,Min);
								DayFind(L->FileNode->day,D)->HTree=H;
							}
						}
						else
						{
							Min=createMinutesTree(L->FileNode->minutes,L->FileNode);
							H=createHourTree(L->FileNode->hour,Min);
							D=DayTreeInsert(L->FileNode->day,D,H);
							MonthFind(L->FileNode->month,M)->DTree=D;
						}
					}
					else
					{
						Min=createMinutesTree(L->FileNode->minutes,L->FileNode);
						H=createHourTree(L->FileNode->hour,Min);
						D=DayTreeInsert(L->FileNode->day,D,H);
						M=MonthTreeInsert(L->FileNode->month,M,D);
						YearFind(L->FileNode->year,T)->MTree=M;
					}
				}
				else
				{
					Min=createMinutesTree(L->FileNode->minutes,L->FileNode);
					H=createHourTree(L->FileNode->hour,Min);
					D=DayTreeInsert(L->FileNode->day,D,H);
					M=createMonthTree(L->FileNode->month,D);
					T=YearTreeInsert(L->FileNode->year,T,M);
				}
				L=L->next;
			}
	}
	cout << "Tree is established" << endl;
	return T;
}
/////////////////////////////////////////////////////////////////////////
void YearSearch(YearTree T,int year)
{
	YearTree Temp=YearFind(year,T);
	cout << "Hit Any key to Show result on Screen"<<endl;
	getch();
	inorderYprint(Temp);
}
void MonthSearch(YearTree T,int month,int year)
{
	YearTree tempYear=YearFind(year,T);
	MonthTree TempMonth=MonthFind(month,tempYear->MTree);
	cout << "Hit Any key to Show result on Screen"<<endl;
	getch();
	inorderMprint(TempMonth);
}

void DaySearch(YearTree T,int day)
{
	//MonthFind(month,T->MTree);
	DayTree Temp=DayFind(day,T->MTree->DTree);
	cout << "Hit Any key to Show result on Screen"<<endl;
	getch();
	inorderDprint(Temp);
}
