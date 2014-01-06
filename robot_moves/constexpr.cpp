#include <iostream>

using namespace std;

constexpr int GetRouteCount(int map, int x, int y) {
	return ((x == -1) || (y == -1) || (x == 4) || (y == 4)) ? 0 :
			((x == 3) && ( y == 3)) ? 1 :
			( ( map & (1 << ( ( x << 2) +y) )) != 0 ) ? 0 :
				(map |= (1 << ( (x << 2) +y)) , GetRouteCount(map, x-1, y) +
            GetRouteCount(map, x+1, y) +
            GetRouteCount(map, x, y-1) +
            GetRouteCount(map, x, y+1));
}

int main(void) {
	cout << GetRouteCount(0, 0, 0) << endl;
	return 0;
}