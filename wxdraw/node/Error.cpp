#include "wxdraw/node/Error.hpp"

namespace wxdraw::node {
/**
 */
Error::Error(const wxString& message)
  : message_(message)
{}
/**
 */
const char* Error::what() const noexcept {
  return message_.c_str();
}
}
