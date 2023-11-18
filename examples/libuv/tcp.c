#include <stdio.h>
#include <uv.h>

void on_connect(uv_connect_t *req, int status) {
  fprintf(stderr, "Status: %d\n", status);

  uv_stream_t *handle = req->handle;

}

int main() {
  uv_loop_t *loop = uv_default_loop();

  struct sockaddr_in dest;
  uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
  uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));

  uv_tcp_init(loop, socket);
  uv_ip4_addr("172.253.63.101", 80, &dest);
  uv_tcp_connect(connect, socket, (const struct sockaddr*)&dest, on_connect);

  int c = 0;
  while (1) {
    fprintf(stderr, "Loop %d: - ", ++c);
    if (!uv_run(loop, UV_RUN_ONCE)) {
      break;
    }
  }
  return 0;
}
