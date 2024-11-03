/*
                    ----------
                    | TASK-1 |
                    ----------
    Number Guessing Game
    ---------------------
    Develop a number guessing game where the computer
    randomly selects a number, and the player has to
    guess it. Provide hints like "too high" or "too
    low" to help the player guess the correct number

*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << "\n---------- WELCOME TO NUMBER GUESSING GAME----------------\n";

    char ch1;
    cout << "\n-> I have select a random number between 1 to 100.\n-> You have to guess the number correctly to win the game" << endl;
    cout << "\nDo you want to try you luck (y/n): ";

    cin >> ch1;
    if (ch1 == 'n' || ch1 == 'N')
    {
        cout << "\n--------------------\n";
        cout << "Sad to see you go!\n";
        cout << "--------------------\n";
        return 0;
    }

    int ch;

    do
    {
        // Generating random number between 1 to 100
        srand(time(0));
        int random_number = rand() % 100 + 1;

        int difficulty;
        cout << "\nSelect difficulty level: " << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        cout << "Enter Your Choice -> ";
        cin >> difficulty;

        int attempts;
        if (difficulty == 1)
        {
            attempts = 15;
        }
        else if (difficulty == 2)
        {
            attempts = 10;
        }
        else if (difficulty == 3)
        {
            attempts = 5;
        }
        else
        {
            cout << "------------------------------------------------------------" << endl;
            cout << "Invalid difficulty level. Difficulty level is set to Medium" << endl;
            cout << "------------------------------------------------------------" << endl;
            attempts = 10;
        }

        string guess_num;
        int guess;
        while (attempts--)
        {
            cout << "\nGuess the number: ";
            cin >> guess_num;

            bool isNumber = true;
            for (int i = 0; i < guess_num.length(); i++)
            {
                if (guess_num[i] < '0' || guess_num[i] > '9')
                {
                    isNumber = false;
                    break;
                }
            }

            if (isNumber)
            {
                guess = stoi(guess_num);
            }
            else
            {
                attempts++;
                cout << "\nInvalid Input! Please enter a valid number" << endl;
                continue;
            }

            if (guess == random_number)
            {
                cout << "\n------------- You Won -------------------" << endl;
                cout << "Congratulations!!! Your guess is correct" << endl;
                cout << "-----------------------------------------" << endl;
                break;
            }
            else
            {
                if (guess < random_number)
                {
                    cout << "\nYour guess is too low! try again" << endl;
                    cout << attempts << " attempts left" << endl;
                }
                else
                {
                    cout << "\nYour guess is too high! try again" << endl;
                    cout << attempts << " attempts left" << endl;
                }
            }
        }

        if (attempts == -1)
        {
            cout << "\n--------------------------------" << endl;
            cout << "Oops you loose the game!" << endl;
            cout << "The number correct number was: " << random_number << endl;
            cout << "--------------------------------" << endl;
        }

        cout << "\nDo you want to play again:" << endl;
        cout << "1. Yes \n2. No" << endl;
        cout << "Enter you choice (1/2) - > ";
        cin >> ch;

        if (ch == 2)
        {
            cout << "\nThanks for playing the game!!" << endl;
        }
        cout << "___________________________________________________________" << endl;

    } while (ch == 1);

    return 0;
}
