# Prototype playground for learning C++ coroutines and libuv

## Libuv

- [fibonacci](./examples/libuv/fibonacci.c)
  A simple C code which splits the regular fibonacci calculation into series of events.

- [coroutine](./examples/libuv/coroutine.cpp)
  A simple C++ code in which coroutine is executed via libuv event loop.

- [coroutine_fibonacci](./examples/libuv/coroutine_fibonacci.cpp)
  Adopt coroutine in fibonacci calculation and execute it via libuv event loop.
