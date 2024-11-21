#ifdef IGNORE_THIS_FILE
  vector<int> sieve(int n){
    vector<bool> is_prime(n + 1);
    vector<int> prime;
    for(int i = 2; i <= n; ++i){
      is_prime[i] = true;
    }
    for(int i = 2; i * i <= n; ++i){
      if(is_prime[i]){
        for(int j = i * i; j <= n; j += i)
          is_prime[j] = false;
      }
    }
    for(int i = 2; i <= n; ++i){
      if(is_prime[i])
        prime.push_back(i);
    }
    return prime;
  }
#endif