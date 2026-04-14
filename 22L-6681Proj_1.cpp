#include<iostream>
#include<fstream>
#include<Windows.h>
#include<chrono>
using namespace std;
int fileInput(char gridWords[15][15], char wordsToFind[100][16]);
void wordsLengths(char wordsToFind[100][16], int lengthOfWords[], int wordCount);
void lettersCapitalization(char wordsToFind[100][16], int lengthOfWords[], int wordCount);
void colourArray(int characterCount[15][15]);
bool leftToRightSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& horizaontalForward);
bool rightToLeftSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& horizaontalBackwars);
bool topToBottomSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& verticalForward);
bool bottomToTopSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& verticalBackward);
bool upperLeftToLowerRightDiagonalSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& diagonalForward);
bool lowerRightToUpperLeftDiagonalSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& diagonalBackward);
bool upperRightToLowerLeftDiagonalSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& diagonalBackward);
bool lowerLeftToUpperRightDiagonalSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& diagonalForward);
void gridPrinting(char gridCharacters[15][15], int colourDetermination[15][15]);
void telewordFinding(char gridCharacters[15][15], int colourDetermination[15][15]);
void wordStatistics(int wordsLengths[100], int countOfwords);
void wordDistribution(int countOfHorizontalForward, int countOfHorizontalBackward, int countOfVerticalForward, int countOfVerticalBackward, int countOfDiagonalForward, int countOfDiagonalBackward);
int telewordScatter(int colourDetermination[15][15]);
void heaviestRowAndColoumn(int mostUsedRow[], int mostUsedColoumn[]);

int main()
{

	//declaration and initialization
	int i = 0, j = 0, wordCount, lengthOfWords[100];
	char gridWords[15][15], wordsToFind[100][16], userOption = 'a', wordList[100][16];
	int characterCount[15][15], horizontalForward = 0, horizontalBackward = 0, verticalForward = 0, verticalBackward = 0, diagonalForward = 0, diagonalBackward = 0;
	int heaviestRow[15] = { 0 }, heaviestColoumn[15] = { 0 };

	// This function will take input from the file and return the total number of words to find
	wordCount = fileInput(gridWords, wordsToFind);

	//This function will remove the commas and full stop and store the length of easch word in an integer array
	wordsLengths(wordsToFind, lengthOfWords, wordCount);

	//This function will capitalize all the alphabets
	lettersCapitalization(wordsToFind, lengthOfWords, wordCount);

	//This function will initialize the integer array, made for determining the colours, with 0
	colourArray(characterCount);

	cout << endl;
	while (userOption != 'S' && userOption != 'T' && userOption != 'X')   //the loop will continue taking the input until the user enters S, T or X
	{
		cout << "\n1. Press S to solve the puzzle at once.\n2. Press T to solve the puzzle step by step.\n3. Press X to print puzzle statistics." << endl;
		cin >> userOption;
		cout << endl;
		if (userOption == 'S' || userOption == 'T' || userOption == 'X')
			break;
		cout << "\nInvalid Input.Enter your choice again";
	}

	auto t1 = chrono::high_resolution_clock::now();    //measuring the starting time
	for (int k = 0; k < wordCount; k++)       //this loop will search each word in all the searching functions.If the word is found in one function, the loop will not check other functions for the same word.
	{
		if (leftToRightSearch(gridWords, wordsToFind[k], userOption, characterCount, heaviestRow, heaviestColoumn, horizontalForward) == true)
			continue;
		else if (rightToLeftSearch(gridWords, wordsToFind[k], userOption, characterCount, heaviestRow, heaviestColoumn, horizontalBackward) == true)
			continue;
		else if (topToBottomSearch(gridWords, wordsToFind[k], userOption, characterCount, heaviestRow, heaviestColoumn, verticalForward) == true)
			continue;
		else if (bottomToTopSearch(gridWords, wordsToFind[k], userOption, characterCount, heaviestRow, heaviestColoumn, verticalBackward) == true)
			continue;
		else if (upperLeftToLowerRightDiagonalSearch(gridWords, wordsToFind[k], userOption, characterCount, heaviestRow, heaviestColoumn, diagonalForward) == true)
			continue;
		else if (lowerRightToUpperLeftDiagonalSearch(gridWords, wordsToFind[k], userOption, characterCount, heaviestRow, heaviestColoumn, diagonalBackward) == true)
			continue;
		else if (upperRightToLowerLeftDiagonalSearch(gridWords, wordsToFind[k], userOption, characterCount, heaviestRow, heaviestColoumn, diagonalBackward) == true)
			continue;
		else if (lowerLeftToUpperRightDiagonalSearch(gridWords, wordsToFind[k], userOption, characterCount, heaviestRow, heaviestColoumn, diagonalForward) == true)
			continue;
	}
	auto t2 = chrono::high_resolution_clock::now();   //measuring the ending time
	auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();


	if (userOption == 'S')
	{
		gridPrinting(gridWords, characterCount);
		;
		cout << endl << "Found Words" << endl;

		for (i = 0; i < wordCount; i++)
		{
			if (i == wordCount - 1)
			{
				cout << wordsToFind[i] << ".";
			}
			else
			cout << wordsToFind[i] << ", ";
		}

		cout << endl;

		telewordFinding(gridWords, characterCount);
		cout << endl;
	}
	else if (userOption == 'T')
	{
		cout << endl << "Found Words" << endl;
		for (i = 0; i < wordCount; i++)
		{

			if (i == wordCount - 1)
			{
				cout << wordsToFind[i] << ".";
			}
			else
			cout << wordsToFind[i] << ", ";
		}

		cout << endl;

		telewordFinding(gridWords, characterCount);
		cout << endl;
	}
	else if (userOption == 'X')
	{
		gridPrinting(gridWords, characterCount);

		cout << endl<<"Found Words"<<endl;

		for (i = 0; i < wordCount; i++)
		{

			if (i == wordCount - 1)
			{
				cout << wordsToFind[i] << ".";
			}
			else
			cout << wordsToFind[i] << ", ";
		}
		cout << endl;
		telewordFinding(gridWords, characterCount);
		cout << endl << endl << "TIME";
		cout << endl << "Time to solve : " << duration << " microsecond";
		cout << endl << "WORD STATISTICS";
		wordStatistics(lengthOfWords, wordCount);
		cout << endl << "WORD DISTRIBUTION";
		wordDistribution(horizontalForward, horizontalBackward, verticalForward, verticalBackward, diagonalForward, diagonalBackward);
		cout << endl << "TELEWORD SCATTER";
		cout << endl << "Teleword Scatter : " << telewordScatter(characterCount);
		cout << endl << "HEAVIEST ROW, HEAVIEST COLOUMN";
		heaviestRowAndColoumn(heaviestRow, heaviestColoumn);
	}

	return 0;
}


