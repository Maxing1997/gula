// Use of this source code is governed by a BSD-style license
// that can be found in the License file.


#ifndef GULA_BASE_COUNTDOWNLATCH_H
#define GULA_BASE_COUNTDOWNLATCH_H

#include "gula/base/Condition.h"
#include "gula/base/Mutex.h"

namespace gula
{

class CountDownLatch : noncopyable
{
 public:

  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  int getCount() const;

 private:
  mutable MutexLock mutex_;
  Condition condition_ GUARDED_BY(mutex_);
  int count_ GUARDED_BY(mutex_);
};

}  // namespace gula
#endif  // GULA_BASE_COUNTDOWNLATCH_H
