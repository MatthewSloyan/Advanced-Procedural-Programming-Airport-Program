#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

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

int searchList(struct node* top);
int searchListByPassport(struct node* top);
void searchDisplayList(struct node* top, int passengerLocation);
void updatePassenger(struct node* top, int passengerLocation);

void deletePassengerAtStart(struct node** top);
void deletePassengerAtEnd(struct node* top);
void deletePassengerAtPos(struct node* top, int passengerLocation);
int length(struct node* top);

void printPassengersToFile(struct node* top, int length);
void readPassengersFromFile(struct node** top);

FILE* filep;

void main()
{ 
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
	int location = 0;
	int compare;
	int lengthOfList = 0;

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

			//READ IN FROM FILE ====================
			readPassengersFromFile(&headPtr);

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
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						displayAllPassenger(headPtr);
					}
					break;
				case 3:
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						location = searchList(headPtr);

						if (location == 0) {
							printf("\nPassenger not found, please try again.");
						}
						else {
							searchDisplayList(headPtr, location);
						}
					}
					break;
				case 4:
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						location = searchList(headPtr);

						if (location == 0) {
							printf("\nPassenger not found, please try again.");
						}
						else {
							updatePassenger(headPtr, location);
						}
					}
					break;
				case 5:
					if (headPtr == NULL)
					{
						printf("Sorry the list is empty");
					}

					else
					{
						location = searchListByPassport(headPtr);
						if (location == 0) {
							printf("\nPassenger not found, please try again.");
						}
						else {
							printf("\nDeleting Passenger %d", location);

							if (location < 2)
							{
								deletePassengerAtStart(&headPtr);
							}
							else if (location >= 2 && location < length(headPtr))
							{
								deletePassengerAtPos(headPtr, location);
							}
							else
							{
								deletePassengerAtEnd(headPtr);
							}
						}
					} //outer else
					break;
				case 6:
					
					break;
				case 7:
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						printf("\nPrinting to file =========\n");
						lengthOfList = length(headPtr);
						printPassengersToFile(headPtr, lengthOfList);
					}
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

			//once the program is exited all the linked list data is printed to a file.
			lengthOfList = length(headPtr);
			printPassengersToFile(headPtr, lengthOfList);
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

//function to search a specific element in a list and return the location
int searchList(struct node* top)
{
	struct node* curr;
	char userInput[30];
	char passPortNumConverted[30];
	int passengerNum = 0;
	int passengerNumFinal = 0;
	int found = 0;

	//set the curr to the head pointer
	curr = top;

	//ask the user to input a value
	printf("\nPlease enter the passport number or first/second name to search by\n");
	scanf("%s", userInput);

	//while the current pointer is not equal to null continue through the list
	while (curr != NULL)
	{
		passengerNum++;

		//convert the passport number to a string for comparision
		sprintf(passPortNumConverted, "%d", curr->passportNum);

		//if the value is found print out the value, location and exit the loop
		if (strcmp(userInput, passPortNumConverted) == 0 || strcmp(userInput, curr->firstName) == 0 || strcmp(userInput, curr->secondName) == 0) {
			curr = curr->NEXT;
			found = 1;
			break;
		}

		//move curr to the next pointer
		curr = curr->NEXT;
	}

	if (found == 1) {
		passengerNumFinal = passengerNum;
	}
	return passengerNumFinal;
}

//function to search a specific element in a list by passport and return the location
int searchListByPassport(struct node* top)
{
	struct node* curr;
	int userInput;
	int passengerNum = 0;
	int passengerNumFinal = 0;
	int found = 0;

	//set the curr to the head pointer
	curr = top;

	//ask the user to input a value
	printf("\nPlease enter the passport number to search by\n");
	scanf("%d", &userInput);

	//while the current pointer is not equal to null continue through the list
	while (curr != NULL)
	{
		passengerNum++;

		//if the value is found print out the value, location and exit the loop
		if (userInput == curr->passportNum) {
			curr = curr->NEXT;
			found = 1;
			break;
		}

		//move curr to the next pointer
		curr = curr->NEXT;
	}

	if (found == 1) {
		passengerNumFinal = passengerNum;
	}
	return passengerNumFinal;
}

//function to print out the node at the given location
void searchDisplayList(struct node* top, int passengerLocation)
{
	struct node* curr;
	int i;

	//set the curr to the head pointer
	curr = top;

	if (passengerLocation != 1) {
		for (i = 0; i < passengerLocation - 1; i++)
		{
			curr = curr->NEXT;
		}
	}

	printf("\nPASSENGER %d\n===========\n", passengerLocation);

	printf("Passport Num: %d\n", curr->passportNum);
	printf("Name: %s %s\n", curr->firstName, curr->secondName);
	printf("DOB: %d\n", curr->dob);
	printf("Email: %s\n", curr->emailAddress);
	printf("Country traveled from: %d\n", curr->countryTraveledFrom);
	printf("Travel Class: %d\n", curr->travelClass);
	printf("Trips per year: %d\n", curr->tripsPerYear);
	printf("Duration: %d\n", curr->journeyTime);
}

