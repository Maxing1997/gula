#include "gula/base/ThreadLocalSingleton.h"
#include "gula/base/CurrentThread.h"
#include "gula/base/Thread.h"

#include <stdio.h>

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

void threadFunc(const char* changeTo)
{
  printf("tid=%d, %p name=%s\n",
         gula::CurrentThread::tid(),
         &gula::ThreadLocalSingleton<Test>::instance(),
         gula::ThreadLocalSingleton<Test>::instance().name().c_str());
  gula::ThreadLocalSingleton<Test>::instance().setName(changeTo);
  printf("tid=%d, %p name=%s\n",
         gula::CurrentThread::tid(),
         &gula::ThreadLocalSingleton<Test>::instance(),
         gula::ThreadLocalSingleton<Test>::instance().name().c_str());

  // no need to manually delete it
  // gula::ThreadLocalSingleton<Test>::destroy();
}

int main()
{
  gula::ThreadLocalSingleton<Test>::instance().setName("main one");
  gula::Thread t1(std::bind(threadFunc, "thread1"));
  gula::Thread t2(std::bind(threadFunc, "thread2"));
  t1.start();
  t2.start();
  t1.join();
  printf("tid=%d, %p name=%s\n",
         gula::CurrentThread::tid(),
         &gula::ThreadLocalSingleton<Test>::instance(),
         gula::ThreadLocalSingleton<Test>::instance().name().c_str());
  t2.join();

  pthread_exit(0);
}
