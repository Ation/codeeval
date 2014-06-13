#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <list>

using namespace std;

bool getUnsignedInteger(const string &line, size_t &position, unsigned int &number) {
    unsigned int result = 0;
    char temp;

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            break;
        }
    }

    if (position >= line.length()) {
        return false;
    }

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            position ++;
            break;
        }
    }

    number = result;
    return true;
}

class PeriodDate {
public:
    PeriodDate(unsigned int month, unsigned int year) : m_month(month), m_year(year) {}

    PeriodDate() :  m_month(0), m_year(0) {
    }

    bool init(const string &line, size_t &position) {
        for (; position < line.length(); position++) {
            if (line[position] >= 'A' && line[position] <= 'Z') {
                break;
            }
        }

        if (position > line.length() - 8) {
            return false;
        }

        switch (line[position]) {
        case 'J':
            switch(line[position + 1]) {
            case 'a':
                m_month = 1;
                break;
            case 'u':
                switch(line[position + 2]) {
                case 'n':
                    m_month = 6;
                    break;
                case 'l':
                    m_month = 7;
                    break;
                default:
                    return false;
                }
                break;
            default:
                return false;
            }
			break;
        case 'F':
            m_month = 2;
            break;
        case 'M':
            if (line[position + 2] == 'r') {
                m_month = 3;
            } else {
                m_month = 5;
            }
            break;
        case 'A':
            if (line[position + 1] == 'p') {
                m_month = 4;
            } else {
                m_month = 8;
            }
            break;
        case 'S':
            m_month = 9;
            break;
        case 'O':
            m_month = 10;
            break;
        case 'N':
            m_month = 11;
            break;
        case 'D':
            m_month = 12;
            break;
        default:
            return false;
        }

        position += 4;

        return getUnsignedInteger(line, position, m_year);
    }

    unsigned int monthTo(const PeriodDate &date) const {
        unsigned int total = 0;
        if (m_year == date.m_year) {
            total = date.m_month - m_month + 1;
        } else {
            total = 13 - m_month + date.m_month;
            total += 12 * (date.m_year - m_year - 1);
        }

        return total;
    }

    bool lessThen(const PeriodDate &other) const {
        return (m_year < other.m_year) || ( ( m_year == other.m_year) && (m_month < other.m_month));
    }

private:
    unsigned int m_month;
    unsigned int m_year;
};

class WorkPeriod {
public:
    WorkPeriod() {}

    bool init(const string &line, size_t &position) {
        return m_start.init(line, position) && m_end.init(line, position);
    }

    bool startedBefore(const WorkPeriod &other) {
        return m_start.lessThen(other.m_start);
    }

    bool isOverlapped(const WorkPeriod &other) {
        return ( isInsidePeriod(other.m_start) || isInsidePeriod(other.m_end) ||
			other.isInsidePeriod(m_start) || other.isInsidePeriod(m_end));
    }

    void join(const WorkPeriod &other) {
        if (other.m_start.lessThen(m_start)) {
            m_start = other.m_start;
        }

        if (m_end.lessThen(other.m_end) ) {
            m_end = other.m_end;
        }
    }

    unsigned int getDuration() const {
        return m_start.monthTo(m_end);
    }

private:
    PeriodDate  m_start;
    PeriodDate  m_end;

    bool isInsidePeriod(const PeriodDate &date) const {
		return !(date.lessThen(m_start) || m_end.lessThen(date));
    }
};

void printExperience(const string &line) {
    list<WorkPeriod> periods;

    WorkPeriod period;

    size_t position = 0 ;

    while (period.init(line, position)) {
        for (auto it = periods.begin(); ; ++it) {
            if (it == periods.end()) {
                periods.push_back(period);
                break;
            }
            if ( period.startedBefore(*it) ) {
                periods.insert(it, period);
                break;
            }
        }
    }

    unsigned int total_month = 0;

    for (auto it = periods.begin(); it != periods.end(); ) {
        period = *it;

        ++it;
        while (it != periods.end()) {
            if (!period.isOverlapped(*it)) {
                break;
            }
            period.join(*it);
            ++it;
        }

        total_month += period.getDuration();
    }

    cout << total_month / 12 << endl;
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
        printExperience(inputLine);
    }

    return 0;
}
