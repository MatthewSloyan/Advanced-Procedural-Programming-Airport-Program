#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	int value;
	struct node* NEXT;
};

typedef struct
{
	int passportNum;
	char firstName[30];
	char SecondName[25];
	int dob;
	char emailAddress[50];
	int countryTraveledFrom;
	int countryTraveledTo;
	int tripsPerYear;
	int journeyTime;
}passenger;

void main()
{ 
	FILE* filep;
	int userSelection;
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
		} //outer while
	}

	else {
		printf("\n\nUser not found, please try again\n");
	}
}