#include "FamilySet.h"


///////////////////////////////////////////////////////////////

template <typename T>
bool InVec(vector<T> &vec, T val) {
    for (int i = 0; i<vec.size();i++)
        if ( vec[i] == val ) return true;
        return false;
}

///////////////////////////////////////////////////////////////

string FamilySet::getRandomWord()
{
	int ind = rand() % wordlist->size();
	return wordlist->at(ind);
}

int FamilySet::numWords()
{
	return wordlist->size();
}

int FamilySet::numFamilies()
{
	return dictionaries.size();
}

vector<string> FamilySet::getWords() {
    return *wordlist;
}


vector<string> FamilySet_Helper(vector<string> &words,string line, vector<char> letters){
    for (int i = 0; i<letters.size(); i++){
        vector<char> tmp_vec = letters;
        string tmp_line = line;
        std::vector<char>::iterator it = tmp_vec.begin();
        std::advance(it, i);
        tmp_vec.erase(it);
        for (int j = 0; j < tmp_line.length(); j++)
            if (tmp_line[j] == letters[i]) tmp_line[j] = '*';
        if (! InVec(words,tmp_line)) words.push_back(tmp_line);
        if (tmp_vec.size() >= 0) vector<string> tmp_words = FamilySet_Helper(words,tmp_line,tmp_vec);
    } return words;
}


FamilySet::FamilySet(string dictFile, int len) {
    wordlist = new vector<string>;
    resetFamilyIter();
    string line;
    ifstream myfile (dictFile);
    if (!myfile.is_open()) throw DictionaryError(dictFile+" failed to open");
    while ( getline (myfile,line) ){
        if (line.length() == len)
            wordlist->push_back(line);
    } myfile.close();
}


FamilySet::~FamilySet() {
    unordered_map<string, vector<string>*>::const_iterator it = dictionaries.begin();
    if(it != dictionaries.end()){
        delete it->second;
        dictionaries.erase(it);
    }
    delete wordlist;
}

void FamilySet::filterFamilies(string letter, string guessPattern) {

    if (dictionaries.count(guessPattern) == 0) {
        dictionaries.insert(pair<string, vector<string>*>(guessPattern, new vector<string>));
    }

    for (int i = 0; i < wordlist->size(); i++) {
        string word = (*wordlist)[i];

        for (int j = 0; j<guessPattern.length(); j++){
            bool match = false;
            for (int k = 0; k < letter.length(); k++) {
                if (word[j] == letter[k]) match = true;
            }
            if (match) continue;

            word[j] = guessPattern[j];
        }

        if (word != guessPattern) {
            if (dictionaries.count(word) == 0) {
                dictionaries.insert(pair<string, vector<string>*>(word, new vector<string>));
            }
            dictionaries[word]->push_back((*wordlist)[i]);
        }
        else {
            dictionaries[guessPattern]->push_back((*wordlist)[i]);
        }
    }


}


void FamilySet::setFamily(string family) {

    vector<string> tmp = *(dictionaries[family]);
    wordlist->clear();
    for (int i = 0; i<tmp.size(); i++){
        wordlist->push_back(tmp[i]);
    }

    unordered_map<string, vector<string>*>::const_iterator it = dictionaries.begin();
    if(it != dictionaries.end()){
        delete it->second;
    }
    dictionaries.clear();

}

int FamilySet::familySize(string family) {
    return dictionaries[family]->size();
}

void FamilySet::resetFamilyIter() {
    famIter = dictionaries.begin();
}

string FamilySet::getNextFamily() {
    string val;
    if (famIter == dictionaries.end()) {
        val = "";
    }else{
        val = famIter->first;
        famIter++;
    }
    return val;
}

