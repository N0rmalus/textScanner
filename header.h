#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <regex>

using std::vector;
using std::string;
using std::smatch;
using std::regex;
using std::pair;
using std::map;
using std::cin;
using std::cout;
using std::cerr;
using std::left;
using std::setw;
using std::endl;
using std::setfill;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::istringstream;

bool isPunctuation(char c);
bool isWordCharacter(char c);
vector<string> findURLs(const string& text);
string cleanWord(const string& word);
void wordCount(map<string, int> wordCounts);
void wordLocation(int lineNumber, map<string, vector<int>> wordOccurrences, map<string, vector<int>> wordLineCounts);