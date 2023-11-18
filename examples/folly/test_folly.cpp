#include <folly/experimental/coro/Task.h>

folly::coro::Task<int> task42() {
  co_return 42;
}

int main() {
  
}
