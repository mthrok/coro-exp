#include <folly/experimental/coro/Task.h>
#include <folly/experimental/coro/BlockingWait.h>

folly::coro::Task<int> task42() {
  co_return 42;
}

folly::coro::Task<int> taskSlow43() {
  co_await folly::futures::sleep(std::chrono::seconds{1});
  co_return co_await task42() + 1;
}

int main() {

  CHECK_EQ(43, folly::coro::blockingWait(taskSlow43().scheduleOn(
                   folly::getGlobalCPUExecutor().get())));  
}
