/***********************************************************************//**
	@file
***************************************************************************/
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#define GRAED_PLATFORM "mac"
#define GRAED_PLATFORM_MAC

#else
#error "not support platform"
#endif
/***********************************************************************//**
	@brief 
***************************************************************************/
#if defined(GRAED_PLATFORM_MAC)
#define _FILE_OFFSET_BITS 64
#define __WXMAC__
#define __WXOSX__
#define __WXOSX_COCOA__
#endif

#include <wx/wx.h>
#include <wx/aui/aui.h>
/***********************************************************************//**
	@brief 
***************************************************************************/
#define GRAED_DECLARE_CLASS(klass)                              \
  class klass;                                                  \
  using klass##Ptr = std::shared_ptr<klass>;                    \
  using Const##klass##Ptr = std::shared_ptr<const klass>;

#define GRAED_SETTER(name, var)                                         \
  auto set##name(const decltype(var)& value) -> decltype(*this)& {      \
    var = value;                                                        \
    return *this;                                                       \
  }

#define GRAED_GETTER(name, var)                 \
  const decltype(var)& get##name() const {      \
    return var;                                 \
  }

#define GRAED_ACCESSOR(name, var)               \
  FDK_SETTER(name, var);                        \
  FDK_GETTER(name, var);                        \
  decltype(var)& get##name() {                  \
    return var;                                 \
  }
/***********************************************************************//**
	@brief 
***************************************************************************/
namespace graed {
GRAED_DECLARE_CLASS(Application);
GRAED_DECLARE_CLASS(Canvas);
GRAED_DECLARE_CLASS(Layer);
GRAED_DECLARE_CLASS(MainFrame);
}
/***********************************************************************//**
	$Id$
***************************************************************************/
