//NOTE: in case of needing modulo operations, use Modular template
template<class T> struct Matrix{
    vector<vector<T>> m;
    int N, M;
    Matrix(bool identity, int rows, int columns){
        N = rows; M = columns;
        m.resize(N, vector<T>(M, 0));
        if(identity && N == M)
            for(int i = 0; i < N; i++) m[i][i] = 1;
    }
    Matrix operator * (const Matrix &o){
        Matrix<T> r(false, N, o.M);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < o.M; j++)
                for(int k = 0; k < M; k++) r.m[i][j] = m[i][k] * o.m[k][j] + r.m[i][j];
        return r;
    }
	friend Matrix binpow(Matrix<T> M, long long r){
		Matrix<T> ans(true, M.N, M.N);
		for(; r; M = M * M, r >>= 1)
			if(r & 1) ans = ans * M;
		return ans;
	}
};
