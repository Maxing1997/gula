#ifndef GULA_NET_EVENTLOOPTHREAD_H
#define GULA_NET_EVENTLOOPTHREAD_H

#include "gula/base/Condition.h"
#include "gula/base/Mutex.h"
#include "gula/base/Thread.h"

namespace gula
{
namespace net
{

class EventLoop;

class EventLoopThread : noncopyable
{
 public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;

  EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),
                  const string& name = string());
  ~EventLoopThread();
  EventLoop* startLoop();

 private:
  void threadFunc();

  EventLoop* loop_ GUARDED_BY(mutex_);
  bool exiting_;
  Thread thread_;
  MutexLock mutex_;
  Condition cond_ GUARDED_BY(mutex_);
  ThreadInitCallback callback_;
};

}  // namespace net
}  // namespace gula

#endif  // GULA_NET_EVENTLOOPTHREAD_H

