#include "gula/base/CurrentThread.h"
#include "gula/base/Exception.h"
#include <functional>
#include <vector>
#include <stdio.h>

class Bar
{
 public:
  void test(std::vector<std::string> names = {})
  {
    printf("Stack:\n%s\n", gula::CurrentThread::stackTrace(true).c_str());
    [] {
      printf("Stack inside lambda:\n%s\n", gula::CurrentThread::stackTrace(true).c_str());
    }();
    std::function<void()> func([] {
      printf("Stack inside std::function:\n%s\n", gula::CurrentThread::stackTrace(true).c_str());
    });
    func();

    func = std::bind(&Bar::callback, this);
    func();

    throw gula::Exception("oops");
  }

 private:
   void callback()
   {
     printf("Stack inside std::bind:\n%s\n", gula::CurrentThread::stackTrace(true).c_str());
   }
};

void foo()
{
  Bar b;
  b.test();
}

int main()
{
  try
  {
    foo();
  }
  catch (const gula::Exception& ex)
  {
    printf("reason: %s\n", ex.what());
    printf("stack trace:\n%s\n", ex.stackTrace());
  }
}
