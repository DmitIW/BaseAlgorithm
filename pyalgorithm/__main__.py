from pyalgorithm.algorithmlib import lib_init, print_algorithm_names

try:
    lib_init("cmake-build-debug/libalgorithms.dll")
except ...:
    print("Wrong context")
    raise
print_algorithm_names()
