# ------------------------------------------------------------------------------

add_executable(
  test_folly
  test_folly.cpp
  )
target_link_libraries(test_folly folly)
list(APPEND examples test_folly)

# ------------------------------------------------------------------------------


set(examples "${examples}" PARENT_SCOPE)
