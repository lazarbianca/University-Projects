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

    def generate_keys(self, bits=16, verbose=True):
        """
        Generates a public key and a private key.
        
        Public key: (n, x)
        Private key: (p, q)
        
        Parameters:
            bits (int): Bit length of each prime number. Default is 16 bits.
            verbose (bool): If True, prints the generated keys. Default is True.
        """

        def generate_prime(bits):
            """
            Generates a prime number of specified bit length satisfying p ≡ 3 mod 4.
            """
            lower = 2**(bits - 1)
            upper = 2**bits - 1
            while True:
                prime = sympy.randprime(lower, upper)
                if prime % 4 == 3:
                    return prime

        # Generate two large primes p and q
        p = generate_prime(bits)
        q = generate_prime(bits)
        n = p * q

        # Find a quadratic non-residue x
        while True:
            x = random.randint(2, n - 1)
            if (
                math.gcd(x, n) == 1
                and jacobi_symbol(x, p) == -1
                and jacobi_symbol(x, q) == -1
            ):
                break

        self.public_key = (n, x)
        self.private_key = (p, q)

        if verbose:
            print(f"Public key: (n={n}, x={x})")
            print(f"Private key: (p={p}, q={q})")

    def validate_plaintext(self, plaintext):
        """
        Validates that the plaintext consists of valid characters.

        Parameters:
            plaintext (str): The plaintext to validate.

        Raises:
            ValueError: If plaintext contains invalid characters.
        """
        plaintext = str(plaintext)
        if not all(char in self.alphabet for char in plaintext):
            raise ValueError("Plaintext contains invalid characters.")

    def validate_ciphertext(self, ciphertext):
        """
        Validates that the ciphertext is a list of integers.

        Parameters:
            ciphertext (list): The ciphertext to validate.

        Raises:
            ValueError: If ciphertext is not a list of integers.
        """
        if not isinstance(ciphertext, list) or not all(isinstance(c, int) for c in ciphertext):
            raise ValueError("Ciphertext must be a list of integers.")

    def generate_random(self, n):
        """
        Generate a random number co-prime to n.

        Parameters:
            n (int): The modulus.

        Returns:
            int: A random integer co-prime to n.
        """
        while True:
            r = random.randint(2, n - 1)
            if math.gcd(r, n) == 1:
                return r

    def encrypt_bit(self, bit, r, n, x):
        """
        Encrypts a single bit.

        Parameters:
            bit (int): The bit to encrypt (0 or 1).
            r (int): A random number co-prime to n.
            n (int): The modulus.
            x (int): The quadratic non-residue.

        Returns:
            int: The encrypted bit.
        """
        return (pow(r, 2, n) * pow(x, bit, n)) % n

    def encrypt(self, plaintext):
        """
        Encrypts a given plaintext using the public key.

        Parameters:
            plaintext (str): The plaintext to encrypt.

        Returns:
            list: The ciphertext as a list of integers.

        Raises:
            ValueError: If plaintext validation fails.
            ValueError: If keys have not been generated.
        """
        if self.public_key is None:
            raise ValueError("Public key not generated. Call generate_keys() first.")

        try:
            self.validate_plaintext(plaintext)
            n, x = self.public_key
            binary_message = ''.join(self.char_to_bin[char] for char in plaintext)
            print(binary_message)

            ciphertext = []
            for bit in binary_message:
                r = self.generate_random(n)
                encrypted_bit = self.encrypt_bit(int(bit), r, n, x)
                ciphertext.append(encrypted_bit)
            return ciphertext
        except ValueError as e:
            print(f"Encryption Error: {e}")
            return None

    def decrypt(self, ciphertext):
        """
        Decrypts a given ciphertext using the private key.

        Parameters:
            ciphertext (list): The ciphertext to decrypt.

        Returns:
            str: The decrypted plaintext.

        Raises:
            ValueError: If ciphertext validation fails.
            ValueError: If keys have not been generated.
            ValueError: If decrypted bitstream is invalid.
        """
        if self.private_key is None:
            raise ValueError("Private key not generated. Call generate_keys() first.")

        try:
            self.validate_ciphertext(ciphertext)
            p, q = self.private_key
            n, _ = self.public_key

            binary_message = []
            for c in ciphertext:
                # Check if c is a quadratic residue modulo p and q
                is_residue_p = pow(c, (p - 1) // 2, p) == 1
                is_residue_q = pow(c, (q - 1) // 2, q) == 1

                if is_residue_p and is_residue_q:
                    binary_message.append('0')
                else:
                    binary_message.append('1')

            # Ensure the binary message length is a multiple of 5
            if len(binary_message) % 5 != 0:
                raise ValueError("Decrypted bitstream length is not a multiple of 5.")

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
            print(f"Decryption Error: {e}")
            return None


if __name__ == "__main__":
    gm = GoldwasserMicali()
    gm.generate_keys(bits=16, verbose=True)

    # Valid plaintext
    plaintext = "hello"
    print(f"\nTesting valid plaintext: '{plaintext}'")
    ciphertext = gm.encrypt(plaintext)
    if ciphertext is not None:
        print(f"Ciphertext: {ciphertext}")
        decrypted_plaintext = gm.decrypt(ciphertext)
        if decrypted_plaintext is not None:
            print(f"Decrypted plaintext: '{decrypted_plaintext}'")
        else:
            print("Decryption failed.")
    else:
        print("Encryption failed.")

    # Invalid plaintext: string with invalid characters
    plaintext = "123!?"
    print(f"\nTesting invalid plaintext - string: '{plaintext}'")
    ciphertext = gm.encrypt(plaintext)
    if ciphertext is not None:
        print(f"Ciphertext: {ciphertext}")
        decrypted_plaintext = gm.decrypt(ciphertext)
        if decrypted_plaintext is not None:
            print(f"Decrypted plaintext: '{decrypted_plaintext}'")
        else:
            print("Decryption failed.")
    else:
        print("Encryption failed.")
