#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

string databaseName = "database.txt";
void promptAddIngredients();
string inputIngredients();
string ingredients;
int persistIngredients(string);
void promptHealthCheck();
int healthCheck;
const int healthCheckValues[5] = {1,2,3,4,5};
int inputHealthCheck();
int persistHealthCheck(int);
map<int, vector<string>> tallyIngredients();
vector<string> unhealthyIngredients;
vector<string> findUnhealthyIngredients(const map<int, vector<string>> &);
void reviewMsg(const vector<string> &);
void resetUserInput();
char IngrDelim = ',';
string healthCheckDelim = ":"; // TODO into char

// TODO
// variable scope
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

    map<int, vector<string>> tally = tallyIngredients();
    unhealthyIngredients = findUnhealthyIngredients(tally);
    reviewMsg(unhealthyIngredients);
    
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

map<int, vector<string>> tallyIngredients()
{
    string line;
    ifstream iDatabase(databaseName);
    map<int, vector<string>> tally;

    vector<string> ingredientsV;

    // initialise tallies
    for (int i : healthCheckValues)
    {
        tally[i] = ingredientsV;
    }

    while (getline(iDatabase, line))
    {
        ingredientsV.clear();
        char healthCheck = line.back() - 48;

        string ingredients = line.substr(0, line.find(healthCheckDelim));
        string ingredient = "";
        for (size_t i = 0; i < ingredients.length(); i++)
        {
            if (ingredients.at(i) == IngrDelim) {
                tally[healthCheck].push_back(ingredient);
                ingredient.clear();
            } else {
                ingredient.push_back(ingredients.at(i));
            }
        }
        tally[healthCheck].push_back(ingredient);
        ingredient.clear();
    }

    return tally;
}

vector<string> findUnhealthyIngredients(const map<int, vector<string>> &tally) // TODO check const
{
    vector<string> unhealthyIngredients;

    for (string suspiciousIngredient: tally.at(1)) {
        if (find(tally.at(5).begin(), tally.at(5).end(), suspiciousIngredient) == tally.at(5).end()) {
            unhealthyIngredients.push_back(suspiciousIngredient);
        }
    }

    return unhealthyIngredients;
}

void reviewMsg(const vector<string> &unhealthyIngredients)
{
    cout << "your unhealthy ingredients are: " << endl;
    for (string unhealthyIngredient: unhealthyIngredients) {
        cout << unhealthyIngredient << ", ";
    }
    cout << endl;
}

void resetUserInput()
{
    cin.ignore(); // TODO es por el getline?
}