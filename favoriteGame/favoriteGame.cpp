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

			outfile << title << "|" << genre << "|" << year << "|" << charName << endl;

			return 0;

		}
		else
		{
			return showError;
		}

	}

	void gameInfo()
	{
		cout << "what is the title: ";
		getline(cin, title);
		cout << "Enter the genre: ";
		getline(cin, genre);
		cout << "Entr your favorite charactor name in the game: ";
		getline(cin, charName);
		cout << "Enter release year for the game: ";
		cin >> year;
		cin.ignore();
		cin.clear();
	}


	void showGamInfo()
	{

		cout << "Title " + title << endl;
		cout << "Genre " + genre << endl;
		cout << "Year of game release " + year + "year" << endl;
		cout << "Favorite charactor in the game" + charName << endl;

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
	void captureInput() {
		string userInput = "y";
		cout << "Enter game Y/N?" << endl;
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
	int savegList(string filename) {
		ofstream output(filename, ios::trunc);
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
	int ReadgList(string filename)
	{
		string theTitle, theYear, theChar, theGenre;
		ifstream infile(filename, ios::in);
		if (!infile)
		{
			cout << "File could not be opened for reading" << endl;
			return readError;
		}


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
				getline(infile, theYear);
				getline(infile, theChar);
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
	string filename;
	cout << "Enter full-path filename: ";
	getline(cin, filename);

	gList gameList;
	string userInput;

	int error = gameList.ReadgList(filename);
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
	gameList.savegList(filename);
	gameList.DisplayListofGames();
	gameList.delMemory();

	return 0;
}