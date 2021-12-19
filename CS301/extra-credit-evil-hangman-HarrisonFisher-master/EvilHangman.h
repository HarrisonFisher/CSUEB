#pragma once
#define AskForSizes

bool debug;

bool PromptYesNoMessage(string msg) {
    while (true) {
        cout << msg << " (y/n)";
        string response;
        cin >> response;
        if (response == "y")
            return true;
        if (response == "n")
            return false;
        cout << "Please enter y or n." << endl;
    }
}

int PromptGuesses()
{
    while (true) {
        int len;
        cout << "Please enter how many guesses: ";
        cin >> len;
        if (len > 0)
            return len;
    }
}


int PromptWordLength()
{
    int len;

    // Your code here...
    while (true) {
        cout << "Please enter word length: ";
        cin >> len;
        if (len > 0)
            return len;
    }
}

string PromptGuess(string& guessedLetters)
{
    string guess = "";

    // Your code here...
    while (true) {
        cout << "Enter guess: ";
        cin >> guess;
        if (guess.length() == 1) break;
    }
    guessedLetters += guess;

    return guess;
}

string ChooseFamily(string guess, string guessProgress, FamilySet& set)
{
    // filter families by guess and guessProgress/guessPattern

    string maxFamily;

    /*
     * Use the iterator to loop through each family and
     * figure out the biggest family size.
     * Return this family
     */

    set.filterFamilies(guess,guessProgress);
    set.resetFamilyIter();

    maxFamily = set.getNextFamily();

    if (debug) cout << maxFamily << "   " << set.familySize(maxFamily) << endl;

    while (true){
        string val = set.getNextFamily();
        if (val == "" ) break;
        if (debug) cout << val << "   " << set.familySize(val) << endl;

        if (set.familySize(val) > set.familySize(maxFamily)) maxFamily = val;
    }

    if (debug) cout << "Max family size is " << set.familySize(maxFamily) << " for " <<  maxFamily << endl;

    set.resetFamilyIter();
    set.setFamily(maxFamily);

    return maxFamily;
}

bool isWin(string guessedProgress)
{
    return guessedProgress.find('*') == string::npos;
}

void PlayEvilHangman(string file)
{
    bool quickRun = true;

    int len, guessesLeft;
    string guessProgress = "";      // correctly guessed positions
    string guessedLetters = "";     // letters already guessed by user

    // Prompt user for word length and number of guesses

    #ifdef AskForSizes
        len = PromptWordLength();
        guessesLeft = PromptGuesses();
    #else
        len = 6;
        guessesLeft = 50;
    #endif

    // Load dictionary based on word length
    cout << "Loading dictionary..." << endl;
    FamilySet families(file, len);

    // Show *'s for the guessProgress at the beginning
    for (int i = 0; i < len; i++)
        guessProgress += "*";

    // Actual game loop...
    while (true) {
        cout << endl << endl;
        cout << guessProgress << endl;
        cout << "Guesses Left: " << guessesLeft << endl;
        cout << "Guessed Letters: " << guessedLetters << endl;

        // Your code here
        guessesLeft--;
        PromptGuess(guessedLetters);
        guessProgress = ChooseFamily(guessedLetters, guessProgress, families);


        if (isWin(guessProgress)) {
            cout << endl << "Wow! You won!" << endl;
            return;
        }

        if (guessesLeft <= 0) {
            cout << "Wow... you are a really bad guesser..." << endl;
            cout << "The mystery word was " << families.getRandomWord() << endl;
            return;
        }

    }
}