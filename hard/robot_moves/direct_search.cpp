#include <iostream>
#include <list>

using namespace std;

class MoveRoute {
public:
	MoveRoute() : m_map(1), m_position(0) { }
	MoveRoute(const MoveRoute& src) : m_map(src.m_map), m_position(src.m_position) { }

	bool	reach_end() { return m_position == 15; }

	void	move_right() { 
		move_to_position( get_right_position() );
	}

	void	move_left() {
		move_to_position( get_left_position() );
	}

	void	move_up() {
		move_to_position( get_up_position() );
	}

	void	move_down() { 
		move_to_position( get_down_position() );
	}

	bool	can_move_right() { 
		return ( (m_position % 4 != 3) && ( !is_marked( get_right_position() ) ) );
	}

	bool	can_move_left() { 
		return ( (m_position % 4) && ( !is_marked( get_left_position() ) ) );
	}

	bool	can_move_up() {
		return ( ( m_position > 3) && ( !is_marked( get_up_position() ) ) );
	}

	bool	can_move_down() { 
		return ( ( m_position < 12) && ( !is_marked( get_down_position() ) ) );
	}

private:
	unsigned short 	get_up_position() { return m_position - 4; }
	unsigned short 	get_down_position() { return m_position + 4; }
	unsigned short 	get_left_position() { return m_position - 1; }
	unsigned short 	get_right_position() { return m_position + 1; }

	bool	is_marked(unsigned short position) {
		return (m_map & (1 << position)) != 0;
	}

	void 	move_to_position(unsigned short position) {
		m_position = position;
		m_map |= ( 1 << m_position);
	}

	unsigned short 	m_map;
	unsigned short  	m_position;
};

int main(int argc, char *argv[]) {
	int			result = 0;

	list<MoveRoute>	routes;
	MoveRoute start;
	start.move_down();

	routes.push_front(start);

	while (!routes.empty()) {
		MoveRoute &current = routes.front();

		if (current.reach_end()) {
			result++;
		} else {
			if (current.can_move_down()) {
				MoveRoute	next(current);
				next.move_down();
				routes.push_back(next);
			}
			if (current.can_move_up()) {
				MoveRoute	next(current);
				next.move_up();
				routes.push_back(next);
			}
			if (current.can_move_left()) {
				MoveRoute	next(current);
				next.move_left();
				routes.push_back(next);
			}
			if (current.can_move_right()) {
				MoveRoute	next(current);
				next.move_right();
				routes.push_back(next);
			}
		}
		routes.pop_front();
	}

	cout << result*2 << endl;

	return 0;
}