#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#define WXDRAW_PLATFORM "mac"
#define WXDRAW_PLATFORM_MAC

#else
#error "not support platform"
#endif
/**
   wxWidgets
*/
#if defined(WXDRAW_PLATFORM_MAC)
#define _FILE_OFFSET_BITS 64
#define __WXMAC__
#define __WXOSX__
#define __WXOSX_COCOA__
#endif

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/cmdproc.h>
#include <wx/propgrid/propgrid.h>
#include <wx/treelist.h>
/**
   GLM
*/
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
/**
   マクロ定義
*/
#define WXDRAW_DECLARE_CLASS(klass)                             \
  class klass;                                                  \
  using klass##Ptr = std::shared_ptr<klass>;                    \
  using Const##klass##Ptr = std::shared_ptr<const klass>;

#define WXDRAW_SETTER(name, var)                                        \
  auto set##name(const decltype(var)& value) -> decltype(*this)& {      \
    var = value;                                                        \
    return *this;                                                       \
  }

#define WXDRAW_GETTER(name, var)                \
  const decltype(var)& get##name() const {      \
    return var;                                 \
  }

#define WXDRAW_ACCESSOR(name, var)              \
  WXDRAW_SETTER(name, var);                     \
  WXDRAW_GETTER(name, var);                     \
  decltype(var)& get##name() {                  \
    return var;                                 \
  }
/**
   クラス宣言
*/
namespace wxdraw {
WXDRAW_DECLARE_CLASS(Application);

namespace command {
WXDRAW_DECLARE_CLASS(InsertNode);
}
using namespace command;

namespace gui {
WXDRAW_DECLARE_CLASS(Canvas);
WXDRAW_DECLARE_CLASS(Inspector);
WXDRAW_DECLARE_CLASS(MainFrame);
WXDRAW_DECLARE_CLASS(Outliner);
WXDRAW_DECLARE_CLASS(Renderer);
}
using namespace gui;

namespace node {
WXDRAW_DECLARE_CLASS(Layer);
WXDRAW_DECLARE_CLASS(Node);
WXDRAW_DECLARE_CLASS(Project);
}
using namespace node;

namespace property {
WXDRAW_DECLARE_CLASS(MemberBase);
WXDRAW_DECLARE_CLASS(Property);
}
using namespace property;
}
