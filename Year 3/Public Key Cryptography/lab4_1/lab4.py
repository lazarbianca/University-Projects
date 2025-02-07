import random

# Define the alphabet
ALPHABET = " ABCDEFGHIJKLMNOPQRSTUVWXYZ"

# Map characters to integers
CHAR_TO_INT = {char: i for i, char in enumerate(ALPHABET)}
INT_TO_CHAR = {i: char for char, i in CHAR_TO_INT.items()}

# Helper Functions
def gcd(a, b):
    """Calculate the Greatest Common Divisor using the Euclidean Algorithm."""
    while b:
        a, b = b, a % b
    return a

def is_prime(n):
    """Check if a number is prime using an optimized method."""
    if n < 2:
        return False
    if n in (2, 3):
        return True  # 2 and 3 are prime
    if n % 2 == 0 or n % 3 == 0:
        return False  # Eliminate multiples of 2 and 3

    # Check divisors of the form 6k ± 1 up to sqrt of n
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def find_prime(start, end):
    """Find a random prime number in a given range."""
    primes = (num for num in range(start, end + 1) if is_prime(num))
    primes_list = list(primes)
    if not primes_list:
        raise ValueError("No primes found in the specified range.")
    return random.choice(primes_list)

def modular_inverse(e, phi):
    """Compute the modular inverse of e modulo phi using the Extended Euclidean Algorithm."""
    x0, x1, original_phi = 0, 1, phi
    while e > 0:
        q = phi // e
        phi, e = e, phi % e
        x0, x1 = x1, x0 - q * x1
    if phi == 1:
        return x0 % original_phi
    raise ValueError("Modular inverse does not exist")

def generate_keypair(prime_min, prime_max):
    """
    Generate RSA public and private keypair by directly specifying the interval 
    for prime number generation.
    
    :param prime_min: Minimum value for the primes.
    :param prime_max: Maximum value for the primes.
    """
    # Step 1: Generate two distinct primes p and q within the given interval
    p, q = find_prime(prime_min, prime_max), find_prime(prime_min, prime_max)
    while p == q:
        q = find_prime(prime_min, prime_max)

    # Step 2: Compute n and phi(n)
    n = p * q
    phi = (p - 1) * (q - 1)

    # Step 3: Find e such that gcd(e, phi) == 1
    e = random.randint(2, phi - 1)
    while gcd(e, phi) != 1:
        e = random.randint(2, phi - 1)

    # Step 4: Calculate d (modular inverse of e mod phi)
    d = modular_inverse(e, phi)

    return (e, n), (d, n)  # Return public and private keys

def validate_input(data, validator):
    """Generic input validation using a custom validator function."""
    return all(validator(item) for item in data)

def encrypt(plaintext, public_key):
    """Encrypt the plaintext using the public key."""
    e, n = public_key

    # Validate plaintext
    if not validate_input(plaintext, lambda char: char in CHAR_TO_INT):
        raise ValueError("Plaintext contains invalid characters.")

    # Convert plaintext to numbers and encrypt
    return [(CHAR_TO_INT[char] ** e) % n for char in plaintext]

def decrypt(ciphertext, private_key):
    """Decrypt the ciphertext using the private key."""
    d, n = private_key

    # Validate ciphertext
    if not validate_input(ciphertext, lambda num: isinstance(num, int) and num < n):
        raise ValueError("Ciphertext contains invalid format or values.")

    # Decrypt numbers to plaintext
    return ''.join([INT_TO_CHAR[(num ** d) % n] for num in ciphertext])

# Main Execution
if __name__ == "__main__":
    # Generate keys
    prime_min, prime_max = 350, 500  # Prime number range
    public_key, private_key = generate_keypair(prime_min, prime_max)
    print("Public Key:", public_key)
    print("Private Key:", private_key)

    encrypted = None
    while True:
        print("\n1. Enter plaintext and encrypt")
        print("2. Decrypt last ciphertext")
        print("3. Exit")
        
        choice = input("Choose an option: ").strip()
        
        if choice == "1":
            plaintext = input("Enter plaintext: ").strip()
            try:
                encrypted = encrypt(plaintext, public_key)
                print("Encrypted text:", encrypted)
            except ValueError as e:
                print(e)
        
        elif choice == "2":
            if encrypted:
                try:
                    decrypted = decrypt(encrypted, private_key)
                    print("Decrypted text:", decrypted)
                except ValueError as e:
                    print(e)
            else:
                print("No encrypted text available. Please encrypt first.")
        
        elif choice == "3":
            print("Exiting...")
            break
        
        else:
            print("Invalid choice. Please try again.")