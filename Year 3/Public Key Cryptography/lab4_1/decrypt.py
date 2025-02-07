def mod_exp(base, exp, mod):
    """
    Efficient modular exponentiation (base^exp % mod).
    """
    result = 1
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp //= 2
    return result


def decrypt_ciphertext(ciphertext_block, d, n, alphabet):
    """
    Decrypt a numerical ciphertext block using RSA decryption.
    """
    # Decrypt the ciphertext block (C^d % n)
    decrypted_value = mod_exp(ciphertext_block, d, n)
    print(decrypted_value)
    # Convert the numerical decrypted value back to letters (base-27)
    decrypted_message = decode_numerical_value(decrypted_value, alphabet)

    return decrypted_message


def decode_numerical_value(value, alphabet):
    """
    Decode a numerical value to letters using base-27 encoding.
    """
    block = []
    base = len(alphabet)

    while value > 0:
        remainder = value % base
        block.append(alphabet[remainder])
        value //= base

    # Reverse to get the correct order
    return ''.join(reversed(block))


# Define the alphabet (27-character encoding: A-Z and '_')
alphabet = ['_'] + [chr(i) for i in range(ord('A'), ord('Z') + 1)]  # _ = 0, A = 1, ..., Z = 26

# Example ciphertext blocks (numeric equivalents)
ciphertext_blocks = [2304, 4685, 2223]  # Replace with your actual ciphertext values

# RSA parameters
d = 1901
n = 4891

# Decrypt each block
decrypted_blocks = [decrypt_ciphertext(block, d, n, alphabet) for block in ciphertext_blocks]

# Output the decrypted message
decrypted_message = ''.join(decrypted_blocks)

print(f"Decrypted Message: {decrypted_message}")
