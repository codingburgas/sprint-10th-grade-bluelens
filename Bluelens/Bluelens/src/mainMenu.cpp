#include <iostream>
#include "../include/mainMenu.h"
#include "../include/maze.h"
#include "../include/howToPlay.h"
#include "../include/credits.h"
using namespace std;

void menuChoice()
{
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		system("cls");
		mazeGen();
		break;
	}
	case 2:
	{
		system("cls");
		howToPlay();
		break;
	}
	case 3:
	{
		system("cls");
		credits();
		break;
	}
	default:
	{
		cout << "    Oops! Incorrect input! Try again!" << endl;
		menuChoice();
	}
	}
}
void menu()
{
	cout << endl <<"          Main Menu ";
	for (int i = 0; i < 5; i++)
	{
		cout << endl;
	}
	cout << " 1. Start maze" << endl << " 2.How to play" << endl << " 3. Credits" << endl;
	menuChoice();
}

