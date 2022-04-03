#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <ctime>
using namespace std;
using std::cout;
using std::endl;
using std::fstream;
using std::string;

void addRecipe(string recipebook_filename)
{
    string name;
    string ingrediants;
    string author;
    string steps;
    cout << "Please enter recipe name: ";
    cin >> name;

    cout << "Please enter recipe author: ";
    cin >> author;

    cout << "Please enter the ingrediants: (to end type !) ";

    string line_ingrediants;
    while (getline(cin, line_ingrediants))
    {
        if (line_ingrediants == "!")
            break;
        ingrediants += line_ingrediants;
    }

    cout << "Please enter the instructions: (to end type !) ";

    string line_steps;
    int iter = 1;
    while (getline(cin, line_steps))
    {
        if (line_steps == "!")
            break;
        string s = std::to_string(iter);
        line_steps = s + ". " + line_steps + "\n";
        steps += line_steps;
        iter++;
    }

    ofstream recipebook;
    string filename = recipebook_filename;
    // recipebook.open ("RecipeBook2.txt");
    recipebook.open(filename, std::ios_base::app | std::ios_base::in);    
    if (recipebook.is_open())
    {
        recipebook << "________________ \n";
        recipebook << name << "\n";
        recipebook << author << "\n";
        recipebook << "Ingredients:"
               << "\n";
        recipebook << ingrediants << "\n";
        recipebook << "Instructions:"
               << "\n";
        recipebook << steps << "\n";
        recipebook.close();
    }
}

void Parser(unordered_map<int, vector<string>> &RecipeBook, string recipebook_filename)
{
    // Create a text string, which is used to output the text file
    string line;
    string name;
    string ingrediants;
    string steps;
    int recipe_index = 0;
    int mode;
    mode = 0;
    // unordered_map<string, vector<string>> RecipeBook;

    // Read from the text file
    ifstream MyReadFile(recipebook_filename);

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, line))
    {
        // cout << line + "\n";
        // Output the text from the file
        // cout << line << "\n";
        if (line == "________________")
        {
            mode = 0;
            // cout << name << "\n";
            // cout << ingrediants ;
            // cout << steps ;
            name = "";
            ingrediants = "";
            steps = "";
            recipe_index = recipe_index + 1;
            continue;
        }
        if (line == "Ingredients:")
        {
            mode = 1;
            continue;
        }
        if (line == "Instructions:")
        {
            mode = 2;
            continue;
        }
        if (line.length() == 0)
        {
            continue;
        }
        if (mode == 0)
        {
            name = line;
            // cout << name + "\n";
            RecipeBook[recipe_index] = {name, ingrediants, steps};
            mode = 3;
        }
        if (mode == 1)
        {
            // cout << name;
            ingrediants = ingrediants + line + "\n";
            RecipeBook[recipe_index] = {name, ingrediants, steps};
        }
        if (mode == 2)
        {
            // cout << name;
            steps = steps + line + "\n";
            RecipeBook[recipe_index] = {name, ingrediants, steps};
        }
    }

    // Close the file
    MyReadFile.close();
}

int userInput(string user_input, string recipebook_filename ) {
    cout << "Type `A` to Add a recipe or `R` to receive a recipe: ";
    cin >> user_input;
    if (user_input == "A" | user_input == "a"){
        return 0;}
    else if (user_input == "R" | user_input == "r"){
            return 1;}
    else {
        return 2;
    }
}




int main(int argc,char *argv[], char *envp[]) 
{
    string user_input;
    string recipebook_filename = "RecipeBook.txt";
    int mode;
    bool run = true;
    while(run){
        mode = userInput( user_input, recipebook_filename);
    if (mode == 0){
        addRecipe(recipebook_filename);
    }
    if (mode == 1) {
        unordered_map<int, vector<string>> RecipeBook;
        Parser(RecipeBook, recipebook_filename);
        auto it = RecipeBook.begin();
        srand(time(NULL));
        advance(it, rand() % RecipeBook.size());
        int random_key = it->first;
        for (auto &c : RecipeBook.at(random_key))
        {
            cout << "\n"
                 << c << "\n";
        }
    }
    if (mode == 2){
        run = false;
    }
    }
}