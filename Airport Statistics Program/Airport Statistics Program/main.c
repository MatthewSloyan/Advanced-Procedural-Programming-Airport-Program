// 2nd Year Advanced Procedural Programming Airport Statistics Program
// by Matthew Sloyan G00348036

//Github Link:
//https://github.com/MatthewSloyan/Advanced-Procedural-Programming-Airport-Program

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

//declare the linked list struct
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

//function declaration
//adding functions
void addPassengerAtStart(struct node** top, int passportNum);
void addPassengerAtEnd(struct node* top, int passportNum);
void addElementAtPos(struct node* top, int position, int passportNum);
void userInputs(struct node* top);
int findSortedPosition(struct node* top, int userPassportNumber);
void isEmailValid(struct node* top);

//displaying
void displayAllPassenger(struct node* top);
void getPassengerStatNames(int choice[6], char *statNames[6]);

//searches
int searchList(struct node* top);
void searchListByPassport(struct node* top, int locationFoundArray[2], int userInput);
void searchDisplayList(struct node* top, int passengerLocation);

//update or delete
void updatePassenger(struct node* top, int passengerLocation);
void deletePassengerAtStart(struct node** top);
void deletePassengerAtEnd(struct node* top);
void deletePassengerAtPos(struct node* top, int passengerLocation);

//read from file or print to file
void readPassengersFromFile(struct node** top);
void printPassengersToFile(struct node* top, int length);

//statistics functions
void generateStats(struct node* top, int selection, int length);
void countCountryStats(int travelClass, int travelFrom, int selection, int pos);
void countDuration(int travelClass, int duration, int selection, int pos);
void printStatsToConsole(int selection);
void printStatsToFile();
int length(struct node* top);

//copy and sort
int copyLinkedList(struct node* top, struct node** topTwo);
void sortByDOB(struct node *top);
void swapValues(struct node *valueOne, struct node *valueTwo);

//global variables for statistics
FILE* filep;
int countedStatsOne[37];
float finalStatOne[37];
int countedStatsTwo[10];
float finalStatTwo[10];
const char *classes[] = { "Economy","Premium Economy","Business Class", "First Class"};
const char *countries[] = { "UK:\t ","Europe:\t ","Asia:\t ","America: ","AustAsia ", "= 1 Day: ", "< 3 Days:", "< 7 Days:", "> 7 Days:"};