//This function will input the word grid and words to find from the file, count the number of words to find and also print the grid and list of words
int fileInput(char gridWords[15][15], char wordsToFind[100][16])
{
	ifstream telewordFile;
	int i = 0, j = 0, wordCount = 0;
	telewordFile.open("teleword_1.txt");
	if (telewordFile.is_open())
	{
		for (i = 0; i < 15; i++)
		{
			for (j = 0; j < 15; j++)
			{
				telewordFile >> gridWords[i][j];
			}
		}




		//This chunk of code will receive all the words to find until the last word with a full stop at the end is found and count the total number of words

		for (i = 0; i < 100; i++)
		{
			bool lastWordFound = false;
			telewordFile >> wordsToFind[i];
			for (j = 0; j < 15; j++)
			{
				if (wordsToFind[i][j] == '.')
					lastWordFound = true;
			}
			if (lastWordFound == true)
				break;
			else
				wordCount++;
		}
		wordCount++;
	}
	telewordFile.close();

	//printing of the grid
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
			cout << gridWords[i][j] << " ";
		cout << endl;
	}

	//printing the words to find
	cout << endl << "Words to find" << endl;
	for (i = 0; i < wordCount; i++)
	{
		cout << wordsToFind[i] << " ";
	}
	return wordCount;
}




//This chunk of code will remove all the commas and full stop at the end of the words and will store the length of each word in an integer array(lengthOfWords)
void wordsLengths(char wordsToFind[100][16], int lengthOfWords[], int wordCount)
{
	int wordLength = 0, i = 0, j = 0;
	for (i = 0; i < wordCount; i++)
	{
		wordLength = 0;
		for (j = 0; j < 15; j++)
		{
			if (wordsToFind[i][j] == ',' || wordsToFind[i][j] == '.')
			{
				wordsToFind[i][j] = '\0';
				break;
			}
			wordLength++;
		}
		lengthOfWords[i] = wordLength;
	}
}




//This chunk of code will capitalize all the letters
void lettersCapitalization(char wordsToFind[100][16], int lengthOfWords[], int wordCount)
{
	int i = 0, j = 0;
	for (i = 0; i < wordCount; i++)
	{
		for (j = 1; j < lengthOfWords[i]; j++)
		{
			wordsToFind[i][j] = wordsToFind[i][j] - 32;
		}
	}
}



