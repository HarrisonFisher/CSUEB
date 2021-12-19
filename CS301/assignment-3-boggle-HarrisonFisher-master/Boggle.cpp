
#include "Dictionary.h"
#include "Boggle.h"

// Your code here

/*
 * Function:  Constructor
 *
 * Precondition: dictionary.txt can be opened
 *
 * Post-condition: all the words in dictionary.txt are located into dict
 */
Boggle::Boggle() : dict("dictionary.txt") {

}


/*
 * Function: Constructor with file name
 *
 * Precondition: The file can be opened
 *
 * Post-condition: All the words in the file are loaded into dict
 */
Boggle::Boggle(string filename) : dict(filename){

}

/*
 * Function: Sets the values of the board
 *
 * Precondition: none
 *
 * Post-condition: all the values in the 2d array are copied over to this->board at the same location
 */
void Boggle::SetBoard(string (*board)[BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            this->board[i][j] = board[i][j];
        }
    }
}

/*
 * Function: Solves
 *
 * Precondition:
 * Board is set and dict loaded.
 * If printBoard is false then it will only list the words
 *
 * Post-condition:
 * The results to solve the board are outputted
 */
void Boggle::SolveBoard(bool printBoard, ostream &output) {
    int count = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            {//clear visited
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        visited[i][j] = 0;
                    }
                }
            }
            SolveBoardHelper(printBoard,i,j,"",1,count,output);
        }
    }
}

/*
 * Function: Saves wordsFound dict
 *
 * Precondition: filename must be valid
 *
 * Post-condition: all the words in dict are outputted to the file name
 */
void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

/*
void Boggle::PrintBoard(ostream &output) {
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        output << "Row " << i << ":";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            output  << " " << this->board[i][j];
        }
        output << endl;
    }

}
 */


/*
 * Function: Recursive board word search
 *
 * Precondition:
 * i and j must be less than BOARD_SIZE and greater than 0.
 * The i and j position can not be visited already.
 * w must be a prefix
 *
 * Post-condition:
 * If it is a word it will save to dict
 * If it is a prefix it will call function again 8 times and move to each nearby position
 */
void Boggle::SolveBoardHelper(bool printBoard, int i, int j, string w, int v, int &count, ostream &output) {
    //cout << "\t\t" << w << "\t" << i << "  " << j << endl;


    if (i < 0 || i >= BOARD_SIZE ) {
        //cout << "\t\t\t\tflag 1" << endl;
        return;
    }
    if (j < 0 || j >= BOARD_SIZE ){
        //cout << "\t\t\t\tflag 2" << endl;
        return;
    }
    if (visited[i][j] != 0) {
        //cout << "\t\t\t\tflag 3" << visited[i][j] << endl;
        return;
    }
    if (!dict.IsPrefix(w)){
        //cout << "\t\t\t\tflag 4" << endl;
        return;
    }

    w = w + board[i][j];


    int visitedCopy[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            visitedCopy[i][j] = visited[i][j];
        }
    }




    //cout << "\t\t\t" << w << "\t" << i << "  " << j <<  endl;




    if (dict.IsWord(w) && !wordsFound.IsWord(w)){
        visited[i][j] = v;
        wordsFound.AddWord(w);

        if (!printBoard){
            output << count << "\t" << w << endl;
        } else {
            output << "Word: " << w << endl;
            output << "Number of Words: " << count << endl;
            for (int l = 0; l < BOARD_SIZE; l++) {
                for (int o = 0; o < BOARD_SIZE; o++){
                    if (visited[l][o] == 0) {
                        output << "  " << board[l][o] << "  ";
                    }else {
                        output << ' ';
                        output << '\'';
                        output << board[l][o];
                        output << '\'';
                        output << ' ';
                    }
                }
                output << '\t';
                for (int o = 0; o < BOARD_SIZE; o++){
                    output << "  " << visited[l][o] << "  ";
                }
                output << endl;
            }
            output << endl;
        }

        count++;

    }

    if (dict.IsPrefix(w)){
        //output << w  << "--" << endl;
        visited[i][j] = v;

        //copy visited


        {
            /*
            North
            Northeast
            East
            Southeast
            South
            Southwest
            West
            Northwest
             */

            SolveBoardHelper(printBoard,i-1,j+0,w,v+1,count,output);    //North
            SolveBoardHelper(printBoard,i-1,j+1,w,v+1,count,output);    //Northeast
            SolveBoardHelper(printBoard,i+0,j+1,w,v+1,count,output);    //East
            SolveBoardHelper(printBoard,i+1,j+1,w,v+1,count,output);    //Southeast
            SolveBoardHelper(printBoard,i+1,j+0,w,v+1,count,output);    //South
            SolveBoardHelper(printBoard,i+1,j-1,w,v+1,count,output);    //Southwest
            SolveBoardHelper(printBoard,i+0,j-1,w,v+1,count,output);    //West
            SolveBoardHelper(printBoard,i-1,j-1,w,v+1,count,output);    //Northwest


        }



    }

    //turn visited to how it used to be
    //memcpy(visited, visitedCopy, sizeof(visited));
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                visited[i][j] = visitedCopy[i][j];
            }
        }
    }
}


// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}
