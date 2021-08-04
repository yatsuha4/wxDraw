#pragma once

#define WXDRAW_DECLARE_ERROR(ErrorType)         \
  class Error::ErrorType                        \
    : public Error                              \
  {                                             \
    using Error::Error;                         \
  }

namespace wxdraw::node {
/**
   エラー
*/
class Error
  : public std::exception
{
 public:
  class RecursionRendering;

 private:
  wxString message_;

 public:
  Error(const wxString& message);
  Error(const Error& src) = default;
  ~Error() override = default;

  const char* what() const noexcept override;
};
WXDRAW_DECLARE_ERROR(RecursionRendering);
}
