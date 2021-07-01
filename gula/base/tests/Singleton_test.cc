#include "gula/base/Singleton.h"
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

class TestNoDestroy : gula::noncopyable
{
 public:
  // Tag member for Singleton<T>
  void no_destroy();

  TestNoDestroy()
  {
    printf("tid=%d, constructing TestNoDestroy %p\n", gula::CurrentThread::tid(), this);
  }

  ~TestNoDestroy()
  {
    printf("tid=%d, destructing TestNoDestroy %p\n", gula::CurrentThread::tid(), this);
  }
};

void threadFunc()
{
  printf("tid=%d, %p name=%s\n",
         gula::CurrentThread::tid(),
         &gula::Singleton<Test>::instance(),
         gula::Singleton<Test>::instance().name().c_str());
  gula::Singleton<Test>::instance().setName("only one, changed");
}

int main()
{
  gula::Singleton<Test>::instance().setName("only one");
  gula::Thread t1(threadFunc);
  t1.start();
  t1.join();
  printf("tid=%d, %p name=%s\n",
         gula::CurrentThread::tid(),
         &gula::Singleton<Test>::instance(),
         gula::Singleton<Test>::instance().name().c_str());
  gula::Singleton<TestNoDestroy>::instance();
  printf("with valgrind, you should see %zd-byte memory leak.\n", sizeof(TestNoDestroy));
}