void main()
{ 
	//declare head pointer 1 and 2. 1 is for the main linked list. 2 is for the copied linked used for sorting
	struct node* headPtr = NULL;
	struct node* headPtr2 = NULL;

	//userName and password variables
	char userNameInput[30];
	char passwordInput[15];
	char passwordChar = ' ';
	char userName[30];
	char password[15];
	
	int pos;
	int userSelection = 0;
	int userPassportInput = 0;
	int statisticsSelection = 0;

	int found = 0;
	int location = 0;
	int sortedLocation = 0;
	int sortedLength = 0;
	int compare;
	int lengthOfList = 0;
	int ifCopied = 0;
	int userInput;

	int locationFound[2];

	int i, j;

	printf("XYZ Airport Ltd\n");
	printf("===============\n\n");

	do
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
			printf("\n\nAccess granted, hello %s!", userNameInput);

			//READ IN FROM FILE ====================
			readPassengersFromFile(&headPtr);

			//allow the user to enter a selection from the menu (intitial read)
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

			} while (userSelection < 0 || userSelection > 8); //validation to allow only numbers between 0 and 8

			// main while loop of program until -1 is encountered
			while (userSelection != 0)
			{
				//switch based on the user input
				switch (userSelection)
				{
				case 1:
					printf("\nAdd a Passenger ============\n");

					//ask the user to input values
					do
					{
						printf("\nPlease enter your passport number:\n");
						scanf("%d", &userPassportInput);

						//intitalize to 0
						locationFound[1] = 0;

						//call the search by passport function to check if the passport number already exists, if it does then it returns 1 into position 1 of the array
						// the array is used so the function can be used again later in the program to cut down on code, it's basically returning two values.
						searchListByPassport(headPtr, locationFound, userPassportInput);

						if (locationFound[1] == 1) {
							printf("Error! The passport number entered must be unique, please try again\n");
						}
					} while (locationFound[1] == 1); //validation to allow only if the passport number is unique

					//gets the length of the linked list
					sortedLength = length(headPtr);

					//gets the position to place the node based on the order of passport numbers
					sortedLocation = findSortedPosition(headPtr, userPassportInput);

					if (headPtr == NULL || sortedLocation == 1)
					{
						//if the linked doesn't exist or the node is to be placed at the start (location 1)
						addPassengerAtStart(&headPtr, userPassportInput);
					}
					else if (sortedLocation = length)
					{
						//if the sorted location is the length, then the node should be placed at the end
						addPassengerAtEnd(headPtr, userPassportInput);
					}
					else {
						//place the node at the sorted location that was found, so that it is in order based on the passport number
						addElementAtPos(headPtr, sortedLocation, userPassportInput);
					}
					break;
				case 2:
					//Display all passengers
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						displayAllPassenger(headPtr);
					}
					break;
				case 3:
					//Search for a spefic passenger and output their data if found
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						//search the list based on name or passport number and return the location
						location = searchList(headPtr);

						if (location == 0) {
							printf("\nPassenger not found, please try again.");
						}
						else {
							//display the passenger using the returned location
							searchDisplayList(headPtr, location);
						}
					}
					break;
				case 4:
					//update passenger details
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						//search the list based on name or passport number and return the location (used again to save code)
						location = searchList(headPtr);

						if (location == 0) {
							printf("\nPassenger not found, please try again.");
						}
						else {
							//update the passenger using the returned location
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
						//initialize values back to 0 to be able to use it again
						locationFound[0] = 0;
						locationFound[1] = 0;

						//ask the user to input a value
						printf("\nPlease enter the passport number to search by\n");
						scanf("%d", &userInput);

						//search the list only by passport number and return the location found into position 0 of the array (used again)
						searchListByPassport(headPtr, locationFound, userInput);

						if (locationFound[0] == 0) {
							printf("\nPassenger not found, please try again.");
						}
						else {
							printf("\nDeleting Passenger %d", locationFound[0]);

							if (locationFound[0] < 2)
							{
								//if the location returned is 1 then it's at the start of the list so call that function
								deletePassengerAtStart(&headPtr);
							}
							else if (locationFound[0] >= 2 && locationFound[0] < length(headPtr))
							{
								//if the location returned is 2 or more and is less then the length then it must be deleted at a specific position
								deletePassengerAtPos(headPtr, locationFound[0]);
							}
							else
							{
								//otherwise delete at the end 
								deletePassengerAtEnd(headPtr);
							}
						}
					} //outer else 
					break;
				case 6:
					//generate statistics selection
					do
					{
						//allow the user to enter a selection from the menu
						printf("\n\nPlease select an option to generate statistics by\n [1] Travel Class\n [2] Born before 1980\n");
						scanf("%d", &statisticsSelection);

						if (statisticsSelection < 1 || statisticsSelection > 2) {
							printf("\nError! The value entered must be either 1 or 2, please try again.");
						}

					} while (statisticsSelection < 1 || statisticsSelection > 2); //validation

					//get the length of the list used to divide the result by the number of passengers then call the stats function
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

						//get the length of the linked list to print at the top of the file (used when reading in the data)
						lengthOfList = length(headPtr);
						printPassengersToFile(headPtr, lengthOfList);

						//print the generated stats to file
						printStatsToFile();
					}
					break;
				case 8:
					//list in order of DOB selection
					if (headPtr == NULL)
					{
						printf("Error, the list is empty. Please add a passenger and try again.");
					}
					else {
						//check if the list has been copied already, so it's not done twice
						if (ifCopied == 0) {
							//call the method the copy the linked list into headPtr2 so it doesn't affect the main linked list when sorting
							ifCopied = copyLinkedList(headPtr, &headPtr2);

							//sort the newly copied linked list using a bubble sort
							sortByDOB(headPtr2);
						}
						//display the sorted list ordered by DOB
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

				} while (userSelection < 0 || userSelection > 8); //validation.
			} //while

			//once the program is exited all the linked list data is printed to a file.
			lengthOfList = length(headPtr);
			printPassengersToFile(headPtr, lengthOfList);
		} //if found

		//if user not found output error message
		if (found != 1) {
			printf("\n\nUser not found, please try again.\n\n");
		}

	} while (found != 1); //overall outer do while to validate username/password input
}


//FUNCTIONS =================================

