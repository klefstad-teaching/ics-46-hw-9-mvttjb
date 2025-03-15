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

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Words must be different");
        return {};
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;
    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string &word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder; // returns word ladder
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};  // returns empty
}

void load_words(set<string> &word_list, const string &file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower); // handle uppercase characters
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string> &ladder) {
    if (ladder.empty()) cout << "No word ladder found." << endl;
    else {
        for (size_t i = 0; i < ladder.size(); ++i) {
            if (i > 0) cout << " -> ";
            cout << ladder[i];
        }
        cout << endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "./src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
