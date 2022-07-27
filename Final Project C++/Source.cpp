#include <iostream>
#include <string>
#include <Windows.h>
#include <wingdi.h>
#include <algorithm>
#include <cstdlib>
using namespace std;

void gotoxy(int column, int line) //function for x and y coordinates 
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int linear_search(string* a, int size, string target) //searches for dynamic user choice of word
{
	for (int i = 0; i < size; i++)
	{
		if (a[i] == target)
			return i;
	}
	return -1;
}

struct scorekeep //struct to keep track of score
{
	int cscore, tscore; //current score, total score
};

scorekeep gscore; //global struct to count scores

void instructions() //instruction function
{
	system("cls");
	while (1) //loop so that user can go back to main menu
	{
		cout << "~~~~~~~~~~INSTRUCTIONS~~~~~~~~~~\n";
		cout << endl;
		cout << "The rules are simple:\n";
		cout << "Scattered on the screen are halves of words.\n";
		cout << "Correctly type the word to have it reveal itself into the list of correct words.\n";
		system("pause");
		break;
	}
}

int menu()
{
	system("cls");
	system("color 07");

	int choice; //choice variable
	const int row = 10, col = 30; //row column numbers
	int screen[row][col] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	for (int row = 0; row < 10; row++) // row column loop
	{
		for (int col = 0; col < 30; col++)
		{
			if (screen[row][col] == 1)
			{
				cout << char(219);
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}

	gotoxy(2, 1);
	cout << "Word Puzzle: Beach Edition" << endl; // menu title 
	gotoxy(2, 2);
	cout << "1.Start Game" << endl; // starts game 
	gotoxy(2, 3);
	cout << "2.Load Stage" << endl; // loads stages/levels of game
	gotoxy(2, 4);
	cout << "3.Instructions" << endl;
	gotoxy(2, 5);
	cout << "4.Exit" << endl; //closes game
	gotoxy(0, 12);
	cout << "Select a Menu option: " << endl;
	cin >> choice;

	return choice;
}

void levelone()
{
	system("color 3B"); // changes color

	string word; //string variable for the word user enters
	int choice, length, xyIndex = 0, tempcount = 0, score = 0, wordindex; //integer variables
	const int WORDCOUNT = 10; //variable for word halves count
	int x_end[] = { 0, 2, 0, 2, 0, 4, 0, 4, 0, 2 }, y_end[] = { 4, 4, 6, 6, 3, 3, 2, 2, 5, 5 }; //end coordinates for x and y values for the halves
	gscore.cscore = 0; //global struct assigned to struct for current score and total score
	gscore.tscore = 0;

	int x[WORDCOUNT] = { 100,52,4,112,30,40,76,88,20,64 }; //x value associated with
	int y[WORDCOUNT] = { 20,18,17,16,19,19,16,18,18,20 }; //<--- y value

	string words[WORDCOUNT] = { "wa","ves","sa","nd","surf","board","sand","castle","oc","ean" }; //array for word halves to move
	string fullword[] = { "waves", "sand", "surfboard", "sandcastle", "ocean" }; //fullword user will enter

	system("cls");
	system("color 3B");

	gotoxy(0, 0);
	cout << "CORRECT WORDS\n"; //word bank location
	cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219)
		<< char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << ">";

	for (int i = 0; i < WORDCOUNT; i++) // loop for definining and locating word splits
	{
		word = words[i];
		length = word.length();
		gotoxy(x[xyIndex], y[xyIndex]);
		cout << words[i];
		xyIndex++;
	}

	while (1)
	{
		gotoxy(14, 1);
		cin >> word; //user enters word
		transform(word.begin(), word.end(), word.begin(), ::tolower); //makes it okay for upper and lowercase

		if (word == "waves" || word == "sand" || word == "surfboard" || word == "sandcastle" || word == "ocean")
		{
			wordindex = linear_search(fullword, 5, word); //dynamic for word specific to word halves to travel

			for (int i = 0; i < WORDCOUNT; i++) //loop for word choice when correct
			{
				if (i == (2 * wordindex) || i == (2 * wordindex + 1)) //if word is 1 half + other 
				{
					while (x[i] != x_end[i] || y[i] != y_end[i]) //then move the halves together
					{
						gotoxy(x[i], y[i]); //word halves traveling vvvv
						cout << "      ";
						if (y[i] > y_end[i])
							y[i]--;
						else if (y[i] < y_end[i])
							y[i]++;
						if (x[i] > x_end[i])
							x[i]--;
						else if (x[i] < x_end[i])
							x[i]++;
						gotoxy(x[i], y[i]);
						cout << words[i];
						Sleep(30); //speed of word halves travelling
					}
				}
			}
			gotoxy(14, 1);
			cout << "                       Correct!\n";
			gscore.cscore++; //add current score if correct
		}
		else
		{
			gotoxy(14, 1);
			cout << "          Incorrect, try again."; //if word is wrong
		}
		gscore.tscore++; //and add total score/words entered
		gotoxy(28, 0);
		cout << "CURRENT SCORE: " << gscore.cscore << "/" << gscore.tscore; //display score
		if (gscore.cscore % 5 == 0) //if remainder is 0
		{
			gotoxy(14, 1);
			cout << "                                       ";
			gotoxy(0, 9);
			cout << "LEVEL 1 COMPLETE";
			gotoxy(0, 10);
			cout << "PRESS ENTER TO ADVANCE TO LEVEL 2.\n";
			gotoxy(0, 11);
			system("pause");
			break;
		}
	}
}

void leveltwo()
{
	string word;
	int choice, length, xyIndex = 0, tempcount = 0, score = 0, wordindex;
	const int WORDCOUNT = 10;
	int x_end[] = { 0, 2, 0, 3, 0, 2, 0, 2, 0, 2 }, y_end[] = { 2, 2, 3, 3, 5, 5, 4, 4, 6, 6 };

	int x[WORDCOUNT] = { 100,52,20,112,30,40,76,88,4,64 }; //x value associated with
	int y[WORDCOUNT] = { 21,17,18,15,20,18,15,19,17,21 }; //<--- y value
	string words[WORDCOUNT] = { "sh","ore","coa","st","di","ve","co","ral","bu","oy" };
	string fullword[] = { "shore", "coast", "dive", "coral", "buoy" };

	system("cls");
	system("color 9E");

	gotoxy(0, 0);
	cout << "CORRECT WORDS\n";
	cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219)
		<< char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << ">";

	for (int i = 0; i < WORDCOUNT; i++) // loop for definining word splits
	{
		word = words[i];
		length = word.length();
		gotoxy(x[xyIndex], y[xyIndex]);
		cout << words[i];
		xyIndex++;
	}

	while (1)
	{
		gotoxy(14, 1);
		cin >> word;
		transform(word.begin(), word.end(), word.begin(), ::tolower);

		if (word == "shore" || word == "coast" || word == "dive" || word == "coral" || word == "buoy")
		{
			wordindex = linear_search(fullword, 5, word);

			for (int i = 0; i < WORDCOUNT; i++)
			{
				if (i == (2 * wordindex) || i == (2 * wordindex + 1))
				{
					while (x[i] != x_end[i] || y[i] != y_end[i])
					{
						gotoxy(x[i], y[i]);
						cout << "      ";
						if (y[i] > y_end[i])
							y[i]--;
						else if (y[i] < y_end[i])
							y[i]++;
						if (x[i] > x_end[i])
							x[i]--;
						else if (x[i] < x_end[i])
							x[i]++;
						gotoxy(x[i], y[i]);
						cout << words[i];
						Sleep(30);
					}
				}
			}
			gotoxy(14, 1);
			cout << "                        Correct!\n";
			gscore.cscore++;
		}
		else
		{
			gotoxy(14, 1);
			cout << "          Incorrect, try again.";
		}
		gscore.tscore++;
		gotoxy(28, 0);
		cout << "CURRENT SCORE: " << gscore.cscore << "/" << gscore.tscore;
		if (gscore.cscore % 5 == 0)
		{
			gotoxy(14, 1);
			cout << "                                    ";
			gotoxy(0, 9);
			cout << "LEVEL 2 COMPLETE";
			gotoxy(0, 10);
			cout << "PRESS ENTER TO ADVANCE TO LEVEL 3.\n";
			gotoxy(0, 11);
			system("pause");
			break;
		}
	}
}

