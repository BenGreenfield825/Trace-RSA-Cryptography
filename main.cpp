//-------------------------
//  Program By Ben Greenfield
//  10/26/2020
//-------------------------


#include <iostream>
#include <math.h>

using namespace std;
//Given values
const int p = 13;   //Alice's two primes p and q
const int q = 29;
const int n = p * q;
const int e = 5;    //Alice uses 5 at random (normaly this would be a gcd)
const int M = 27;   //Bob's message to send

int ComputeSecret(int p, int q);
int FindUniqueD(int n, int e, int totient);
int CalculateCipherText(int M, int e, int n);
int Decipher(int c, int d, int n);
int FastModExp(int a, int b, int n);

int main() {
    int totient = ComputeSecret(p, q);
    int d = FindUniqueD(n, e, totient);
    int c = CalculateCipherText(M, e, n);
    int mPrime = Decipher(c, d, n);
    cout << "p: " << p << ", q: " << q << ", n: " << n << ", Totient: " << totient << ", e: " << e << ", d: " << d;
    cout << ", M: " << M << ", C: " << c << ", M': " << mPrime << endl;
    return 0;
}

int ComputeSecret(int p, int q) {   //compute the Euler Totient Function
    int n = (p - 1) * (q - 1);
    return n;
}

int FindUniqueD(int n, int e, int totient) {  //find unique integer d
    int d = 0;
    while (1) {  //loop through values of d to find a value which satisfies requirements
        if (d > 1 && d < (n - 1)) {
            if ((d * e) % totient == 1) {
                return d;
            }
        }
        d++;
    }
}

int CalculateCipherText(int M, int e, int n) {  //create cipher text from M
    int c = FastModExp(M, e, n);
    return c;
}

int Decipher(int c, int d, int n) {     //decipher the cipher text back to plain text
    int mPrime = FastModExp(c, d, n);
    return mPrime;
}

int FastModExp(int a, int b, int n) {   //a: number getting a power, b: the power, n: what we want to mod with
    int i = b;
    int prod = 1;
    int x = a % n;

    do {
        if (i % 2 != 0) {    //if the b is odd
            prod = (prod * x) % n;
        }
        x = (x * x) % n;
        i = floor(i / 2);
    } while (i > 0);
    return prod;
}

