#include <iostream>
#include <queue>
#include <fstream>
#include <map>
#include <dirent.h>
using namespace std;

typedef struct {     //Struct Value dataType for multi-Value Map
    int freq;
    string code;
} value;

map<char, value> charactersTable;
map<char, value>::iterator itr;

map<string, char> charactersTable_code;
map<string, char>::iterator itrCode;

bool writeToFile = false, readCompFile = false, read_Folder = false, decodeFolder = false , bin= false;
float srcSize = 0, desSize = 0;
string fileName, tmp = "files", tmp2 , tmp3 = "files" ;
string strArry[100];
int countF = 0;



struct MinHeapNode            // A Huffman tree node
{
    char data;                // One of the input characters
    unsigned freq;             // Frequency of the character
    MinHeapNode *left, *right; // Left and right child

    MinHeapNode(char data, unsigned freq) {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(MinHeapNode *l, MinHeapNode *r) {
        return (l->freq > r->freq);
    }
};

void printCodes(struct MinHeapNode *root, string str)   // print codes by traversing the built Huffman Tree
{
    if (!root)
        return;

    if (root->data != '$') {
        cout << "\t" << root->data << ": " << str << "\n";
        itr = charactersTable.find(root->data);
        itr->second.code = str;
        char tmp = root->data;
        desSize = desSize + str.length();
    }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}


priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;

void HuffmanCodes(char *data, int *freq, int size)   // The main function that builds a Huffman Tree and
{
    struct MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted
        // node as left and right children of this new node. Add
        // this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    // Print Huffman codes using the Huffman tree built above
    printCodes(minHeap.top(), "");
}

void mapping(char c) {
    map<char, value>::iterator iterate = charactersTable.find(c);
    value tmp;
    tmp.freq = 1;
    tmp.code = "0";

    if (iterate == charactersTable.end()) //character not Found
    {
        charactersTable.insert(pair<char, value>(c, tmp));

    } else {
        iterate->second.freq = iterate->second.freq + 1;
    }
}

void writeFile(string st) {
    map<char, value>::iterator itrr;
    ofstream destfile;
    //unsigned char bit_buffer ;
    string bit_buffer ;
    int bit  , coun = 0;

    if (bin){
        destfile.open (fileName,ios::binary);
    } else{
        destfile.open (fileName,ios::app);
    }

    string sign = "#";  // using in Folder compression only (as files flag)

    if (destfile.is_open()) {
            
        if (readCompFile) {
            for (char &c : st) {
               destfile << c;
            }

            if (read_Folder) {
                destfile << sign;
            }
            destfile.close();
        } else {

            for (char &c : st) {
                itrr = charactersTable.find(c);
                destfile << itrr->second.code ;
                desSize = desSize + (itrr->second.code).length();
                }

            }

            destfile.close();
        }

     else cout << "Unable to open file";

}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct MinHeapNode *root, string s) {
    string ans = "";
    countF = 0 ;
    struct MinHeapNode *curr = root;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left == NULL and curr->right == NULL) {
            if (curr->data == '#') {

                fileName = strArry[countF];

                writeFile(ans);
                countF++;
                ans = "";
            } else {
                ans += curr->data;
            }

            curr = root;
        }
    }
    cout << ans << endl;
    fileName = "decoded.txt";
    writeFile(ans);
    return ans + '\0';
}

//Read source file
void readFile(string srcFile) {

    string encodedText, tmp;
    char ch;

    fstream fin(srcFile, fstream::in);
    //ifstream fin;
   // fin.open (srcFile, ios::in | ios::app | ios::binary);

    if (writeToFile) {
        while (fin >> noskipws >> ch) {
            tmp += ch;
        }
        cout << tmp;
        writeFile(tmp);
        writeToFile = false;
        fin.close();
        return;
    } else if (readCompFile) {
        while (fin >> noskipws >> ch) {
            encodedText += ch;

        }
        fin.close();
        decode_file(minHeap.top(), encodedText);
        return;
    } else {
        while (fin >> noskipws >> ch) {
            srcSize ++ ;
            mapping(ch); // update exciting character's frequency value OR add a new character
        }
        fin.close();

    }
}

