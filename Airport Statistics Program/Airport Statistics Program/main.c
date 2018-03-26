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
void getPassengerStatNames(int choice[6], char *statNames[6]);
void isEmailValid(struct node* top);

void readPassengersFromFile(struct node** top);
void printPassengersToFile(struct node* top, int length);

int searchList(struct node* top);
void searchListByPassport(struct node* top, int locationFoundArray[2], int userInput);

void searchDisplayList(struct node* top, int passengerLocation);
void updatePassenger(struct node* top, int passengerLocation);

void deletePassengerAtStart(struct node** top);
void deletePassengerAtEnd(struct node* top);
void deletePassengerAtPos(struct node* top, int passengerLocation);

void generateStats(struct node* top, int selection, int length);
void countCountryStats(int travelClass, int travelFrom, int selection, int pos);
void countDuration(int travelClass, int duration, int selection, int pos);
void printStatsToConsole(int selection);
void printStatsToFile();
int length(struct node* top);

int copyLinkedList(struct node* top, struct node** topTwo);
void sortByDOB(struct node *top);
void swapValues(struct node *valueOne, struct node *valueTwo);

//global variables
FILE* filep;
int countedStatsOne[37];
float finalStatOne[37];

int countedStatsTwo[10];
float finalStatTwo[10];

const char *classes[] = { "Economy","Premium Economy","Business Class", "First Class"};
const char *countries[] = { "UK:\t ","Europe:\t ","Asia:\t ","America: ","AustAsia ", "= 1 Day: ", "< 3 Days:", "< 7 Days:", "> 7 Days:"};

