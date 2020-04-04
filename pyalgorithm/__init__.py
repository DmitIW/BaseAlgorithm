from pyalgorithm.algorithmlib import (lib_init,
                                      print_algorithm_names,
                                      _lib, GeilShapley)


def init_guard(func, *args):
    try:
        func(*args)
    except TypeError as e:
        print("Library was not init")
        print(e)
        raise RuntimeError("Library exception")


def available_algorithms_names() -> None:
    print("Available algorithms:")
    init_guard(print_algorithm_names)


def geil_shapley(left: list, left_weights: list,
                 right: list, right_weights: list) -> list:
    algo = GeilShapley(len(left))
    return algo.apply(left, right, left_weights, right_weights)


__all__ = [
    lib_init,
    available_algorithms_names,
    geil_shapley
]
