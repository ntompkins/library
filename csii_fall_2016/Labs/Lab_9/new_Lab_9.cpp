#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

struct WordCount {
	string word;
	int count;
	WordCount(string s) { word = s; count = 1; }
};

struct WordCountSortCompare {
    bool operator ()(WordCount const& wc1, WordCount const& wc2) const {
    	return (wc1.word < wc2.word) ? true : false;
    }
};

std::string GetTextFileName();					      // Prompt user for file name and validate
std::string ReadTextFile (std::string);				// Read contents of text file into string
std::string Normalize    (std::string);				// Convert string to lowercase and remove punctuation

vector<WordCount> DistinctWords(string);	// Build sorted vector of word count structures
int FindWord (string, vector<WordCount>);	// Linear search for word in vector of structures

int main() 
{
	cout << "Lab 9 - Word Counter" << endl
	     << "--------------------" << endl;
	std::string filename = GetTextFileName();
	while(filename != "") 
	{
	  // Don't read a file that doesn't exist -- throw an error in previous function?
		std::string contents = ReadTextFile(filename);
		cout << endl << "This is the text string read from " << filename << endl;
		cout << "---------------------------------------------------" << endl;
		
	  cout << contents << endl << endl;
		
		vector<WordCount> words = DistinctWords(contents);
		cout << "There are " << words.size() << " unique words in the above text."<< endl;
		cout << "--------------------------------------------" << endl;
		for(WordCount wc : words) 
		{
			string times = (wc.count == 1 ) ? "time" : "times";
			cout << "The word \"" << wc.word << "\" occurs " << wc.count << " " << times << "." << endl;
		}
		filename = GetTextFileName();
	}
	return 0;
}

string GetTextFileName() {
	cout << "Enter a file name: "; 
	string name = ""; 
	getline(cin, name);
	ifstream usrFile(name);
	
	if (usrFile) cout << name << " was successfully opened.\n";
	else if (name == "") return name;
	else cout << name << " was not found.\n";
	return name;
}

vector<WordCount> DistinctWords(string s) {
	// Normalize and grab all the words
	stringstream all_words(Normalize(s));

    // Push all the words into the vector	
	vector<string> sorted;
	string current_word = "";
	do {
	    current_word = "";
	    all_words >> current_word;
	    if(current_word != "") {
	        sorted.push_back(current_word);
	    }
	} while (all_words);
	
	// Sort vector of words
	sort(sorted.begin(), sorted.end());
	
	current_word = "";
	// Push sorted words into WC vector
	vector<WordCount> final_words;
	for (int i = 0; i != sorted.size(); i++) {
	    int index = FindWord(current_word, final_words);
	    if (index == -1) {
	        // Add the word if its not in the vector
	        WordCount wc(current_word);
	        final_words.push_back(wc);
	    } else {
	        // Increase the count if the word's already in the vector
	      final_words[index].count += 1;  
	    }
	       
	}
	
	
// 	// string stream to feed into vector
// 	stringstream contents(Normalize(s)); 
// 	// Move all the strings into a vector
// 	string word="";
// 	do {
// 	  word="";
//     contents >> word;
//     if(word != "")
//       holder.push_back(word);
// 	} while (contents);
	
// 	// Sort the string vector
// 	sort(holder.begin(), holder.end());
	
//   // Populate the struct vector
//   vector<WordCount> words;
//   for(int index = 0; index != holder.size(); ++index) {
//     int location = FindWord(word, words);
//     if( index == -1 ) {
//       WordCount wc(word);
//       words.push_back(wc);
//     } 
//     else {
//       words[location].count += 1;
//     }
//   }
  return final_words;
  
}

string Normalize(string s) {
  string y = "";
  for (char& x : s) {
	  (ispunct(x)) ? y += ' ' : y += tolower(x);
    }
  return y;
}

int FindWord(string w, vector<WordCount> v) {
	int result = -1;
	for (int i = 0; i < v.size(); i++) {
	  if(w == v.at(i).word)
	    result = i;
	}
	return result;
}

string ReadTextFile(string filename) {
	// Open user's file
	std::ifstream infile(filename);
	std::string contents;
	// Read each line into the string
	for (std::string line; getline(infile, line);) {
	  contents += line;
	}
	return contents;
}