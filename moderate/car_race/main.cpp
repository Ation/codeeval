#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

bool getDouble(const string &line, size_t &position, double &number) {
    bool negative = false;
    double result = 0;
    char symbol;
    // find start
    for (; position < line.length(); position++ ) {
        symbol = line[position];
        if (symbol == '-') {
            negative = true;
            position++;
            break;
        }
        if (symbol >= '0' && symbol <= '9') {
            break;
        }
    }

    if (position == line.length()) {
        return false;
    }

    for (; position < line.length(); position++) {
        symbol = line[position];
        if (symbol == '.') {
            int devider = 10;

            // after dot
            position++;
            for (; position < line.length(); position++) {
                symbol = line[position];
                if (symbol >= '0' && symbol <= '9') {
                    result = result + ((double)(symbol - '0')) / devider;
                    devider *= 10;
                } else {
                    break;
                }
            }
            break;
        } else if (symbol >= '0' && symbol <= '9') {
            result = result * 10 + (symbol - '0');
        } else {
            break;
        }
    }

    if (negative) {
        result = -result;
    }

    number = result;
    return true;
}

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

class Track {
public:
    typedef struct __segment {
        double length;
        unsigned int angle;
    } segment;

    Track(const string &line) {
        size_t position = 0;

        double length;
        unsigned int angle;

        while (getDouble( line, position, length)) {
            if (getUnsignedInteger( line, position, angle ) ) {
                m_segments.emplace_back( decltype(m_segments)::value_type{ length, angle} );
            }
        }
    }

    vector< segment >:: const_iterator begin() const {
        return m_segments.begin();
    }

    vector< segment >:: const_iterator end() const {
        return m_segments.end();
    }

private:
    vector< segment > m_segments;
};

class Car {
public:
    Car ( const string &line) {
        size_t position = 0;

        getUnsignedInteger(line, position, m_id);
        getUnsignedInteger(line, position, m_maxSpeed);

        getDouble(line, position, m_accelerateTime);
        getDouble(line, position, m_breakTime);

        m_raceTime = 0;
    }

    void Race(const Track& track) {
        double v0 = 0;
        double max_speed = (double)m_maxSpeed / 3600;

        m_raceTime = 0;

        double acceleration = max_speed / m_accelerateTime;
        double break_acceleration = max_speed / m_breakTime;

        for (auto s = track.begin(); s != track.end(); ++s) {
            if (s->angle != 0 ) {
                double end_speed = (( 180 - s->angle ) * max_speed) / 180;

                double acc_time = (max_speed - v0) / acceleration;
                double break_time = ( max_speed - end_speed) / break_acceleration;

                double acc_distance = (max_speed + v0) * acc_time / 2;
                double break_distance = (max_speed + end_speed) * break_time / 2;

                double max_distance = (double)s->length - acc_distance - break_distance;
                double max_time = max_distance / max_speed;

                m_raceTime += acc_time + max_time + break_time;

                v0 = end_speed;
            } else {
                double acc_time = (max_speed - v0) / acceleration;

                double acc_distance = (max_speed + v0) * acc_time / 2;

                double max_distance = (double)s->length - acc_distance;
                double max_time = max_distance / max_speed;

                m_raceTime += acc_time + max_time;
            }
        }
    }

    unsigned int getId() const {
        return m_id;
    }

    double raceTime() const {
        return m_raceTime;
    }

    void print() const {
        cout << m_id << ' ' << m_raceTime << endl;
    }

    bool operator < ( const Car &right ) const {
        return m_raceTime < right.m_raceTime;
    }

private:
    unsigned int m_id;

    unsigned int m_maxSpeed;

    double m_accelerateTime;
    double m_breakTime;

    double m_raceTime;
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

    getline(inFile, inputLine);

    Track track(inputLine);
    vector< Car > cars;

    while ( getline(inFile, inputLine)) {
        cars.emplace_back( inputLine );
    }

    for(auto&& c : cars) {
        c.Race(track);
    }

    sort( cars.begin(), cars.end() );

    std::cout.precision(2);
    cout << std::fixed;

    for ( auto i = cars.begin(); i != cars.end(); ++i) {
        cout << i->getId() << ' ' << i->raceTime() << endl;
    }

    return 0;
}
