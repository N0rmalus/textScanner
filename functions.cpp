#include "header.h"

bool isPunctuation(char c) { // Funkcija skirta patikrinti, ar simbolis yra skyrybos ženklas
    return (c == ',' || c == '.' || c == '?' || c == '!' || c == ':' || c == ';' || c == '(' || c == ')' || c == '"' || c == '\'' || c == '-');
} 
bool isWordCharacter(char c) { // Funkcija skirta patikrinti, ar simbolis yra dalis žodžio
    return (isalpha(c) || c == '\'');
}

// Funkcija, kuri suranda URL adresus tekste
vector<string> findURLs(const string& text) {
    regex urlRegex("[(http(s)?):\\/\\/(www\\.)?a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");
    smatch urlMatch;
    vector<string> urls;

    string::const_iterator searchStart = text.begin();
    while (regex_search(searchStart, text.end(), urlMatch, urlRegex)) {
        string url = urlMatch.str(0);

        // Patikriname, ar URL adresas nėra dokumento arba nuotraukos tipo
        regex extensionRegex(R"(\.(txt|pdf|doc|docx|jpg|tiff|dng|jpeg|png|svg|gif))", std::regex_constants::icase);
        if (!regex_search(url, extensionRegex)) {
            urls.push_back(url);
        }

        searchStart = urlMatch.suffix().first;
    }

    return urls;
}


// Funkcija skirta konvertuoti žodį į mažąsias raides ir pašalinti skyrybos ženklus
string cleanWord(const string& word) {
    string sanitized;
    for (char c : word) {
        if (isWordCharacter(c))
            sanitized += tolower(c);
    }
    return sanitized;
}

// Išveda žodžius ir jų kiekį tekste
void wordCount(map<string, int> wordCounts) {
    ofstream count("word_count.txt");
    vector<pair<string, int>> sortedWordCounts;
    for (const auto& pair : wordCounts) {
        if (pair.second > 1) {
            sortedWordCounts.push_back({pair.first, pair.second});
        }
    }

    sort(sortedWordCounts.begin(), sortedWordCounts.end(),
              [](const pair<string, int>& a, const pair<string, int>& b) {
                  return a.second > b.second;
              });

    count << left << setw(31) << "Žodis" << "Kiekis" << endl;
    count << setfill('-') << setw(36) << "" << endl;
    count << setfill(' ');

    for (const auto& pair : sortedWordCounts) {
        count << left << setw(30) << pair.first << pair.second << endl;
    }

    count.close();
}

// Išveda žodžius ir jų vietą (eilutės numerį) tekste
void wordLocation(int lineNumber, map<string, vector<int>> wordOccurrences, map<string, vector<int>> wordLineCounts) {
    ofstream output("word_location.txt");
    output << setw(15) << left << "Žodis";
    for (int i = 1; i <= lineNumber; ++i) {
        output << setw(5) << left << i;
    }
    output << endl << setfill('-') << setw(16 + 5 * lineNumber) << "" << endl << setfill(' '); 

    for (const auto& pair : wordOccurrences) {
        output << setw(15) << left << pair.first;
        
        vector<int> occurrences = wordLineCounts[pair.first];
        vector<bool> lineFlags(lineNumber, false);

        for (int line : occurrences) {
            lineFlags[line - 1] = true;
        }

        for (bool flag : lineFlags) {
            if (flag)
                output << setw(5) << left << "*";
            else
                output << setw(5) << left << "";
        }

        output << endl;
    }
}

