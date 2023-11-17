#include <uv.h>
#include <coroutine>
#include <iostream>

#define LOG() std::cerr << "    " << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl;

struct Task {
  struct promise_type;
  using coro_handle = std::coroutine_handle<promise_type>;

  coro_handle handle;

  explicit Task(coro_handle handle) : handle(handle) {};

  void resume() {
    handle.resume();
  }

  struct promise_type {
    void unhandled_exception() {
      LOG();
    }

    Task get_return_object() {
      LOG();
      return Task{ coro_handle::from_promise(*this) } ;
    }

    std::suspend_always initial_suspend() {
      LOG();
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
};

Task some_task() {
  LOG();
  co_return;
}

void job(uv_work_t *req) {
  LOG();

  Task* task = (Task*)(req->data);
  if (task) {
    task->resume();
  }
}

void callback(uv_work_t *req, int status) {
  LOG();
  
  Task* task = (Task*)(req->data);
  if (!task->handle.done()) {
    std::cerr << "Queue next" << std::endl;
    uv_queue_work(req->loop, req, job, callback);
  } else {
    std::cerr << "Done." << std::endl;
  }
}

int main() {
  std::cerr << "Initialize coroutine." << std::endl;
  auto task = some_task();

  std::cerr << "Creating event loop." << std::endl;
  uv_loop_t *loop  = uv_default_loop();

  std::cerr << "Queueing the coroutine." << std::endl;
  uv_work_t req;
  req.data = (void*) &task;
  uv_queue_work(loop, &req, job, callback);

  std::cerr << "Running loop." << std::endl;
  int c = 0;
  while (true) {
    std::cerr << "Loop " << ++c << std::endl;
    if (!uv_run(loop, UV_RUN_ONCE)) {
      break;
    }
  }
  return 0;
}