//function to update a passengers details based on a search for their name or passport number
void updatePassenger(struct node* top, int passengerLocation) {
	struct node* curr;
	int i;

	//set the curr to the head pointer
	curr = top;

	if (passengerLocation != 1) {
		for (i = 0; i < passengerLocation - 1; i++)
		{
			curr = curr->NEXT;
		}
	}

	//ask the user to input values
	printf("\nPlease enter your new email address:\n");
	scanf("%s", curr->emailAddress);

	do
	{
		printf("\nWhich of the following areas did you travel from:\n [1] UK\n [2] Rest of Europe\n [3] Asia\n [4] Americas\n [5] Australasia\n");
		scanf("%d", &curr->countryTraveledFrom);
	} while (curr->countryTraveledFrom < 1 || curr->countryTraveledFrom > 5);

	do
	{
		printf("\nWhat travel class did you use to travel to Ireland:\n [1] Economy\n [2] Premium Economy\n [3] Business Class\n [4] First Class\n");
		scanf("%d", &curr->travelClass);
	} while (curr->travelClass < 1 || curr->travelClass > 4);

	do
	{
		printf("\nHow many trips to Ireland do you make per year:\n [1] Less than three times per year\n [2] Less than five times per year\n [3] More than five times per year\n");
		scanf("%d", &curr->tripsPerYear);
	} while (curr->tripsPerYear < 1 || curr->tripsPerYear > 3);

	do
	{
		printf("\nOn average how long is your duration:\n [1] One Day\n [2] Less than 3 days\n [3] Less than 7 days\n [4] More than 7 days\n");
		scanf("%d", &curr->journeyTime);
	} while (curr->journeyTime < 1 || curr->journeyTime > 4);
}

//function to delete a passenger at the start of the linked list
void deletePassengerAtStart(struct node** top)
{
	struct node* temp;

	temp = *top;
	*top = temp->NEXT;
	free(temp);
}

//function to delete a passenger at the end of the linked list
void deletePassengerAtEnd(struct node* top)
{
	struct node* curr;
	struct node* prev_curr;

	curr = top;

	while (curr->NEXT != NULL)
	{
		prev_curr = curr;
		curr = curr->NEXT;
	}

	prev_curr->NEXT = NULL;
	free(curr);
}

//function to delete a passenger based on a search for their passport number
void deletePassengerAtPos(struct node* top, int passengerLocation)
{
	struct node* curr;
	struct node* prev_curr;
	int i;

	curr = top;

	for (i = 0; i < passengerLocation - 1; i++)
	{
		prev_curr = curr;
		curr = curr->NEXT;
	}

	prev_curr->NEXT = curr->NEXT;
	free(curr);
}

//function to print all passengers to file
void printPassengersToFile(struct node* top, int length)
{
	struct node* curr;

	curr = top;

	filep = fopen("passenger.txt", "w");

	if (filep == NULL)
	{
		printf("The file could not be opened to write\n");
	}

	else
	{
		fprintf(filep, "%d\n", length);

		while (curr != NULL)
		{
			//print out the data to file
			fprintf(filep, "%d\n", curr->passportNum);
			fprintf(filep, "%s\n", curr->firstName);
			fprintf(filep, "%s\n", curr->secondName);
			fprintf(filep, "%d\n", curr->dob);
			fprintf(filep, "%s\n", curr->emailAddress);
			fprintf(filep, "%d\n", curr->countryTraveledFrom);
			fprintf(filep, "%d\n", curr->travelClass);
			fprintf(filep, "%d\n", curr->tripsPerYear);
			fprintf(filep, "%d\n", curr->journeyTime);

			//set the curr pointer to the next pointer to move through linked list
			curr = curr->NEXT;
		}
		fclose(filep); //close the file
	}
}

void readPassengersFromFile(struct node** top) {

	struct node* curr;
	struct node* newNode;
	int i;
	int length = 0;

	//open the that the player has entered if found
	filep = fopen("passenger.txt", "r");

	if (filep == NULL)
	{
		printf("The file cannot be opened\n");
	}

	else
	{
		//read in the length of the list
		fscanf(filep, "%d", &length);

		//scan in the each players cards into array
		for (i = 0; i < length; i++)
		{
			newNode = (struct node*)malloc(sizeof(struct node));

			//read in the passenger details from the file
			fscanf(filep, "%d", &newNode->passportNum);
			fscanf(filep, "%s", newNode->firstName);
			fscanf(filep, "%s", newNode->secondName);
			fscanf(filep, "%d", &newNode->dob);
			fscanf(filep, "%s", newNode->emailAddress);
			fscanf(filep, "%d", &newNode->countryTraveledFrom);
			fscanf(filep, "%d", &newNode->travelClass);
			fscanf(filep, "%d", &newNode->tripsPerYear);
			fscanf(filep, "%d", &newNode->journeyTime);

			if (i == 0) {
				//set newNode->NEXT to the headpointer
				newNode->NEXT = *top;
				//set the head pointer to the newNode
				*top = newNode;

				// set curr to the headpointer NULL
				curr = *top;
			}
			else {
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
		}
		fclose(filep); //close the file

	} //else
}

//function to get the length of the linked list
int length(struct node* top)
{
	struct node* curr;
	int length = 0;

	//set the curr to the head pointer
	curr = top;

	//while the current pointer is not equal to null continue through the list
	while (curr != NULL)
	{
		length++; //increment the length at every node
		curr = curr->NEXT; //move curr to the next pointer
	}

	return length;
}