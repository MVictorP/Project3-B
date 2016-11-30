// Name: Pearson, Matthew
// Project: 3B

#include "morse.h"

TNODE *Message::morseRoot = 0;
LNODE *Message::morseHead = 0;

string Message::openMessage() { // read data from file into Message object

	string line;
	string messageData;
	ifstream file;
	file.clear();
	file.open("text2morse.txt"); // contains text to be converted to morse
	//file.open("morse2text.txt"); // contains morse code to be converted to text

	if (!file) // if no file show error
	{
		cerr << "\n\nError: No File With That Name!\n";
		system("pause");
		return 0;
	}
	while (getline(file, line))
	{
		messageData += line;
	}
	cout << "\nOriginal message:\n\n";
	cout << messageData;
	return messageData;
}

void Message::openMorse() { // create a tree to be used for encoding and decoding

	char tmpLetter; // create a temporary letter
	string tmpMorseCode; // create a temporary code

	morseHead = new LNODE(' ', ""); // create a new head
	morseRoot = new TNODE; // create a new root

	if (!morseRoot) // if unable to find root return
	{
		return;
	}
	morseRoot->letter = ' '; // start with blank

	ifstream file;
	file.clear();
	file.open("morse.txt"); // name of file to be used for decoding and encoding
	if (!file) // if no file show error
	{
		cerr << "\n\nError: No File With That Name!\n";
		system("pause");
		exit(0);
	}
	while (!file.eof())
	{
		file >> tmpLetter >> tmpMorseCode;
		tmpLetter = toupper(tmpLetter); // convert to upper case
		insertNodes(tmpLetter, tmpMorseCode); // insert the nodes until the end of file is reached
	}
}

void Message::removeNodes() { // removes the binary tree

	LNODE *Node = morseHead; // node that starts at head
	LNODE *Next = 0;
	while (Node) // will continue until head is NULL
	{
		Next = Node->Next;
		delete Node;
		Node = Next;
	}
	morseHead = NULL; // sets head to NULL
	removeRoots(morseRoot); // removes roots
	morseRoot = 0; // sets root to NULL
}

void Message::removeRoots(TNODE *root)
{
	if (!root)
	{
		return;
	}
	else if (root->Right) // check if there is a right subtree
	{
		removeRoots(root->Right); // removes subtree
		delete root;
	}
	else if (root->Left) // check if there is a left subtree
	{
		removeRoots(root->Left); // removes subtree
		delete root;
	}
}

void Message::insertNodes(char letter, const string &morseCode) // insert morse code nodes into the tree
{
	LNODE *LNode;
	LNode = morseHead;

	while (LNode->Next)
	{
		LNode = LNode->Next;
	}
	LNode->Next = new LNODE(letter, morseCode);
	TNODE *TNode = morseRoot;

	for (int i = 0; i < (signed)morseCode.length(); i++)
	{
		if (morseCode[i] == '.') // if dot
		{
			if (!TNode->Left) // Goes left in subtree if dot
			{
				TNode->Left = new TNODE(); // create new node
			}
			TNode = TNode->Left; // move TNode left of the new node
		}
		else // if a dash
		{
			if (!TNode->Right) // goes left in subtree if dash
			{
				TNode->Right = new TNODE(); // create new node
			}
			TNode = TNode->Right; // move TNode right of new node
		}
	}
	TNode->letter = letter; // assign letter
}

void Message::encode(const string &text, string &morse)
{
	LNODE *LNode;
	char ch;
	morse = ""; // create empty string
	for (int i = 0; i < (signed)text.length(); i++)
	{
		ch = toupper(text[i]); 
		for (LNode = morseHead; LNode; LNode = LNode->Next) // search for letter in tree
		{
			if (LNode->letter == ch)
			{
				break;
			}
		}
		if (LNode) // add the code to the morse string
		{
			morse += LNode->morseCode + ' ';
		}
	}
}

void Message::decode(const string &morse, string &text)
{
	TNODE *TNode;
	text = ""; // create empty string
	TNode = morseRoot;
	for (int i = 0; i < (signed)morse.length(); i++)
	{
		if (morse[i] == '.') // if a dot is found
		{
			TNode = TNode->Left; // go left in tree
		}
		if (morse[i] == '_') // if dash is found
		{
			TNode = TNode->Right; // go right in tree
		}
		if (morse[i] == ' ') // if space is found
		{
			text += TNode->letter; // add the letter to the text string
			TNode = morseRoot; // set TNode to next letter
		}
	}
	text += TNode->letter; // if end of input is found, add the letter to the text string
}