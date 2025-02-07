from math import gcd
import random
import sympy as sp
# Pollard’s ρ algorithm for integer factorization.
# The default function is f(x) = x^2 + 1 mod n, but it allows a user-defined function as well.


def gcd_recursive(a, b):
    # Recursive implementation of the Euclidean algorithm for gcd
    if b == 0:
        return a
    return gcd_recursive(b, a % b)


def pollards_rho(n, f):
    if f is None:
        f = default_f

    x = (random.randint(0, 2) % (n - 2)) # x0
    y = x
    d = 1

    while d == 1:
        x = f(x) % n  # tortoise move
        y = f(f(y)) % n  # hare move
        d = gcd(abs(x - y), n)
        print(f"x= {x}, y={y}, d={d}")

    if d == n:
        return pollards_rho(n, f)  # algorithm failed, try again with a different initial value
    else:
        return d  # found a non-trivial factor


def default_f(x):
    return x**2 + 1


def get_user_defined_function():
    print("\nFormat: a * x**2 + b * x + c")
    expression = input("Enter a polynomial : f(x) = ")
    x = sp.symbols('x')
    user_defined_function = sp.lambdify(x, expression, 'numpy')
    return user_defined_function


if __name__ == '__main__':
    #user_choice = input("Do you want to use the default function? (y/n): ").lower()

    #if user_choice == 'y':
    #     user_function = None  # use the default function
    # else:
    #     user_function = get_user_defined_function()

    n = 9983
    # n = 4087
    # n = 73
    # factor = pollards_rho(n, None)
    # print("Factors: {}, {}".format(factor, n // factor))

    n = 7453
    current_x = 4183
    res = default_f(current_x)
    print(f"{current_x}^2 + 1 = {res}")
    print(f"{res} mod {n} = {res % n}")

    x2j = 5299
    xj = 4835
    # print(gcd_recursive(21, 9983))
    print(f"gcd({abs(x2j-xj)},{n}) = {gcd(abs(x2j-xj),n)}")


    print(n/29)