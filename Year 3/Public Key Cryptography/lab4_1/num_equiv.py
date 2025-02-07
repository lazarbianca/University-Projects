def compute_numerical_equivalent(block, alphabet):
    """
    Compute the numerical equivalent of a block of letters using base-27 encoding.

    Parameters:
    - block: A string of letters (e.g., "CDI").
    - alphabet: The mapping of characters to numerical values.

    Returns:
    - The numerical equivalent as an integer.
    """
    base = len(alphabet)
    numerical_value = 0

    for char in block:
        numerical_value = numerical_value * base + alphabet[char]

    return numerical_value


# Define the alphabet (27-character encoding: A-Z and '_')
alphabet = {'_': 0}  # Start with blank as 0
alphabet.update({chr(i): i - ord('A') + 1 for i in range(ord('A'), ord('Z') + 1)})  # A = 1, ..., Z = 26

# Example input: block of letters
block = "CAI"  # Example block

# Compute the numerical equivalent
numerical_equivalent = compute_numerical_equivalent(block, alphabet)

# Output the result
print(f"Block: {block}")
print(f"Numerical Equivalent: {numerical_equivalent}")
