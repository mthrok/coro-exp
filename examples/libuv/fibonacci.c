#include <stdio.h>
#include <uv.h>

#define MAX_N 25

typedef struct {
  long n;
  long val;
  long prev;
} state_t;

void compute(uv_work_t *req) {
  state_t* state = (state_t*) req->data;
  if (state->n > 1) {
    long tmp = state->val;
    state->val += state->prev;
    state->prev = tmp;
  }
  fprintf(stderr, "fib(%ld) = %lu\n", state->n, state->val);
}

void callback(uv_work_t *req, int status) {
  state_t* state = (state_t*) req->data;

  if (state->n < MAX_N) {
    // fprintf(stderr, "Queing next\n");
    state->n += 1;
    uv_queue_work(req->loop, req, compute, callback);
  } else {
    fprintf(stderr, "Done\n");
  }
}

int main() {
    uv_loop_t *loop = uv_default_loop();

    state_t state = { .n = 1, .prev = 1, .val = 0 };
    uv_work_t req;
    req.data = (void*) &state;
    uv_queue_work(loop, &req, compute, callback);

    int c = 0;
    while (1) {
      fprintf(stderr, "Loop %d: - ", ++c);
      if (!uv_run(loop, UV_RUN_ONCE)) {
        break;
      }
    }
    fprintf(stderr, "Final State: %ld\n", state.val);
    return 0;
}
