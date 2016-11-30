// Name: Pearson, Matthew
// Project: 3B

#include "morse.h"

int main() {
	Message output;
	string morse, text;
	Message::openMorse();
	cout << string(100, '*') << endl;
	cout << "Welcome to the Morse code encoder/decoder! \n\n";
	cout << "Options:\n";
	int choice = 0;
	char tmp;
	cout << "1. Encode Message\n2. Decode Message\n3. Exit\n" << endl;
	cout << "Enter an option: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		text = Message::openMessage();
		cout << "\n\n\nEncoded message:\n\n";
		output.encode(text, morse);
		cout << morse << "\n\n";
		system("pause");
		Message::removeNodes();
		return 0;
	case 2:
		morse = Message::openMessage();
		cout << "\n\n\nDecoded message:\n\n";
		output.decode(morse, text);
		cout << text << "\n\n";
		system("pause");
		Message::removeNodes();
		return 0;
	case 3:
		cout << "Thanks. Bye." << endl;
		system("pause");
		Message::removeNodes();
		return 0;
	}
}