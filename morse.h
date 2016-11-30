// Name: Pearson, Matthew
// Project: 3B

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct LNODE { // "L" letter node

	char letter;
	string morseCode;
	LNODE *Next;
	LNODE(char c, const string &str) : letter(c), morseCode(str), Next(0) {}
};

struct TNODE { // "T" text node

	char letter;
	TNODE *Left;
	TNODE *Right;
	TNODE() : letter('*'), Left(0), Right(0) {}
};

class Message {

public:
	static string openMessage();
	static void openMorse();
	static void removeNodes();
	void encode(const string &text, string &morse);
	void decode(const string &morse, string &text);

private:
	static TNODE *morseRoot;
	static LNODE *morseHead;
	static void removeRoots(TNODE *root);
	static void insertNodes(char letter, const string &morseCode);
};