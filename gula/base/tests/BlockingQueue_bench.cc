#include "gula/base/BlockingQueue.h"
#include "gula/base/CountDownLatch.h"
#include "gula/base/Thread.h"
#include "gula/base/Timestamp.h"

#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>

class Bench
{
 public:
  Bench(int numThreads)
    : latch_(numThreads)
  {
    threads_.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i)
    {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      threads_.emplace_back(new gula::Thread(
            std::bind(&Bench::threadFunc, this), gula::string(name)));
    }
    for (auto& thr : threads_)
    {
      thr->start();
    }
  }

  void run(int times)
  {
    printf("waiting for count down latch\n");
    latch_.wait();
    printf("all threads started\n");
    for (int i = 0; i < times; ++i)
    {
      gula::Timestamp now(gula::Timestamp::now());
      queue_.put(now);
      usleep(1000);
    }
  }

  void joinAll()
  {
    for (size_t i = 0; i < threads_.size(); ++i)
    {
      queue_.put(gula::Timestamp::invalid());
    }

    for (auto& thr : threads_)
    {
      thr->join();
    }
  }

 private:

  void threadFunc()
  {
    printf("tid=%d, %s started\n",
           gula::CurrentThread::tid(),
           gula::CurrentThread::name());

    std::map<int, int> delays;
    latch_.countDown();
    bool running = true;
    while (running)
    {
      gula::Timestamp t(queue_.take());
      gula::Timestamp now(gula::Timestamp::now());
      if (t.valid())
      {
        int delay = static_cast<int>(timeDifference(now, t) * 1000000);
        // printf("tid=%d, latency = %d us\n",
        //        gula::CurrentThread::tid(), delay);
        ++delays[delay];
      }
      running = t.valid();
    }

    printf("tid=%d, %s stopped\n",
           gula::CurrentThread::tid(),
           gula::CurrentThread::name());
    for (const auto& delay : delays)
    {
      printf("tid = %d, delay = %d, count = %d\n",
             gula::CurrentThread::tid(),
             delay.first, delay.second);
    }
  }

  gula::BlockingQueue<gula::Timestamp> queue_;
  gula::CountDownLatch latch_;
  std::vector<std::unique_ptr<gula::Thread>> threads_;
};

int main(int argc, char* argv[])
{
  int threads = argc > 1 ? atoi(argv[1]) : 1;

  Bench t(threads);
  t.run(10000);
  t.joinAll();
}
