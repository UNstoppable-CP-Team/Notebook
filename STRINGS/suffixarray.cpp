struct SufAr {
	//Suffix array, class array, and lcp array
	vector <int> p, c, lcp; 
	void countsort(){ 
		int n = p.size();
		vector <int> cnt(n, 0);
		for(int i : c) {
			cnt[i]++;
		}
		vector<int> newp(n), pos(n);
		pos[0] = 0;
		for(int i = 1; i < n; ++i) {
			pos[i] = pos[i-1] + cnt[i-1];
		}
		for(int i : p) {
			int k = c[i];
			newp[pos[k]] = i;
			pos[k]++;
		}
		p = newp;
	}
	SufAr(string &s){
		s += '$';
		int n = s.size();
		p.assign(n, 0); c.assign(n, 0); lcp.assign(n, 0);
		//Suffix Array construction
		vector <pair<char, int>> a(n); 
		for (int i = 0; i < n; ++i) {
			a[i] = {s[i], i};
		}
		sort(a.begin(), a.end());
		for(int i = 0; i < n; ++i) {
			p[i] = a[i].second;
		}
		c[p[0]] = 0;
		for(int i = 1; i < n; ++i) {
			c[p[i]] = c[p[i-1]];
			if(a[i].first != a[i-1].first) c[p[i]]++;
		}
		for(int k = 0; (1 << k) < n; ++k) {
			for(int i = 0; i < n; ++i) {
				p[i] = (p[i] - (1 << k) + n) % n;
			}
			countsort();
			vector <int> newc(n);
			newc[0] = 0;
			for(int i = 1; i < n; ++i) {
				pii prev = {c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
				pii cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
				newc[p[i]] = newc[p[i-1]];
				if(prev != cur) newc[p[i]]++;
			}
			c = newc;
		}
		//LCP Array construction
		for (int i = 0, k = 0; i < n - 1; ++i) {
			int pi = c[i];
			int j = p[pi - 1];
			while (s[i + k] == s[j + k]) k++;
			lcp[pi] = k;
			k = max(k - 1, 0);
		}
	}
};
