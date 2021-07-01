#include "gula/base/ThreadLocal.h"
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

gula::ThreadLocal<Test> testObj1;
gula::ThreadLocal<Test> testObj2;

void print()
{
  printf("tid=%d, obj1 %p name=%s\n",
         gula::CurrentThread::tid(),
         &testObj1.value(),
         testObj1.value().name().c_str());
  printf("tid=%d, obj2 %p name=%s\n",
         gula::CurrentThread::tid(),
         &testObj2.value(),
         testObj2.value().name().c_str());
}

void threadFunc()
{
  print();
  testObj1.value().setName("changed 1");
  testObj2.value().setName("changed 42");
  print();
}

int main()
{
  testObj1.value().setName("main one");
  print();
  gula::Thread t1(threadFunc);
  t1.start();
  t1.join();
  testObj2.value().setName("main two");
  print();

  pthread_exit(0);
}