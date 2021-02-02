#include "proc-server/server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <ctime>
#include <iostream>

#include "proc-server/proc.h"

namespace procserver {

#define PORT 9909

void SetSystemInfoDetails(procserver::SystemInfo* systeminfo) {
  const char* sysctlvalues[] = {SYS_UPTIME, SYS_RAMSIZE, SYS_LOADAVG};
  get_system_info(systeminfo, sysctlvalues,
                  sizeof(sysctlvalues) / sizeof(sysctlvalues[0]));
}

}  // namespace procserver

int main(int argc, char const* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  procserver::SystemInfo system_info;

  int server_fd, new_socket, valread;
  struct sockaddr_in socket_address;
  int opt = 1;
  int addrlen = sizeof(socket_address);
  const char* hello = "Hello from server";

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  socket_address.sin_family = AF_INET;
  socket_address.sin_addr.s_addr = INADDR_ANY;
  socket_address.sin_port = htons(PORT);

  // Forcefully attaching socket to the port
  if (bind(server_fd, reinterpret_cast<struct sockaddr*>(&socket_address),
           sizeof(socket_address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  while (1) {
    if ((new_socket = accept(server_fd, (struct sockaddr*)&socket_address,
                             reinterpret_cast<socklen_t*>(&addrlen))) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }
    char buffer[1024] = {0};
    valread = read(new_socket, buffer, 1024);
    printf("[*] CLIENT | %s\n", buffer);

    // Add an details.
    procserver::SetSystemInfoDetails(&system_info);

    std::string data;
    system_info.SerializeToString(&data);
    char bts[data.length()];  // NOLINT(runtime/arrays)
    snprintf(bts, data.length() + 1, "%s", data.c_str());

    // Sending data to client
    if ((send(new_socket, bts, sizeof(bts), 0)) < 0) {
      perror("send");
      exit(EXIT_FAILURE);
    }
    printf("[*] SERVER | TCP Packets sent\n");
    close(new_socket);
    sleep(1);
  }
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
