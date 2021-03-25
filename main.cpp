#include "automata.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	//  if (argc != 2) {
	//    cout << "Usage: main filename" << endl;
	//    return 1;
	//  }

	// open input file
//	ifstream inputFile(argv[1]);
//	ifstream inputFile(R"(C:\Users\aless\Downloads\Automi\labTest\tests\test1)");
	//  if (inputFile.fail()) {
	//    // file open error
	//    cout << "Error while reading file " << argv[1] << endl;
	//    return 1;
	//  }
	// read file into a string
//	string inputProgram((istreambuf_iterator<char>(inputFile)),
//	                    (istreambuf_iterator<char>()));
	
//	string inputProgram = "repeat";
//	string inputProgram = "Repeat";
	string inputProgram = "(*repea\n\nt//*)";
//	string inputProgram = "{ blah } vlah }";
//	string inputProgram = "//foo\n";
	cout << "Input: " << inputProgram << endl;
	// close input file
//	inputFile.close();
	// Try to recognize with automaton for "repeat"
//	WordDFA repeatDFA("repeat");
//	cout << "REPEAT: " << repeatDFA.run(inputProgram) << endl;
	// Try to recognize with automaton for comments
	CommentDFA commentDFA;
	cout << "COMMENT: " << commentDFA.run(inputProgram) << endl;

	return 0;
}