//this chunk will initialize the characterCount integer array, integer array for colours, with 0
void colourArray(int characterCount[15][15])
{
	int i = 0, j = 0;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			characterCount[i][j] = 0;
		}
	}
}




//This chunk of code will search the words in the grid from left to right
bool leftToRightSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& horizontalForward)
{
	//startingPointRow, startingPointColoumn, endingPointRow and endingPointColoumn are for updating the values in integer arrays for heaviest row(heaviestRow), heaviest coloumn(heaviestColoumn), and colouring(characterCount) 
	int i = 0, j = 0, startingPointRow = 0, startingPointColoumn = 0, endingPointRow = 0, endingPointColoumn = 0;
	bool wordFoundFromLeftToRight = false;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			int l = 0;  //alphabet index for the word to find
			if (wordsToFind[l] == gridWords[i][j])
			{
				startingPointRow = endingPointRow = i;  //for horizontal words stating point row and ending point row will be the same
				startingPointColoumn = j;  //starting point coloumn will be the one with the first alphabet of the word to find
				int temp_j = j;
				while (j < 15 && wordsToFind[l] == gridWords[i][j])  //the loop will continue until the word matches with the grid
				{
					l++;
					j++;
				}
				if (wordsToFind[l] == '\0')   //if the next character of the word is null character then we have found our word
				{

					wordFoundFromLeftToRight = true;
					endingPointColoumn = j - 1;
					horizontalForward++;   //for measuring the number of horizontal words in forward direction
					heaviestRow[i]++;
				}
				else
				{
					j = temp_j;
					temp_j = 0;
					startingPointRow = endingPointRow = startingPointColoumn = 0;
				}
			}
			if (wordFoundFromLeftToRight == true)
				break;
		}
		if (wordFoundFromLeftToRight == true)
			break;
	}
	if (wordFoundFromLeftToRight == true)
	{
		while (startingPointColoumn <= endingPointColoumn)   //updating the values of the integer arrays for colouring(characterCount) and for heaviest coloumn(heavuestColoumn)
		{
			characterCount[startingPointRow][startingPointColoumn] = characterCount[startingPointRow][startingPointColoumn] + 1;
			heaviestColoumn[startingPointColoumn]++;
			startingPointColoumn++;
		}
	}
	if (userOption == 'T' && wordFoundFromLeftToRight == true)   //if the user has selected the second option it will pause after the first word is found
	{
		system("pause");
		gridPrinting(gridWords, characterCount);
		cout << endl << "The word found : " << wordsToFind << endl;
	}
	return wordFoundFromLeftToRight;
}




//This chunk of code will search the words in the grid from right to left
bool rightToLeftSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& horizontalBackward)
{
	//startingPointRow, startingPointColoumn, endingPointRow and endingPointColoumn are for updating the values in integer arrays for heaviest row(heaviestRow), heaviest coloumn(heaviestColoumn), and colouring(characterCount)
	int i = 0, j = 0, startingPointRow = 0, startingPointColoumn = 0, endingPointRow = 0, endingPointColoumn = 0;
	bool wordFoundFromRightToLeft = false;
	startingPointRow = startingPointColoumn = endingPointRow = endingPointColoumn = 0;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			int l = 0;    //alphabet index for the word to find
			if (wordsToFind[l] == gridWords[i][j])
			{
				startingPointRow = endingPointRow = i;   //for horizontal words stating point row and ending point row will be the same
				startingPointColoumn = j;    //starting point coloumn will be the one with the first alphabet of the word to find
				int temp_j = j;
				while (l < 15 && j >= 0 && wordsToFind[l] == gridWords[i][j])    //the loop will continue until the word matches with the grid
				{
					l++;
					j--;
				}
				if (wordsToFind[l] == '\0')     //if the next character of the word is null character then we have found our word
				{

					wordFoundFromRightToLeft = true;
					endingPointColoumn = j + 1;
					horizontalBackward++;     //for measuring the number of horizontal words in backward direction
					heaviestRow[i]++;
				}
				else
				{
					j = temp_j;
					temp_j = 0;
					startingPointRow = endingPointRow = startingPointColoumn = 0;
				}
			}
			if (wordFoundFromRightToLeft == true)
				break;

		}
		if (wordFoundFromRightToLeft == true)
			break;
	}
	if (wordFoundFromRightToLeft == true)
	{
		while (startingPointColoumn >= endingPointColoumn)    //updating the values of the integer arrays for colouring(characterCount) and for heaviest coloumn(heavuestColoumn)
		{
			characterCount[startingPointRow][startingPointColoumn] = characterCount[startingPointRow][startingPointColoumn] + 1;
			heaviestColoumn[startingPointColoumn]++;
			startingPointColoumn--;
		}
	}
	if (userOption == 'T' && wordFoundFromRightToLeft == true)     //if the user has selected the second option it will pause after the first word is found
	{
		system("pause");
		gridPrinting(gridWords, characterCount);
		cout << endl << "The word found : " << wordsToFind << endl;
	}
	return wordFoundFromRightToLeft;
}




