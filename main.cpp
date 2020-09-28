#include <string>
#include <iostream>
#include <algorithm>
#include "FamilySet.h"

using namespace std;

bool debug;	// Global variable to indicate debugging


//function to trigger prompts for user yes or no input
bool PromptYesNoMessage(string msg)
{
    while (true) {
        cout << msg << "(y/n) ";
        string response;
        cin >> response;
        if (response == "y")
            return true;
        if (response == "n")
            return false;
        cout << "Please enter y or n..." << endl;
    }
}
//function to trigger prompts for guess

int PromptGuesses()
{
    while (true) { //while it is true that the user wants to play the game
        int len;  //declaring length as integer
        cout << "Please enter how many guesses: ";
        cin >> len;
        if (len > 0)  //if user enter number greater than 0, return the length
            return len;
    }
}
//COMMENT HERE

int PromptWordLength()
{

    //check if words of that length exist in the dictionary

    int len;

    while (true)
    {
        cout << "Enter word length: ";
        cin >> len;

        if (len > 0)
            break;
    }

    return len;
}

//function prompts guess from user
string PromptGuess(string& guessedLetters)
{
    string guess = "";

    while (true)                //while true do the following
    {
        cout << "Enter a letter to guess: "; //prompt for user to input a letter
        cin >> guess;

        transform(guess.begin(), guess.end(), guess.begin(), ::toupper); //converting lowercase to uppercase, optional did it for clarity.
        //ensuring that the user that does guess the same letter twice
        if (guess.size() == 1 && guessedLetters.find(guess[0]) == string::npos) //npos, static member value return greatest possible value for element size
            break;

        cout << "Error: Enter only an unguessed letter" << endl;
    }

    //adding left operand to right operand.

    guessedLetters += guess;
    return guess;
}



//COMMENT HERE

string ChooseFamily(string guess, string guessProgress, FamilySet& set)

//for loop is from 0 to number of families in the dictionary
{
    // filter families by guess and guessProgress/guessPattern
    cout<<endl<<guessProgress;
    set.filterFamilies(guess, guessProgress);
    cout<<"Filtering"<<endl;
    //need two ints
    //call filter families and reset family iterators <- there is a function for this
    //call function for reset family iterator
    //create a loop to test everything
    //test condition for size is going to be num families

    int HighestFamily=0;
    int temp =0;

    string maxFamily = "";

    string Holder="";

    //first send place holder and then random
    //COMMENT FOR LOOP TO MAKE IT WORK

    set.resetFamilyIter();


    for (int i = 0; i<set.numFamilies(); i++)
    {
        Holder = set.getNextFamily();
        HighestFamily =set.familySize(Holder);
        cout<<"size"<<HighestFamily<<endl;

        if(HighestFamily > temp)
        {
            temp=HighestFamily;
            maxFamily=Holder;
        }



    }



    /*
    * Use the iterator to loop through each family and
    * figure out the biggest family size.
    * Return this family


    set.resetFamilyIter();

    while (set.hasNext())
    {
     //   if(debug){}

        string nextFamily = set.getNextFamily();

        if (maxFamily == "" || set.getFamily(nextFamily).size() > set.getFamily(maxFamily).size())
            maxFamily = nextFamily;
        cout<<nextFamily<<endl;
    }
    */
    return maxFamily;
}



//COMMENT HERE
bool isWin(string guessedProgress)
{
    return guessedProgress.find("*") == string::npos;
}

void PlayEvilHangman(string file)
{
    // Prompt user for word length and number of guesses
    int len = PromptWordLength();
    int guessesLeft = PromptGuesses();
    cout<<len<<endl;
    //int len = 4;
    //int guessesLeft = 3;

    // Load dictionary based on word length
    cout << "Loading dictionary..." << endl;
    FamilySet families(file, len);



    string guessedLetters = "";
    string correctlyGuessed = "";	// correctly guessed positions
    string guessProgress = "";

    for (int i = 0; i < len; i++)
        guessProgress += "*";

    string randomword=families.getRandomWord();                          
    // cout<<endl<<randomword<<endl;
    // Actual game loop...

    int SIZE=families.numWords();
    while (true) {

          if(debug) {

        // Your code here...
        cout << "PROGRESS: " << guessProgress << endl;
        cout << "Guesses Left: " << guessesLeft << endl;
        cout << "Attempted Letters: " << guessedLetters << endl;
        cout<<"Candidate words: "<<families.numWords()<<endl;


        //after choose family, get size of family and make it equal to candidate words

        string guess = PromptGuess(guessedLetters);
        //cout<<endl<<"Guess: "<<guess;

        for (int a = 0; a < len; a++) {         //dont need this here
            if (randomword[a] == guess[0]) {
                guessProgress[a] = guess[0];
            }
        }

        families.filterFamilies(guess, guessProgress);


        //LOOK OVER THIS


        //guessProgress = ChooseFamily(guess, guessProgress, families);
        bool badGuess = true;
/*
            for (unsigned i = 0; i < family.size(); i++) {
                if (family[i] != '*' && guessProgress[i] == '*') {
                    guessProgress[i] = family[i];
                    badGuess = false;
                }
            }



*/
        guessProgress=ChooseFamily(guess,guessProgress,families);
        families.setFamily(guessProgress);
        guessesLeft--;


        int FamilyS=families.familySize(guessProgress);
        cout<< "Max Family is: "<<guessProgress<<"for size"<<families.familySize(guessProgress)<<endl;
        //families.numWords()=families.familySize(guessProgress);
        SIZE=FamilyS;


         }

          else if(!debug){

              cout << "PROGRESS: " << guessProgress << endl;
              cout << "Guesses Left: " << guessesLeft << endl;
              cout << "Attempted Letters: " << guessedLetters << endl;
              cout<<"Candidate words: "<<families.numWords()<<endl;
              string guess = PromptGuess(guessedLetters);
              guessesLeft--;


          }


        if (isWin(guessProgress)) {
            cout << "Wow! You won!" << endl;
            break;
        }


        if (guessesLeft <= 0) {
            cout << "Wow... you are a really bad guesser..." << endl;
            cout << "The mystery word was: " << families.getRandomWord() << endl;
            //cout<<endl<<randomword<<endl;


            break;
        }
        //  guessesLeft--;
        //  families.setFamily(family);

    }
}

int main()
{
    string file;
    cout << "Enter file: ";
    cin >> file;				// Can comment out this line and include the following while developing
    // file = "small.txt";  // Convenient to hard code while developing

    while (true) {
        debug = PromptYesNoMessage("Turn debugging on?");
        PlayEvilHangman(file);
        if (!PromptYesNoMessage("Would you like to play again ?"))
            break;
    }
    return 0;
}
