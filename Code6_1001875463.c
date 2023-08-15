//Coding Assignment 6 Part 2
//Fawaz Asif - 1001875463

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define HASHTABLESIZE 30
 
/* Node for storing information */
typedef struct goPack
{
    char *playerName;
    float weightlbs;
    char position;
    int jerseyNum;
    int expYears;
    struct goPack *nextPtr;
}
GOPACK;
 
/* This function creates an index corresponding to the input key */
int MyHashFunction(char num[])
{
    // perform hash method
    int value = 0;
    int counter = 0;
    while(counter < strlen(num))
    {
        value = value + num[counter];
        counter++;

    }
    return value % HASHTABLESIZE;
}

void AddNode(GOPACK *NewNode, GOPACK *Packers[])
{
	int HashIndex = MyHashFunction(NewNode->playerName);
	
	/* a linked list does not exist for this cell of the array */
	if (Packers[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->playerName, HashIndex);
		#endif
		Packers[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		GOPACK *TempPtr = Packers[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->nextPtr != NULL) 
		{
			TempPtr = TempPtr->nextPtr;
		}
		TempPtr->nextPtr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->playerName, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(GOPACK *Packers[])
{
	GOPACK *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = Packers[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->playerName);
				NextPtr = TempPtr->nextPtr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(GOPACK *Packers[])
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the player to cut from the Packers ");
	fgets(LookupName, sizeof(LookupName), stdin);
	if (LookupName[0] == '\n')
    {
        fgets(LookupName, sizeof(LookupName), stdin);
    }
    if (LookupName[strlen(LookupName)-1] == '\n')
    {
        LookupName[strlen(LookupName)-1] = '\0';
    }

	int HashIndex = MyHashFunction(LookupName);

	/* Get linked list at key in array */
	GOPACK *TempPtr = Packers[HashIndex];
	GOPACK *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nPlayer %s is not on the Packers\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->playerName, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == Packers[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					Packers[HashIndex] = TempPtr->nextPtr;
					printf("\nPlayer %s has been cut from the Packers\n\n", TempPtr->playerName);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->nextPtr = TempPtr->nextPtr;
					printf("\nPlayer %s has been cut from the Packers\n\n", TempPtr->playerName);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->nextPtr;
			}
		}
		if (result == 0)
		{
			printf("\n\nPlayer %s is not on the Packers\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(GOPACK *Packers[])
{
	int i;
	GOPACK *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Packers[i];

		printf("\nPackers[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->playerName);
				TempPtr = TempPtr->nextPtr;
			}
		}
	}
}

void ShowByLetter(GOPACK *Packers[])
{
	int i;
	GOPACK *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Packers[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->playerName[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->playerName);
				}
				TempPtr = TempPtr->nextPtr;
			}
		}
	}
}

void ShowByName(GOPACK *Packers[])
{
	GOPACK *TempPtr = NULL;
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter player's name ");
	fgets(LookupName, sizeof(LookupName), stdin);
	if (LookupName[0] == '\n')
    {
        fgets(LookupName, sizeof(LookupName), stdin);
    }
    if (LookupName[strlen(LookupName)-1] == '\n')
    {
        LookupName[strlen(LookupName)-1] = '\0';
    }

	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Packers[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->playerName, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n%s\n", TempPtr->playerName);
					
	                printf("Weight\t\t%.1f lbs\n", TempPtr->weightlbs);

                //change this later, it could be where you put position equivalents?
					// if (TempPtr->gender == 'B')
					// 	printf("Gender\t\tM F\n");
					// else if (TempPtr->gender == 'U')
					// 	printf("Genger\t\tUnknown\n");
					// else
					// 	printf("Gender\t\t%c\n", TempPtr->gender);

					printf("Position\t%c\n", TempPtr->position);
					printf("Jersey Number\t%d\n", TempPtr->jerseyNum);
					printf("Years of Experience\t%d\n", TempPtr->expYears);

				}
				TempPtr = TempPtr->nextPtr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nPlayer %s not on the Packers\n\n", LookupName);
}

void AddNewPlayer(GOPACK *Packers[])
{
	int HashIndex = 0;
	GOPACK *NewNode;
	char TempBuffer[100] = {};

	NewNode = malloc(sizeof(GOPACK));
	NewNode->nextPtr = NULL;
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 

	printf("\n\nEnter new player's name to sign ");
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
	TempBuffer[strlen(TempBuffer)-1] = '\0';
	NewNode->playerName = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->playerName, TempBuffer);
	
	printf("\n\nEnter %s's weight as pounds.ounces ", NewNode->playerName);
	scanf("%f", &(NewNode->weightlbs));
	
    // again this pertains to what was commented earlier about transfering this
        // similar mechanism of gender to position
	printf("\n\nEnter %s's position ", NewNode->playerName);
	scanf(" %c", &(NewNode->position));
	NewNode->position = toupper(NewNode->position);

	printf("\n\nEnter %s's jersey number ", NewNode->playerName);
	scanf("%d", &(NewNode->jerseyNum));

	printf("\n\nEnter %s's years of experience in the NFL ", NewNode->playerName);
	scanf("%d", &(NewNode->expYears));

	AddNode(NewNode, Packers);
}

int ReadFileIntoHashTable(int argc, char *argv[], GOPACK *Packers[])
{
	FILE *FH = NULL;
	char FileLine[100] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	GOPACK *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
			token = strtok(FileLine, "|");

			NewNode = malloc(sizeof(GOPACK));
			NewNode->nextPtr = NULL;

			NewNode->playerName = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->playerName, token);
			
			token = strtok(NULL, "|");
			NewNode->weightlbs = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->position = *token;

			token = strtok(NULL, "|");
			NewNode->jerseyNum = atoi(token);
			
			token = strtok(NULL, "|");
			NewNode->expYears = atoi(token);

			AddNode(NewNode, Packers);

			counter++;
		}

	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	GOPACK *Packers[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, Packers);

	do
	{
		printf("\n\nPackers Menu\n\n"
			   "1. Show all players on roster for a given letter\n"
			   "2. Look up player by name\n"
			   "3. How many players are on the Packers?\n"
			   "4. Display the Packers roster\n"
			   "5. Sign a new player\n"
			   "6. Cut a player from the team\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(Packers);
				break;
			case SHOWBYNAME:
				ShowByName(Packers);
				break;
			case COUNT:
				printf("Your team contains %d players\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(Packers);
				break;
			case ADD:
				AddNewPlayer(Packers);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(Packers))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(Packers);

	return 0;
}