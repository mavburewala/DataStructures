
//Written By 
//Muhammad Nadeem Azam
//Reg# 2009176
//Successfully Compiled at MS Visual C++ 2006
//Assignment No: 1
//Course: CS211
//Ghulam Ishaq Khan Institite of Engineering Sciences and Technology,Topi


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

//Part 1: Creating structure of provided data records
struct node
{
  int patientId;
	int patientFileNo;
	char patientName[10];
	char patientDepartment[10];
	char timeOfVisit[10];
	char dateOfVisit[10];
	char physicianName[10];
	struct node* next;
};

struct node* createHead(void)
{
	struct node* head;
	head=(struct node*)malloc(sizeof(struct node));
	head->next=NULL;
	return head;
}

struct node* search_by_name(struct node* L,char name[10])
{
	struct node* P=L->next;
	while(P!=NULL&&strcmp (P->patientName, name)!=0)
	{
		P=P->next;
	}
	return P;
}
struct node* search_by_doctor(struct node* L,char name[10])
{
	struct node* P=L->next;
	while(P!=NULL&&strcmp (P->physicianName, name)!=0)
	{
		P=P->next;
	}
	return P;
}
struct node* searchPrevious_by_name(struct node* L,char name[10])
{
	struct node* P=L;
	while(P->next!=NULL&&strcmp (P->next->patientName, name)!=0)
	{
		P=P->next;
	}
	return P;
}
struct node* searchPrevious_by_doctor(struct node* L,char name[10])
{
	struct node* P=L;
	while(P->next!=NULL&&strcmp (P->next->physicianName, name)!=0)
	{
		P=P->next;
	}
	return P;
}



void print_list(struct node* L);
void print_node(struct node* P);
void insert_at_end_justId_name(struct node* L);
void Delete_all_list(struct node* L);
void Delete_node_between(struct node* P);
void update_time_date(struct node* L);
void insert_between_fullRecords(struct node* P);
void insert_at_end_fullRecords(struct node* L);


void main()
{
	int i;
	struct node* L;
	char name[10];
	L=createHead();
	//Part 2: creating data records for three patient entries
	for(i=0;i<3;i++)
	{
		printf("Enter data records of Patient %d\n",i+1);
		insert_at_end_fullRecords(L);
	}
	print_list(L);

	//Part 3: Updating Particular Patient's Entry records
	printf("Enter Name of patient whose records you wanna update\n");
	scanf("%s",name);
	print_node(search_by_name(L,name));
	update_time_date(search_by_name(L,name));
	print_node(search_by_name(L,name));
	
	//Part 4: Deleting Data Entry Records of Particular Patient
	printf("Enter Name of patient whose records you wanna delete\n");
	scanf("%s",name);
	print_node(search_by_name(L,name));
	Delete_node_between(searchPrevious_by_name(L,name));
	print_list(L);
	
	//Part 5: Adding New Patient Entry at last of the list
	insert_at_end_justId_name(L);
	print_list(L);
	
	//Part 6:Updating last Entered Patient's Entry Records
	char temp[10]={'P','a','t','i','e','n','t','E'};
	update_time_date(search_by_name(L,temp));
	print_list(L);
	
	//Part 7: Adding New Patient Data Entry Records At last of the List
	printf("We are gonna add records of new patient at End of List\nHit any key to process\n");
	getch();
	insert_at_end_fullRecords(L);
	print_list(L);
	
	//Part 8: Deleting All data Entries patient appointed with particular doctor
	printf("Enter Doctor Name whose Appointments you wanna cancel, We will delete all records of concerned patients\n");
	scanf("%s",name);
	print_node(search_by_doctor(L,name));
	Delete_node_between(searchPrevious_by_doctor(L,name));
	print_list(L);
	
	//Part 9: Adding Patient Entry Records after Patient A
	printf("Now a New Records Entry will be inserted in the list after PatientA, Hit any key to process\n");
	getch();
	char temp1[10]={'P','a','t','i','e','n','t','A'};
	insert_between_fullRecords(search_by_name(L,temp1));
	print_list(L);
	
	//Part 10: Deleting Whole list
	Delete_all_list(L);
	print_list(L);
	
	printf("Thanks for Using Program\nPress Any key To End");
	getch();
}
void print_list(struct node* L)
{
	int a=1;
	struct node* P=L;
	P=P->next;
	printf("Current List is:\n\n");
	if(P!=NULL)
	{
		while(P!=NULL)
		{
			printf("Data Entry of %d patient\n",a);
			printf("Patient ID is		 : %d\n",P->patientId);
			if(P->patientName!=NULL)
				printf("Patient Name is		 : %s\n",P->patientName);
			if(P->patientDepartment!=NULL)
				printf("Department of Patient	 : %s\n",P->patientDepartment);
			if(P->patientFileNo!=NULL)
				printf("Patient File No.	 : %d\n",P->patientFileNo);
			if(P->timeOfVisit!=NULL)
				printf("Time of Visit		 : %s\n",P->timeOfVisit);
			if(P->dateOfVisit!=NULL)
				printf("Date Of Visit		 : %s\n",P->dateOfVisit);
			if(P->physicianName!=NULL)
				printf("Doctor's name		 : %s\n",P->physicianName);
		printf("\n\n*******\n\n");
		a++;
		P=P->next;
		}
	}
	else
		printf("List is Empty\n");
}