//This chunk of code will search the words in the grid from top to bottom
bool topToBottomSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& verticalForward)
{
	//startingPointRow, startingPointColoumn, endingPointRow and endingPointColoumn are for updating the values in integer arrays for heaviest row(heaviestRow), heaviest coloumn(heaviestColoumn), and colouring(characterCount)
	int i = 0, j = 0, startingPointRow = 0, startingPointColoumn = 0, endingPointRow = 0, endingPointColoumn = 0;
	bool wordFoundFromTopToBottom = false;
	startingPointRow = startingPointColoumn = endingPointRow = endingPointColoumn = 0;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			int l = 0;    //alphabet index for the word to find
			if (wordsToFind[l] == gridWords[i][j])
			{
				startingPointColoumn = endingPointColoumn = j;   //for vertical words stating point coloumn and ending point coloumn will be the same
				startingPointRow = i;     //starting point row will be the one with the first alphabet of the word to find
				int temp_i = i;
				while (l < 15 && i < 15 && wordsToFind[l] == gridWords[i][j])     //the loop will continue until the word matches with the grid
				{
					l++;
					i++;
				}
				if (wordsToFind[l] == '\0')    //if the next character of the word is null character then we have found our word
				{

					wordFoundFromTopToBottom = true;
					endingPointRow = i - 1;
					verticalForward++;      //for measuring the number of vertical words in forward direction
					heaviestColoumn[j]++;
				}
				else
				{
					i = temp_i;
					temp_i = 0;
					startingPointColoumn = endingPointColoumn = startingPointRow = 0;
				}
			}
			if (wordFoundFromTopToBottom == true)
				break;
		}
		if (wordFoundFromTopToBottom == true)
			break;
	}
	if (wordFoundFromTopToBottom == true)
	{
		while (startingPointRow <= endingPointRow)      //updating the values of the integer arrays for colouring(characterCount) and for heaviest coloumn(heavuestColoumn)
		{
			characterCount[startingPointRow][startingPointColoumn] = characterCount[startingPointRow][startingPointColoumn] + 1;
			heaviestRow[startingPointRow]++;
			startingPointRow++;
		}
	}
	if (userOption == 'T' && wordFoundFromTopToBottom == true)     //if the user has selected the second option it will pause after the first word is found
	{
		system("pause");
		gridPrinting(gridWords, characterCount);
		cout << endl << "The word found : " << wordsToFind << endl;
	}
	return wordFoundFromTopToBottom;
}





//This chunk of code will search the words in the grid from bottom to top
bool bottomToTopSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& verticalBackward)
{
	//startingPointRow, startingPointColoumn, endingPointRow and endingPointColoumn are for updating the values in integer arrays for heaviest row(heaviestRow), heaviest coloumn(heaviestColoumn), and colouring(characterCount)
	int i = 0, j = 0, startingPointRow = 0, startingPointColoumn = 0, endingPointRow = 0, endingPointColoumn = 0;
	bool wordFoundFromBottomToTop = false;
	startingPointRow = startingPointColoumn = endingPointRow = endingPointColoumn = 0;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			int l = 0;    //alphabet index for the word to find
			if (wordsToFind[l] == gridWords[i][j])
			{
				startingPointColoumn = endingPointColoumn = j;   //for vertical words stating point coloumn and ending point coloumn will be the same
				startingPointRow = i;     //starting point row will be the one with the first alphabet of the word to find
				int temp_i = i;
				while (l < 15 && i >= 0 && wordsToFind[l] == gridWords[i][j])    //the loop will continue until the word matches with the grid
				{
					l++;
					i--;
				}
				if (wordsToFind[l] == '\0')   //if the next character of the word is null character then we have found our word
				{

					wordFoundFromBottomToTop = true;
					endingPointRow = i + 1;
					verticalBackward++;     //for measuring the number of vertical words in backward direction
					heaviestColoumn[j]++;
				}
				else
				{
					i = temp_i;
					temp_i = 0;
					startingPointColoumn = endingPointColoumn = startingPointRow = 0;
				}
			}
			if (wordFoundFromBottomToTop == true)
				break;

		}
		if (wordFoundFromBottomToTop == true)
			break;
	}
	if (wordFoundFromBottomToTop == true)
	{
		while (startingPointRow >= endingPointRow)      //updating the values of the integer arrays for colouring(characterCount) and for heaviest coloumn(heavuestColoumn)
		{
			characterCount[startingPointRow][startingPointColoumn] = characterCount[startingPointRow][startingPointColoumn] + 1;
			heaviestRow[startingPointRow]++;
			startingPointRow--;
		}
	}
	if (userOption == 'T' && wordFoundFromBottomToTop == true)     //if the user has selected the second option it will pause after the first word is found
	{
		system("pause");
		gridPrinting(gridWords, characterCount);
		cout << endl << "The word found : " << wordsToFind << endl;
	}
	return wordFoundFromBottomToTop;
}






