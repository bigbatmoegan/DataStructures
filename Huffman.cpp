#include <ctype.h>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;
//used to directly write to file as needed instead of creating one when needed
static ofstream ofs("codetable.txt");

//node class
class Node {
	public:
		int freq;
		char ch[100];
		Node *left, *right;
		Node();
		~Node();
};

//constructor
Node::Node() {
}

//destructor
Node::~Node() {
}

//tree class
class Tree {
	public:
		Tree();
		map<char*,vector<int>> Map;
		void sort(Node *[], int);
		Node *createNode(char[], int);
		void right(Node *[], int);
		void assignCode(Node*, int[], int);
		void listCode();
};

//tree constructor
Tree::Tree() {
}

//sort the nodes on the tree
void Tree::sort(Node *a[], int n)
{
    int i, j;
    Node* temp;
    
    for (i = 0; i < n - 1; i++)
        for (j = i; j < n; j++)
			//check if next node is smaller and move if needed
            if (a[i]->freq > a[j]->freq)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
}

//create a new node 
Node *Tree::createNode(char chars1[], int freq1)
{
    Node* n;
    n = new Node;
    n->freq = freq1;
    strcpy( n->ch , chars1);
    n->right = n->left = NULL;
    return(n);
}

//move nodes to the right on the tree
void Tree::right(Node* x[], int a) {
	for(int i=1; i<a-1; i++) {
		x[i]=x[i+1];
	}
}

//get the code for each node
void Tree::assignCode(Node* tree, int code[], int n) {
	int i=0;
    if ((tree->left == NULL) && (tree->right == NULL))
    {
        vector<int> temp;
        for (i = 0; i < n; i++)
        {
            temp.push_back(code[i]);
        }
        std::pair<char*,vector<int> > pair (tree->ch,temp);
        Tree::Map.insert(pair);
    }
    else
    {
        code[n] = 0;
        n++;
        assignCode(tree->left, code, n);
        code[n - 1] = 1;
        assignCode(tree->right, code, n);
    }
}

//write the code to the codetable.txt file
void Tree::listCode() {
	ofs << "Letter | Code" << endl;
	ofs << "-------------" << endl;
	for (std::map<char*,vector<int> >::iterator it = Tree::Map.begin();it!=Tree::Map.end();++it){
        //check if end of a line
		if (it->first[0] == '\n') {
            ofs << "LF  | ";
        }
        else
        {
            ofs << "" << it->first << "   | ";
        }
        
        for (int i = 0; i < it->second.size(); i++) {
            ofs << it->second.at(i);
        }
        ofs << endl;
    }
}


int main()
{
    int i, letterUsed=0, q=0, u, freq[256], code[256];
    char letters[2], str[100], inChar;
    Node *pTree, *trNode[255];
    Tree treeObj;
    ifstream inFile;
    string line = "";
    int idx=0;
	//get the file from the directory
    inFile.open("test.txt");
    if (!inFile)
    {
        cout<<"Error: File couldn't be open\n";
    }
    for(i=0; i<=255; i++)
        freq[i]=0;
    while (getline(inFile, line)) {
        if (line.find("LF") != std::string::npos) {
            freq[(int)'\n']=line.c_str()[3]-'0';
		}
        else{
            char letter;
            string occurances="";
            while (line.c_str()[idx] != '\0') {
                if (idx == 0) {
                    letter = line.c_str()[idx];
                }
                else{
                    occurances += line.c_str()[idx];
                }
                idx++;
            }
            freq[(int) letter] = atoi(occurances.c_str());
            idx=0;
        }
    }
    for(i=0; i<255; i++)
        if(freq[i]!=0)
            letterUsed++;
    cout << "Character Frequencies: " << endl;
    for (i=0; i<letterUsed; i++)
    {
        while ((freq[q]==0)&&(q<255))
            q++;
        letters[0]=q;
        letters[1]='\0';
        if (letters[0] == '\n') {
            cout<<"LR"<<","<<freq[q]<<endl;
        }
        else
            cout<<letters[0]<<","<<freq[q]<<endl;
        trNode[i] = treeObj.createNode(letters, freq[q]);
        q++;
    }
    // construct the huffman tree
    while (letterUsed > 1) // for each letter
    {
        // sort the tree for each letter
        treeObj.sort(trNode, letterUsed);
        u = trNode[0]->freq + trNode[1]->freq;
		//add the first two no madder what
        strcpy(str, trNode[0]->ch);
        strcat(str, trNode[1]->ch);
		//make a new node 
        pTree = treeObj.createNode(str, u);
		//the bigger one gets the right pointer
        pTree->right = trNode[1];
		//smaller one gets the left one
        pTree->left = trNode[0];
        trNode[0] = pTree;
		//shift so we can decrease the number of letters used
        treeObj.right(trNode, letterUsed);
        letterUsed--;
    }
    treeObj.assignCode(trNode[0], code, 0);
    treeObj.listCode();
    cout << "Open codetable.txt for output." << endl;
    cout<<endl<<endl;
    return 0;
}