//functio to add a passenger at the start of a new linked list
void addPassengerAtStart(struct node** top, int passportNum)
{
	//create a new node and instantiate
	struct node* newNode;
	newNode = (struct node*)malloc(sizeof(struct node));

	printf("\nAdding to the start of the list:\n");

	//set the passed in passport number
	newNode->passportNum = passportNum;

	//call the method for the rest of the user inputs and pass in the newNode
	userInputs(newNode);

	//set newNode->NEXT to the headpointer which is a double pointer
	newNode->NEXT = *top;
	//set the head pointer to the newNode
	*top = newNode;
}

void addPassengerAtEnd(struct node* top, int passportNum)
{
	//create a new node, curr node and instantiate
	struct node* curr;
	struct node* newNode;

	newNode = (struct node*)malloc(sizeof(struct node));

	printf("\nAdding to the end of the list:\n");

	//set the passed in passport number
	newNode->passportNum = passportNum;

	//call the method for the user inputs
	userInputs(newNode);

	// set curr to the head pointer
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

void addElementAtPos(struct node* top, int position, int passportNum)
{
	struct node* curr;
	struct node* newNode;
	int i;

	newNode = (struct node*)malloc(sizeof(struct node));

	printf("\nAdding to position: %d\n", position);

	//set the passed in passport number
	newNode->passportNum = passportNum;

	//call the method for the user inputs
	userInputs(newNode);

	// set curr to the head pointer
	curr = top;

	//loop through till at the position before the one passed in to add element bewteen them
	for (i = 0; i < position - 2; i++)
	{
		curr = curr->NEXT;
	}

	newNode->NEXT = curr->NEXT;
	curr->NEXT = newNode;
}

//function which has all the user inputs and inputs them into the newNode that is passed in (it's used in all add functions to save code)
void userInputs(struct node* top) {

	printf("\nPlease enter your First Name:\n");
	scanf("%s", top->firstName);

	printf("\nPlease enter your Last Name:\n");
	scanf("%s", top->secondName);

	do
	{
		printf("\nPlease enter the year you were born (E.g 1990) It must be between 1920 and 2018.:\n");
		scanf("%d", &top->dob);
	} while (top->dob < 1920 || top->dob > 2018); //validation to make sure it's a correct dob

	isEmailValid(top);

	do
	{
		printf("\nWhich of the following areas did you travel from:\n [1] UK\n [2] Rest of Europe\n [3] Asia\n [4] Americas\n [5] Australasia\n");
		scanf("%d", &top->countryTraveledFrom);
	} while (top->countryTraveledFrom < 1 || top->countryTraveledFrom > 5);

	do
	{
		printf("\nWhat travel class did you use to travel to Ireland:\n [1] Economy\n [2] Premium Economy\n [3] Business Class\n [4] First Class\n");
		scanf("%d", &top->travelClass);
	} while (top->travelClass < 1 || top->travelClass > 4);

	do
	{
		printf("\nHow many trips to Ireland do you make per year:\n [1] Less than three times per year\n [2] Less than five times per year\n [3] More than five times per year\n");
		scanf("%d", &top->tripsPerYear);
	} while (top->tripsPerYear < 1 || top->tripsPerYear > 3);

	do
	{
		printf("\nOn average how long is your duration:\n [1] One Day\n [2] Less than 3 days\n [3] Less than 7 days\n [4] More than 7 days\n");
		scanf("%d", &top->journeyTime);
	} while (top->journeyTime < 1 || top->journeyTime > 4);

}

//find the position to place a node based on the order of the passport number
int findSortedPosition(struct node* top, int userPassportNumber)
{
	struct node* curr;
	int locatation = 0;

	//set the curr to the head pointer
	curr = top;

	//while the current pointer is not equal to null continue through the list
	while (curr != NULL)
	{
		locatation++;

		//if the value is greater than the passed in passport number then use this location and exit
		if (curr->passportNum > userPassportNumber) {
			break;
		}

		//move curr to the next pointer
		curr = curr->NEXT;
	}

	//return the location the method call
	return locatation;
}

//function to check if the email is valid
void isEmailValid(struct node* top) {

	int n = 0;
	int foundFullStop = 0;
	int foundAtSymbol = 0;
	int foundDotCom = 0;
	int foundAll = 0;
	char *returnedValue; //pointer to the returned string

	do
	{
		printf("\nPlease enter your email Address (Must contain a @, full stop and .com):\n");
		scanf("%s", top->emailAddress);

		foundFullStop = 0;
		foundAtSymbol = 0;
		foundDotCom = 0;

		n = 0;
		//loop through the string input and check if the character at n is a fullstop
		while (top->emailAddress[n] != '\0') {
			if (top->emailAddress[n] == '.') {
				foundFullStop = 1;
			}
			n++;
		}

		n = 0;
		//loop through the string input and check if the character at n is a @ symbol
		while (top->emailAddress[n] != '\0') {
			if (top->emailAddress[n] == '@') {
				foundAtSymbol = 1;
			}
			n++;
		}

		//call the strstr() method to find the first occurance of the substring .com in the string input
		returnedValue = strstr(top->emailAddress, ".com");

		//if returned string is not equal to null then found
		if (returnedValue) {
			foundDotCom = 1;
		}

		//if all found variables are equal to one then email is valid
		if (foundFullStop == 1) {
			if (foundAtSymbol == 1) {
				if (foundDotCom == 1) {
					foundAll = 1;
				}
			}
		}
	} while (foundAll == 0); //validation to make sure all criteria is present
}

//function to display all passenger details to the console
void displayAllPassenger(struct node* top)
{
	struct node* curr;
	int passengerNum = 0;
	int i;

	curr = top;

	int choices[6];
	char *values[6] = {'\0'};

	//initalize the user choices and values array 0
	for (i = 0; i < 6; i++)
	{
		choices[i] = 0;
		values[i] = " ";
	}

	//loop through nodes till the headpointer is null to make sure you get all values
	while (curr != NULL)
	{
		//place the curr linked list values for countryTraveledFrom, travelClass, tripsPerYear and journeyTime into the array.
		choices[0] = curr->countryTraveledFrom;
		choices[1] = curr->travelClass;
		choices[2] = curr->tripsPerYear;
		choices[3] = curr->journeyTime;

		//call the method to set the curr nodes values as strings rather than numbers depending on what the user entered.
		//the values array is updated in the method and used to print out below. E.g 1 for countryTraveledFrom would become UK.
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

		//set the curr to the next pointer
		curr = curr->NEXT;
		passengerNum++;
	}
}

//function to get the user values as a string rather than a number (used again in the display selected passenger)
void getPassengerStatNames(int choice[6], char *statNames[6]) {

	//get the string value for the choice input for countryTraveledFrom
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

	//get the string value for the choice input for travelClass
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

	//get the string value for the choice input for tripsPerYear
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

	//get the string value for the choice input for journeyTime
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

//function to search a specific element in a list based on the passport num or name and return the location
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

		//if either the passort number, first name or last name is found
		if (strcmp(userInput, passPortNumConverted) == 0 || strcmp(userInput, curr->firstName) == 0 || strcmp(userInput, curr->secondName) == 0) {
			curr = curr->NEXT;
			found = 1;
			break;
		}

		//move curr to the next pointer
		curr = curr->NEXT;
	}

	//if found set the final value for the location/passenger number 
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

		//if the value is found set pos q in the array to 1 (found)
		if (userInput == curr->passportNum) {
			curr = curr->NEXT;
			locationFoundArray[1] = 1;
			break;
		}

		//move curr to the next pointer
		curr = curr->NEXT;
	}

	if (locationFoundArray[1] == 1) {
		//if found also set the pos 0 to the location of the passenger in the linked list, basically returning two values to the caller
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

	//initalize the user choices and values array 0
	for (i = 0; i < 6; i++)
	{
		choices[i] = 0;
		values[i] = " ";
	}

	//set the curr to the head pointer
	curr = top;

	//place the curr linked list values for countryTraveledFrom, travelClass, tripsPerYear and journeyTime into the array.
	choices[0] = curr->countryTraveledFrom;
	choices[1] = curr->travelClass;
	choices[2] = curr->tripsPerYear;
	choices[3] = curr->journeyTime;

	//call the method to set the curr nodes values as strings rather than numbers depending on what the user entered.
	//the values array is updated in the method and used to print out below. E.g 1 for countryTraveledFrom would become UK.
	getPassengerStatNames(choices, values);

	if (passengerLocation != 1) {
		//loop through linked list till at the position of the passed in location
		for (i = 0; i < passengerLocation - 1; i++)
		{
			curr = curr->NEXT;
		}
	}

	//print out the values of the curr node and the returned array values
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
		//loop through linked list till at the position of the passed in location
		for (i = 0; i < passengerLocation - 1; i++)
		{
			curr = curr->NEXT;
		}
	}

	//input updated values, only allows for basic inputs like email etc.
	isEmailValid(curr);

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
	struct node* curr;

	//set curr to the headpointer
	curr = *top;
	//set the headpointer to the pointer of the next node to start the list there now
	*top = curr->NEXT;

	//free the deleted node
	free(curr);
}

