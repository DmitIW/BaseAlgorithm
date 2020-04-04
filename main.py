from pyalgorithm import available_algorithms_names, lib_init, geil_shapley

if __name__ == "__main__":
    lib_init("cmake-build-debug/libalgorithms.dll")
    available_algorithms_names()

    left: list = [
        "Adam", "Marcus", "Tom"
    ]

    right: list = [
        "Anna", "Elizabeth", "Marry"
    ]

    weights_left: list = [
        [10, 9, 12],
        [11, 7, 14],
        [5, 17, 3]
    ]

    weight_right: list = [
        [5, 4, 1],
        [6, 18, 2],
        [18, 2, 3]
    ]

    for pair in geil_shapley(left, weights_left, right, weight_right):
        print(pair[0], "+", pair[1])

