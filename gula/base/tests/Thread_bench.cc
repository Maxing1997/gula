#include "gula/base/CurrentThread.h"
#include "gula/base/Mutex.h"
#include "gula/base/Thread.h"
#include "gula/base/Timestamp.h"

#include <map>
#include <string>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

gula::MutexLock g_mutex;
std::map<int, int> g_delays;

void threadFunc()
{
  //printf("tid=%d\n", gula::CurrentThread::tid());
}

void threadFunc2(gula::Timestamp start)
{
  gula::Timestamp now(gula::Timestamp::now());
  int delay = static_cast<int>(timeDifference(now, start) * 1000000);
  gula::MutexLockGuard lock(g_mutex);
  ++g_delays[delay];
}

void forkBench()
{
  sleep(10);
  gula::Timestamp start(gula::Timestamp::now());
  int kProcesses = 10*1000;

  for (int i = 0; i < kProcesses; ++i)
  {
    pid_t child = fork();
    if (child == 0)
    {
      exit(0);
    }
    else
    {
      waitpid(child, NULL, 0);
    }
  }

  double timeUsed = timeDifference(gula::Timestamp::now(), start);
  printf("process creation time used %f us\n", timeUsed*1000000/kProcesses);
  printf("number of created processes %d\n", kProcesses);
}

int main(int argc, char* argv[])
{
  printf("pid=%d, tid=%d\n", ::getpid(), gula::CurrentThread::tid());
  gula::Timestamp start(gula::Timestamp::now());

  int kThreads = 100*1000;
  for (int i = 0; i < kThreads; ++i)
  {
    gula::Thread t1(threadFunc);
    t1.start();
    t1.join();
  }

  double timeUsed = timeDifference(gula::Timestamp::now(), start);
  printf("thread creation time %f us\n", timeUsed*1000000/kThreads);
  printf("number of created threads %d\n", gula::Thread::numCreated());

  for (int i = 0; i < kThreads; ++i)
  {
    gula::Timestamp now(gula::Timestamp::now());
    gula::Thread t2(std::bind(threadFunc2, now));
    t2.start();
    t2.join();
  }
  {
    gula::MutexLockGuard lock(g_mutex);
    for (const auto& delay : g_delays)
    {
      printf("delay = %d, count = %d\n",
             delay.first, delay.second);
    }
  }

  forkBench();
}
