#include "./ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    int i = 0, j = 0, edits = 0;

    if (abs(len1 - len2) > d) return false;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++edits > d) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else { i++; j++; }
    }
    return (edits + abs(len1 - i) + abs(len2 - j)) <= d;
}

bool is_adjacent(const string &word1, const string &word2) {
    return edit_distance_within(word1, word2, 1); // returns if adjacent (d = 1)
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Could not open file " << file_name << endl;
    }
    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower); // handle uppercase characters
        word_list.insert(word);
    }
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list) {
    
}
