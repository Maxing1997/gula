// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
#ifndef GULA_NET_POLLER_EPOLLPOLLER_H
#define GULA_NET_POLLER_EPOLLPOLLER_H

#include "gula/net/Poller.h"

#include <vector>

struct epoll_event;

namespace gula
{
namespace net
{

///
/// IO Multiplexing with epoll(4).
///
class EPollPoller : public Poller
{
 public:
  EPollPoller(EventLoop* loop);
  ~EPollPoller() override;

  Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;
  void updateChannel(Channel* channel) override;
  void removeChannel(Channel* channel) override;

 private:
  static const int kInitEventListSize = 16;

  static const char* operationToString(int op);

  void fillActiveChannels(int numEvents,
                          ChannelList* activeChannels) const;
  void update(int operation, Channel* channel);

  typedef std::vector<struct epoll_event> EventList;

  int epollfd_;
  EventList events_;
};

}  // namespace net
}  // namespace gula
#endif  // GULA_NET_POLLER_EPOLLPOLLER_H
