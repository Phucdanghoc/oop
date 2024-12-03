/***********************************************************************
// OOP244 Project, milestone 56 : tester program
//
// File	ms56.cpp
// Version 1.0
// Date 2024-11-28
// Author Fardad
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
#include "Ordering.h"
using namespace std;
using namespace seneca;

void displayMainMenu()
{
   cout << "Seneca Restaurant\n";
   cout << "1 - Order\n";
   cout << "2 - Print Bill\n";
   cout << "3 - Start a New Bill\n";
   cout << "4 - List Foods\n";
   cout << "5 - List Drinks\n";
   cout << "0 - End Program\n";
}

void displayOrderMenu()
{
   cout << "Order Menu\n";
   cout << "1 - Food\n";
   cout << "2 - Drink\n";
   cout << "0 - Back to main menu\n";
}

void displayConfirmationMenu()
{
   cout << "You have bills that are not saved. Are you sure you want to exit?\n";
   cout << "1 - Yes\n";
   cout << "0 - No\n";
}

int getMenuSelection(int min, int max)
{
   int choice;
   while (true)
   {
      cout << "Your choice: ";
      cin >> choice;
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(INT_MAX, '\n');
         cout << "Only an integer please.\n";
      }
      else if (choice < min || choice > max)
      {
         cout << "Invalid value: [" << min << " <= value <= " << max << "], try again: ";
      }
      else
      {
         return choice;
      }
   }
}

int main()
{
   cout << "Testing Invalid Ordering if bad data is in data file!" << endl;
   // Ordering badord("drinks.csv", "badfoods.csv");
   // if (badord)
   // {
   //    cout << "The ordering should have been invalid" << endl;
   // }
   // else
   // {
   //    cout << "Passed!" << endl;
   // }

   Ordering ord("drinks.csv", "badfoods.csv");

   // cout << "Testing fool proofint..............................." << endl;
   // ord.orderDrink();

   int choice;
   int confirmExit;
   int subChoice;

   while (true)
   {
      displayMainMenu();
      choice = getMenuSelection(0, 5);

      switch (choice)
      {
      case 0:
         displayConfirmationMenu();
         confirmExit = getMenuSelection(0, 1);
         if (confirmExit == 1)
         {
            cout << "Exiting program..." << endl;
            return 0;
         }
         break;
      case 1:
         displayOrderMenu();
         subChoice = getMenuSelection(0, 2);
         if (subChoice == 1)
         {
            ord.orderFood();
         }
         else if (subChoice == 2)
         {
            ord.orderDrink();
         }
         break;
      case 2:
         ord.printBill(cout);
         break;
      case 3:
         ord.resetBill();
         break;
      case 4:
         ord.listFoods();
         break;
      case 5:
         ord.listDrinks();
         break;
      default:
         cout << "Invalid option!" << endl;
         break;
      }
   }
   return 0;
}