void levelthree()
{
	string word;
	int choice, length, xyIndex = 0, tempcount = 0, score = 0, wordindex;
	const int WORDCOUNT = 10;
	int x_end[] = { 0, 2, 0, 2, 0, 4, 0, 4, 0, 4 }, y_end[] = { 6, 6, 5, 5, 4, 4, 3, 3, 2, 2 };

	int x[WORDCOUNT] = { 10,76,20,112,30,40,52,88,100,64 }; //x value associated with
	int y[WORDCOUNT] = { 21,17,18,15,20,18,15,19,17,21 }; //<--- y value
	string words[WORDCOUNT] = { "cr","ab","sh","ell","paci","fic","salt","water","life","guard" };
	string fullword[] = { "crab", "shell", "pacific", "saltwater", "lifeguard" };

	system("cls");
	system("color DE");

	gotoxy(0, 0);
	cout << "CORRECT WORDS\n";
	cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219)
		<< char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << ">";

	for (int i = 0; i < WORDCOUNT; i++) // loop for definining word splits
	{
		word = words[i];
		length = word.length();
		gotoxy(x[xyIndex], y[xyIndex]);
		cout << words[i];
		xyIndex++;
	}

	while (1)
	{
		gotoxy(14, 1);
		cin >> word;
		transform(word.begin(), word.end(), word.begin(), ::tolower);

		if (word == "crab" || word == "shell" || word == "pacific" || word == "saltwater" || word == "lifeguard")
		{
			wordindex = linear_search(fullword, 5, word);

			for (int i = 0; i < WORDCOUNT; i++)
			{
				if (i == (2 * wordindex) || i == (2 * wordindex + 1))
				{
					while (x[i] != x_end[i] || y[i] != y_end[i])
					{
						gotoxy(x[i], y[i]);
						cout << "      ";
						if (y[i] > y_end[i])
							y[i]--;
						else if (y[i] < y_end[i])
							y[i]++;
						if (x[i] > x_end[i])
							x[i]--;
						else if (x[i] < x_end[i])
							x[i]++;
						gotoxy(x[i], y[i]);
						cout << words[i];
						Sleep(30);
					}
				}
			}
			gotoxy(14, 1);
			cout << "                        Correct!\n";
			gscore.cscore++;
		}
		else
		{
			gotoxy(14, 1);
			cout << "          Incorrect, try again.";
		}
		gscore.tscore++;
		gotoxy(28, 0);
		cout << "CURRENT SCORE: " << gscore.cscore << "/" << gscore.tscore;
		if (gscore.cscore % 5 == 0)
		{
			gotoxy(14, 1);
			cout << "                                    ";
			gotoxy(0, 9);
			cout << "LEVEL 3 COMPLETE";
			gotoxy(0, 10);
			cout << "PRESS ENTER TO ADVANCE TO LEVEL 4.\n";
			gotoxy(0, 11);
			system("pause");
			break;
		}
	}
}

