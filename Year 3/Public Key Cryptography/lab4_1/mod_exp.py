def modular_exponentiation(base, exponent, modulus):
    """
    Compute (base^exponent) % modulus efficiently.
    """
    result = 1  # Initialize result
    base = base % modulus  # Reduce base if it's greater than modulus

    while exponent > 0:
        # If the exponent is odd, multiply the base with the result
        if exponent % 2 == 1:
            result = (result * base) % modulus

        # Update exponent to half and square the base
        exponent = exponent // 2
        base = (base * base) % modulus

    return result


# Values
base = 405
exponent = 7
modulus = 5063

# Compute and print the result
result = modular_exponentiation(base, exponent, modulus)
print(f"({base}^{exponent}) % {modulus} = {result}")
