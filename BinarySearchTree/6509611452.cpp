/*
	Name: Natanan Phopradit
	Student ID: 6509611452
*/

#include <iostream>
#include <ctype.h>
#include <fstream>
#include <string>
#include <deque>
#include <cstddef>
#include <algorithm>
#include <iomanip>

using namespace std;

class BinarySearchTree {
protected:
	struct Node {
		string data;
		deque<int>* indices;
		BinarySearchTree* left;
		BinarySearchTree* right;

		Node(string data, int index) {
			this->data = data;
			indices = new deque<int>;
			indices->push_back(index);
			left = right = NULL;
		}
	};
	Node* root = NULL;

public:
	BinarySearchTree() {
		root = NULL;
	}

	BinarySearchTree(string data, int index) {
		root = new Node(data, index);
		root->left = new BinarySearchTree();
		root->right = new BinarySearchTree();
	}

	void insertNode(string data, int index) {
		if (root == NULL) {
			root = new Node(data, index);
			root->left = new BinarySearchTree();
			root->right = new BinarySearchTree();

		}

		else if (root->data == data) {
			root->indices->push_back(index);
		}

		else if (root->data < data) {
			root->right->insertNode(data, index);
		}
		else {
			root->left->insertNode(data, index);
		}
	}

	void insertNodesFromFile(string filePath) {
		ifstream* file = new ifstream(filePath);
		if (!file->is_open()) {
			throw filePath + " file is not found";
			return;
		}
		string line;
		int lineCount = 0;

		while (getline(*file, line)) {
			if (line != "") {
				lineCount++;
				transform(line.begin(), line.end(), line.begin(), ::tolower);
				char seps[] = " .,;()\"'-_1234567890\t\n\r";
				char* token1 = NULL;
				char* next_token1 = NULL;

				token1 = strtok_s((char*)line.c_str(), seps, &next_token1);

				// While there are tokens in "string1" or "string2"
				while ((token1 != NULL))
				{
					// Get next token:
					if (token1 != NULL)
					{
						if ((string)token1 != "a" && (string)token1 != "an" && (string)token1 != "the") {
							insertNode(token1, lineCount);
						}
						token1 = strtok_s(NULL, seps, &next_token1);
					}
				}
			}
		}
	}

	void printTreeBeginWith(string letter) {
		if (root != NULL) {
			root->left->printTreeBeginWith(letter);
			if (root->data[0] == (char)tolower(letter[0])) {
				cout << "\t" << setw(20) << left << root->data << "   ";
				for_each(root->indices->begin(), root->indices->end(), [](int& n) {
					cout << setw(3) << n << " ";
					});
				cout << endl;
			}
			root->right->printTreeBeginWith(letter);
		}
	}

	void printTreeFromFile(string filePath) {
		try
		{
			insertNodesFromFile(filePath);
			transform(filePath.begin(), filePath.end(), filePath.begin(), ::toupper);
			cout << "====================" + filePath + "====================" << endl;
			for (int i = 0; i < 26; i++) {
				string character(1, toupper('a' + i));
				cout << character << endl;
				printTreeBeginWith(character);
			}
		}
		catch (string error)
		{
			cerr << error << endl;
		}
	}

	void printTree() {
		for (int i = 0; i < 26; i++) {
			string character(1, toupper('a' + i));
			cout << character << endl;
			printTreeBeginWith(character);
		}
	}
};

int main(int argc, char** argv) {
	BinarySearchTree* tree = new BinarySearchTree();
	tree->printTreeFromFile("document.txt");
	tree->printTree();
}