//This chunk of code will search the words in the grid in upper left to lower right diagonal
bool upperLeftToLowerRightDiagonalSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& diagonalForward)
{
	//startingPointRow, startingPointColoumn, endingPointRow and endingPointColoumn are for updating the values in integer arrays for heaviest row(heaviestRow), heaviest coloumn(heaviestColoumn), and colouring(characterCount)
	int i = 0, j = 0, startingPointRow = 0, startingPointColoumn = 0, endingPointRow = 0, endingPointColoumn = 0;
	bool wordFoundInUpperLeftToLowerRightDiagonal = false;
	startingPointRow = startingPointColoumn = endingPointRow = endingPointColoumn = 0;
	for (i = 0; i < 15; i++)

	{
		for (j = 0; j < 15; j++)
		{
			int l = 0;    //alphabet index for the word to find
			if (wordsToFind[l] == gridWords[i][j])
			{
				startingPointRow = i;    //starting point row will be the one with the first alphabet of the word to find
				startingPointColoumn = j;    //starting point coloumn will be the one with the first alphabet of the word to find
				int temp_j = j;
				int temp_i = i;
				while (i < 15 && j < 15 && l < 15 && wordsToFind[l] == gridWords[i][j])     //the loop will continue until the word matches with the grid
				{
					l++;
					j++;
					i++;
				}
				if (wordsToFind[l] == '\0')    //if the next character of the word is null character then we have found our word
				{

					wordFoundInUpperLeftToLowerRightDiagonal = true;
					endingPointRow = i - 1;   //ending point for the row
					endingPointColoumn = j - 1;  //ending point for the coloumn
					diagonalForward++;      //for measuring the number of diagonal words in forward direction
				}
				else
				{
					j = temp_j;
					i = temp_i;
					temp_i = 0;
					temp_j = 0;
					startingPointRow = startingPointColoumn = 0;
				}
			}
			if (wordFoundInUpperLeftToLowerRightDiagonal == true)
				break;
		}
		if (wordFoundInUpperLeftToLowerRightDiagonal == true)
			break;
	}
	if (wordFoundInUpperLeftToLowerRightDiagonal == true)
	{
		while (startingPointRow <= endingPointRow && startingPointColoumn <= endingPointColoumn)      //updating the values of the integer arrays for colouring(characterCount) and for heaviest coloumn(heavuestColoumn)
		{
			characterCount[startingPointRow][startingPointColoumn] = characterCount[startingPointRow][startingPointColoumn] + 1;
			heaviestRow[startingPointRow]++;
			heaviestColoumn[startingPointColoumn]++;
			startingPointRow++;
			startingPointColoumn++;
		}
	}
	if (userOption == 'T' && wordFoundInUpperLeftToLowerRightDiagonal == true)     //if the user has selected the second option it will pause after the first word is found
	{
		system("pause");
		gridPrinting(gridWords, characterCount);
		cout << endl << "The word found : " << wordsToFind << endl;
	}
	return wordFoundInUpperLeftToLowerRightDiagonal;
}



