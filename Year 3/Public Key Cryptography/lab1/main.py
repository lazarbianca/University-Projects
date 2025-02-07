import time


# GCD (highest common factor) for 2 nrs algorithm comparison
# one for nrs of arbitrary size

# Recursive algorithm: Euclidean; highest common factor
def hcf(a, b):
    if b == 0:
        return a
    else:
        return hcf(b, a % b)


# Recursive function to return gcd of a and b
def gcd_recursive(a, b):
    # Everything divides 0 (zero divided by anything is that number)
    if a == 0:
        return b
    if b == 0:
        return a

    # base case
    if a == b:
        return a

    # a is greater
    if a > b:
        return gcd_recursive(a - b, b)
    return gcd_recursive(a, b - a)


# stein's algorithm - non negative nrs
def gcd_stein(a, b):
    # Everything divides 0 (zero divided by anything is that number)
    if a == 0:
        return b

    if b == 0:
        return a

    # Find K = greatest power of 2 that divides both a and b
    k = 0
    # bitwise operations:
    # if zero => nr is even; else odd
    # if both a and b are even, shift right and discard remainder (divide by 2 until one is odd)
    while ((a | b) & 1) == 0:
        a = a >> 1
        b = b >> 1
        k = k + 1

    # divide a by 2 until it becomes odd
    while (a & 1) == 0:
        a = a >> 1

    # from here on, "a" is ALWAYS odd
    while b != 0:
        # if b is even, remove all factor of 2 in b
        while (b & 1) == 0:
            b = b >> 1

        # here, a and b are both odd; put min(a,b) in a
        if a > b:
            # swap
            temp = a
            a = b
            b = temp
        # b - a  is an even result
        b = (b - a)

    # when b becomes 0, the remaining value of a is the GCD
    # restore common factors of 2
    return a << k


if __name__ == "__main__":
    inputs = [(12, 0),
              (0, 4356),
              (15, 23),
              (22, 48),
              (2020938, 73847239),
              (4566436623737373773, 673237373736363636),
              (12345368273782578346, 67378436876438634864),
              (12 ** 3, 10 ** 3),
              (14 ** 7, 12 ** 10),
              (20 ** 9, 30 ** 9)

              ]

    for pair in inputs:
        a, b = pair
        t1_start = time.perf_counter()
        result_hcf = hcf(a, b)
        t1_stop = time.perf_counter()

        print("HCF result for a = ", a, " b = ", b, " is: ", result_hcf, ", runtime: ", t1_stop - t1_start)

        t2_start = time.perf_counter()
        result_gcd_recursive = gcd_recursive(a, b)
        t2_stop = time.perf_counter()

        print("GCD_recursive result for a = ", a, " b = ", b, " is: ", result_gcd_recursive, ", runtime: ",
              t2_stop - t2_start)

        t3_start = time.perf_counter()
        result_gcd_stein = gcd_stein(a, b)
        t3_stop = time.perf_counter()

        print("GCD_lambda runtime for a = ", a, " b = ", b, " is: ", result_gcd_stein, ", runtime: ",
              t3_stop - t3_start)
        print('\n')
