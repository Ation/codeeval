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
            position ++;
            break;
        }
    }

    return result;
}

using house_event = struct __house_event {
    unsigned int    felon_id;
    bool            entered;

    __house_event(unsigned int _id, bool _entered) : felon_id(_id), entered(_entered){}
};

void process_line(const string &line) {
    size_t position = 0;
    int inside_count = 0;
    int known_felons_inside_count = 0;

    vector<house_event> events;

    events.reserve(getUnsignedInteger(line, position));

    while (position < line.length()) {
        bool entered = false;
        if (line[position] == 'E') {
            entered = true;
        } else if (line[position] != 'L') {
            ++position;
            continue;
        }
        position += 2;
        unsigned int id = getUnsignedInteger(line, position);

        if (id != 0) {
            for (int i = events.size() - 1; i >= 0; --i) {
                if (events[i].felon_id == id) {
                    if (events[i].entered == entered) {
                        for (; i < events.size(); ++i) {
                            if ( (events[i].felon_id == 0) && (events[i].entered != entered)) {
                                events[i].felon_id = id;
                                break;
                            }
                        }
                        if (i == events.size()) {
                            cout << "CRIME TIME" << endl;
                            return;
                        }
                    }
                    break;
                }
            }
        }

        events.emplace_back( id, entered);
    }

    for (int i=0; i < events.size(); i++) {
        if (events[i].entered) {
            if (events[i].felon_id == 0) {
                inside_count++;
            } else {
                known_felons_inside_count++;
            }
        } else {
            if ( (known_felons_inside_count + inside_count) > 0) {
                if (events[i].felon_id == 0) {
                    inside_count--;
                } else {
                    bool felon_was_seen_entering = false;
                    for (int j=i-1; j >= 0; --j) {
                        if (events[j].felon_id == events[i].felon_id) {
                            if (events[j].entered) {
                                felon_was_seen_entering = true;
                            }
                            break;
                        }
                    }

                    if (felon_was_seen_entering) {
                        known_felons_inside_count--;
                    } else {
                        inside_count--;
                    }
                }

                if (known_felons_inside_count + inside_count <= 0) {
                    known_felons_inside_count = 0;
                    inside_count = 0;
                }
            }
        }
    }
    cout << inside_count + known_felons_inside_count << endl;
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
        process_line(inputLine);
    }

    return 0;
}
