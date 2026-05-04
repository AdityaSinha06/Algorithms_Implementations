// 1. Single Number Check: to check if a specific number 'n' is prime.
// Logic Used: all primes are of form : 6k +/- 1. 
// So, the method is mostly like prime-factorisation , checking if it has multiple other prime-factors

bool isPrime(int n) {
    if (n < 2) return false; 
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    int limit = sqrt(n); 
    for (int i = 5; i <= limit; i += 6) { // here, we check with all numbers of form 6k +/- 1 , which potentially includes all the primes as well, however some other nos too.
        if (n % i == 0 || n % (i + 2) == 0) 
            return false;
    }
    return true;
}

// Tc: O(sqrt(n0)


// 2. Sieve of Eratosthenes : Use this when you need to find all primes up to a limit 'n'

vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true); // [0 -- n] :: all indexs are to be considered as num
    isPrime[0] = isPrime[1] = false; //0 , 1 are not prime

    for (int p = 2; p * p <= n; p++) { // for each of the num from 2 --> sqrt(n) :: coz , all the smaller factors are <= sqrt(n)  
        if (isPrime[p]) { // if this num is prime , mark all its multiples are false :> they can't be primes
            // Start crossing out from p*p
            for (int i = p * p; i <= n; i += p) // coz' nos like 2p , 3p ,.. will already be marked earlier 
                isPrime[i] = false;
        }
    }
    return isPrime; 
}
