// Use of this source code is governed by a BSD-style license
// that can be found in the License file.


#ifndef GULA_BASE_ASYNCLOGGING_H
#define GULA_BASE_ASYNCLOGGING_H

#include "gula/base/BlockingQueue.h"
#include "gula/base/BoundedBlockingQueue.h"
#include "gula/base/CountDownLatch.h"
#include "gula/base/Mutex.h"
#include "gula/base/Thread.h"
#include "gula/base/LogStream.h"

#include <atomic>
#include <vector>

namespace gula
{

class AsyncLogging : noncopyable
{
 public:

  AsyncLogging(const string& basename,
               off_t rollSize,
               int flushInterval = 3);

  ~AsyncLogging()
  {
    if (running_)
    {
      stop();
    }
  }

  void append(const char* logline, int len);

  void start()
  {
    running_ = true;
    thread_.start();
    latch_.wait();
  }

  void stop() NO_THREAD_SAFETY_ANALYSIS
  {
    running_ = false;
    cond_.notify();
    thread_.join();
  }

 private:

  void threadFunc();

  typedef gula::detail::FixedBuffer<gula::detail::kLargeBuffer> Buffer;
  typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
  typedef BufferVector::value_type BufferPtr;

  const int flushInterval_;
  std::atomic<bool> running_;
  const string basename_;
  const off_t rollSize_;
  gula::Thread thread_;
  gula::CountDownLatch latch_;
  gula::MutexLock mutex_;
  gula::Condition cond_ GUARDED_BY(mutex_);
  BufferPtr currentBuffer_ GUARDED_BY(mutex_);
  BufferPtr nextBuffer_ GUARDED_BY(mutex_);
  BufferVector buffers_ GUARDED_BY(mutex_);
};

}  // namespace gula

#endif  // GULA_BASE_ASYNCLOGGING_H
