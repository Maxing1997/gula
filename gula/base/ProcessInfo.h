// Use of this source code is governed by a BSD-style license
// that can be found in the License file.


#ifndef GULA_BASE_PROCESSINFO_H
#define GULA_BASE_PROCESSINFO_H

#include "gula/base/StringPiece.h"
#include "gula/base/Types.h"
#include "gula/base/Timestamp.h"
#include <vector>
#include <sys/types.h>

namespace gula
{

namespace ProcessInfo
{
  pid_t pid();
  string pidString();
  uid_t uid();
  string username();
  uid_t euid();
  Timestamp startTime();
  int clockTicksPerSecond();
  int pageSize();
  bool isDebugBuild();  // constexpr

  string hostname();
  string procname();
  StringPiece procname(const string& stat);

  /// read /proc/self/status
  string procStatus();

  /// read /proc/self/stat
  string procStat();

  /// read /proc/self/task/tid/stat
  string threadStat();

  /// readlink /proc/self/exe
  string exePath();

  int openedFiles();
  int maxOpenFiles();

  struct CpuTime
  {
    double userSeconds;
    double systemSeconds;

    CpuTime() : userSeconds(0.0), systemSeconds(0.0) { }

    double total() const { return userSeconds + systemSeconds; }
  };
  CpuTime cpuTime();

  int numThreads();
  std::vector<pid_t> threads();
}  // namespace ProcessInfo

}  // namespace gula

#endif  // GULA_BASE_PROCESSINFO_H