//This chunk of code will search the words in the grid in lower right to upper left diagonal
bool lowerRightToUpperLeftDiagonalSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& diagonalBackward)
{
	//startingPointRow, startingPointColoumn, endingPointRow and endingPointColoumn are for updating the values in integer arrays for heaviest row(heaviestRow), heaviest coloumn(heaviestColoumn), and colouring(characterCount)
	int i = 0, j = 0, startingPointRow = 0, startingPointColoumn = 0, endingPointRow = 0, endingPointColoumn = 0;
	bool wordFoundInLowerRightToUpperLeftDiagonal = false;
	startingPointRow = startingPointColoumn = endingPointRow = endingPointColoumn = 0;
	for (i = 0; i < 15; i++)

	{
		for (j = 0; j < 15; j++)
		{
			int l = 0;    //alphabet index for the word to find
			if (wordsToFind[l] == gridWords[i][j])
			{
				startingPointRow = i;   //starting point row will be the one with the first alphabet of the word to find
				startingPointColoumn = j;   //starting point coloumn will be the one with the first alphabet of the word to find
				int temp_j = j;
				int temp_i = i;
				while (l < 15 && j >= 0 && i >= 0 && wordsToFind[l] == gridWords[i][j])    //the loop will continue until the word matches with the grid
				{
					l++;
					j--;
					i--;
				}
				if (wordsToFind[l] == '\0')   //if the next character of the word is null character then we have found our word
				{

					wordFoundInLowerRightToUpperLeftDiagonal = true;
					endingPointRow = i + 1;   //ending point for the row
					endingPointColoumn = j + 1;   //ending point for the coloumn
					diagonalBackward++;   //for measuring the number of diagonal words in backward direction
				}
				else
				{
					j = temp_j;
					i = temp_i;
					temp_i = 0;
					temp_j = 0;
					startingPointRow = startingPointColoumn = 0;
				}
			}
			if (wordFoundInLowerRightToUpperLeftDiagonal == true)
				break;
		}
		if (wordFoundInLowerRightToUpperLeftDiagonal == true)
			break;
	}
	if (wordFoundInLowerRightToUpperLeftDiagonal == true)
	{
		while (startingPointRow >= endingPointRow && startingPointColoumn >= endingPointColoumn)     //updating the values of the integer arrays for colouring(characterCount) and for heaviest coloumn(heavuestColoumn)
		{
			characterCount[startingPointRow][startingPointColoumn] = characterCount[startingPointRow][startingPointColoumn] + 1;
			heaviestRow[startingPointRow]++;
			heaviestColoumn[startingPointColoumn]++;
			startingPointRow--;
			startingPointColoumn--;
		}
	}
	if (userOption == 'T' && wordFoundInLowerRightToUpperLeftDiagonal == true)     //if the user has selected the second option it will pause after the first word is found
	{
		system("pause");
		gridPrinting(gridWords, characterCount);
		cout << endl << "The word found : " << wordsToFind << endl;
	}
	return wordFoundInLowerRightToUpperLeftDiagonal;
}



//	//This chunk of code will search the words in the grid in upper right to lower left diagonal
bool upperRightToLowerLeftDiagonalSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& diagonalBackward)
{

	//startingPointRow, startingPointColoumn, endingPointRow and endingPointColoumn are for updating the values in integer arrays for heaviest row(heaviestRow), heaviest coloumn(heaviestColoumn), and colouring(characterCount)
	bool wordFoundInUpperRightToLowerLeftDiagonal = false;
	int i = 0, j = 0, startingPointRow = 0, startingPointColoumn = 0, endingPointRow = 0, endingPointColoumn = 0;
	startingPointRow = startingPointColoumn = endingPointRow = endingPointColoumn = 0;
	for (i = 0; i < 15; i++)

	{
		for (j = 0; j < 15; j++)
		{
			int l = 0;    //alphabet index for the word to find
			if (wordsToFind[l] == gridWords[i][j])
			{
				startingPointRow = i;   //starting point row will be the one with the first alphabet of the word to find
				startingPointColoumn = j;   //starting point coloumn will be the one with the first alphabet of the word to find
				int temp_j = j;
				int temp_i = i;
				while (l < 15 && j >= 0 && i < 15 && wordsToFind[l] == gridWords[i][j])    //the loop will continue until the word matches with the grid
				{
					l++;
					j--;
					i++;
				}
				if (wordsToFind[l] == '\0')    //if the next character of the word is null character then we have found our word
				{

					wordFoundInUpperRightToLowerLeftDiagonal = true;
					endingPointRow = i - 1;   //ending point for the row
					endingPointColoumn = j + 1;   //ending point for the coloumn
					diagonalBackward++;    //for measuring the number of diagonal words in backward direction
				}
				else
				{
					j = temp_j;
					i = temp_i;
					temp_i = 0;
					temp_j = 0;
					startingPointRow = startingPointColoumn = 0;
				}
			}
			if (wordFoundInUpperRightToLowerLeftDiagonal == true)
				break;
		}
		if (wordFoundInUpperRightToLowerLeftDiagonal == true)
			break;
	}
	if (wordFoundInUpperRightToLowerLeftDiagonal == true)
	{
		while (startingPointRow <= endingPointRow && startingPointColoumn >= endingPointColoumn)    //updating the values of the integer arrays for colouring(characterCount) and for heaviest coloumn(heavuestColoumn)
		{
			characterCount[startingPointRow][startingPointColoumn] = characterCount[startingPointRow][startingPointColoumn] + 1;
			heaviestRow[startingPointRow]++;
			heaviestColoumn[startingPointColoumn]++;
			startingPointRow++;
			startingPointColoumn--;
		}
	}
	if (userOption == 'T' && wordFoundInUpperRightToLowerLeftDiagonal == true)    //if the user has selected the second option it will pause after the first word is found
	{
		system("pause");
		gridPrinting(gridWords, characterCount);
		cout << endl << "The word found : " << wordsToFind << endl;
	}
	return wordFoundInUpperRightToLowerLeftDiagonal;

}




