#include "Dictionary.h"

// Your code here

/*
 * Function: Constructor
 *
 * Precondition: none
 *
 * Post-condition: numWords set to zero and added new root
 */
Dictionary::Dictionary(): numWords(0), root(new Node) {}

/*
 * Function: de-constructor
 *
 * Precondition: there must be a root
 *
 * Post-condition: root deleted
 */
Dictionary::~Dictionary() {
    if (root) delete root;
}


/*
 * Function: Sets the values of the board
 *
 * Precondition: none
 *
 * Post-condition:
 * new root is made
 * dictionary is copied to itself
 */
Dictionary::Dictionary(const Dictionary &otherDict): numWords(0), root(new Node) {
    copyOther(otherDict);
    this->numWords = otherDict.numWords;
}

/*
 * Function: Constructor, loads dict from file
 *
 * Precondition: valid filename given
 *
 * Post-condition: all words from file are added to dictionary
 */
Dictionary::Dictionary(string filename): numWords(0), root(new Node)  {
    LoadDictionaryFile(filename);
}

/*
 * Function: Operator for copying
 *
 * Precondition: none
 *
 * Post-condition: all data is changed to match the other dictionary
 */
Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    copyOther(otherDict);
    this->numWords = otherDict.numWords;
    return *this;
}

/*
 * Function: Loads Dictionary from file
 *
 * Precondition: valid file name
 *
 * Post-condition: all words from file are added to dictionary
 */
void Dictionary::LoadDictionaryFile(string filename) {
    string file_name = filename;
    ifstream inFile;
    inFile.open(file_name);
    string word;
    while (inFile) {
        getline(inFile, word);
        //cout << word << endl;
        AddWord(word);
    }
    inFile.close();
}

/*
 * Function: Saves dictionary to file
 *
 * Precondition: valid file name
 *
 * Post-condition: all words in dictionary are outputted to file
 */
void Dictionary::SaveDictionaryFile(string filename) {

    ofstream myfile;
    myfile.open (filename);

    if(myfile) {
        SaveDictionaryHelper(this->root,"",myfile);
    } else {
        string msg = filename+"failed to open";
        throw DictionaryError(msg);
    }

    myfile.close();
}

/*
 * Function: Adds word to dictionary
 *
 * Precondition: none
 *
 * Post-condition: adds all letters and changes to last letter node is_word to true
 */
void Dictionary::AddWord(string word) {
    auto *cur = root;
    for (const auto& c : word) {
        if (!cur->leaves.count(c)) {
            cur->leaves[c] = new Node();
        }
        cur = cur->leaves[c];
    }
    if (cur->is_word != true){
        cur->is_word = true;
        numWords++;
    }
}

/*
 * Function: Empty dict
 *
 * Precondition: must be a root or it breaks
 *
 * Post-condition: deletes the current node and adds a new one
 */
void Dictionary::MakeEmpty() {
    delete this->root;
    this->root = new Node();
    this->numWords = 0;
}

/*
 * Function: Checks if word is in dictionary
 *
 * Precondition: none
 *
 * Post-condition:
 * returns false if no more leaves
 * returns true if the spot it ends on is a word
 */
bool Dictionary::IsWord(string word) {
    auto *cur = root;
    for (const auto& c : word) {
        if (cur->leaves.count(c)) {
            cur = cur->leaves[c];
        } else {
            return false;
        }
    }
    return cur->is_word == true;
}

/*
 * Function: Sets the values of the board
 *
 * Precondition: none
 *
 * Post-condition:
 * searches down the tree and will return false if dead end
 */
bool Dictionary::IsPrefix(string word) {
    auto *cur = root;
    for (const auto& c : word) {
        if (cur->leaves.count(c)) {
            cur = cur->leaves[c];
        } else {
            return false;
        }
    }
    return true;
}

/*
 * Function: Find Dictionary word count
 *
 * Precondition: none
 *
 * Post-condition: returns copy of numWords
 */
int Dictionary::WordCount() {
    return numWords;
}

/*
 * Function: Copy the other dict to it
 *
 * Precondition: it will not copy itself
 *
 * Post-condition: the root node tree are now equal to the other root node tree
 */
void Dictionary::copyOther(const Dictionary &otherDict) {
    if (!(this == &otherDict))
        copyHelper(this->root, otherDict.root);
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {

}

/*
 * Function: Helper function for copyOther
 *
 * Precondition: The address of dictionaries are not the same
 *
 * Post-condition:
 * node are now equal to the other node
 * recursively calls itself for every leaf of the node
 */
void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    auto *cur = otherTree;
    std::map<char, Node *>::iterator it = cur->leaves.begin();
    while(it != cur->leaves.end()) {
        thisTree->leaves[it->first] = new Node();
        thisTree->leaves[it->first]->is_word = it->second->is_word;
        copyHelper(thisTree->leaves[it->first],it->second);
        it++;
    }
}

/*
 * Function: Helper function for copyOther
 *
 * Precondition: none
 *
 * Post-condition:
 * if leaf is a word it will output it
 * recursively calls function again for each leaf of node
 *
 */
void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    auto *cur = curr;
    std::map<char, Node *>::iterator it = curr->leaves.begin();
    while(it != cur->leaves.end()) {
        if (it->second->is_word) {
            outFile << currPrefix << it->first << endl;
        }
        string nextPrefix = currPrefix + std::string(1, it->first);
        SaveDictionaryHelper(it->second,nextPrefix,outFile);
        it++;
    }
}

/*
 * Function: Node constructor
 *
 * Precondition: none
 *
 * Post-condition:
 * sets is_word value to false
 */
Dictionary::Node::Node(): is_word(false) {

}

/*
 * Function: Node Destructor
 *
 * Precondition:
 * the node is being deleted
 *
 * Post-condition:
 * each leaf deleted
 */
Dictionary::Node::~Node() {
    std::map<char, Node *>::iterator it = this->leaves.begin();
    while(it != leaves.end()) {
        delete it->second;
        it++;
    }
}
