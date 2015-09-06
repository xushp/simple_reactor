namespace net {
SockAcceptor::SockAcceptor(int _port) : port_(_port), handle(0) { 
  
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
  
  if 

  

}
}