//This chunk of code will search the words in the grid in lower left to upper right diagonal
bool lowerLeftToUpperRightDiagonalSearch(char gridWords[15][15], char wordsToFind[16], char userOption, int characterCount[15][15], int heaviestRow[], int heaviestColoumn[], int& diagonalForward)
{
	//startingPointRow, startingPointColoumn, endingPointRow and endingPointColoumn are for updating the values in integer arrays for heaviest row(heaviestRow), heaviest coloumn(heaviestColoumn), and colouring(characterCount)
	int i = 0, j = 0, startingPointRow = 0, startingPointColoumn = 0, endingPointRow = 0, endingPointColoumn = 0;
	bool wordFoundLowerLeftToUpperRightDiagonal = false;
	startingPointRow = startingPointColoumn = endingPointRow = endingPointColoumn = 0;
	for (i = 0; i < 15; i++)

	{
		for (j = 0; j < 15; j++)
		{
			int l = 0;    //alphabet index for the word to find
			if (wordsToFind[l] == gridWords[i][j])
			{
				startingPointRow = i;   //starting point row will be the one with the first alphabet of the word to find
				startingPointColoumn = j;    //starting point coloumn will be the one with the first alphabet of the word to find
				int temp_j = j;
				int temp_i = i;
				while (l < 15 && j < 15 && i >= 0 && wordsToFind[l] == gridWords[i][j])    //the loop will continue until the word matches with the grid
				{
					l++;
					j++;
					i--;
				}
				if (wordsToFind[l] == '\0')    //if the next character of the word is null character then we have found our word
				{

					wordFoundLowerLeftToUpperRightDiagonal = true;
					endingPointRow = i + 1;   //ending point for the row
					endingPointColoumn = j - 1;   //ending point for the coloumn
					diagonalForward++;    //for measuring the number of diagonal words in forward direction
				}
				else
				{
					j = temp_j;
					i = temp_i;
					temp_i = 0;
					temp_j = 0;
					startingPointRow = startingPointColoumn = 0;
				}
			}
			if (wordFoundLowerLeftToUpperRightDiagonal == true)
				break;
		}
		if (wordFoundLowerLeftToUpperRightDiagonal == true)
			break;
	}
	if (wordFoundLowerLeftToUpperRightDiagonal == true)
	{
		while (startingPointRow >= endingPointRow && startingPointColoumn <= endingPointColoumn)     //updating the values of the integer arrays for colouring(characterCount) and for heaviest coloumn(heavuestColoumn)
		{
			characterCount[startingPointRow][startingPointColoumn] = characterCount[startingPointRow][startingPointColoumn] + 1;
			heaviestRow[startingPointRow]++;
			heaviestColoumn[startingPointColoumn]++;
			startingPointRow--;
			startingPointColoumn++;
		}
	}
	if (userOption == 'T' && wordFoundLowerLeftToUpperRightDiagonal == true)    //if the user has selected the second option it will pause after the first word is found
	{
		system("pause");
		gridPrinting(gridWords, characterCount);
		cout << endl << "The word found : " << wordsToFind << endl;
	}
	return wordFoundLowerLeftToUpperRightDiagonal;
}


