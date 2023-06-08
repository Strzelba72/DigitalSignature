The RSA key generation mechanism is based on the mathematical principles of number theory. Here is a brief description of the process:


1.Prime number selection: Two distinct prime numbers, denoted as p and q, are chosen.

2.Calculation of modulus: The modulus N is calculated as the product of p and q (N = p * q). This number is used as part of both the public and private keys.

3.Euler's function calculation: The Euler's function φ(N) is calculated, which represents the number of integers that are coprime with N. For prime numbers, φ(N) = (p - 1) * (q - 1).

4.Exponent selection: The public exponent e is chosen, which is a number coprime with φ(N) (i.e., e and φ(N) have no common divisors other than 1).

5.Calculation of modular inverse: The modular inverse of e with respect to φ(N) is calculated. This involves finding a number d such that (d * e) mod φ(N) = 1. The number d is part of the private key.

6.Key generation: The public key is represented by the pair (e, N), and the private key is represented by the pair (d, N).


The information exchange mechanism based on RSA works as follows:


1.Person A, having the public key of person B, encrypts a message using B's public key. The message is transformed into a numerical form and then encrypted using B's public key.

2.The encrypted message is sent to person B.

3.Person B receives the encrypted message and uses their private key to decrypt it. The private key is used to transform the encrypted message back into its original form.

The private key is kept strictly confidential by its owner, while the public key is shared with others who wish to encrypt messages for the private key owner. Thanks to the mathematical properties of RSA, encrypted messages can only be read using the corresponding private key, ensuring the confidentiality of the communication.
To generate TRNG I used https://github.com/Strzelba72/TrueRandomGenerator.

![alt text](https://github.com/Strzelba72/DigitalSignature/blob/main/message1.png?raw=true)
