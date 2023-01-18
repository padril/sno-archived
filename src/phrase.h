#ifndef PHRASE_H
#define PHRASE_H

#include <string>
#include <list>
#include <iostream>
#include <tuple>
#include <vector>

class Phrase {
public:
	enum Token;

	struct PhraseType {
		std::vector<Token> tokens;
		std::list<void*> literals;
	};

	struct TypedPtr {
		void* ptr;
		Phrase::Token type;
	};

	std::vector<void*> data;

	Phrase(const std::string& expression);
	Phrase(const char* expression);
	Phrase(std::list<Token> token_list);
	Phrase(const Phrase& other);

	~Phrase();
	
private:
	PhraseType parse(const std::string& str);
	TypedPtr evaluate(std::vector<Phrase::Token> token_list, std::list<void*>& literal_list, bool terminating = false);

	int t = 0; // used for int&pos

	std::string expression;
	PhraseType phrase;
	std::string result;
};


#endif
