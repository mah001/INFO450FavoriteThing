#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const int ArraySize = 50;
const int readError = 50;
const int showError = 50;

class FavoriteGames
{
private:
	int disList;
	string title;
	string genre;
	string charName;
	string year;
	FavoriteGames ** games;
public:
	FavoriteGames()
	{
		year = "";
		title = "";
		genre = "";
		charName = "";
	}
	FavoriteGames(string t, string yr, string thefavChar, string g)
	{
		title = t;
		year = yr;
		charName = thefavChar;
		genre = g;
	}
	~FavoriteGames()
	{
		for (int i = 0; i < disList; i++)
		{
			delete games[i];
		}

	}


	int savGamFile(ofstream &outfile)
	{
		if (outfile.is_open())
		{

			outfile << title << "|" << genre << "|" << charName << "|" << year << endl;

			return 0;

		}
		else
		{
			return showError;
		}

	}

	void gameInfo() // get user input
	{
		cout << "what is the title of the game: ";
		getline(cin, title);
		cout << "Enter the genre of the game: ";
		getline(cin, genre);
		cout << "Enter your favorite charactor name in the game: ";
		getline(cin, charName);
		cout << "Enter release year for the game: ";
		getline(cin, year);
		cin.ignore();
		cin.clear();
	}


	void showGamInfo() // output user data
	{

		cout << "The title of the game is: " + title << endl;
		cout << "The genre of the game is: " + genre << endl;
		cout << "Favorite charactor in the game is: " + charName << endl;
		cout << "The release year for the game is: " + year << endl;
	}
};
class gList : public FavoriteGames
{
private:
	FavoriteGames ** games;
	int listCap;
	int recordNum;


public:

	gList() :FavoriteGames() { listCap = 0; recordNum = 0; }
	// method for cleaning up the memory
	void delMemory() {
		for (int i = 0; i < recordNum; i++)
		{
			delete games[i];
		}
		delete[]games;
	}
	void gameInfo() {}
	void showGamInfo() {}
	int resetArray() {

		FavoriteGames ** one;
		one = new FavoriteGames *[listCap + ArraySize];
		listCap = listCap + ArraySize;
		for (int i = 0; i < recordNum; i++)
		{
			one[i] = games[i];
		}
		delete[]games;
		games = one;


		return 0;
	}
	// ask user if they want to continue and ask if they want to add another game
	void captureInput() {
		string userInput = "y";
		cout << "do you want to enter game name Y/N?" << endl;
		getline(cin, userInput);
		while (userInput == "Y" || userInput == "y")
		{
			games[recordNum] = new FavoriteGames();
			games[recordNum]->gameInfo();
			recordNum++;
			cout << "enter another game Y/N?" << endl;
			getline(cin, userInput);
		}
	}
	void DisplayListofGames() {
		for (int i = 0; i < recordNum; i++)
		{
			games[i]->showGamInfo();
		}
	}
	int savegList(string fileTitle) {
		ofstream output(fileTitle, ios::trunc);
		if (output)
		{
			for (int i = 0; i < recordNum; i++)
			{
				games[i]->savGamFile(output);
			}
			output.close();

			return 0;
		}
		else
		{
			return showError;
		}
		return 0;
	}
	int ReadgList(string fileTitle)
	{
		string theTitle, theYear, theChar, theGenre;
		ifstream infile(fileTitle, ios::in);
		if (!infile)
		{
			cout << "File could not be opened for reading" << endl;
			return readError;
		}

		// read data from file
		while (!infile.eof())
		{
			if (recordNum == listCap)
			{
				resetArray();
			}
			getline(infile, theTitle, '|');
			if (!theTitle.empty())
			{
				getline(infile, theGenre, '|');
				getline(infile, theChar);
				getline(infile, theYear);
				games[recordNum] = new FavoriteGames(theTitle, theYear, theChar, theGenre);
				recordNum++;
			}
		}
		infile.close();
		return 0;
	}
};

int main()
{
	string fileTitle;
	cout << "Enter full-path filename: ";
	getline(cin, fileTitle);

	gList gameList;
	string userInput;

	int error = gameList.ReadgList(fileTitle);
	if (error)
	{
		cout << "can't read list. Do you want to try again? Y/N ";
		getline(cin, userInput);
		if (userInput != "Y" && userInput != "y")
		{
			return -1;
		}
	}
		gameList.captureInput();
	gameList.savegList(fileTitle);
	gameList.DisplayListofGames();
	gameList.delMemory();
	
	system("pause");
	return 0;
}