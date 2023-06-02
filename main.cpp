#include "header.h"

int main() {
    string filename;

    cout << "-----------------------------------------------------------------------" << endl;
    do {
        cout << "Failu sarasas: ";
        system("ls *.dat");
        cout << "Pasirinkite faila: ";
        cin >> filename;

        ifstream file(filename);
        if(file.is_open()) {
            cout << "-----------------------------------------------------------------------" << endl;
            
            map<string, int> wordCounts;
            map<string, vector<int>> wordOccurrences;
            vector<string> urls;
            map<string, vector<int>> wordLineCounts;

            string line;
            int lineNumber = 1;
            
            regex urlRegex("(https?|ftp)://[^\\s/$.?#].[^\\s]*");
            while (getline(file, line)) {
                istringstream iss(line);
                string word;

                while (iss >> word) {
                    string sanitizedWord = cleanWord(word);

                    if (sanitizedWord.empty() || regex_match(word, urlRegex))
                        continue;
                    if (!isPunctuation(sanitizedWord[0]) && sanitizedWord.size() > 1) {
                        ++wordCounts[sanitizedWord];
                        wordOccurrences[sanitizedWord].push_back(lineNumber);
                        wordLineCounts[sanitizedWord].push_back(lineNumber);
                    }
                }

                ++lineNumber;
            }
            file.close();

            // Išveda žodžius ir jų kiekį tekste
            wordCount(wordCounts);

            // Išveda žodžius ir jų vietą (eilutės numerį) tekste
            wordLocation(lineNumber, wordOccurrences, wordLineCounts);

            // Išveda surastus puslapių adresus tekste
            ifstream inputFile("tekstas.dat");
            if (inputFile.is_open()) {
                stringstream buffer;
                buffer << inputFile.rdbuf();

                string text = buffer.str();
                int i = 1;

                vector<string> urls = findURLs(text);

                cout << "Rasti puslapiu adresai:" << endl;
                for (const string& url : urls) {
                    cout << i++ << ". " << url << endl;
                }
            } else {
                cout << "Nepavyko atidaryti failo." << endl;
            }
            inputFile.close();

            break;
        } else {
            cerr << endl << "Tokio failo [" << filename << "] nera." << endl;

            continue;
        }
    } while (true);

    cout << "-----------------------------------------------------------------------" << endl;

    return 0;
}
