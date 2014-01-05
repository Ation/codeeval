#include <iostream>

using namespace std;

template< template<int, int, int> class _MR, int map, int x, int y, bool visited>
struct GetCount {
	enum Result
	{
		value =	_MR<(map | (1 << ( ( x * 4) +y ))), (x-1), y>::value +
				_MR<(map | (1 << ( ( x * 4) +y ))), (x+1), y>::value +
				_MR<(map | (1 << ( ( x * 4) +y ))), x, (y-1)>::value +
				_MR<(map | (1 << ( ( x * 4) +y ))), x, (y+1)>::value
	};
};

template< template<int, int, int> class _MR, int map, int x, int y>
struct GetCount<_MR, map, x, y, true> {
	enum Result
	{
		value = 0
	};
};

template <int map, int x, int y>
struct MapRoute {
	enum Result { value = 	GetCount<MapRoute, map, x, y, ( (map & ( 1 << ( (x * 4) +y))) != 0 )>::value };
};

template<int map, int y>
struct MapRoute<map, -1, y> {
	enum Result { value = 0 };
};

template<int map, int y>
struct MapRoute<map, 4, y> {
	enum Result { value = 0 };
};

template<int map, int x>
struct MapRoute<map, x, -1> {
	enum Result { value = 0 };
};

template<int map, int x>
struct MapRoute<map, x, 4> {
	enum Result { value = 0 };
};

template<int map>
struct MapRoute<map, 3, 3> {
	enum Result { value = 1 };
};

struct SearchResult {
	enum Result { value = MapRoute<0, 0, 0>::value };
};

int main(void) {
	cout << MapRoute<0, 0, 0>::value << endl;
	return 0;
}