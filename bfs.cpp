#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <functional>
#include <limits>

using namespace std;

struct node {
	int val;			// value
	vector<node*> suc;	// successors
	node() {};
	node(int i) : val(i) {}
};

void bfs(node* src, function<void(node*)> visit) {
	set<node*> x;		// x is the set of black nodes
	queue<node*> y;		// y is the queue of grey nodes
	y.push(src); 		// at the beginning, the source is the only grey node
	x.insert(src);

	while (!y.empty()) {
		node* u = y.front();
		visit(u);
		for (node* n : u->suc) {
			if (x.find(n) == x.end()) {		// n is a white successor of u
				y.push(n); 					// n becomes grey
				x.insert(n);
			}
		}
		y.pop();							// u becomes black
	}
}

void visit(node* v) {
	cout << v->val << " ; ";
}

void findDistances(node* src, map<node*, size_t>* distances) {

	function<size_t(node*)> distance = [&](node* v) {
		// local function used to return infinity when
		// for a node we do not yet know a distance to the source

		map<node*,size_t>::iterator distIt = distances->find(v);
		if (distIt == distances->end()) {
			return numeric_limits<size_t>::max();
		}
		return distIt->second;
	};

	function<void(node*)> visit = [&](node* v) {
		// update the shortest known distance to the
		// successors of the currently visited node

		size_t vDist = distance(v);

		for (node* n : v->suc) {
			size_t nDist = distance(n);
			(*distances)[n] = min(nDist, 1 + vDist);
		}
	};

	// distance from the source to the source is zero
	(*distances)[src] = 0;

	bfs(src, visit);
}

int main() {
	node n0(0);
	node n1(1);
	node n2(2);
	node n3(3);
	node n4(4);
	node n5(5);
	node n6(6);
	n0.suc.push_back(&n1);
	n1.suc.push_back(&n2);
	n1.suc.push_back(&n3);
	n2.suc.push_back(&n0);
	n3.suc.push_back(&n2);
	n4.suc.push_back(&n5);
	n4.suc.push_back(&n6);
	n5.suc.push_back(&n1);
	n5.suc.push_back(&n6);

	bfs(&n4, visit);
	cout << endl;

	map<node*, size_t> distances;
	findDistances(&n4, &distances);
	for (const auto& p : distances) {
		cout << (p.first)->val << " : " << p.second << " ; ";
	}
	cout << endl;

	return 0;
}
