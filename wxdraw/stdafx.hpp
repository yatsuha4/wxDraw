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
#include <wx/artprov.h>
#include <wx/aui/aui.h>
#include <wx/cmdproc.h>
#include <wx/dataview.h>
#include <wx/listctrl.h>
#include <wx/numformatter.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/propgrid.h>
#include <wx/regex.h>
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
#include <map>
#include <stack>
#include <typeindex>
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
  }                                                                     \
  decltype(var)& get##name() {                                          \
    return var;                                                         \
  }
#define WXDRAW_GETTER(name, var)                \
  const decltype(var)& get##name() const {      \
    return var;                                 \
  }
#define WXDRAW_IS_GETTER(name, var)             \
  bool is##name() const {                       \
    return var;                                 \
  }
#define WXDRAW_CAN_GETTER(name, var)            \
  bool can##name() const {                      \
    return var;                                 \
  }
#define WXDRAW_ACCESSOR(name, var)              \
  WXDRAW_SETTER(name, var);                     \
  WXDRAW_GETTER(name, var);
#define WXDRAW_IS_ACCESSOR(name, var)           \
  WXDRAW_SETTER(name, var);                     \
  WXDRAW_IS_GETTER(name, var);
#define WXDRAW_CAN_ACCESSOR(name, var)          \
  WXDRAW_SETTER(name, var);                     \
  WXDRAW_CAN_GETTER(name, var);
/**
   クラス宣言
*/
namespace wxdraw {
WXDRAW_DECLARE_CLASS(Application);

namespace command {
}
using namespace command;

namespace component {
WXDRAW_DECLARE_CLASS(BrushComponent);
WXDRAW_DECLARE_CLASS(ComponentBase);
WXDRAW_DECLARE_CLASS(CompositionComponent);
WXDRAW_DECLARE_CLASS(ContainerComponent);
WXDRAW_DECLARE_CLASS(EllipseComponent);
WXDRAW_DECLARE_CLASS(GridComponent);
WXDRAW_DECLARE_CLASS(LayerComponent);
WXDRAW_DECLARE_CLASS(LayoutComponent);
WXDRAW_DECLARE_CLASS(PaletteComponent);
WXDRAW_DECLARE_CLASS(PenComponent);
WXDRAW_DECLARE_CLASS(ProjectComponent);
WXDRAW_DECLARE_CLASS(ProxyComponent);
WXDRAW_DECLARE_CLASS(RectangleComponent);
WXDRAW_DECLARE_CLASS(TextComponent);
WXDRAW_DECLARE_CLASS(ViewComponent);
}
using namespace component;

namespace container {
WXDRAW_DECLARE_CLASS(Layout);
WXDRAW_DECLARE_CLASS(Rect);
}
using namespace container;

namespace file {
WXDRAW_DECLARE_CLASS(Exporter);
WXDRAW_DECLARE_CLASS(ImageExporter);
WXDRAW_DECLARE_CLASS(Importer);
WXDRAW_DECLARE_CLASS(XmlExporter);
WXDRAW_DECLARE_CLASS(XmlImporter);
}
using namespace file;

namespace gui {
WXDRAW_DECLARE_CLASS(Canvas);
WXDRAW_DECLARE_CLASS(GradientList);
WXDRAW_DECLARE_CLASS(GradientStopList);
WXDRAW_DECLARE_CLASS(ImageList);
WXDRAW_DECLARE_CLASS(Inspector);
WXDRAW_DECLARE_CLASS(MainFrame);
WXDRAW_DECLARE_CLASS(Menu);
WXDRAW_DECLARE_CLASS(Outliner);
WXDRAW_DECLARE_CLASS(Palette);
WXDRAW_DECLARE_CLASS(PaletteListBase);
WXDRAW_DECLARE_CLASS(Renderer);
}
using namespace gui;

namespace node {
WXDRAW_DECLARE_CLASS(Error);
WXDRAW_DECLARE_CLASS(Node);
}
using namespace node;

namespace object {
WXDRAW_DECLARE_CLASS(Object);
}
using namespace object;

namespace palette {
WXDRAW_DECLARE_CLASS(Brush);
WXDRAW_DECLARE_CLASS(Color);
WXDRAW_DECLARE_CLASS(ColorBase);
WXDRAW_DECLARE_CLASS(Font);
WXDRAW_DECLARE_CLASS(Gradient);
WXDRAW_DECLARE_CLASS(GradientStop);
WXDRAW_DECLARE_CLASS(PaletteItem);
WXDRAW_DECLARE_CLASS(Pen);
WXDRAW_DECLARE_CLASS(PenBase);
}
using namespace palette;

namespace property {
WXDRAW_DECLARE_CLASS(Choice);
WXDRAW_DECLARE_CLASS(MemberBase);
WXDRAW_DECLARE_CLASS(Property);
WXDRAW_DECLARE_CLASS(PropertyMember);
}
using namespace property;
}
#define WXDRAW_PROPERTY_CLASSES                 \
  int,                                          \
    double,                                     \
    bool,                                       \
    wxString,                                   \
    wxColour,                                   \
    wxFileName,                                 \
    wxFont,                                     \
    Choice,                                     \
    PenPtr,                                     \
    BrushPtr,                                   \
    ColorPtr,                                   \
    ColorBasePtr,                               \
    FontPtr,                                    \
    NodePtr
