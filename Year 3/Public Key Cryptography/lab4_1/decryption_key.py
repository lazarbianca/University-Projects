def gcd_extended(a, b):
    """
    Extended Euclidean Algorithm to find gcd and coefficients.
    Solves ax + by = gcd(a, b).
    Returns gcd, x, y.
    """
    if a == 0:
        return b, 0, 1
    gcd, x1, y1 = gcd_extended(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return gcd, x, y

def compute_decryption_key(e, phi_n):
    """
    Compute the decryption key d, where d * e ≡ 1 (mod phi_n).
    """
    gcd, x, _ = gcd_extended(e, phi_n)
    if gcd != 1:
        raise ValueError("e and phi_n are not coprime!")
    return x % phi_n  # Ensure d is positive

# RSA Parameters
p = 67  # Example prime 1
q = 73  # Example prime 2
e = 5  # Encryption exponent

# Compute n and phi(n)
n = p * q
phi_n = (p - 1) * (q - 1)

# Compute the decryption key
d = compute_decryption_key(e, phi_n)

# Output the results
print(f"p = {p}, q = {q}, n = {n}, phi(n) = {phi_n}")
print(f"Encryption key (e) = {e}")
print(f"Decryption key (d) = {d}")
