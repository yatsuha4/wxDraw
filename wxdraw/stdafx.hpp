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
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/propgrid.h>
#include <wx/treelist.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>
/**
   GLM
*/
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
/**
   C++
*/
#include <sstream>
#include <stack>
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
WXDRAW_DECLARE_CLASS(Command);
WXDRAW_DECLARE_CLASS(InsertNodeCommand);
}
using namespace command;

namespace component {
WXDRAW_DECLARE_CLASS(BrushComponent);
WXDRAW_DECLARE_CLASS(Component);
WXDRAW_DECLARE_CLASS(EllipseComponent);
WXDRAW_DECLARE_CLASS(LayerComponent);
WXDRAW_DECLARE_CLASS(LayoutComponent);
WXDRAW_DECLARE_CLASS(RectangleComponent);
}
using namespace component;

namespace container {
WXDRAW_DECLARE_CLASS(Layout);
WXDRAW_DECLARE_CLASS(Rect);
}
using namespace container;

namespace file {
WXDRAW_DECLARE_CLASS(Exporter);
WXDRAW_DECLARE_CLASS(Importer);
WXDRAW_DECLARE_CLASS(XmlExporter);
}
using namespace file;

namespace gui {
WXDRAW_DECLARE_CLASS(Canvas);
WXDRAW_DECLARE_CLASS(Inspector);
WXDRAW_DECLARE_CLASS(MainFrame);
WXDRAW_DECLARE_CLASS(Outliner);
WXDRAW_DECLARE_CLASS(Renderer);
}
using namespace gui;

namespace node {
WXDRAW_DECLARE_CLASS(EllipseNode);
WXDRAW_DECLARE_CLASS(LayerNode);
WXDRAW_DECLARE_CLASS(Node);
WXDRAW_DECLARE_CLASS(ProjectNode);
WXDRAW_DECLARE_CLASS(RectangleNode);
WXDRAW_DECLARE_CLASS(RootNode);
}
using namespace node;

namespace property {
WXDRAW_DECLARE_CLASS(MemberBase);
WXDRAW_DECLARE_CLASS(Property);
}
using namespace property;
}