void main()
{ 
	struct node* headPtr = NULL;
	struct node* headPtr2 = NULL;

	int pos;
	int userSelection = 0;
	int statisticsSelection = 0;
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
	int ifCopied = 0;
	int userInput;

	int locationFound[2];

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
				printf(" [7] Print all passenger details to report file\n [8] List all the passenger of	UK in order of DOB\n");
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
					//delete a passenger selection
					if (headPtr == NULL)
					{
						printf("Sorry the list is empty");
					}

					else
					{
						locationFound[0] = 0;
						locationFound[1] = 0;

						//ask the user to input a value
						printf("\nPlease enter the passport number to search by\n");
						scanf("%d", &userInput);

						searchListByPassport(headPtr, locationFound, userInput);

						if (locationFound[0] == 0) {
							printf("\nPassenger not found, please try again.");
						}
						else {
							printf("\nDeleting Passenger %d", locationFound[0]);

							if (locationFound[0] < 2)
							{
								deletePassengerAtStart(&headPtr);
							}
							else if (locationFound[0] >= 2 && locationFound[0] < length(headPtr))
							{
								deletePassengerAtPos(headPtr, locationFound[0]);
							}
							else
							{
								deletePassengerAtEnd(headPtr);
							}
						}
					} //outer else 
					break;
				case 6:
					//generate statistics selection
					do
					{
						//allow the user to enter a selection from the menu (intitial read)
						printf("\n\nPlease select an option to generate statistics by\n [1] Travel Class\n [2] Born before 1980\n");
						scanf("%d", &statisticsSelection);

						if (statisticsSelection < 1 || statisticsSelection > 2) {
							printf("\nError! The value entered must be either 1 or 2, please try again.");
						}

					} while (statisticsSelection < 1 || statisticsSelection > 2);

					lengthOfList = length(headPtr);
					generateStats(headPtr, statisticsSelection, lengthOfList);
					break;
				case 7:
					//print passengers to file selection
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						printf("\nPrinting to file =========\n");
						lengthOfList = length(headPtr);
						printPassengersToFile(headPtr, lengthOfList);

						printStatsToFile();
					}
					break;
				case 8:
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						if (ifCopied == 0) {
							ifCopied = copyLinkedList(headPtr, &headPtr2);

							sortByDOB(headPtr2);
						}
						displayAllPassenger(headPtr2);
					}
					break;
				default:
					printf("Invalid option\n");
				}

				//subsequent Read
				do
				{
					printf("\n\nPlease select an option\n [1] Add Passenger\n [2] Display all passengers \n [3] Display passenger details\n");
					printf(" [4] Update Passenger Statistics\n [5] Delete Passenger \n [6] Generate Statistic\n");
					printf(" [7] Print all passenger details to report file\n [8] List all the passenger of	UK in order of DOB\n");
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

	//no need to validate as the first node is always going to be unique 
	printf("\nPlease enter your passport number:\n");
	scanf("%d", &newNode->passportNum);

	printf("\nPlease enter your First Name:\n");
	scanf("%s", newNode->firstName);

	printf("\nPlease enter your Last Name:\n");
	scanf("%s", newNode->secondName);

	do
	{
		printf("\nPlease enter the year you were born (E.g 1990) It must be between 1920 and 2018.:\n");
		scanf("%d", &newNode->dob);
	} while (newNode->dob < 1920 || newNode->dob > 2018);

	isEmailValid(newNode);

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

	int locationFound[2];

	newNode = (struct node*)malloc(sizeof(struct node));

	printf("\nAdding to the end of the list:\n");

	//ask the user to input values
	do
	{
		printf("\nPlease enter your passport number:\n");
		scanf("%d", &newNode->passportNum);

		//intitalize to 0
		locationFound[1] = 0;

		searchListByPassport(top, locationFound, newNode->passportNum);

		if (locationFound[1] == 1) {
			printf("Error! The passport number entered must be unique, please try again\n");
		}
	} while (locationFound[1] == 1);

	printf("\nPlease enter your First Name:\n");
	scanf("%s", newNode->firstName);

	printf("\nPlease enter your Last Name:\n");
	scanf("%s", newNode->secondName);

	do
	{
		printf("\nPlease enter the year you were born (E.g 1990) It must be between 1920 and 2018.:\n");
		scanf("%d", &newNode->dob);
	} while (newNode->dob < 1920 || newNode->dob > 2018);

	isEmailValid(newNode);

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

void isEmailValid(struct node* top) {

	int n = 0;
	int foundFullStop = 0;
	int foundAtSymbol = 0;
	int foundDotCom = 0;
	int foundAll = 0;
	char *returnedValue;

	do
	{
		printf("\nPlease enter your email Address (Must contain a @, full stop and .com):\n");
		scanf("%s", top->emailAddress);

		foundFullStop = 0;
		foundAtSymbol = 0;
		foundDotCom = 0;

		n = 0;
		while (top->emailAddress[n] != '\0') {
			if (top->emailAddress[n] == '.') {
				foundFullStop = 1;
			}
			n++;
		}

		n = 0;
		while (top->emailAddress[n] != '\0') {
			if (top->emailAddress[n] == '@') {
				foundAtSymbol = 1;
			}
			n++;
		}

		returnedValue = strstr(top->emailAddress, ".com");

		if (returnedValue) {
			foundDotCom = 1;
		}

		if (foundFullStop == 1) {
			if (foundAtSymbol == 1) {
				if (foundDotCom == 1) {
					foundAll = 1;
				}
			}
		}
	} while (foundAll == 0);
}

void displayAllPassenger(struct node* top)
{
	struct node* curr;
	int passengerNum = 0;
	int i;

	curr = top;

	int choices[6];
	char *values[6] = {'\0'};

	//initalize to 0
	for (i = 0; i < 6; i++)
	{
		choices[i] = 0;
		values[i] = " ";
	}

	while (curr != NULL)
	{
		choices[0] = curr->countryTraveledFrom;
		choices[1] = curr->travelClass;
		choices[2] = curr->tripsPerYear;
		choices[3] = curr->journeyTime;

		getPassengerStatNames(choices, values);

		printf("\nPASSENGER %d\n===========\n", passengerNum + 1);

		printf("Passport Num: \t\t%d\n", curr->passportNum);
		printf("Name: \t\t\t%s %s\n", curr->firstName, curr->secondName);
		printf("DOB: \t\t\t%d\n", curr->dob);
		printf("Email: \t\t\t%s\n", curr->emailAddress);
		printf("Country traveled from: \t%s\n", values[0]);
		printf("Travel Class: \t\t%s\n", values[1]);
		printf("Trips per year: \t%s\n", values[2]);
		printf("Duration: \t\t%s\n", values[3]);
		curr = curr->NEXT;
		passengerNum++;
	}
}

void getPassengerStatNames(int choice[6], char *statNames[6]) {

	switch (choice[0])
	{
	case 1:
		statNames[0] = "UK";
		break;
	case 2:
		statNames[0] = "Rest of Europe";
		break;
	case 3:
		statNames[0] = "Asia";
		break;
	case 4:
		statNames[0] = "America";
		break;
	default:
		statNames[0]= "Australasia";
	}

	switch (choice[1])
	{
	case 1:
		statNames[1] = "Economy";
		break;
	case 2:
		statNames[1] = "Premium Economy";
		break;
	case 3:
		statNames[1] = "Business Class";
		break;
	default:
		statNames[1] = "First Class";
	}

	switch (choice[2])
	{
	case 1:
		statNames[2] = "< than 3 times per year";
		break;
	case 2:
		statNames[2] = "< than 5 times per year";
		break;
	default:
		statNames[2] = "> than 5 times per year";
	}

	switch (choice[3])
	{
	case 1:
		statNames[3] = "One Day";
		break;
	case 2:
		statNames[3] = "< than 3 days";
		break;
	case 3:
		statNames[3] = "< than 5 days";
		break;
	default:
		statNames[3] = "> than 7 days";
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
void searchListByPassport(struct node* top, int locationFoundArray[2], int userInput)
{
	struct node* curr;
	int passengerNum = 0;
	int passengerNumFinal = 0;

	//set the curr to the head pointer
	curr = top;

	//while the current pointer is not equal to null continue through the list
	while (curr != NULL)
	{
		passengerNum++;

		//if the value is found print out the value, location and exit the loop
		if (userInput == curr->passportNum) {
			curr = curr->NEXT;
			locationFoundArray[1] = 1;
			break;
		}

		//move curr to the next pointer
		curr = curr->NEXT;
	}

	if (locationFoundArray[1] == 1) {
		locationFoundArray[0] = passengerNum;
	}
}

//function to print out the node at the given location
void searchDisplayList(struct node* top, int passengerLocation)
{
	struct node* curr;
	int i;

	int choices[6];
	char *values[6] = { '\0' };

	//initalize to 0
	for (i = 0; i < 6; i++)
	{
		choices[i] = 0;
		values[i] = " ";
	}

	//set the curr to the head pointer
	curr = top;

	choices[0] = curr->countryTraveledFrom;
	choices[1] = curr->travelClass;
	choices[2] = curr->tripsPerYear;
	choices[3] = curr->journeyTime;

	getPassengerStatNames(choices, values);

	if (passengerLocation != 1) {
		for (i = 0; i < passengerLocation - 1; i++)
		{
			curr = curr->NEXT;
		}
	}

	printf("\nPASSENGER %d\n===========\n", passengerLocation);
	printf("Passport Num: \t\t%d\n", curr->passportNum);
	printf("Name: \t\t\t%s %s\n", curr->firstName, curr->secondName);
	printf("DOB: \t\t\t%d\n", curr->dob);
	printf("Email: \t\t\t%s\n", curr->emailAddress);
	printf("Country traveled from: \t%s\n", values[0]);
	printf("Travel Class: \t\t%s\n", values[1]);
	printf("Trips per year: \t%s\n", values[2]);
	printf("Duration: \t\t%s\n", values[3]);
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

//function to generate the statistics based on the user input
void generateStats(struct node* top, int selection, int length) {

	struct node* curr;
	int passengerNum = 0;
	int i;
	int posCounter = 5;

	curr = top;

	if (selection == 1) {
		//initalize the arrays to zero or back to 0
		for (i = 0; i < 36; i++)
		{
			finalStatOne[i] = 0;
			countedStatsOne[i] = 0;
		}

		while (curr != NULL)
		{
			for (i = 0; i < 4; i++)
			{
				countCountryStats(curr->travelClass, curr->countryTraveledFrom, i + 1, i*9);
			}

			/*for (i = 0; i < 4; i++)
			{
				countDuration(curr->travelClass, curr->journeyTime, i + 1, posCounter);
			}*/
			countDuration(curr->travelClass, curr->journeyTime, 1, 5);
			countDuration(curr->travelClass, curr->journeyTime, 2, 14);
			countDuration(curr->travelClass, curr->journeyTime, 3, 23);
			countDuration(curr->travelClass, curr->journeyTime, 4, 32);
			
			curr = curr->NEXT;
		}

		for (i = 0; i < 36; i++)
		{
			finalStatOne[i] = (float)countedStatsOne[i] / length * 100;
		}

		printStatsToConsole(1);
	}
	else {
		//initalize the arrays to zero or back to 0
		for (i = 0; i < 10; i++)
		{
			finalStatTwo[i] = 0;
			countedStatsTwo[i] = 0;
		}

		while (curr != NULL)
		{
			if (curr->dob < 1980) {

				if (curr->countryTraveledFrom == 1)
					countedStatsTwo[0]++;
				else if (curr->countryTraveledFrom == 2)
					countedStatsTwo[1]++;
				else if (curr->countryTraveledFrom == 3)
					countedStatsTwo[2]++;
				else if (curr->countryTraveledFrom == 4)
					countedStatsTwo[3]++;
				else
					countedStatsTwo[4]++;

				if (curr->journeyTime == 1)
					countedStatsTwo[5]++;
				else if (curr->journeyTime == 2)
					countedStatsTwo[6]++;
				else if (curr->journeyTime == 3)
					countedStatsTwo[7]++;
				else
					countedStatsTwo[8]++;
			}

			curr = curr->NEXT;
		}

		for (i = 0; i < 9; i++)
		{
			finalStatTwo[i] = (float)countedStatsTwo[i] / length * 100;
		}

		printStatsToConsole(2);
	}
}

void countCountryStats(int travelClass, int travelFrom, int selection, int pos) {

	if (travelClass == selection) {
		if (travelFrom == 1)
			countedStatsOne[pos]++;
		else if (travelFrom == 2)
			countedStatsOne[pos + 1]++;
		else if (travelFrom == 3)
			countedStatsOne[pos + 2]++;
		else if (travelFrom == 4)
			countedStatsOne[pos + 3]++;
		else
			countedStatsOne[pos + 4]++;
	}
}

//function to count each class or year born and which country they traveled to.
void countDuration(int travelClass, int duration, int selection, int pos) {

	if (travelClass == selection) {
		if (duration == 1)
			countedStatsOne[pos]++;
		else if (duration == 2)
			countedStatsOne[pos + 1]++;
		else if (duration == 3)
			countedStatsOne[pos + 2]++; 
		else
			countedStatsOne[pos + 3]++;
	}
}

//function to print the statistics option One
void printStatsToConsole(int selection) {
	int i;
	int pos = 0;
	int counter = 0;

	if (selection == 1) {
		for (i = 0; i < 36; i++)
		{
			if (i == 0 || i == 9 || i == 18 || i == 27) {
				printf("\n%s ===========\n", classes[pos]);
				pos++;
			}
			printf("%s %12.2f%%\n", countries[counter], finalStatOne[i]);
			counter++;

			if (counter == 9) {
				counter = 0;
			}
		}
	}
	else {
		printf("\nBorn before 1980 ========\n");
		for (i = 0; i < 9; i++)
		{
			printf("%s %12.2f%%\n", countries[i], finalStatTwo[i]);
		}
	}
}

//function to print the statistics to a file
void printStatsToFile() {
	int i;
	int pos = 0;
	int counter = 0;

	filep = fopen("passengerStatistics.txt", "w");

	if (filep == NULL)
	{
		printf("The file could not be opened to write\n");
	}

	else
	{
		for (i = 0; i < 36; i++)
		{
			if (i == 0 || i == 9 || i == 18 || i == 27) {
				fprintf(filep, "\n%s ===========\n", classes[pos]);
				pos++;
			}
			fprintf(filep, "%s %12.2f%%\n", countries[counter], finalStatOne[i]);
			counter++;

			if (counter == 9) {
				counter = 0;
			}
		}

		fprintf(filep, "\n\nBorn before 1980 ========\n");
		for (i = 0; i < 9; i++)
		{
			fprintf(filep, "%s %12.2f%%\n", countries[i], finalStatTwo[i]);
		}

		fclose(filep); //close the file
	}
}

int copyLinkedList(struct node* top, struct node** topTwo)
{
	struct node* curr;
	struct node* currTwo;
	struct node* newNode;

	int pos = 0;
	int ifDone = 0;

	curr = top;

	while (curr != NULL)
	{
		newNode = (struct node*)malloc(sizeof(struct node));

		newNode->passportNum = curr->passportNum;
		strcpy(newNode->firstName, curr->firstName);
		strcpy(newNode->secondName, curr->secondName);
		newNode->dob = curr->dob;
		strcpy(newNode->emailAddress, curr->emailAddress);
		newNode->countryTraveledFrom = curr->countryTraveledFrom;
		newNode->travelClass = curr->travelClass;
		newNode->tripsPerYear = curr->tripsPerYear;
		newNode->journeyTime = curr->journeyTime;

		if (pos == 0) {
			//set newNode->NEXT to the headpointer
			newNode->NEXT = *topTwo;
			//set the head pointer to the newNode
			*topTwo = newNode;

			// set curr to the headpointer NULL
			currTwo = *topTwo;
		}
		else {
			//loop through till you find the last node
			while (currTwo->NEXT != NULL)
			{
				currTwo = currTwo->NEXT;
			}

			//set curr->NEXT to the new node
			currTwo->NEXT = newNode;
			//set newNode->NEXT pointer to NULL to signify the end of the list
			newNode->NEXT = NULL;
		}

		//set the curr pointer to the next pointer to move through linked list
		pos++;
		ifDone = 1;
		curr = curr->NEXT;
	}
	return ifDone;
}

/* Bubble sort the given linked lsit */
void sortByDOB(struct node *top)
{
	int swapCondition, i;
	struct node *curr;

	do
	{
		swapCondition = 0;
		curr = top;

		while (curr->NEXT != NULL)
		{
			if (curr->dob > curr->NEXT->dob)
			{
				swapValues(curr, curr->NEXT);
				swapCondition = 1;
			}
			curr = curr->NEXT;
		}
	} while (swapCondition);
}

/* function to swap data of two nodes a and b*/
void swapValues(struct node *valueOne, struct node *valueTwo)
{
	int tempPassportNum;
	char tempFirstName[30];
	char tempSecondName[25];
	int tempDob;
	char tempEmailAddress[50];
	int tempCountryTraveledFrom;
	int tempTravelClass;
	int tempTripsPerYear;
	int tempJourneyTime;

	tempPassportNum = valueOne->passportNum;
	valueOne->passportNum = valueTwo->passportNum;
	valueTwo->passportNum = tempPassportNum;

	strcpy(tempFirstName, valueOne->firstName);
	strcpy(valueOne->firstName, valueTwo->firstName);
	strcpy(valueTwo->firstName, tempFirstName);

	strcpy(tempSecondName, valueOne->secondName);
	strcpy(valueOne->secondName, valueTwo->secondName);
	strcpy(valueTwo->secondName, tempSecondName);

	tempDob = valueOne->dob;
	valueOne->dob = valueTwo->dob;
	valueTwo->dob = tempDob;

	strcpy(tempEmailAddress, valueOne->emailAddress);
	strcpy(valueOne->emailAddress, valueTwo->emailAddress);
	strcpy(valueTwo->emailAddress, tempEmailAddress);

	tempCountryTraveledFrom = valueOne->countryTraveledFrom;
	valueOne->countryTraveledFrom = valueTwo->countryTraveledFrom;
	valueTwo->countryTraveledFrom = tempCountryTraveledFrom;

	tempTravelClass = valueOne->travelClass;
	valueOne->travelClass = valueTwo->travelClass;
	valueTwo->travelClass = tempTravelClass;

	tempTripsPerYear = valueOne->tripsPerYear;
	valueOne->tripsPerYear = valueTwo->tripsPerYear;
	valueTwo->tripsPerYear = tempTripsPerYear;

	tempJourneyTime = valueOne->journeyTime;
	valueOne->journeyTime = valueTwo->journeyTime;
	valueTwo->journeyTime = tempJourneyTime;
}
