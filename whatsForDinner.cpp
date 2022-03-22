#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <ctime>
using namespace std;


void addRecipe(){

}
 
void Parser(unordered_map<int, vector<string>> &  RecipeBook)
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
    ifstream MyReadFile("RecipeBook.txt");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, line)) {
        // cout << line + "\n";
    // Output the text from the file
    // cout << line << "\n";
        if (line == "________________"){
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
        if (line == "Ingredients:"){
            mode = 1;
            continue;
        }
        if (line == "Instructions:"){
            mode = 2;
            continue;
        }
        if (line.length() == 0 ){
            continue;
        }
        if (mode == 0 ){
            name = line;
            // cout << name + "\n";
            RecipeBook[recipe_index] = {name, ingrediants, steps};
            mode = 3;
        }
        if (mode == 1 ){
            // cout << name;
            ingrediants = ingrediants + line + "\n";
            RecipeBook[recipe_index] = {name, ingrediants , steps};
        }
        if (mode == 2 ){
            // cout << name;
            steps = steps + line + "\n";
            RecipeBook[recipe_index] = {name, ingrediants , steps};

        }}
    


    // Close the file
    MyReadFile.close();
} 


int main( int argc,      // Number of strings in array argv
          char *argv[],   // Array of command-line argument strings
          char *envp[] )  // Array of environment variable strings

{
    string user_input;
    cout << "Type `A` to Add a recipe or `R` to receive a recipe: ";
    cin >> user_input;
    if ( user_input == "A"| user_input == "a"){
        addRecipe();
    }
    if (user_input == "R" |user_input == "r" ) {
        unordered_map<int, vector<string>> RecipeBook;
        Parser( RecipeBook);
        auto it = RecipeBook.begin();
        srand ( time(NULL) );
        advance(it, rand() % RecipeBook.size());
        int random_key = it->first;
        for (auto &c : RecipeBook.at(random_key)) {
                cout << "\n" << c << "\n";
            }
        }


    
}