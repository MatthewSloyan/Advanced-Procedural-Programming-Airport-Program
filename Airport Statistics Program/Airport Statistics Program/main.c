#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	int passportNum;
	char firstName[30];
	char secondName[25];
	int dob;
	char emailAddress[50];
	int countryTraveledFrom;
	int travelClass;
	int tripsPerYear;
	int journeyTime;
	struct node* NEXT;
};

void addPassengerAtStart(struct node** top);
void addPassengerAtEnd(struct node* top);
void displayAllPassenger(struct node* top);
void deletePassengerAtStart(struct node** top);
void deletePassengerAtEnd(struct node* top);

void main()
{ 
	FILE* filep;
	struct node* headPtr = NULL;
	int pos;
	int userSelection = 0;
	char userNameInput[30];
	char passwordInput[15];
	char passwordChar = ' ';
	char userName[30];
	char password[15];
	
	int i, j;

	int found = 0;
	int compare;

	printf("XYZ Airport Ltd\n");
	printf("===============\n\n");

	/*do
	{
		printf("Please enter your username: ");
		scanf("%s", userNameInput);

		i = 0;
		printf("Please enter your password (Max length of 6 characters): ");

		while (i <= 5) {
			passwordInput[i] = getch();
			passwordChar = passwordInput[i];
		
			if (passwordChar == 13) {
				break;
			}
			else {
				printf("*");
			}
			i++;
		}
		passwordInput[i] = '\0';

		//open the that the player has entered if found
		filep = fopen("login.txt", "r");

		if (filep == NULL)
		{
			printf("The file cannot be opened\n");
		}

		else
		{
			while (!feof(filep))
			{
				for (i = 0; i < 3; i++)
				{
					//read in username and password
					fscanf(filep, "%s", userName);
					fscanf(filep, "%s", password);

					if (strcmp(userName, userNameInput) == 0 && strcmp(password, passwordInput) == 0) {
						found = 1;
						break;
					}
				}
			} //while
			fclose(filep); //close the file
		}

		if (found == 1) {
			//print greeting message when access is granted
			printf("\n\nAccess granted, hello %s!", userNameInput); */

			do
			{
				//allow the user to enter a selection from the menu (intitial read)
				printf("\n\nPlease select an option\n [1] Add Passenger\n [2] Display all passengers \n [3] Display passenger details\n");
				printf(" [4] Update Passenger Statistics\n [5] Delete Passenger \n [6] Generate Statistic\n");
				printf(" [7] Print all passenger details to report file\n [8] List all the passenger of	UK & Europe\n");
				printf(" [0] To Exit\n");
				scanf("%d", &userSelection);

				if (userSelection < 0 || userSelection > 8) {
					printf("Error! The value entered must be between 1 and 8, please try again\n");
				}

			} while (userSelection < 0 || userSelection > 8);

			//while loop until -1 is encountered
			while (userSelection != 0)
			{
				switch (userSelection)
				{
				case 1:
					printf("\nAdd a Passenger ============\n");
					if (headPtr == NULL)
					{
						addPassengerAtStart(&headPtr);
					}
					else
					{
						addPassengerAtEnd(headPtr);
					}
					break;
				case 2:
					displayAllPassenger(headPtr);
					break;
				case 3:
					
					break;
				case 4:
					
					break;
				case 5:
					
					break;
				case 6:
					
					break;
				case 7:
					
					break;
				case 8:
					
					break;
				case 9:
					
					break;
				default:
					printf("Invalid option\n");
				}

				//subsequent Read
				do
				{
					printf("\n\nPlease select an option\n [1] Add Passenger\n [2] Display all passengers \n [3] Display passenger details\n");
					printf(" [4] Update Passenger Statistics\n [5] Delete Passenger \n [6] Generate Statistic\n");
					printf(" [7] Print all passenger details to report file\n [8] List all the passenger of	UK & Europe\n");
					printf(" [0] To Exit\n");
					scanf("%d", &userSelection);

					if (userSelection < 0 || userSelection > 8) {
						printf("Error! The value entered must be between 1 and 8, please try again\n");
					}

				} while (userSelection < 0 || userSelection > 8);
			} //while
		} //if found

		//if user not found output error message
		/*if (found != 1) {
			printf("\n\nUser not found, please try again.\n\n");
		}

	} while (found != 1); //overall outer do while to validate username/password input
} */

//FUNCTIONS ==================

