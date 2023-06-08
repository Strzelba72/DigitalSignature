#include <cmath>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <cstdint>
#include <vector>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <cassert>
#include <mutex>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

mutex g_lock;


const int THREAD_COUNT = 8;
const int ITERATIONS_PER_THREAD = 48;
uint8_t nu[8];
double X[8];
double R[8];




void initialXR()
{   X[0]=0.111112;
    X[1]=0.222223;
    X[2]=0.333334;
    X[3]=0.444445;
    X[4]=0.555556;
    X[5]=0.666667;
    X[6]=0.777778;
    X[7]=0.888889;
    for(int i=0;i<8;i++)
    {

        R[i]=3.86+X[i]*0.14;
    }



}
void chaoticMap(double (&X)[8], double (&R)[8], int ti, int y) {

    //g_lock.lock();
    std::cout<<"entered thread: " << this_thread::get_id() << endl;

    //cout<<"I : "<<ti<<endl;

    if (X[ti] >= 0.5) {
        for (int z = 1; z < y; z++) {
            X[ti] = X[ti] * R[ti] * (1 - X[ti]);
            cout << X[ti]<< " ";
        }
        cout<<endl;
        R[ti] = 3.99;
    }
    else {
        double tmp;
        for (int z = 1; z < y; z++) {
            X[ti] = X[ti] * R[ti] * (1 - X[ti]);
            tmp+=(3.86 + (X[ti] * 0.14));
            cout << X[ti]<< " ";
        }
        cout<<endl;

        R[ti] = tmp/(double)y;
    }
    this_thread::sleep_for(chrono::seconds(1));
    std::cout<<"leaving thread: " << this_thread::get_id() << endl;
    //g_lock.unlock();


}
void generate_random_numbers(double (&X)[8],double (&R)[8], int ti,int blk) {

if(blk==0){
        uint64_t C1 = reinterpret_cast<const uint64_t*>(&X[ti])[0];
        uint64_t C2 = reinterpret_cast<const uint64_t*>(&X[(ti + 9) % 8])[0];
        uint32_t M1 = C1 & 0xFF;
        uint32_t M2 = (C1 >> 56) & 0xFF;
        uint32_t M3 = C2 & 0xFF;
        uint32_t M4 = (C2 >> 56) & 0xFF;
        nu[ti] = ((M1 + M4) ^ M3) + M2;
}

}
bool isPrime(int number) {
    if (number <= 1)
        return false;
    if (number <= 3)
        return true;
    if (number % 2 == 0 || number % 3 == 0)
        return false;
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0)
            return false;
    }
    return true;
}
int calculateEulerFunction(int p, int q) {
    return (p - 1) * (q - 1);
}
void generateRandom()
{
    initialXR();
    for(int i=0;i<8;i++)
    {

    thread thread1(chaoticMap,ref(X),ref(R),i,8);
    thread thread2(chaoticMap,ref(X),ref(R),i,8);
    thread thread3(chaoticMap,ref(X),ref(R),i,8);
    thread thread4(chaoticMap,ref(X),ref(R),i,8);
    thread thread5(chaoticMap,ref(X),ref(R),i,8);
    thread thread6(chaoticMap,ref(X),ref(R),i,8);
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
   // cout<<"..............  THREAD:: "<<(i+1)<<endl;

    }

    for(int i=0;i<8;i++)
    {

    thread thread11([ref(X),ref(R),i]()
    {
        //chaoticMap(X,R,i,8);
        generate_random_numbers(X,R,i,0);
    });
     thread thread12([ref(X),ref(R),i]()
    {
        //chaoticMap(X,R,i,8);
        generate_random_numbers(X,R,i,1);
    });
     thread thread13([ref(X),ref(R),i]()
    {
        //chaoticMap(X,R,i,8);
        generate_random_numbers(X,R,i,2);
    });
     thread thread14([ref(X),ref(R),i]()
    {
        //chaoticMap(X,R,i,8);
        generate_random_numbers(X,R,i,3);
    });
     thread thread15([ref(X),ref(R),i]()
    {
        //chaoticMap(X,R,i,8);
        generate_random_numbers(X,R,i,4);
    });
     thread thread16([ref(X),ref(R),i]()
    {
        //chaoticMap(X,R,i,8);
        generate_random_numbers(X,R,i,5);
    });


    thread11.join();
    thread12.join();
    thread13.join();
    thread14.join();
    thread15.join();
    thread16.join();

    }


     for(int i=0;i<8;i++)
     {
         std::cout<<X[i]<<std::endl;
     }
      for(int i=0;i<8;i++)
     {
         std::cout<<R[i]<<std::endl;
     }
      for(int i=0;i<8;i++)
     {
         printf("%d \n",nu[i]);
     }






   std::ofstream outfile;
    outfile.open("output.txt", std::ios::app);
    for(int i = 0; i < 8; i++){
        outfile << (int)nu[i] << "\n";
    }
    //outfile << "---------------"<< "\n";
    outfile.close();
    //cout<<"..............  ITERATION:: "<<(x)<<endl;


}
// Struktura przechowująca klucz publiczny (e, n) i klucz prywatny (d, n)
struct RSAKeys {
    unsigned long long e;  // Wykładnik publiczny
    unsigned long long d;  // Wykładnik prywatny
    unsigned long long n;  // Moduł
};

