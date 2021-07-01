
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.


#include "gula/net/Poller.h"
#include "gula/net/poller/PollPoller.h"
#include "gula/net/poller/EPollPoller.h"

#include <stdlib.h>

using namespace gula::net;

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
  if (::getenv("GULA_USE_POLL"))
  {
    return new PollPoller(loop);
  }
  else
  {
    return new EPollPoller(loop);
  }
}