//function to delete a passenger at the end of the linked list
void deletePassengerAtEnd(struct node* top)
{
	struct node* curr;
	struct node* prev_curr;

	curr = top;

	//loop through to get to the end of the list
	while (curr->NEXT != NULL)
	{
		prev_curr = curr;
		curr = curr->NEXT;
	}

	//set the end pointer to null to signify the end of the list
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

	//loop through linked list till at the position of the passed in location
	for (i = 0; i < passengerLocation - 1; i++)
	{
		prev_curr = curr;
		curr = curr->NEXT;
	}

	//set the previous pointer to the next pointer and free curr e.g 1 2 3, 1 is linked to 3 and 2 is deleted
	prev_curr->NEXT = curr->NEXT;
	free(curr);
}

//function to print all passengers to file
void printPassengersToFile(struct node* top, int length)
{
	struct node* curr;

	curr = top;

	//open the file for reading
	filep = fopen("passenger.txt", "w");

	if (filep == NULL)
	{
		printf("The file could not be opened to write\n");
	}

	else
	{
		//print the length of the list at the top, which is used when reading in.
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

	//open the file for reading if exists
	filep = fopen("passenger.txt", "r");

	if (filep == NULL)
	{
		printf("The file cannot be opened\n");
	}

	else
	{
		//read in the length of the list
		fscanf(filep, "%d", &length);

		//scan in the each passenger into a new node based on the lenth of the list
		for (i = 0; i < length; i++)
		{
			//create a new node for each passenger
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

			//add to the start of the list, used only for first passenger
			if (i == 0) {
				//set newNode->NEXT to the headpointer
				newNode->NEXT = *top;
				//set the head pointer to the newNode
				*top = newNode;

				//set curr to the headpointer to start the list
				curr = *top;
			}
			//add to the end of the list
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

//function to generate the statistics based on the user input
void generateStats(struct node* top, int selection, int length) {

	struct node* curr;
	int passengerNum = 0;
	int i;
	int posCounter = 5;

	curr = top;

	//statistics option 1 (by travel class)
	if (selection == 1) {
		//initalize the arrays to zero or back to 0
		for (i = 0; i < 36; i++)
		{
			finalStatOne[i] = 0;
			countedStatsOne[i] = 0;
		}

		while (curr != NULL)
		{
			//I developed two functions which can do all 9 statistics for all four travel classes in one go by calling a function and passing in the values

			//first five stats
			//loop four times, once for every travel class. E.g 1 = Economny
			for (i = 0; i < 4; i++)
			{
				//pass in the travel class chosen, the country traveled from, the selection and position to start placing at in the array. This is explained further in the function
				countCountryStats(curr->travelClass, curr->countryTraveledFrom, i + 1, i*9);
			}

			//last four stats, again for each class and position, but for some reason I couldn't get this working with a loop.
			countDuration(curr->travelClass, curr->journeyTime, 1, 5);
			countDuration(curr->travelClass, curr->journeyTime, 2, 14);
			countDuration(curr->travelClass, curr->journeyTime, 3, 23);
			countDuration(curr->travelClass, curr->journeyTime, 4, 32);
			
			curr = curr->NEXT;
		}

		//loop through the array of all the counts to calculate the percentage
		for (i = 0; i < 36; i++)
		{
			//using a new array update the counted values by diving by the number of passengers X 100.
			finalStatOne[i] = (float)countedStatsOne[i] / length * 100;
		}

		//print the stats to the colsole with the selection for by class
		printStatsToConsole(1);
	}

	//statistics option 2 (if age is less than 1980)
	else {
		//initalize the arrays to zero or back to 0
		for (i = 0; i < 10; i++)
		{
			finalStatTwo[i] = 0;
			countedStatsTwo[i] = 0;
		}

		while (curr != NULL)
		{
			//if the current person is older than 38, then check with the following values and increment
			if (curr->dob < 1980) {

				//if they were from the UK along with being older than 38 increment pos 0 by 1.
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

		//loop through the array of all the counts to calculate the percentage
		for (i = 0; i < 9; i++)
		{
			//using a new array update the counted values by diving by the number of passengers X 100.
			finalStatTwo[i] = (float)countedStatsTwo[i] / length * 100;
		}

		//print the stats to the colsole with the selection for if age is before 1980
		printStatsToConsole(2);
	}
}

//function to count up values for the first 5 stats in option 1 (by travel class)
void countCountryStats(int travelClass, int travelFrom, int selection, int pos) {

	// the first value passed in is the travel class. e.g 1 = Economy
	// the second value passed in is the country travled from e.g 1 = UK
	//the third value passed in is the selection from 1-4, so it's called for each one to check if theres a match with it
	//the last value passed in is the position to start placing the values in at. So on the second loop it will start placing the values at 9 up to 14.

	//using the example from the previous line value 9 -14 would be incremented if the current person was from the premium economy class (selection 2)..
	//and if it matched one of the chosen countries it would be incremented by 1. So if they were from asia "countedStatsOne[pos + 2]++" would be incremented by 1 at position 11.
	//For every class it moves 9 positions, so economy is 1-5, prem economy is 9-14 and so on. Also 5-9 is used for the other duration stats.
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

//function to count up values for the last 4 stats in option 1 (by travel class)
//it counts up each class or year born and which country traveled to.
void countDuration(int travelClass, int duration, int selection, int pos) {

	//This is much the same as countCountryStats, but with one less option as theres only four durations to choose from
	//this now puts values in at positions 5-9, 14-18 and so on to put them in order for printing out
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
			//if the value is in between classes print out the global variable with all the class names hard coded in.
			if (i == 0 || i == 9 || i == 18 || i == 27) {
				printf("\n%s ===========\n", classes[pos]);
				pos++;
			}
			//print out the global variable with all the stat names hard coded in along with the calculated percentage value.
			printf("%s %12.2f%%\n", countries[counter], finalStatOne[i]);
			counter++;

			//set counter back to print out again in order
			if (counter == 9) {
				counter = 0;
			}
		}
	}
	else {
		//print out stats for born before 1980
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

	//open the file for writing
	filep = fopen("passengerStatistics.txt", "w");

	if (filep == NULL)
	{
		printf("The file could not be opened to write\n");
	}

	else
	{
		//very similar to printing to the console but with fprintf's
		//print by travel class
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

		//print before 1980's
		fprintf(filep, "\n\nBorn before 1980 ========\n");
		for (i = 0; i < 9; i++)
		{
			fprintf(filep, "%s %12.2f%%\n", countries[i], finalStatTwo[i]);
		}

		fclose(filep); //close the file
	}
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

//function to make a copy of the linked list using headPtr2 so it doesn't affect the main list when sorting
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

		//copy all the current values to a new node
		newNode->passportNum = curr->passportNum;
		strcpy(newNode->firstName, curr->firstName);
		strcpy(newNode->secondName, curr->secondName);
		newNode->dob = curr->dob;
		strcpy(newNode->emailAddress, curr->emailAddress);
		newNode->countryTraveledFrom = curr->countryTraveledFrom;
		newNode->travelClass = curr->travelClass;
		newNode->tripsPerYear = curr->tripsPerYear;
		newNode->journeyTime = curr->journeyTime;

		//adding to the start of the list (only used for the first value) 
		if (pos == 0) {
			//set newNode->NEXT to the headpointer
			newNode->NEXT = *topTwo;
			//set the head pointer to the newNode
			*topTwo = newNode;

			// set curr to the headpointer 2
			currTwo = *topTwo;
		}
		//adding to the end of the list
		else {
			//loop through till you find the last node in the new linked list
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
	//return ifDone to make sure it's only ever done once
	return ifDone;
}

// function which uses a Bubble sort to sort the linked list by dob
void sortByDOB(struct node *top)
{
	//I researched different sorts and learned how the bubble sort works and devised an algorithm to sort it based on the passengers dob
	int swapCondition, i;
	struct node *curr;

	do
	{
		swapCondition = 0;
		curr = top;

		//it works by going though the list over and over again till it's sorted making one change when it can. So if the curr dob is greater than the next one then it swaps the next node with the previous one.
		//e.g curr = 1990 and curr->NEXT = 1980 they would be swapped and become 1980, 1990
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

	//valueOne = curr value
	//valueTwo = curr->NEXT
	//first save the curr value to be able to add it to curr->NEXT (valueTwo->passportNum)
	//then set valueTwo to valueOne swapping the values
	//then set valueTwo to the saved temp value to finish the swap
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
