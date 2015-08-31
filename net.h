#ifndef NET_H_
#define NET_H_
namespace net {
class SockAcceptor {
 public:
  int get_handle(void);
};

class SockStream {

};

class InetAddr {
 public:
   InetAddr(int _port);
};
}
#endif
