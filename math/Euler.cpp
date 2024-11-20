#ifdef IGNORE_THIS_FILE
  // vector<int> fac(n + 1);
  auto sieve = [&](int n) -> vector<int> {
    vector<int> prime;
    vector<bool> no_prime(n + 1);
    for(int i = 2; i <= n; ++i){
      if(!no_prime[i]){
        prime.push_back(i);
        // fac[i] = i;
      }
      for(int j: prime){
        if(j * i > n) break;
        no_prime[j * i] = true;
        // fac[j * i] = j;
        if(i % j == 0) break;
      }
    }
    return prime;
  };
#endif