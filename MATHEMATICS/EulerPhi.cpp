//primes is a vector of primes less or equal than sqrt(n)
//Initially all numbers are coprime
//Complexity O(sqrt(n))
ll ans = n; 
for(int i=0; primes[i]*primes[i] <= n; ++i){
  if(n%primes[i] == 0) ans -= ans/primes[i];
  while(n%primes[i] == 0) n/=primes[i];
}
if(n > 1) ans-= ans/n;
