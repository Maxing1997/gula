// Use of this source code is governed by a BSD-style license
// that can be found in the License file.


#ifndef GULA_BASE_EXCEPTION_H
#define GULA_BASE_EXCEPTION_H

#include "gula/base/Types.h"
#include <exception>

namespace gula
{

class Exception : public std::exception
{
 public:
  Exception(string what);
  ~Exception() noexcept override = default;

  // default copy-ctor and operator= are okay.

  const char* what() const noexcept override
  {
    return message_.c_str();
  }

  const char* stackTrace() const noexcept
  {
    return stack_.c_str();
  }

 private:
  string message_;
  string stack_;
};

}  // namespace gula

#endif  // GULA_BASE_EXCEPTION_H