//This function will print the coloured characters in the grid
void gridPrinting(char gridCharacters[15][15], int colourDetermination[15][15])
{
	system("CLS");
	HANDLE character = GetStdHandle(STD_OUTPUT_HANDLE);
	int i = 0, j = 0;

	//these nested loops will print each character of the grid according to the value stored in the corresponding index of integer array
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (colourDetermination[i][j] == 0)
			{
				SetConsoleTextAttribute(character, 15);   //for white colour
				cout << gridCharacters[i][j] << " ";
			}
			else if (colourDetermination[i][j] == 1)
			{
				SetConsoleTextAttribute(character, 6);    //for yellow colour
				cout << gridCharacters[i][j] << " ";
			}
			else if (colourDetermination[i][j] == 2)
			{
				SetConsoleTextAttribute(character, 1);   //for blue colour
				cout << gridCharacters[i][j] << " ";
			}
			else
			{
				SetConsoleTextAttribute(character, 4);  //for red colour
				cout << gridCharacters[i][j] << " ";
			}


		}
		cout << endl;
	}
	SetConsoleTextAttribute(character, 15);

}



//this function will find the teleword
void telewordFinding(char gridCharacters[15][15], int colourDetermination[15][15])
{
	char teleword[15];
	int i = 0, j = 0, index = 0;

	//these nested loops will store all the characters of the grid with the value zero in the corresponding integer array
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (colourDetermination[i][j] == 0)
			{
				teleword[index] = gridCharacters[i][j];
				index++;
			}
		}
	}
	cout << endl << "Teleword : ";
	for (i = 0; i < index; i++)
		cout << teleword[i];
}



//this function will find the longest word length,shortest word length and the average word length
void wordStatistics(int wordsLengths[100], int countOfWords)
{
	int max = wordsLengths[0], min = wordsLengths[0], sum = 0;
	for (int i = 1; i < countOfWords; i++)  //this loop will find the maximum length and minimum length using the integer array of lengths
	{
		if (max <= wordsLengths[i])
		{
			max = wordsLengths[i];
		}
		if (min >= wordsLengths[i])
		{
			min = wordsLengths[i];
		}
	}
	for (int i = 0; i < countOfWords; i++)
	{
		sum = sum + wordsLengths[i];   //this will find the sum of all the lengths stored in the integer arry of lengths
	}
	cout << endl << "The Longest word length : " << max;
	cout << endl << "The Shortest word length : " << min;
	cout << endl << "The Average word length : " << sum / countOfWords;
}



//this function will find the number of horizontal,vertical and diagonal words
void wordDistribution(int countOfHorizontalForward, int countOfHorizontalBackward, int countOfVerticalForward, int countOfVerticalBackward, int countOfDiagonalForward, int countOfDiagonalBackward)
{
	cout << endl << "Horizontal : " << countOfHorizontalForward + countOfHorizontalBackward << " (" << countOfHorizontalForward << " , " << countOfHorizontalBackward << ")";
	cout << endl << "Vertical : " << countOfVerticalForward + countOfVerticalBackward << " (" << countOfVerticalForward << " , " << countOfVerticalBackward << ")";
	cout << endl << "Diagonal : " << countOfDiagonalForward + countOfDiagonalBackward << " (" << countOfDiagonalForward << " , " << countOfDiagonalBackward << ")";
}


//this function will determine the teleword scatter ( i.e. the number of rows touches by teleword)
int telewordScatter(int colourDetermination[15][15])
{
	int i = 0, j = 0, temp_i = -1, countOfRows = 0;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (colourDetermination[i][j] == 0)
			{
				countOfRows++;
				if (temp_i == i)  //this will see if two or more words are found in a single row.In this case this will decrement the value of countOfRows, bringing it to the original value
					countOfRows--;
				temp_i = i;  //storing the value of row for further comparison
			}
		}
	}
	return countOfRows;
}


//this chunk will determine the heaviest row and heaviest coloumn
void heaviestRowAndColoumn(int mostUsedRow[], int mostUsedColoumn[])
{
	int heaviestRow = mostUsedRow[0], heaviestColoumn = mostUsedColoumn[0];
	int i = 0, max_row = 0, max_coloumn = 0;
	for (i = 1; i < 15; i++)  //this loop will compare all the values stored in the integer array for heaviest row and find the maximum one
	{
		if (heaviestRow < mostUsedRow[i])
		{
			max_row = i;
			heaviestRow = mostUsedRow[i];
		}
	}
	for (i = 1; i < 15; i++)    //this loop will compare all the values stored in the integer array for heaviest coloumn and find the maximum one
	{
		if (heaviestColoumn < mostUsedColoumn[i])
		{
			max_coloumn = i;
			heaviestColoumn = mostUsedColoumn[i];
		}
	}
	cout << endl << "Heaviest Row : " << max_row;
	cout << endl << "Heaviest Coloumn : " << max_coloumn;
}