struct SufAut{
	const static int maxn = 2e5 + 10; //Maximum string lenght
	struct Node {
		int len, link;
		map <char, int> next;
	};
	int sz, last;
	Node aut[2 * maxn]; //Maximum number of states 2 * n - 1
	SufAut() : last(0), sz(1) { aut[0]. len = 0, aut[0].link = -1;}
	void add(string &s) {
		for (char c : s) {
			int cur = sz++;
			aut[cur].len = aut[last].len + 1;
			int p = last;
			while (p != -1 && !aut[p].next.count(c)) {
				aut[p].next[c] = cur;
				p = aut[p].link;
			}
			if (p == -1) aut[cur].link = 0;
			else {
				int q = aut[p].next[c];
				if (aut[p].len + 1 == aut[q].len) aut[cur].link = q;
				else {
					int clone = sz++;
					aut[clone].len = aut[p].len + 1;
					aut[clone].next = aut[q].next;
					aut[clone].link = aut[q].link;
					while (p != -1 && aut[p].next[c] == q) {
						aut[p].next[c] = clone;
						p = aut[p].link;
					}
					aut[p].link = aut[cur].link = clone;
				}
			}
			last = cur;
		}
	}
};
