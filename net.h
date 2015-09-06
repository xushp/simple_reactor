#ifndef NET_H_
#define NET_H_
namespace net {
class SockAcceptor {
 public:
  SockAcceptor(int _port); 
  inline int get_handle(void) {
    return handle_;
  }
  int init(void);
 private:
  int handle_;
  int port_;
};

class SockStream {

};

class InetAddr {
 public:
   InetAddr(int _port);
};
}
#endif
