#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <stack>

using namespace std;

struct node {
	int val;
	vector<node*> suc;
	node() {};
	node(int i) : val(i) {}
};

void visit(node* v) {
	cout << v->val << " ; ";
}

void dfsrec0(node* n, function<void(node*)> visit, set<node*>& x) {
	x.insert(n);
	for (node* s : n->suc) {
		if (x.find(s) == x.end()) {
			dfsrec0(s, visit, x);
		}
	}
	visit(n);
}

void dfsrec(node* src, function<void(node*)> visit) {
	set<node*> x;
	dfsrec0(src, visit, x);
}

void dfs(node* src, function<void(node*)> f) {
	set<node*> x;		// x contains the black and grey nodes
	stack<pair<node*, vector<node*>::iterator>> y;

	y.push({src, src->suc.begin()});	// initially the source is grey
	x.insert(src);

	while (!y.empty()) {				// while there are still grey nodes...

		node* u = y.top().first;		// u is the grey node we will make black by exploring his sons

		if (y.top().second != u->suc.end()) {	// if u has still unexplored sons
			node* next = *(y.top().second);		// next is a son of u
			++(y.top().second);					// set the iterator on the sons of u to the next unexplored one

			if (x.find(next) == x.end()) {				// if this son of u is white
				y.push({next, next->suc.begin()});		// it becomes grey
				x.insert(next);
			}
		}
		else {				// u has no more unexplored sons.
			f(u);			// we can visit u
			y.pop();		// u becomes black
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
	n0.suc.push_back(&n1);
	n1.suc.push_back(&n2);
	n1.suc.push_back(&n3);
	n2.suc.push_back(&n0);
	n3.suc.push_back(&n2);
	n4.suc.push_back(&n5);
	n4.suc.push_back(&n6);
	n5.suc.push_back(&n1);
	n5.suc.push_back(&n6);

	dfsrec(&n5, visit);
	cout << endl;

	dfs(&n5, visit);
	cout << endl;

	return 0;
}
