#include "../utilities/template.h"

#include "../../content/data-structures/LazySegmentTreeFast.h"

static unsigned R;
int ra() {
	R *= 791231;
	R += 1231;
	return (int)(R >> 1);
}

volatile int res;
int main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](int x) { return ra() % x; });

	SegTree tree(N, v);
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = tree.id;
		rep(k,i,j) ma += v[k];
		assert(ma == tree.query(i,j));
	}
	rep(it,0,1000000) {
		int i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 50) {
			::res = tree.query(i, j);
			int ma = tree.id;
			rep(k,i,j) ma += v[k];
			assert(ma == ::res);
		}
		else {
			tree.update(i, j, x);
			rep(k,i,j) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