// Funkcja obliczająca odwrotność modulo
unsigned long long modInverse(unsigned long long a, unsigned long long m) {
    unsigned long long m0 = m;
    unsigned long long y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        unsigned long long q = a / m;
        unsigned long long t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}
int findRandomPrime() {

    int prime;
    while(true){
    generateRandom();
    for(int i = 0; i < 8; i++){
        prime=(int)nu[i];
        if(isPrime(prime))
            return prime;
            }
    }
}
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int findRelativelyPrime(int phi) {
    int e;
    while(true){
    generateRandom();
    for(int i = 0; i < 8; i++){
        e=((int)nu[i])%phi;
        if (gcd(e, phi) == 1)
            return e;
            }
    }
}
// Funkcja generująca klucze publiczny i prywatny RSA
RSAKeys generateRSAKeys() {
    RSAKeys keys;

    unsigned long long p, q;

// Generowanie dwóch losowych liczb pierwszych
    p = findRandomPrime();
    q = findRandomPrime();

    keys.n = p * q;
    unsigned long long phi = (p - 1) * (q - 1);

//Wybór losowego wykładnika publicznego e (1 < e < phi), względnie pierwszego z phi

    keys.e = findRelativelyPrime(phi);


// Obliczanie wykładnika prywatnego d, który jest odwrotnością modulo phi
    keys.d = modInverse(keys.e, phi);

    return keys;
}

// Funkcja szyfrująca wiadomość
unsigned long long encrypt(unsigned long long message, unsigned long long e, unsigned long long n) {
    unsigned long long encrypted = 1;

    for (unsigned long long i = 0; i < e; ++i) {
        encrypted = (encrypted * message) % n;
    }

    return encrypted;
}

// Funkcja deszyfrująca wiadomość
unsigned long long decrypt(unsigned long long encrypted, unsigned long long d, unsigned long long n) {
    unsigned long long decrypted = 1;

    for (unsigned long long i = 0; i < d; ++i) {
        decrypted = (decrypted * encrypted) % n;
    }

    return decrypted;
}


int main()
{
     // Generowanie kluczy RSA
    RSAKeys keys = generateRSAKeys();
    cout << "Public Key (e, n): (" << keys.e << ", " << keys.n << ")" << endl;
    cout << "Private Key (d, n): (" << keys.d << ", " << keys.n << ")" << endl;

    // Szyfrowanie i deszyfrowanie wiadomoœci
    unsigned long long message;
    message=105;

    unsigned long long encrypted = encrypt(message, keys.e, keys.n);
    unsigned long long decrypted = decrypt(encrypted, keys.d, keys.n);
    cout<<"Original message: "<< message<<endl;
    cout << "Encrypted message: " << encrypted << endl;
    cout << "Decrypted message: " << decrypted << endl;
    bool isMessageValid = (decrypted == message);
    cout<<"Message Verification: " << (isMessageValid ? "Valid" : "Invalid") <<endl;


    return 0;
}
