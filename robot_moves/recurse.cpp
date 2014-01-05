#include <iostream>

using namespace std;

int GetRouteCount(int map, int x, int y) {
	if ((x == -1) || (y == -1) || (x == 4) || (y == 4)) {
		return 0;
	}

	if ((x == 3) && ( y == 3)) {
		return 1;
	}

	if ( ( map & (1 << ( ( x << 2) +y) )) != 0 ) {
		return 0;
	}

	map |= (1 << ( (x << 2) +y));

	return	GetRouteCount(map, x-1, y) +
			GetRouteCount(map, x+1, y) +
			GetRouteCount(map, x, y-1) +
			GetRouteCount(map, x, y+1);
}

int main(void) {
	int result = GetRouteCount(1, 0, 1);

	cout << (result<<1) << endl;

	return 0;
}