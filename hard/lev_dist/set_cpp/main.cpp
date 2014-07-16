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

class CharHasher {
public:
    explicit CharHasher(size_t length) : m_length(length) {
    }

    CharHasher(): m_length(0) {
    }

    CharHasher(const CharHasher& src) : m_length(src.m_length) {
    }

    inline size_t operator() (const char* str) const {
        if (m_length == 0) {
            cout << "CharHasher default!" << endl;
        }

#if defined(_M_X64) || defined(_LP64) || defined(__x86_64) || defined(_WIN64)
        const size_t _FNV_offset_basis = 14695981039346656037ULL;
        const size_t _FNV_prime = 1099511628211ULL;

 #else /* defined(_M_X64), etc. */
        const size_t _FNV_offset_basis = 2166136261U;
        const size_t _FNV_prime = 16777619U;
 #endif /* defined(_M_X64), etc. */

        size_t _Val = _FNV_offset_basis;
        for (size_t _Next = 0; _Next < m_length; ++_Next) {
           // fold in another byte
            _Val ^= (size_t)str[_Next];
            _Val *= _FNV_prime;
        }

 #if defined(_M_X64) || defined(_LP64) || defined(__x86_64) || defined(_WIN64)
        _Val ^= _Val >> 32;
 #endif /* defined(_M_X64), etc. */

        return (_Val);
    }
private:
    size_t m_length;
};

class CharCompare {
public:
    explicit CharCompare(size_t length) : m_length(length) {
    }

    CharCompare(): m_length(0) {
    }

    CharCompare(const CharCompare& src) : m_length(src.m_length) {
    }

    bool operator() (const char *str1, const char* str2) const {
        if (m_length == 0) {
            cout << "CharCompare default!" << endl;
        }
        for (size_t i=0; i < m_length; ++i) {
            if (str1[i] != str2[i]) {
                return false;
            }
        }
        return true;
    }
private:
    size_t m_length;
};

class CharVocabulary {
public:
    CharVocabulary() {}
    CharVocabulary(const CharVocabulary&) = delete;

    void insert(const string &word) {
        unsigned int length = word.length();

        auto &_c = getContainer(length);
        char *tmp = new char[length];
        memcpy(tmp, word.c_str(), length);

        _c.insert(tmp);
    }

    bool end() const {
        return false;
    }

    bool find(const string &word) {
        unsigned int length = word.length();

		unordered_set< char*, CharHasher, CharCompare> &_c = getContainer(length);

		char *str = const_cast<char*>(word.c_str());

        return _c.find(str) != _c.end();
    }

private:
    vector < unordered_set< char*, CharHasher, CharCompare> > m_vocabulary;

    unordered_set< char*, CharHasher, CharCompare>& getContainer(unsigned int length) {
        while (m_vocabulary.size() < length - 1) {
            m_vocabulary.emplace_back(10, CharHasher(length), CharCompare(length) );
        }

        return m_vocabulary[length - 2];
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    vector < int> results = {6, 3, 1, 3, 5, 3, 7, 1, 5, 4, 4, 3, 3, 2, 3, 3, 2, 4, 3, 3 };

    string inputLine;
    ifstream inFile(argv[1]);

    const string marker = "END OF INPUT";

    CharVocabulary       vocabulary;
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

    int ir = 0;
    for(auto&& test_case : test_cases) {
        list<string>            words_to_check;
        FriendsCounter< CharVocabulary >          counter(vocabulary, test_case);

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

        if (counter.getFriendsCount() + 1 != results[ir]) {
            cout << "Failed (" << results[ir] << ") "<< endl;
        }
        ir++;
        cout << counter.getFriendsCount() + 1 <<endl;
    }

    return 0;
}
