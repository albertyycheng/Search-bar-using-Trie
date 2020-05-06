#include <iostream>
#include <string>
#include <fstream>
using namespace std;



class Node
{
	friend class Trie;
private:
	char c;
	bool word; 
	Node* child[128]; 
public:
	Node() 
	{
	this->setChar('\0');
	this->setWord(false);
	for (int i = 0; i < 128; i++)
		this->child[i] = NULL;
	}
	
	~Node() {}
	void setWord(int i) {this->word = i;} 
	bool isWord() {return this->word;}
	void setChar(char ch) {this->c = ch;}
	char getChar() const {return this->c;}
};

class Trie
{
	friend class Node;
private:
	bool space; 
	string no_prefix; 
	Node* root;
public:
	Trie() {root = new Node(); this->space = false;}
	~Trie() {}
	void is_space(string data) 
	{
	char cstr[data.length()];

	data.copy(cstr, data.length());
	for (int i = 0; i < data.length(); i++)
	{
		if (cstr[i] == ' ')
		{
			space = true;
			return;
		}
		else
			continue;
	}
	}
	
	bool getSpace() {return space;}
	
	void insert(string data) 
	{
		Node* tmp = root;
		char cstr[data.length()];
		
		data.copy(cstr, data.length()); 
		for (int i = 0; i < data.length(); i++)
		{
			if (tmp->child[static_cast<int>(cstr[i])] != NULL) 
				tmp = tmp->child[static_cast<int>(cstr[i])];
			else
			{
				tmp->child[static_cast<int>(cstr[i])] = new Node(); 
				tmp = tmp->child[static_cast<int>(cstr[i])];
				tmp->setChar(cstr[i]); 
			}
		}
	tmp->setWord(true); 
	}; 
	
	void search(string data) 
	{
	Node* tmp = root;
	char cstr[data.length()];

	data.copy(cstr, data.length(), 0); 
	for (int i = 0; i < data.length(); i++) 
	{
		if (tmp->child[static_cast<int>(cstr[i])] == NULL) 
		{
			cout << "String not found" << endl;
			return;
		}
		else
			tmp = tmp->child[static_cast<int>(cstr[i])];
		if (tmp->getChar() != cstr[i])  
		{
			cout << "String not found" << endl;
			return;
		}
	}
	string str = data; 
	print_tree(tmp, data, str);	
	}
	
	void print_tree(Node* root, string data, string str) 
	{	
	for (int i = 0; i < 128; i++) 
	{
		Node* adv = root;
		if (adv->child[i] != NULL) 
		{
			adv = adv->child[i]; 
			str += adv->getChar(); 
			if (adv->isWord()) 
			{
				if (this->getSpace() == true) 
					cout << this->getNo_prefix();
				cout << str << endl;
			}
			print_tree(adv, str); 
		}
		str = data; 
	}
	}; 
	
	void print_tree(Node* root, string str) 
	{
	string str_tmp = str;

	for (int i = 0; i < 128; i++)
	{
		Node* adv = root;
		if (adv->child[i] != NULL)
		{
			adv = adv->child[i];
			str += adv->getChar();
			if (adv->isWord())
			{
				if (this->getSpace() == true)
					cout << this->no_prefix;
				cout << str << endl;
			}
			print_tree(adv, str);
		}
		str = str_tmp;
	}
	};
	
	void remove_prefix(string data) 
	{
	char cstr[data.length()];
	data.copy(cstr, data.length());

	for (int i = data.length(); i-- > 0;) 
	{
		if (cstr[i] == ' ') 
			break;
		else
			cstr[i] = '\0'; 
	}
	no_prefix = cstr; 
	}
	string getNo_prefix() {return no_prefix;}
	
	string break_string(string data) 
	{
	char cstr[data.length()];
	string str;
	data.copy(cstr, data.length());

	for (int i = data.length(); i-- > 0;) 
	{
		if (cstr[i] == ' ') 
			 break;
		else
			str.insert(str.begin(),cstr[i]); 
	}
	return str; 
	}
};

int main(int argc, char const *argv[])
{
	string data;
	fstream dictionary;
	Trie myQuery;

	dictionary.open("dictionary.txt", fstream::in); 
	if (dictionary.is_open())
	{	
		while (dictionary)
		{
			dictionary >> data;
			myQuery.insert(data);
		}
	}	
	else
	{
		cout << "File did not open" << endl;
		return -1;
	}
	dictionary.close();
	data.clear(); 
	cout << "Please type your search query:" << endl;
	getline(cin, data); 
	myQuery.is_space(data); 
	cout << "Your options are:  " << endl;
	if (myQuery.getSpace() == true) 
	{
		myQuery.remove_prefix(data);
		myQuery.search(myQuery.break_string(data));
	}
	else
		myQuery.search(data);
	return 0;
} 	
