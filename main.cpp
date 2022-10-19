#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
int review();
void resetUserInput();
string IngrDelim = ",";
string healthCheckDelim = ":";

// TODO
// refactor in m,v,c,l
// roughly prevent user input error

int main()
{
    cout << "Eat healthy" << endl;

    for (int i = 0; i < 3; i++) {
        promptAddIngredients();
        ingredients = inputIngredients();
        persistIngredients(ingredients);
        promptHealthCheck();
        healthCheck = inputHealthCheck();
        persistHealthCheck(healthCheck);
        resetUserInput();
    }

    review();
    
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
    ofstream database(databaseName, ios_base::app);
    database << ingredients + healthCheckDelim;
    database.close();

    return 0;
}

void promptHealthCheck()
{
    cout << "Please review your wellbeing after the meal from 1 (I feel terrible) to 5 (I feel GREAT)" << endl;
}

int inputHealthCheck() // TODO user misinput
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
    
    iDatabase.seekg(-1, ios_base::end);
    getline(iDatabase, line);

    ofstream oDatabase(databaseName, ios_base::app);
    oDatabase << to_string(healthCheck) << endl;

    return 0;
}

int review()
{
    string line;
    ifstream iDatabase(databaseName);

    // TODO put vectors in a map
    vector<string> one;
    vector<string> two;
    vector<string> three;
    vector<string> four;
    vector<string> five;

    while (getline(iDatabase, line))
    {
        char healthCheck = line.back();
        if (healthCheck == '1')
        {
            string ingredients = line.substr(0, line.find(healthCheckDelim));
            // TODO put ingredients in vectors
        }
    }

    return 0;
}

void resetUserInput()
{
    cin.ignore();
}