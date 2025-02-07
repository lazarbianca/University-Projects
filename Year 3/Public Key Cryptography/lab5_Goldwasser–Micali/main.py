import math
import random
import sympy
from sympy import jacobi_symbol


class GoldwasserMicali:
    def __init__(self):
        self.alphabet = " abcdefghijklmnopqrstuvwxyz"
        self.char_to_bin = {char: format(i, '05b') for i, char in enumerate(self.alphabet)}
        self.bin_to_char = {v: k for k, v in self.char_to_bin.items()}
        self.public_key = None
        self.private_key = None

    def generate_keys(self):
        """
        Generates a public key and a private key.
        Public key: (n, x)
        Private key: (p, q)
        """

        def generate_prime(bits=16):
            while True:
                prime = random.getrandbits(bits)
                if sympy.isprime(prime):
                    return prime

        # Generate two large primes
        p = generate_prime()
        q = generate_prime()
        n = p * q

        # Find a non-residue x
        while True:
            x = random.randint(1, n - 1)
            if (
                    math.gcd(x, n) == 1
                    and jacobi_symbol(x, p) == -1
                    and jacobi_symbol(x, q) == -1
            ):
                break

        self.public_key = (n, x)
        self.private_key = (p, q)
        print(f"Public key: (n={n}, x={x})")
        print(f"Private key: (p={p}, q={q})")

    def validate_plaintext(self, plaintext):
        """
        Validates that the plaintext consists of valid characters.
        """
        plaintext = str(plaintext)
        if not all(char in self.alphabet for char in plaintext):
            raise ValueError("Plaintext contains invalid characters.")

    def validate_ciphertext(self, ciphertext):
        """
        Validates that the ciphertext is a list of integers.
        """
        if not isinstance(ciphertext, list) or not all(isinstance(c, int) for c in ciphertext):
            raise ValueError("Ciphertext must be a list of integers.")

    def generate_random(self, n):
        """
        Generate a random number co-prime to n.
        """
        while True:
            r = random.randint(1, n)
            if math.gcd(r, n) == 1:
                return r

    def encrypt_bit(self, bit, r, n, x):
        """
        Encrypt a single bit.
        """
        return (pow(r, 2, n) * pow(x, bit, n)) % n

    def encrypt(self, plaintext):
        """
        Encrypts a given plaintext using the public key.
        """
        try:
            self.validate_plaintext(plaintext)
            n, x = self.public_key
            binary_message = ''.join(self.char_to_bin[char] for char in plaintext)

            ciphertext = []
            for bit in binary_message:
                r = self.generate_random(n)
                encrypted_bit = self.encrypt_bit(int(bit), r, n, x)
                ciphertext.append(encrypted_bit)
            return ciphertext
        except ValueError as e:
            print(e)

    def decrypt(self, ciphertext):
        """
        Decrypts a given ciphertext using the private key.
        """
        try:
            self.validate_ciphertext(ciphertext)
            p, q = self.private_key
            n, _ = self.public_key

            binary_message = []
            for c in ciphertext:
                # Check if c is a quadratic residue modulo p and q
                is_residue_p = pow(c % p, (p - 1) // 2, p) == 1
                is_residue_q = pow(c % q, (q - 1) // 2, q) == 1

                if is_residue_p and is_residue_q:
                    binary_message.append('0')
                else:
                    binary_message.append('1')

            # Group binary bits into 5-bit blocks and decode characters
            try:
                plaintext = ''.join(
                    self.bin_to_char[''.join(binary_message[i:i + 5])]
                    for i in range(0, len(binary_message), 5)
                )
            except KeyError:
                raise ValueError("Decrypted binary sequence does not map to valid plaintext characters.")
            return plaintext
        except ValueError as e:
            print(e)

# Example Usage
if __name__ == "__main__":
    gm = GoldwasserMicali()
    # Generate keys
    gm.generate_keys()

    plaintext = "hello world"
    print(f"\nTesting valid plaintext: {plaintext}")
    # Encrypt the plaintext
    ciphertext = gm.encrypt(plaintext)
    print(f"Ciphertext: {ciphertext}")
    # Decrypt the ciphertext
    decrypted_plaintext = gm.decrypt(ciphertext)
    print(f"Decrypted plaintext: {decrypted_plaintext}")

    # Invalid plaintext:
    plaintext = 1234
    print(f"\nTesting invalid ciphertext - int: {plaintext}")
    # Encrypt the plaintext
    ciphertext = gm.encrypt(plaintext)
    print(f"Ciphertext: {ciphertext}")
    # Decrypt the ciphertext
    decrypted_plaintext = gm.decrypt(ciphertext)
    print(f"Decrypted plaintext: {decrypted_plaintext}")

    # Invalid plaintext:
    plaintext = "123!?"
    print(f"\nTesting invalid ciphertext - string: {plaintext}")
    # Encrypt the plaintext
    ciphertext = gm.encrypt(plaintext)
    print(f"Ciphertext: {ciphertext}")
    # Decrypt the ciphertext
    decrypted_plaintext = gm.decrypt(ciphertext)
    print(f"Decrypted plaintext: {decrypted_plaintext}")