void print_node(struct node* P)
{
	printf("Data Records of Current Patient are:\n\n");
		printf("Patient ID is		 : %d\n",P->patientId);
		if(P->patientName!=NULL)
			printf("Patient Name is		 : %s\n",P->patientName);
		if(P->patientDepartment!=NULL)
			printf("Department of Patient	 : %s\n",P->patientDepartment);
		if(P->patientFileNo!=NULL)
			printf("Patient File No.	 : %d\n",P->patientFileNo);
		if(P->timeOfVisit!=NULL)
			printf("Time of Visit		 : %s\n",P->timeOfVisit);
		if(P->dateOfVisit!=NULL)
			printf("Date Of Visit		 : %s\n",P->dateOfVisit);
		if(P->physicianName!=NULL)
			printf("Doctor's name		 : %s\n",P->physicianName);
		printf("\n\n*******\n\n");
}
void insert_at_end_justId_name(struct node* L)
{
	struct node* P=L;
	while(P->next!=NULL)
	{
		P=P->next;
	}
	
	struct node* node;
	node=(struct node*)malloc(sizeof(struct node));
		
	printf("Now we will add records of new patient at last\nHit any key to process\n");
	getch();
		printf("Enter Patient ID		 : ");
		scanf("%d",&node->patientId);
		printf("\nEnter Patient Name 		 : ");
		scanf("%s",&node->patientName);
		printf("\n*************\n");

		char patientDepartment[10]={NULL};
		char dateOfVisit[10]={NULL};
		char physicianName[10]={NULL};
		char timeOfVisit[10]={NULL};
		
		
		node->patientFileNo=NULL;
		strcpy (node->patientDepartment, patientDepartment);
		strcpy (node->dateOfVisit, dateOfVisit);
		strcpy (node->physicianName, physicianName);
		strcpy (node->timeOfVisit, timeOfVisit);
	
		P->next=node;
		node->next=NULL;
}
void Delete_all_list(struct node* L)
{
	struct node* P;
	struct node* temp;
	printf("We are gonna delete all the entries in the list while keeping Header alive for tracing\n");
	printf("Hit any key to process\n");
	getch();
	while(L->next!=NULL)
	{
		P=L->next;
		temp=L;
		while(P->next!=NULL)
		{
			P=P->next;
			temp=temp->next;
		}
		temp->next=NULL;
		free(P);
	}
	printf("Task Completed, whole list has been deleted\n");
	printf("Hit any key to continue\n");
	getch();
}
void Delete_node_between(struct node* P)
{
	
	struct node* temp=P->next;
	printf("We are gonna delete all data entries of mentioned patient\n");
	printf("Hit any key to process\n");
	getch();
	P->next=temp->next;
	free(temp);
	printf("Task Accomplished, Hit any key to continue\n");
	getch();
}
void update_time_date(struct node* L)
{
	printf("Enter new Time for the this record to update\n");
	scanf("%s",L->timeOfVisit);
	printf("Enter new Date for the this record to update\n");
	scanf("%s",L->dateOfVisit);
}
void insert_between_fullRecords(struct node* P)
{
	
	struct node* node;
	node=(struct node*)malloc(sizeof(struct node));
		
		printf("Enter Patient ID		 : ");
		scanf("%d",&node->patientId);
		printf("\nEnter Patient Name 		 : ");
		scanf("%s",&node->patientName);
		printf("\nEnter Department of Patient	 : ");
		scanf("%s",&node->patientDepartment);
		printf("\nEnter Patient File No.		 : ");
		scanf("%d",&node->patientFileNo);
		printf("\nEnter Time of Visit		 : ");
		scanf("%s",&node->timeOfVisit);
		printf("\nEnter Date Of Visit		 : ");
		scanf("%s",&node->dateOfVisit);
		printf("\nEnter Doctor's name		 : ");
		scanf("%s",&node->physicianName);
		printf("\n*************\n");

		node->next=P->next;
		P->next=node;
}
void insert_at_end_fullRecords(struct node* L)
{
	struct node* P=L;
	while(P->next!=NULL)			//This moves the pointer to last node of the list
	{
		P=P->next;
	}
	
	struct node* node;
	node=(struct node*)malloc(sizeof(struct node));
		
		printf("Enter Patient ID		 : ");
		scanf("%d",&node->patientId);
		printf("\nEnter Patient Name 		 : ");
		scanf("%s",&node->patientName);
		printf("\nEnter Department of Patient	 : ");
		scanf("%s",&node->patientDepartment);
		printf("\nEnter Patient File No.		 : ");
		scanf("%d",&node->patientFileNo);
		printf("\nEnter Time of Visit		 : ");
		scanf("%s",&node->timeOfVisit);
		printf("\nEnter Date Of Visit		 : ");
		scanf("%s",&node->dateOfVisit);
		printf("\nEnter Doctor's name		 : ");
		scanf("%s",&node->physicianName);
		printf("\n*************\n");

		P->next=node;
		node->next=NULL;
}
