from math import gcd

def is_prime(n):
    """
    Check if a number is a prime number.
    """
    if n < 2:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

def smallest_prime_coprime_to(a):
    """
    Find the smallest prime number coprime to 'a'.
    """
    candidate = 2  # Start with the smallest prime number
    while True:
        if gcd(a, candidate) == 1 and is_prime(candidate):
            return candidate
        candidate += 1

# Input the number 'a'
a = int(input("Enter a number: "))

# Find and output the smallest prime coprime to 'a'
result = smallest_prime_coprime_to(a)
print(f"The smallest prime number coprime to {a} is {result}.")
