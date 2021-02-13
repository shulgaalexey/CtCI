# Given two natural numbers
# Return max using operations: + - / * % =


# If a < b return 0, otherwise 1
def suppress_min(a, b):
    z = a / b
    d = 1 - 1 % (z + 1)
    return d


# If numbers are equal, returns 1, otherwise 0
def suppress_dif(a, b):
    # If numbers are equal,then a % b is 0, same as the opposite
    d = a % b + b % a
    # We need it to be mapped to:
    # d = 0           ->  r = 1
    # d = 1, 2, 3...  ->  r = 0
    r = 1 - 1 % (d + 1)
    return r


def get_max(a, b):
    z1 = suppress_min(a, b)
    z2 = suppress_min(b, a)
    zd = suppress_dif(a, b)
    my_max = z1 * b + z2 * a + zd * a
    return my_max


print("Exhostive testing.............")
for i in range(1, 10):
    for j in range(1, 10):
        my_max1 = get_max(i, j)
        my_max2 = get_max(j, i)
        true_max = i if i > j else j
        if (my_max1 != true_max):
            print("Error:  Max of %s and %s is %s" % (i, j, my_max1))
        if (my_max2 != true_max):
            print("Error:  Max of %s and %s is %s" % (j, i, my_max2))

print("DONE")
