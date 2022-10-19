#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string databaseName = "database.txt";
void promptAddIngredients();
string inputIngredients();
string ingredients;
int persistIngredients(string);
void promptHealthCheck();
int healthCheck;
int inputHealthCheck();
int persistHealthCheck(int);

int main()
{
    cout << "Eat healthy" << endl;

    promptAddIngredients();
    ingredients = inputIngredients();
    persistIngredients(ingredients);
    promptHealthCheck();
    healthCheck = inputHealthCheck();
    persistHealthCheck(healthCheck);
    
    return 0;
}

void promptAddIngredients()
{
    cout << "Please write the current meal ingredients separated by commas" << endl;
}

string inputIngredients() // TODO trim commas, avoid repetition, etc
{
    getline(cin, ingredients);

    return ingredients;
}

int persistIngredients(string ingredients)
{
    ofstream database(databaseName);
    database << ingredients + ":";
    database.close();

    return 0;
}

void promptHealthCheck()
{
    cout << "Please review your wellbeing after the meal from 1 (I feel terrible) to 5 (I feel GREAT)" << endl;
}

int inputHealthCheck()
{
    string input;
    cin >> input;
    healthCheck = stoi(input);

    return healthCheck;
}

int persistHealthCheck(int healthCheck)
{
    string line;
    ifstream iDatabase(databaseName);
    getline(iDatabase, line);
    ofstream oDatabase(databaseName);
    oDatabase << line + to_string(healthCheck) << endl;

    return 0;
}