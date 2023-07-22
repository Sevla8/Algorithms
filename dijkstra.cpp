#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <list>
#include <functional>
#include <utility>
#include <limits>

using namespace std;

struct node {
	int val;
	vector<pair<int, node*>> suc;
	node() {};
	node(int i) : val(i) {}
};

void dijkstra(node* src, node* target, list<node*>& path) {
	map<node*, node*> parent;
	parent[src] = src;

	map<node*, int> d;
	d[src] = 0;

	set<node*> x;			// black nodes

	priority_queue<pair<int, node*>, vector<pair<int, node*>>, greater<pair<int, node*>>> y;

	y.push({0, src});

	function<int(node*)> dist = [&](node* v) {
		map<node*, int>::const_iterator it = d.find(v);
		if (it == d.end()) {
			return numeric_limits<int>::max();
		}
		return it->second;
	};

	while (!y.empty()) {
		node* u = y.top().second;

		if (target == u) {	// once the target found, rebuild the path to it
			path.clear();
			while (u != src) {
				path.push_front(u);
				u = parent[u];
			}
			path.push_front(src);
			return;
		}

		y.pop();
		x.insert(u);		// u, the 'smallest' grey node, becomes black

		for (pair<int, node*>& n : u->suc ) {

			if (x.find(n.second) != x.end()) {
				continue; // if n is black, do nothing...
			}

			// Don't make a special case for n already an element of y.
			// Indeed, the STL priority queue doesn't have an increaseKey operation.
			// Therefore, tolerate duplicates.

			if (dist(n.second) > d[u] + n.first) {
				d[n.second] = d[u] + n.first;
				parent[n.second] = u;
				y.push({d[n.second], n.second});
			}
		}
	}
}

int main() {
	node n0(0);
	node n1(1);
	node n2(2);
	node n3(3);
	node n4(4);
	node n5(5);
	node n6(6);
	n0.suc.push_back({1, &n1});
	n1.suc.push_back({3, &n2});
	n1.suc.push_back({1, &n3});
	n2.suc.push_back({2, &n0});
	n3.suc.push_back({1, &n2});
	n4.suc.push_back({1, &n5});
	n4.suc.push_back({3, &n6});
	n5.suc.push_back({1, &n1});
	n5.suc.push_back({4, &n6});

	list<node*> path;
	dijkstra(&n4, &n0, path);
	for (node* n : path) {
		cout << n->val << " ; ";
	}
	cout << endl;

	return 0;
}