void addPassengerAtStart(struct node** top)
{
	struct node* newNode;
	newNode = (struct node*)malloc(sizeof(struct node));

	printf("\nAdding to the start of the list:\n");

	//ask the user to input values
	printf("\nPlease enter your passport number:\n");
	scanf("%d", &newNode->passportNum);

	printf("\nPlease enter your First Name:\n");
	scanf("%s", newNode->firstName);

	printf("\nPlease enter your Last Name:\n");
	scanf("%s", newNode->secondName);

	printf("\nPlease enter the year you were born (E.g 1990):\n");
	scanf("%d", &newNode->dob);

	printf("\nPlease enter your email Address:\n");
	scanf("%s", newNode->emailAddress);

	do
	{
		printf("\nWhich of the following areas did you travel from:\n [1] UK\n [2] Rest of Europe\n [3] Asia\n [4] Americas\n [5] Australasia\n");
		scanf("%d", &newNode->countryTraveledFrom);
	} while (newNode->countryTraveledFrom < 1 || newNode->countryTraveledFrom > 5);

	do
	{
		printf("\nWhat travel class did you use to travel to Ireland:\n [1] Economy\n [2] Premium Economy\n [3] Business Class\n [4] First Class\n");
		scanf("%d", &newNode->travelClass);
	} while (newNode->travelClass < 1 || newNode->travelClass > 4);

	do
	{
		printf("\nHow many trips to Ireland do you make per year:\n [1] Less than three times per year\n [2] Less than five times per year\n [3] More than five times per year\n");
		scanf("%d", &newNode->tripsPerYear);
	} while (newNode->tripsPerYear < 1 || newNode->tripsPerYear > 3);

	do
	{
		printf("\nOn average how long is your duration:\n [1] One Day\n [2] Less than 3 days\n [3] Less than 7 days\n [4] More than 7 days\n");
		scanf("%d", &newNode->journeyTime);
	} while (newNode->journeyTime < 1 || newNode->journeyTime > 4);

	//set newNode->NEXT to the headpointer
	newNode->NEXT = *top;
	//set the head pointer to the newNode
	*top = newNode;
}

void addPassengerAtEnd(struct node* top)
{
	struct node* curr;
	struct node* newNode;

	newNode = (struct node*)malloc(sizeof(struct node));

	printf("\nAdding to the end of the list:\n");

	//ask the user to input values
	printf("\nPlease enter your passport number:\n");
	scanf("%d", &newNode->passportNum);

	printf("\nPlease enter your First Name:\n");
	scanf("%s", newNode->firstName);

	printf("\nPlease enter your Last Name:\n");
	scanf("%s", newNode->secondName);

	printf("\nPlease enter the year you were born (E.g 1990):\n");
	scanf("%d", &newNode->dob);

	printf("\nPlease enter your email Address:\n");
	scanf("%s", newNode->emailAddress);

	do
	{
		printf("\nWhich of the following areas did you travel from:\n [1] UK\n [2] Rest of Europe\n [3] Asia\n [4] Americas\n [5] Australasia\n");
		scanf("%d", &newNode->countryTraveledFrom);
	} while (newNode->countryTraveledFrom < 1 || newNode->countryTraveledFrom > 5);

	do
	{
		printf("\nWhat travel class did you use to travel to Ireland:\n [1] Economy\n [2] Premium Economy\n [3] Business Class\n [4] First Class\n");
		scanf("%d", &newNode->travelClass);
	} while (newNode->travelClass < 1 || newNode->travelClass > 4);

	do
	{
		printf("\nHow many trips to Ireland do you make per year:\n [1] Less than three times per year\n [2] Less than five times per year\n [3] More than five times per year\n");
		scanf("%d", &newNode->tripsPerYear);
	} while (newNode->tripsPerYear < 1 || newNode->tripsPerYear > 3);

	do
	{
		printf("\nOn average how long is your duration:\n [1] One Day\n [2] Less than 3 days\n [3] Less than 7 days\n [4] More than 7 days\n");
		scanf("%d", &newNode->journeyTime);
	} while (newNode->journeyTime < 1 || newNode->journeyTime > 4);

	// set curr to the headpointer NULL
	curr = top;

	//loop through till you find the last node
	while (curr->NEXT != NULL)
	{
		curr = curr->NEXT;
	}

	//set curr->NEXT to the new node
	curr->NEXT = newNode;
	//set newNode->NEXT pointer to NULL to signify the end of the list
	newNode->NEXT = NULL;
}

void displayAllPassenger(struct node* top)
{
	struct node* curr;
	int passengerNum = 0;
	//char countryTraveledFromOutput[30];
	//char countryTraveledToOutput[30];
	//char tripsPerYearOutput[30];
	//char journeyTimeOutput[30];

	curr = top;

	/*switch (curr->countryTraveledFrom)
	{
	case 1:
		countryTraveledFromOutput = "UK";
		break;
	case 2:
		
		break;
	case 3:

		break;
	case 4:

		break;
	default:
		
	} */

	while (curr != NULL)
	{
		printf("\nPASSENGER %d\n===========\n", passengerNum + 1);

		printf("Passport Num: %d\n", curr->passportNum);
		printf("Name: %s %s\n", curr->firstName, curr->secondName);
		printf("DOB: %d\n", curr->dob);
		printf("Email: %s\n", curr->emailAddress);
		printf("Country traveled from: %d\n", curr->countryTraveledFrom);
		printf("Travel Class: %d\n", curr->travelClass);
		printf("Trips per year: %d\n", curr->tripsPerYear);
		printf("Duration: %d\n", curr->journeyTime);
		curr = curr->NEXT;
		passengerNum++;
	}
}


