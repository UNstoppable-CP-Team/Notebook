mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); //high quality random number generator using time as seed
uniform_int_distribution<int>(l,r)(rng) //returns a randomb number between [l, r]
//There are many distributions that can be generated