void compressionRatio() {
    cout << "Source file size = " << srcSize*8 << " bits" << endl
         << "Destination file size = " << desSize << " bits" << endl
         << "Compression ratio = % " << ((desSize) / (srcSize*8)) * 100 << endl;
}

void decompressFolder(string *files) {
    readFile("src.txt");

}

string *readFolder() {




    DIR *pdir = nullptr;
    pdir = opendir(tmp.c_str());   // "." will refer to the current directory
    struct dirent *pent = nullptr;
    string preTmp = tmp ;

    if (pdir == nullptr) // if pdir wasn't initialised correctly
    {
        cout << "\nERROR! pdir could not be initialised correctly";
        exit(3);
    }

    while ((pent = readdir(pdir))) // while there is still something in the directory to list
    {
        if (pent == nullptr) // if pent has not been initialised correctly
        { // print an error message, and exit the program
            cout << "\nERROR! pent could not be initialised correctly";
            exit(3);
        }


        tmp = pent->d_name;
            cout << "TMMMMP" << tmp << endl ;
        if (strcmp(pent->d_name, ".") != 0) {
            if (strcmp(pent->d_name, "..") != 0) {
                if (tmp.find(".txt") != string::npos) {
                    strArry[countF] = preTmp +"/"+ tmp ;
                    cout << "StrArry = " << strArry[countF] << endl;
                    //tmp3 = "files" ;
                    tmp2 = tmp3+ "/"+ tmp;
                    readCompFile = true;
                    read_Folder = true;
                    writeToFile = true;
                    fileName = "src.txt";
                    readFile(preTmp +"/"+ tmp);

                    countF++;
                }else if (tmp.find("DS") == string::npos) {
                    //chdir(tmp.c_str()) ;

                    tmp3 = /*tmp3 +"/"+ tmp ;*/ "files/" + tmp ;
                    tmp =  preTmp+"/"+tmp   ;
                    cout << "tmp = " + tmp ;
                    readFolder() ;

                   // chdir(tmp.c_str());
                }

            }
        }

    }

    //close the directory
    closedir(pdir);

    return EXIT_SUCCESS;
}


int main() {

    /*********************************** Program UI ****************************************/
    cout << "Press >>" << endl
         << " '0' : Folder Compression" << endl
         <<" '1' : File Compression"    << endl
         << "> " ;
    int option ;
    cin >> option ;
    while (option != 0 && option!= 1){
        cout << "Enter Valid value"<< endl
             << "> " ;
        cin >> option ;
    }
    /************************************************************************************/


    string *files = nullptr;
    string fName ;
    if (option == 0) {
        files = readFolder();
        readCompFile = false;
        read_Folder = false;
        writeToFile = false;
        readFile("src.txt");
    }else{
        cout << "Enter File name (Default : src.txt)" << endl ;
        cin >> fName ;
        readFile(fName);
    }

   // readFile("src.txt");
    //readFile(fName);

    char *chArr = (char *) malloc(charactersTable.size() * sizeof(char));   //Allocate for characters
    int *freArr = (int *) malloc(charactersTable.size() * sizeof(int));    //Allocate for characters's frequency

    int size = charactersTable.size() / sizeof(char);
    int count = 0;

    /***************************************** Copy Characters Map **********************************/
    for (itr = charactersTable.begin(); itr != charactersTable.end(); ++itr) {
        chArr[count] = itr->first;
        freArr[count] = itr->second.freq;
       // srcSize = srcSize + (8 * freArr[count]);
        cout << '\t' << chArr[count]
             << '\t' << freArr[count] << '\n';
        count++;
    }
    /**********************************************************************************************/


    HuffmanCodes(chArr, freArr, size);   /*Build Huffman Code*/



    /*Compress File(s) */
    writeToFile = true;
    bin = true ;
    fileName = "dst.bin";
    readFile("src.txt");
    cout <<  "" << endl ;
    compressionRatio();
    bin = false ;

    /* Decompress File(s) */
    readCompFile = true;
    fileName = "decoded.txt";
     readFile("dst.bin");

    if (option == 0) {
        decompressFolder(files);  //Decompress the Folder
    }


    free(chArr);
    free(freArr);

    return 0;
}