// 9.2 Imagine a robot sitting on the upper left corner of an X  by Y grid. The
// robot can only move in two direction: right and down. How many possible paths
// are there for the robot to go from (0, 0) to (X, Y)?
// FOLLOW UP
// Imagine certain spots  are  "off limits" , such that the robot can not  step
// on them. Design an algorithm to find a path for the robot from the top left
// to the bottom right.
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

class point {
	public:
		int x;
		int y;
	public:
		point() : x(-1),  y(-1)  {}
		point(int X, int Y) : x(X), y(Y) {}
		bool operator==(const point  &p) const { return ((x == p.x) && (y == p.y)); }
		bool empty() const { return ((x == (-1)) && (y == (-1))); }
};

long long _key(const point &p) {
	long long l = p.x;
	l <<= 32;
	l += p.y;
	return l;
}


map<long long, int> _m;

int count_paths(int X, int Y) {
	point pt(X, Y);
	if(_m.count(_key(pt)) > 0) return _m[_key(pt)];
	if(X < 0 || Y < 0) return 0;
	if(X == 1) {
		_m[_key(pt)] = Y - 1;
		return _m[_key(pt)];
	}
	if(Y == 1) {
		_m[_key(pt)] =  X - 1;
		return _m[_key(pt)];
	}
	_m[_key(pt)] = count_paths(X - 1, Y) + count_paths(X, Y - 1);
	return _m[_key(pt)];
}

/* The solution is to start at (0,0) and use BFS to find the way to (X,Y);
 *  - all disallowed cells are skipped
 *  - using DP all duplicating visits are skipped
 *  - the complexity is estimated as about O(XY)
 * The book proposes the opposit way with the same complexity:
 *  - starting from (X,Y) we consider (X-1,Y) and (X, Y-1)
 *  - repeating recursively
 *  - avoiding duplicated visits with help of DP
 */
vector<point> find_path(const vector<vector<bool> > &bariers) {
	const int X = int(bariers[0].size() - 1);
	const int Y = int(bariers.size() - 1);
	queue<point> q;
	q.push(point(0, 0));
	point finish;
	point target(X, Y);
	map<long long, point> parents;
	while(!q.empty()) {
		point pt = q.front();
		q.pop();
		if((pt.x < X) && !bariers[pt.y][pt.x + 1]) {
			point pt2 = pt;
			pt2.x ++;
			//pt2.parent = pt;
			if(pt2 == target) {
				finish = pt2;
			}
			if(parents.count(_key(pt2)) <= 0) {
				parents[_key(pt2)] = pt;
				q.push(pt2);
			}
			if(!finish.empty())
				break;
		}
		if((pt.y < Y) && !bariers[pt.y + 1][pt.x]) {
			point pt2 = pt;
			pt2.y ++;
			//pt2.parent = pt;
			if(pt2 == target) {
				finish = pt2;
			}
			if(parents.count(_key(pt2)) <= 0) {
				parents[_key(pt2)] = pt;
				q.push(pt2);
			}
			if(!finish.empty())
				break;
		}
	}
	vector<point> path;
	point cur_pt = finish;
	while(!cur_pt.empty()) {
		path.insert(path.begin(), cur_pt);
		cur_pt = parents[_key(cur_pt)];
	}
	return path;
}

int main(void) {
	_m[_key(point(1, 2))] = 1;
	_m[_key(point(2, 1))] = 1;
	_m[_key(point(2, 2))] = 2;

	// TODO:

	return 0;
}
