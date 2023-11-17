#include <uv.h>
#include <coroutine>
#include <iostream>

#ifdef DBG
#define LOG() std::cerr << "    " << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl;
#else
#define LOG()
#endif

struct Task {
  struct promise_type;
  using coro_handle = std::coroutine_handle<promise_type>;

  coro_handle handle;
};

struct Task::promise_type {
  void unhandled_exception() {
    LOG();
  }

  Task get_return_object() {
    LOG();
    return Task{ .handle = coro_handle::from_promise(*this) } ;
  }

  std::suspend_always initial_suspend() {
    LOG();
    return {};
  }

  std::suspend_always yield_value(long i) {
    LOG();
    std::cerr << i << std::endl;
    return {};
  }

  void return_void() {
    LOG();
  }

  std::suspend_always final_suspend() noexcept {
    LOG();
    return {};
  }
};


Task fib(long n) {
  LOG();

  long n1 = 0, n2 = 1, tmp;
  co_yield n1;
  co_yield n2;

  for (size_t i = 2; i < n; ++i) {
    tmp = n1 + n2;
    n1 = n2;
    n2 = tmp;
    co_yield n2;
  }
}

void job(uv_work_t *req) {
  LOG();

  Task* task = (Task*)(req->data);
  if (task) {
    task->handle.resume();
  }
}

void callback(uv_work_t *req, int status) {
  LOG();
  
  Task* task = (Task*)(req->data);
  if (!task->handle.done()) {
    uv_queue_work(req->loop, req, job, callback);
  }
}

int main() {
  std::cerr << "Initialize coroutine." << std::endl;
  auto task = fib(10);
  auto &promise = task.handle.promise();

  std::cerr << "Creating event loop." << std::endl;
  uv_loop_t *loop  = uv_default_loop();

  std::cerr << "Queueing the coroutine." << std::endl;
  uv_work_t req;
  req.data = (void*) &task;
  uv_queue_work(loop, &req, job, callback);

  std::cerr << "Running loop." << std::endl;
  int c = 0;
  while (true) {
    ++c;
    std::cerr << "Loop " << c << std::endl;
    if (!uv_run(loop, UV_RUN_ONCE)) {
      break;
    }
  }
  return 0;
}
