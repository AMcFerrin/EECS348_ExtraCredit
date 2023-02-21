#include <stdio.h>

//---------------------------------File IO/var declaration--------------------------------------------------------------------

int main()
{
	FILE *input; //Create a file instance of 'input'
	char fileName[100]; //Create the file name string

	int departments[5][5]; //Create array to hold the departments preferences
	int programmers[5][5]; //Create array to hold the programmers preferences


	int found[5] = {0,0,0,0,0}; //Create array of the found assignments
	int output[5]; //Create array of the initial output


	printf("Enter a file: "); //Print to the user what to input
	fflush(stdout); //Flush the print so that the scan goes in the proper order
	scanf("%s", fileName); //Get the file name from the user
	input = fopen(fileName, "r"); //Open the given file

//------------------------------Assigning data to arrays-----------------------------------------------------------------------------
	if (input == NULL) //Check if the file exists
	{ printf("File name not recognized; check if you typed it in correctly"); } //Print to the user so

	else //Code to run if the given files exists
	{
	    for (int i = 0; i < 5; i++) // for loop to add the department rankings to the array
			{fscanf(input, "%d %d %d %d %d ", &departments[i][0], &departments[i][1], &departments[i][2], &departments[i][3], &departments[i][4]);} // adds the current line to the department array
	    for (int i = 0; i < 5; i++)  // for loop to add the programmer rankings to the array
			{fscanf(input, "%d %d %d %d %d ", &programmers[i][0], &programmers[i][1], &programmers[i][2], &programmers[i][3], &programmers[i][4]);} // adds the current line to the programmer array

		for (int i = 0; i < 5; i++) { //loop through the arrays once
			for (int j = 0; j < 5; j ++) //loop through the arrays again
			{ departments[i][j] -= 1; programmers[i][j] -= 1; } //decrease every item in each array by 1 for easier accessibility
		}

		for(int i = 0; i < 5; i++) //Loop through 5  times
		{
			output[i] = departments[0][i]; //Set the output array as the first line of the departments
		}

//--------------------------------------Algorithm Setup----------------------------------------------------------------------------
		int first; //Variable to be used later for tracking a programmers' preference
		int second; //Another variable to be used later for tracking a programmers' preference
			for (int i = 0; i < 5; i++) //Loop 5 times
			{
				if(found[i] == 1) //Check if the current index's value has been confirmed already
				{continue;} //If so, continue to next loop

				for (int j = 0; j < 5; j++) //Nested loop for 5 times
				{
					if(found[j] == 1) //Check if the current index's value has been confirmed already
					{continue;} //If so, continue to next loop
//--------------------------------non repeats----------------------------------------------------------------------
					int l,m; //variables that will be used to iterate two loops
					for(l = 0; l < 5; l++)  //loop 5 times
					{
						for(m = 0; m < 5; m++) //loop another 5 times
						{
							if(output[l] == output[m] && l != m) //If statement to check if there is a duplicate
							break; //If so, break the loop
						}
						if(m == 5 && found[l] != 1) //If statement to make sure the found non repeated value has not already been found
						{
							found[l] = 1; //If so, check the value off, as no other departments want the programmer at that point
						}
					}

//----------------------------------------advanced duplicates----------------------------------------------------
					if(output[i] == output[j] && i != j) //Check to see if the two loops point to two separate items of the same value
					{
						if (found[i] == 0 && found[j] == 1) //If statement to figure out if 1 of the two items has already been checked off
						{
							int row = 0; //Row variable to keep track of the current row the loop is on
							while(departments[row][i] != output[i]) //While loop to loop until it finds the location of the unset value
							{ row += 1; } //Increment row on each loop
							while (found[departments[row+1][i]] == 1) //Once location is obtained, loop until it gets to an unset value
							{ row += 1; } //Increment row on each loop
							output[i] = departments[row][i]; //Set the value to the new obtained value

							continue; //Continue to next loop
						}
						else if (found[j] == 0  && found[i] == 1)
						{
							int row = 0; //Row variable to keep track of the current row the loop is on
							while(departments[row][j] != output[j]) //While loop to loop until it finds the location of the unset value
							{ row += 1; } //Increment row on each loop
							while (found[departments[row+1][j]] == 1) //Once location is obtained, loop until it gets to an unset value
							{ row += 1; } //Increment row on each loop
							output[j] = departments[row][j]; //Set the value to the new obtained value

							continue; //Continue to next loop
						}

//-------------------------------------basic duplicates--------------------------------------------------------
						for(int x = 0; x < 5; x++) //Loop to find the priority of the conflicted programmer
						{
							if(programmers[x][i] == output[i]) //Check to see if the first department's location is the current
							{ first = x; break; } //If so, set 'first' to the programmer's priority
						}
						for(int x = 0; x < 5; x++) //Loop to find the priority of the conflicted programmer
						{
							if(programmers[x][j] == output[j]) //Check to see if the second department's location is the current
							{ second = x; break; } //If so, set 'second' to the programmer's priority
						}

						if(first < second) //If the first departments' priority is higher than the second, do the following
						{
							int row = 0; //row variable to store the current row
							while(departments[row][j] != output[j]) //While loop to loop through the the departments until it gets to the desired choice
							{ row += 1; } //Increment the row each loop
							output[j] = departments[row+ 1][j]; //Set the current location on output to the obtained number
							found[i] = 1; //Mark the current location
						}
						else if(first > second) //If the second departments' priority is higher than the first, do the following
						{
							int row = 0; //row variable to store the current row
							while(departments[row][i] != i) //While loop to loop through the the departments until it gets to the desired choice
							{ row += 1; } //Increment the row each loop
							output[i] = departments[row + 1][i]; //Set the current location on output to the obtained number
							found[j] = 1; //Mark the current location
						}
					}
				}
			}

//-------------------------------------Assigning last value-------------------------------------------------------------------------
			int numList[5] = {0,1,2,3,4}; //New list of all given values
			int x; //Int to hold the location of the unset value

			for(int i = 0; i < 5; i++) //For loop to loop through 'found'
			{
				if (found[i] == 0) //Check for which value in 'found' is 0
				{ x = i; } //Set x to that location
			}

			for(int i = 0; i < 5; i++) //First for loop to loop 5 times
			{
				for(int j = 0; j < 5; j++) //Second for loop to loop another 5 times
				{
					if(output[i] == numList[j]) //If statement to find if a value in the output matches a number in numList
					{ numList[j] = 9; } //If so, set the value in numList to 9 to signify it already holds that number
				}
			}

			for(int i = 0; i < 5; i++) //For loop to loop 5 times again
			{
				if(numList[i] != 9) //Check for the one location in numList that is not set to 9
				{
					output[x] = numList[i]; //When found, set that value to the unused value
					found[x] = 1; //Signify that the value is set
				}
			}

//-------------------------------Final Output stuff-------------------------------------------------------------------------
		printf("Output: \n"); //Print to signify the data below
		for(int i = 0; i < 5; i++) //Loop through the output index
		{ printf("Department #%d will have programmer #%d\n", i+1, output[i]+1); } //Print the results of the code
	}
	return 0; //return main hooray
}
