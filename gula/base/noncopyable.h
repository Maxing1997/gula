#ifndef GULA_BASE_NONCOPYABLE_H
#define GULA_BASE_NONCOPYABLE_H

namespace gula
{

class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

}  // namespace gula

#endif  // GULA_BASE_NONCOPYABLE_H
