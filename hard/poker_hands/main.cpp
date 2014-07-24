#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Hand {
public:
    Hand() {
        memset(m_suits, 0, 4);
        memset(m_cards, 0, 16);

        m_flash = false;
        m_straight = true;

        m_pairCount = 0;
        m_kicker = 0;
        m_pair = 0;
        m_three = 0;
        m_four = 0;
    }

    ~Hand() {}

    enum CompareResult {
        I_WIN,
        TIE,
        I_LOSE
    };

    void addCard(char value, char suit) {
        int valueIndex;
        int suitIndex;

		valueIndex = getValueIndex(value);
		suitIndex = getSuitIndex(suit);

        m_suits[suitIndex]++;
        if (m_suits[suitIndex] == 5) {
            m_flash = true;
        }

        m_cards[valueIndex]++;

        if (m_cards[valueIndex] == 1) {
            m_kicker |= 1 << valueIndex;
        } else {
            m_straight = false;
            if (m_cards[valueIndex] == 2) {
                m_kicker &= ~( 1 << valueIndex);
                m_pair |= ( 1 << valueIndex);
                m_pairCount ++;
            } else if (m_cards[valueIndex] == 3) {
                m_pairCount--;
                m_pair &= ~( 1 << valueIndex);
                m_three |= ( 1 << valueIndex);
            } else {
                m_three = 0;
                m_four |= ( 1 << valueIndex);
            }
        }
    }

    CompareResult compareTo(Hand& right) {
        unsigned int myScore = getTopScore();
        unsigned int rightScore = right.getTopScore();

        if (myScore < rightScore) {
            return CompareResult::I_LOSE;
        } else if (myScore > rightScore) {
            return CompareResult::I_WIN;
        } else {
            if (m_kicker < right.m_kicker) {
                return I_LOSE;
            } else if (m_kicker > right.m_kicker) {
                return I_WIN;
            }

            return TIE;
        }
    }
private:
    enum SUIT {
        SPADES,
        HEARTS,
        DIAMONDS,
        CLUBS
    };

    enum COMBO_CODE {
        HighCardCombo,
        PairCombo,
        TwoPairCombo,
        ThreeCombo,
        StraightCombo,
        FlushCombo,
        FullHauseCombo,
        FourCombo,
        StraightFlushCombo,
        RoyalFlushCombo
    };

    char m_cards[16];
    char m_suits[4];
    bool m_flash;
    bool m_straight;

    int  m_pairCount;
    int  m_kicker;
    int  m_pair;
    int  m_three;
    int  m_four;

    unsigned int getTopScore() {
        short   comboCode = 0;
        short   cardCode = 0;

        if (m_straight) {
            int i;
            int s;
            for (i=0; i < 13; i++) {
                if (m_cards[i] != 0) {
                    break;
                }
            }

            for (s=i; s < i + 5; s++) {
                if (m_cards[s] == 0) {
                    break;
                }
            }
            if (s == i + 5) {
                cardCode = i + 5 - 1;
                if (m_flash) {
                    if (cardCode == 12) {
                        comboCode = RoyalFlushCombo;
                    } else {
                        comboCode = StraightFlushCombo;
                    }
                } else {
                    comboCode = StraightCombo;
                }
                return (comboCode << 16) | cardCode;
            }
        }

        if (m_flash) {
            comboCode = FlushCombo;
            cardCode = m_kicker;
        } else {
            if (m_four != 0) {
                comboCode = FourCombo;
                cardCode = m_four;
            } else if (m_three != 0) {
                cardCode = m_three;
                if (m_pairCount != 0) {
                    comboCode = FullHauseCombo;
                    m_kicker = m_pair;
                } else {
                    comboCode = ThreeCombo;
                }
            } else if (m_pairCount != 0) {
                cardCode = m_pair;
                if (m_pairCount == 2) {
                    comboCode = TwoPairCombo;
                } else {
                    comboCode = PairCombo;
                }
            } else {
                cardCode = m_kicker;
                comboCode = HighCardCombo;
            }
        }

        return (comboCode << 16) | cardCode;
    }

    int getValueIndex(char value) {
        if (value >= '2' && value <= '9') {
            return value - '2';
        }
        switch(value) {
        case 'T':
            return 8;
        case 'J':
            return 9;
        case 'Q':
            return 10;
        case 'K':
            return 11;
        case 'A':
            return 12;
		default:
			return -1;
        }
    }

    int getSuitIndex(char suit) {
        switch(suit) {
        case 'D':
            return 0;
        case 'C':
            return 1;
        case 'H':
            return 2;
        case 'S':
            return 3;
		default:
			return -1;
        }
    }
};

void addCardToHand(Hand &hand, const string &line, size_t &position) {
    hand.addCard(line[position], line[position+1]);
    position += 3;
}

void printUpperHand(const string &line) {
    Hand leftHand;
    Hand rightHand;

    size_t position = 0;

    for (int i=0; i < 5; i++) {
        addCardToHand(leftHand, line, position);
    }

    for (int i=0; i < 5; i++) {
        addCardToHand(rightHand, line, position);
    }

    auto compare = leftHand.compareTo(rightHand);
    switch (compare) {
    case Hand::I_WIN:
        cout << "left" << endl;
        break;
    case Hand::I_LOSE:
        cout << "right" << endl;
        break;
    default:
        cout << "none" << endl;
        break;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        printUpperHand(inputLine);
    }

    return 0;
}
