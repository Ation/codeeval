#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

unsigned int getUnsignedInteger(const string &line, size_t &position) {
    unsigned int result = 0;
    char temp;
    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            break;
        }
    }

    return result;
}

class SeatMembers {
public:
    SeatMembers() {}

    bool seat_members( const string &line) {
        size_t position = 0;

        unsigned int seats_count = getUnsignedInteger(line, position);
        position += 2;

        _seats.assign(seats_count, false);
        _members_list.clear();

        vector<int> places;
        places.reserve(seats_count);

        while(position < line.length()) {
            while(line[position] != '[') {
                position++;
            }
            position++;

            while (true) {
                places.push_back( getUnsignedInteger(line, position) - 1);
                if (line[position] == ']') {
                    position += 3;
                    break;
                }
                position += 2;
            }
            _members_list.push_back(places);
            places.clear();
        }

        return can_seat(0);
    }
private:
    vector<bool> _seats;
    vector< vector<int> > _members_list;

    bool can_seat(int member_index) {
        if (member_index == _members_list.size()) {
            return true;
        }

        for( auto it = _members_list[member_index].begin(); it != _members_list[member_index].end(); ++it) {
            if (!_seats[*it]) {
                _seats[*it] = true;
                if (can_seat(member_index+1)) {
                    return true;
                }
                _seats[*it] = false;
            }
        }

        return false;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    SeatMembers docker;

    while ( getline(inFile, inputLine)) {
        cout << (docker.seat_members(inputLine) ? "Yes" : "No" ) << endl;
    }

    return 0;
}
