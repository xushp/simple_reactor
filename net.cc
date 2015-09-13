#include "net.h"
namespace net {
SockAcceptor::SockAcceptor(int _port) : port_(_port), handle_(0) { 
  
}

int SockAcceptor::init(void) {
  int yes = 1;
  sockaddr_in local_address;

  if ((handle_ = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    return -1;
  }

  if (setsockopt(handle_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
    return -1;
  }

  local_address.sin_family = AF_INET;
  local_address.sin_addr.s_addr = INADDR_ANY;
  local_address.sin_port = htons(port_);
  
  if (bind(handle_, (struct sockaddr *)&local_address, sizeof(local_address)) == -1) {
    return -1;
  }
  
  if (listen(handle_, 10) == -1) {
    return -1;
  }
  return 0;
}

int SockAcceptor::accept_sock(SockStream &client_stream_) {
  socklen_t len = 0;
  if ((client_stream_.handle_ = accept(handle_,
                                      (struct sockaddr*)&client_stream_.remote_address_,
                                      &len)) == -1)
    return -1;
  return 0;
}

SockStream::SockStream() : handle_(0) {
  bzero(&remote_address_, sizeof(remote_address_));
  bzero(buf_, BUF_SIZE);
}

int SockStream::recv_stream() {
  size_t recv_count = 0;
  if ((recv_count = recv(handle_, buf_, BUF_SIZE, 0)) == -1)
    return -1;
  else {
    buf_[recv_count] = '\0';
    std::cout << buf_ << std::endl;
  }
}

}
