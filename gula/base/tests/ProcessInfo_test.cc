#include "gula/base/ProcessInfo.h"
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

int main()
{
  printf("pid = %d\n", gula::ProcessInfo::pid());
  printf("uid = %d\n", gula::ProcessInfo::uid());
  printf("euid = %d\n", gula::ProcessInfo::euid());
  printf("start time = %s\n", gula::ProcessInfo::startTime().toFormattedString().c_str());
  printf("hostname = %s\n", gula::ProcessInfo::hostname().c_str());
  printf("opened files = %d\n", gula::ProcessInfo::openedFiles());
  printf("threads = %zd\n", gula::ProcessInfo::threads().size());
  printf("num threads = %d\n", gula::ProcessInfo::numThreads());
  printf("status = %s\n", gula::ProcessInfo::procStatus().c_str());
}
