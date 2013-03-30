#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<conio.h>

struct listnode {
  
	int patientId ;
	char patientName[10];
	char patientDepartment[10];
	int patientFileNumber;
	char timeOfVisit[10];
	char dateOfVisit[6];
	char physicianName[10];
	struct listnode *nextptr;
};


typedef struct listnode listnode;
typedef struct listnode *listnodeptr;

int patientId ;
char patientName[10] = {NULL};
	char patientDepartment[10] = {NULL};
	int patientFileNumber = {NULL};
	char timeOfVisit[10] = {NULL};
	char dateOfVisit[6] = {NULL};
	char physicianName[10] = {NULL};

int inserts (listnodeptr *sptr)
{

	

	listnodeptr newptr;
	listnodeptr previousptr;
	listnodeptr currentptr;
	
	newptr = (listnode*)malloc (sizeof(listnode));

	if (newptr != NULL ){
	
		printf ("\nEnter patient name = ");
		scanf ("%s", &patientName);
		printf ("\nEnter patient id = ");
		scanf ("%d", &patientId);
		printf ("\nEnter patient dept = ");
		scanf ("%s", &patientDepartment);
		printf ("\nEnter patient file number = ");
		scanf ("%d", &patientFileNumber);
		printf ("\nEnter time of visit = ");
		scanf ("%s", &timeOfVisit);
		printf ("\nEnter date of visit");
		scanf ("%s", &dateOfVisit);
		printf ("\nEnter physician mane = ");
		scanf ("%s", &physicianName);
		
	
		

		newptr->patientId  = patientId;
		newptr->patientFileNumber = patientFileNumber;
		
		strcpy (newptr->patientDepartment, patientDepartment);
		strcpy (newptr->dateOfVisit, dateOfVisit);
		strcpy (newptr->patientName, patientName);
		strcpy (newptr->physicianName, physicianName);
		strcpy (newptr->timeOfVisit, timeOfVisit);
		newptr->nextptr = NULL;

		previousptr = NULL;
		currentptr = *sptr;
		
		while (currentptr != NULL ){
			previousptr = currentptr;
			currentptr = currentptr->nextptr;
		}
		
		if (previousptr == NULL)						//idea taken from book//
		{
			newptr->nextptr = *sptr;		
			*sptr = newptr;
		}
		else {
			previousptr->nextptr = newptr;
			newptr->nextptr = currentptr;
		}
	}
	return patientId;
}



int printlist (listnodeptr currentptr)
{
	int x = 1;
	if (currentptr == NULL)
	{
		printf ("LIST IS EMPTY ");
	}
	
	else {
	
	

		while (currentptr != NULL)
		{
			printf ("\n\n\t\tRECORD NUMBER %d", x);
			printf ("\n\t\tpatient id = %d", currentptr->patientId);
			printf ("\n\t\tpatient name = %s", currentptr->patientName);
			printf ("\n\t\tpatient dept = %s", currentptr->patientDepartment);
			printf ("\n\t\ttime of visit = %s", currentptr->timeOfVisit);
			printf ("\n\t\tdate of visit = %s", currentptr->dateOfVisit);
			printf ("\n\t\tpatient file number = %d", currentptr->patientFileNumber);
			printf ("\n\t\tphysician name = %s", currentptr->physicianName);
			x++;
			currentptr = currentptr->nextptr;
			printf ("\n");
		}
	}
	getch();

	return x;
}


void update (listnodeptr currentptr)
{

printf ("\n\n\t\tEnter new information \n");


		
		
		printf ("\nEnter time of visit = ");
		scanf ("%s", &timeOfVisit);
		printf ("\nEnter date of visit");
		scanf ("%s", &dateOfVisit);
		strcpy (currentptr->timeOfVisit, timeOfVisit);
		strcpy (currentptr->dateOfVisit, dateOfVisit);

		


}

void deletes (listnodeptr sptr)
{
	listnodeptr temp;
	listnodeptr currentptr;
	currentptr = sptr;
	
	char a[20];
	printf ("\nEnter the name of the patient you want to delete = ");
	scanf("%s",&a);
	
	

	while (currentptr->nextptr != NULL  &&  strcmp (currentptr->nextptr->patientName, a) !=0)
	{
		currentptr = currentptr->nextptr;
	}
	
	temp=currentptr->nextptr;
	currentptr->nextptr = temp->nextptr;
  	
	free (temp);
	printlist (sptr);

}

listnode* search (listnodeptr sptr)
{
	
	

    char hmm[20];
    listnodeptr currentptr;
    currentptr = sptr->nextptr;

		printf ("\n\nEnter patient name to search = ");
	scanf ("%s", &hmm);
         
    while(currentptr != NULL && strcmp (currentptr->patientName, hmm) !=0)
    {
      currentptr = currentptr->nextptr;
    }
          
  
return currentptr;
}


