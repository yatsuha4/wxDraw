#include "wxdraw/node/Error.hpp"

namespace wxdraw::node {
/**
 */
Error::operator bool() const {
  return error_.any();
}
/**
 */
Error& Error::set(int code, bool value) {
  error_.set(code, value);
  return *this;
}
/**
 */
bool Error::test(int code) const {
  return error_.test(code);
}
}
