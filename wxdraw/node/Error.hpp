#pragma once

namespace wxdraw::node {
/**
   エラー
*/
class Error {
 public:
  enum {
    RECURSION_RENDERING, 
    MAX
  };

 private:
  std::bitset<MAX> error_;

 public:
  Error() = default;
  Error(const Error& src) = default;
  ~Error() = default;

  operator bool() const;
  Error& set(int code, bool value = true);
  bool test(int code) const;
};
}
