def decode_ciphertext(ciphertext_value, alphabet):
    """
    Decode a numerical ciphertext value into letters using base-27 encoding.

    Parameters:
    - ciphertext_value: The integer value to decode.
    - alphabet: The mapping of numbers to characters.

    Returns:
    - A string representing the decoded letter block.
    """
    block = []
    base = len(alphabet)

    while ciphertext_value > 0:
        remainder = ciphertext_value % base
        block.append(alphabet[remainder])
        ciphertext_value //= base

    # The result is in reverse order, so reverse it back
    return ''.join(reversed(block))


# Define the alphabet (27-character encoding: A-Z and '_')
alphabet = ['_'] + [chr(i) for i in range(ord('A'), ord('Z') + 1)]  # _ = 0, A = 1, ..., Z = 26

# Ciphertext values to decode
ciphertext_values = [4066, 1372, 2994]

# Decode each ciphertext value
decoded_blocks = [decode_ciphertext(value, alphabet) for value in ciphertext_values]

# Ensure each block is 3 characters long by prepending blanks (if needed)
decoded_blocks = [block.rjust(3, '_') for block in decoded_blocks]

# Combine decoded blocks into the final ciphertext string
decoded_message = ''.join(decoded_blocks)

# Output the results
print("Decoded Blocks:", decoded_blocks)
print("Final Ciphertext:", decoded_message)
