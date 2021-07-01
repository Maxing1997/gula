#include "gula/base/Singleton.h"
#include "gula/base/CurrentThread.h"
#include "gula/base/ThreadLocal.h"
#include "gula/base/Thread.h"

#include <stdio.h>
#include <unistd.h>

class Test : gula::noncopyable
{
 public:
  Test()
  {
    printf("tid=%d, constructing %p\n", gula::CurrentThread::tid(), this);
  }

  ~Test()
  {
    printf("tid=%d, destructing %p %s\n", gula::CurrentThread::tid(), this, name_.c_str());
  }

  const gula::string& name() const { return name_; }
  void setName(const gula::string& n) { name_ = n; }

 private:
  gula::string name_;
};

#define STL gula::Singleton<gula::ThreadLocal<Test> >::instance().value()

void print()
{
  printf("tid=%d, %p name=%s\n",
         gula::CurrentThread::tid(),
         &STL,
         STL.name().c_str());
}

void threadFunc(const char* changeTo)
{
  print();
  STL.setName(changeTo);
  sleep(1);
  print();
}

int main()
{
  STL.setName("main one");
  gula::Thread t1(std::bind(threadFunc, "thread1"));
  gula::Thread t2(std::bind(threadFunc, "thread2"));
  t1.start();
  t2.start();
  t1.join();
  print();
  t2.join();
  pthread_exit(0);
}
