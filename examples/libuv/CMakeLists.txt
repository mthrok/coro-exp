# ------------------------------------------------------------------------------

add_executable(
  libuv_fibonacci
  fibonacci.c
  )
target_link_libraries(libuv_fibonacci uv_a)
list(APPEND examples libuv_fibonacci)

# ------------------------------------------------------------------------------

add_executable(
  libuv_tcp
  tcp.c
  )
target_link_libraries(libuv_tcp uv_a)
list(APPEND examples libuv_tcp)

# ------------------------------------------------------------------------------

add_executable(
  libuv_coroutine
  coroutine.cpp
  )
target_link_libraries(libuv_coroutine uv_a)
list(APPEND examples libuv_coroutine)

# ------------------------------------------------------------------------------

add_executable(
  libuv_coroutine_fibonacci
  coroutine_fibonacci.cpp
  )
target_link_libraries(libuv_coroutine_fibonacci uv_a)
list(APPEND examples libuv_coroutine_fibonacci)

# ------------------------------------------------------------------------------

set(examples "${examples}" PARENT_SCOPE)
