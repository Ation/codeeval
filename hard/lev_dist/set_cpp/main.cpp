#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

template<class _Voc = unordered_set<string> >
class FriendsCounter {
public:
    FriendsCounter(_Voc& _vocabulary, const string word) : m_count(0), m_vocabulary(_vocabulary) {
        m_usedWords.insert(word);
    }

    ~FriendsCounter() {}

    bool addFriend(const string &friendWord) {
        bool result = false;

        if (m_vocabulary.find(friendWord) != m_vocabulary.end()) {
            if (m_usedWords.find(friendWord) == m_usedWords.end()) {
                m_count++;
                m_usedWords.insert(friendWord);

                result = true;
            }
        }

        return result;
    }

    int getFriendsCount() const { return m_count; }

private:
    int                     m_count;
    _Voc&                   m_vocabulary;
    unordered_set<string>   m_usedWords;
};

class VocabularyContainer {
public:
    VocabularyContainer() {}
    VocabularyContainer(const VocabularyContainer&) = delete;

    void insert(const string &word) {
        if (word.length() <= _prefix_length) {
            m_words.insert(word);
        } else {
            string prefix;
            string left;

            split(word, prefix, left);

            m_vocabulary[prefix].insert(left);
        }
    }

    bool end() const {
        return false;
    }

    bool find(const string &word) {
        if (word.length() <= _prefix_length) {
            return m_words.find(word) != m_words.end();
        } else {
            string prefix;
            string left;

            split(word, prefix, left);

            auto _c = m_vocabulary.find(prefix);
            if (_c != m_vocabulary.end()) {
                return _c->second.find(left) != _c->second.end();
            }
            return false;
        }
    }

    unsigned int getWordsCount() const {
        return m_words.size();
    }

    unsigned int getPrefixCount() const {
        return m_vocabulary.size();
    }
private:
    const unsigned int _prefix_length = 3;

    unordered_set < string > m_words;
    unordered_map < string, unordered_set < string > > m_vocabulary;

    void split(const string &word, string &prefix, string &left) {
        prefix = word.substr(0, _prefix_length);
        left = word.substr(_prefix_length);
    }

};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    const string marker = "END OF INPUT";

    VocabularyContainer       vocabulary;
    list<string>                test_cases;

    if ( ! inFile.is_open() ) {
        return 1;
    }

    // reading the test cases
    while ( getline(inFile, inputLine)) {
        if ( marker == inputLine) {
            break;
        }

        test_cases.push_back(inputLine);
    }

    // reading the vocabulary
    while ( getline(inFile, inputLine)) {
        vocabulary.insert(inputLine);
    }

    for(auto&& test_case : test_cases) {
        list<string>            words_to_check;
        FriendsCounter< VocabularyContainer >          counter(vocabulary, test_case);

        words_to_check.push_back(test_case);
        string check_this;

        while (!words_to_check.empty()) {
            string& word = words_to_check.front();

            const int length = word.length();

            // check the removals
            if (length > 1) {
                // check without first symbol
                check_this = word.substr(1, length - 1);
                if (counter.addFriend(check_this)) {
                    words_to_check.push_back(check_this);
                }

                for (int i=1; i < length - 1; i++) {
                    check_this = word.substr(0, i) + word.substr(i+1, length - i - 1);
                    if (counter.addFriend(check_this)) {
                        words_to_check.push_back(check_this);
                    }
                }

                // check without last symbol
                check_this = word.substr(0, length - 1);
                if (counter.addFriend(check_this)) {
                    words_to_check.push_back(check_this);
                }
            }

            // check the replacement
            for (int i=0; i < length; i++) {
                const char originalSymbol = word[i];
                check_this = word;

                for (char symbol = 'a'; symbol <= 'z'; ++symbol) {
                    if (originalSymbol != symbol) {
                        check_this[i] = symbol;
                        if (counter.addFriend(check_this)) {
                            words_to_check.push_back(check_this);
                        }
                    }
                }
            }

            // check the additions
            check_this.assign("a");
            check_this.append(word);

            for (char symbol = 'a'; symbol <= 'z'; ++symbol) {
                check_this[0] = symbol;
                if (counter.addFriend(check_this)) {
                    words_to_check.push_back(check_this);
                }
            }

            for (int i=1; i < check_this.length() - 1; ++i) {
                string left = word.substr(0, i);
                string right = word.substr(i, check_this.length() - i);

                check_this.assign(left);
                check_this.push_back('a');
                check_this.append(right);

                for (char symbol = 'a'; symbol <= 'z'; ++symbol) {
                    check_this[i] = symbol;
                    if (counter.addFriend(check_this)) {
                        words_to_check.push_back(check_this);
                    }
                }
            }


            check_this.assign(word);
            check_this.push_back('a');

            int index = check_this.length() - 1;
            for (char symbol = 'a'; symbol <= 'z'; ++symbol) {
                check_this[index] = symbol;
                if (counter.addFriend(check_this)) {
                    words_to_check.push_back(check_this);
                }
            }

            words_to_check.pop_front();
        }

        cout << counter.getFriendsCount() + 1 << endl;
    }

    return 0;
}