void levelfour()
{
	string word;
	int choice, length, xyIndex = 0, tempcount = 0, score = 0, wordindex;
	const int WORDCOUNT = 10;
	int x_end[] = { 0, 2, 0, 3, 0, 3, 0, 3, 0, 3 }, y_end[] = { 6, 6, 5, 5, 4, 4, 3, 3, 2, 2 };

	int x[WORDCOUNT] = { 10,76,20,112,30,40,52,88,100,64 }; //x value associated with
	int y[WORDCOUNT] = { 21,17,18,15,20,18,15,19,17,21 }; //<--- y value
	string words[WORDCOUNT] = { "ya","cht","jet","ski","san","dbar","sea","gull","dol","phin" };
	string fullword[] = { "yacht", "jetski", "sandbar", "seagull", "dolphin" };

	system("cls");
	system("color 04");

	gotoxy(0, 0);
	cout << "CORRECT WORDS\n";
	cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219)
		<< char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << ">";

	for (int i = 0; i < WORDCOUNT; i++) // loop for definining word splits
	{
		word = words[i];
		length = word.length();
		gotoxy(x[xyIndex], y[xyIndex]);
		cout << words[i];
		xyIndex++;
	}

	while (1)
	{
		gotoxy(14, 1);
		cin >> word;
		transform(word.begin(), word.end(), word.begin(), ::tolower);

		if (word == "yacht" || word == "jetski" || word == "sandbar" || word == "seagull" || word == "dolphin")
		{
			wordindex = linear_search(fullword, 5, word);

			for (int i = 0; i < WORDCOUNT; i++)
			{
				if (i == (2 * wordindex) || i == (2 * wordindex + 1))
				{
					while (x[i] != x_end[i] || y[i] != y_end[i])
					{
						gotoxy(x[i], y[i]);
						cout << "      ";
						if (y[i] > y_end[i])
							y[i]--;
						else if (y[i] < y_end[i])
							y[i]++;
						if (x[i] > x_end[i])
							x[i]--;
						else if (x[i] < x_end[i])
							x[i]++;
						gotoxy(x[i], y[i]);
						cout << words[i];
						Sleep(30);
					}
				}
			}
			gotoxy(14, 1);
			cout << "                        Correct!\n";
			gscore.cscore++;
		}
		else
		{
			gotoxy(14, 1);
			cout << "          Incorrect, try again.";
		}
		gscore.tscore++;
		gotoxy(28, 0);
		cout << "CURRENT SCORE: " << gscore.cscore << "/" << gscore.tscore;
		if (gscore.cscore % 5 == 0)
		{
			gotoxy(14, 1);
			cout << "                                    ";
			gotoxy(0, 8);
			cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
			gotoxy(0, 10);
			cout << "> CONGRATULATIONS! YOU HAVE COMPLETED THE GAME <";
			gotoxy(0, 12);
			cout << ">      PRESS ENTER TO RETURN TO MAIN MENU      <\n";
			gotoxy(0, 14);
			cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
			gotoxy(0, 15);
			system("pause");
			break;
		}
	}
}

