import ctypes
from sys import platform
from platform import architecture
from numpy.ctypeslib import ndpointer

_lib = None
_print_algorithm_names = None


def lib_init(path_to: str) -> None:
    global _lib, _print_algorithm_names
    try:
        print("Platform:", platform, "Arch:", architecture()[0])
        if platform == "linux" or platform == "linux2":
            _lib = ctypes.CDLL(path_to)
        else:
            _lib = ctypes.WinDLL(path_to)
        _print_algorithm_names = _lib.PrintAlgorithmNames
    except ...:
        print("Wrong context")
        raise


def print_algorithm_names() -> None:
    _print_algorithm_names()


class GeilShapley:
    _init = None
    _cleanup = None
    _add_left = None
    _add_right = None
    _apply = None

    _result_as_array = None

    def __init__(self, pair_size: int):
        self._init = _lib.init_geil_shapley
        self._init.argtypes = [ctypes.c_uint32]

        self._cleanup = _lib.cleanup_geil_shapley
        self._cleanup.argtypes = [ndpointer(dtype=ctypes.c_uint64)]

        self._add_left = _lib.geil_shapley_add_prefernce_left
        self._add_left.argtypes = [ctypes.c_uint32, ctypes.c_uint32, ctypes.c_int]

        self._add_right = _lib.geil_shapley_add_prefernce_right
        self._add_right.argtypes = [ctypes.c_uint32, ctypes.c_uint32, ctypes.c_int]

        self._init(pair_size)

    def __del__(self):
        if self._result_as_array is None:
            self._result_as_array = []
        self._cleanup(self._result_as_array)

    def apply(self, left: list, right: list, weights_left: list, weights_right: list) -> list:
        for i in range(0, len(left)):
            for j in range(0, len(left)):
                self._add_left(i, j, weights_left[i][j])
                self._add_right(j, i, weights_right[j][i])

        self._apply = _lib.geil_shapley_apply
        self._apply.restype = ndpointer(shape=(2, len(left)), dtype=ctypes.c_uint64)

        self._result_as_array = self._apply()
        result: list = []
        for i in range(0, len(left)):
            result.append([
                left[self._result_as_array[0, i]],
                right[self._result_as_array[1, i]]
            ])
        return result