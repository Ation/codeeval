#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int val = 1;
	char *detector = (char*)(&val);

	if (detector[0] == 1) {
		cout << "LittleEndian" << endl;
	} else {
		cout << "BigEndian" << endl;
	}
	return 0;
}