void inserts_blank (listnodeptr *sptr)
{

	

	listnodeptr newptr;
	listnodeptr previousptr;
	listnodeptr currentptr;
	
	char patientName[10] = {NULL};
	char patientDepartment[10] = {NULL};
	int patientFileNumber = {NULL};
	char timeOfVisit[10] = {NULL};
	char dateOfVisit[6] = {NULL};
	char physicianName[10] = {NULL};

	newptr = (listnode*)malloc (sizeof(listnode));

	if (newptr != NULL ){
	
		printf ("\nEnter patient name = ");
		scanf ("%s", &patientName);
		printf ("\nEnter patient id = ");
		scanf ("%d", &patientId);
		
		strcpy (newptr->physicianName, physicianName);
		newptr->patientId  = patientId;
	
		newptr->patientFileNumber = patientFileNumber;
		
		strcpy (newptr->patientDepartment, patientDepartment);
		strcpy (newptr->dateOfVisit, dateOfVisit);
		strcpy (newptr->patientName, patientName);
		strcpy (newptr->timeOfVisit, timeOfVisit);

	//	newptr->nextptr = NULL;

		previousptr = NULL;
		currentptr = *sptr;
		
		while (currentptr != NULL ){
			previousptr = currentptr;
			currentptr = currentptr->nextptr;
		}
		
		if (previousptr == NULL)						//idea taken from book//
		{
			newptr->nextptr = *sptr;		
			*sptr = newptr;
		}
		else {
			previousptr->nextptr = newptr;
			newptr->nextptr = currentptr;
		}
	}
	
}
void instructions()
{
	printf ("WELCOME\nPress 1 to enter records\nPress 4 to exit");
}



void deletes_all (listnodeptr sptr)
{
	listnodeptr currentptr;
	
	currentptr  = sptr;
	currentptr->nextptr = NULL;
	
	printlist (sptr);

}
		
	
void search_by_doc (listnodeptr sptr)
{
	
	listnodeptr temp;
	listnodeptr abc = sptr;
    char hmm[20] = {'d','o','c','t','o','r','b'};
    listnodeptr currentptr;		//p
    currentptr = sptr;
	
	
	
	while (currentptr->nextptr != NULL )
    {
		
		if (strcmp (currentptr->nextptr->physicianName, hmm) ==0 )
		{
		
			temp=currentptr->nextptr;
			currentptr->nextptr = temp->nextptr;
  			free (temp);
		}

		else 		
		currentptr = currentptr->nextptr;
		

	}

		
	
	 
  

}

		
		
void insert_in (listnodeptr sptr)
{
	char xyz[20];
	listnodeptr newptr;
	listnodeptr currentptr;
	listnodeptr temp;

	currentptr = sptr;

	printf ("\n\nEnter the name of the patient after which you want to add record = ");
	scanf ("%s",&xyz);
	
	while(currentptr != NULL && strcmp (currentptr->patientName, xyz) !=0)
    {
      currentptr = currentptr->nextptr;
    }

	

	newptr = (listnode*)malloc (sizeof(listnode));
	
	printf ("\nEnter patient name = ");
		scanf ("%s", &patientName);
		printf ("\nEnter patient id = ");
		scanf ("%d", &patientId);
		printf ("\nEnter patient dept = ");
		scanf ("%s", &patientDepartment);
		printf ("\nEnter patient file number = ");
		scanf ("%d", &patientFileNumber);
		printf ("\nEnter time of visit = ");
		scanf ("%s", &timeOfVisit);
		printf ("\nEnter date of visit");
		scanf ("%s", &dateOfVisit);
		printf ("\nEnter physician mane = ");
		scanf ("%s", &physicianName);
		
	
		

		newptr->patientId  = patientId;
		newptr->patientFileNumber = patientFileNumber;
		
		strcpy (newptr->patientDepartment, patientDepartment);
		strcpy (newptr->dateOfVisit, dateOfVisit);
		strcpy (newptr->patientName, patientName);
		strcpy (newptr->physicianName, physicianName);
		strcpy (newptr->timeOfVisit, timeOfVisit);
		newptr->nextptr = NULL;


	temp = currentptr->nextptr;
	currentptr->nextptr = newptr;
	newptr->nextptr = temp;

	printlist (sptr);

}



void main ()
{
	listnodeptr startptr = NULL;
	listnodeptr currentptr;
	listnodeptr abc;
	int y;
	int x=0;
	int z;
	int id;
	char xyz[20];

	instructions ();

	printf ("\n\nEnter your choice = ");
	scanf ("%d", &x);


	
	while (x!=4)
	{
	inserts (&startptr);
	x++;
	}
	

	printlist (startptr);


//	abc = search (startptr);
//	update (abc);

//	printlist (startptr);
//	deletes (startptr);

//	printf ("\n\nEnter the details of the node you want to add at the end of the list\n");
//	inserts(&startptr);

//	printf ("\n\nEnter name and id of the patient with blank information");
//	inserts_blank (&startptr);    //insert blank
//	printlist (startptr);	
//	abc = search (startptr);
//	update (abc);
//	printlist (startptr);
	
//	printf ("\n\nGoing to delete all the patient with appointments with doctor B\n\n");
//	getch();
//	search_by_doc (startptr);
//	printlist (startptr);

//	insert_in (startptr);

	printf ("\n\nGoing to delete the whole list\n\n");

	deletes_all (startptr);

}