int loadlevel() //load level function
{
	int levelchoice; //variable for user to enter which level they choose
	const int row = 10, col = 30; //border row and column
	int screen[row][col] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	system("cls");

	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 30; col++)
		{
			if (screen[row][col] == 1)
			{
				cout << char(219);
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}

	gotoxy(2, 1); //coordinates
	cout << "1. Stage 1:" << endl;
	gotoxy(2, 2);
	cout << "2. Stage 2:" << endl;
	gotoxy(2, 3);
	cout << "3. Stage 3:" << endl;
	gotoxy(2, 4);
	cout << "4. Stage 4:" << endl;
	gotoxy(2, 5);
	cout << "5. Exit game:" << endl;
	gotoxy(0, 12);
	cout << "Select a Level: " << endl;
	cin >> levelchoice;

	return levelchoice; //return to main what user chose
}

int main()
{
	while (1)
	{
		int choice = menu(); //returning choice variable
		
		if (choice == 1) //start game
		{
			levelone();//play levels through
			leveltwo();
			levelthree();
			levelfour();
		}
		else if (choice == 2) //load level
		{
			int levelchoice = loadlevel(); //returning levelchoice variable

			if (levelchoice == 1) {
				levelone();
			}
			else if (levelchoice == 2) {
				leveltwo();
			}
			else if (levelchoice == 3) {
				levelthree();
			}
			else if (levelchoice == 4) {
				levelfour();
			}
		}
		else if (choice == 3) //show instructions
			instructions();
		else
			return 0;
	}
	while (1)
	{
	}
}