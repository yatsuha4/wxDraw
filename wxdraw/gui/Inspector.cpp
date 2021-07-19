#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/Menu.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/Property.hpp"
#include "wxdraw/property/PropertyMember.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param parent 親
   @param mainFrame メインフレーム
*/
Inspector::Inspector(wxWindow* parent, MainFrame* mainFrame)
  : super(parent, wxID_ANY), 
    mainFrame_(mainFrame)
{
  Bind(wxEVT_PG_CHANGED, &Inspector::onChanged, this);
  Bind(wxEVT_PG_RIGHT_CLICK, &Inspector::onRightClick, this);
}
/**
 */
void Inspector::show(const PropertyPtr& property) {
  clear();
  property_ = property;
  showProperty(*property);
  SetPropertyAttributeAll(wxPG_BOOL_USE_CHECKBOX, true);
  SetPropertyAttributeAll(wxPG_COLOUR_ALLOW_CUSTOM, true);
  SetPropertyAttributeAll(wxPG_COLOUR_HAS_ALPHA, true);
}
/**
 */
void Inspector::clear() {
  Clear();
  property_ = nullptr;
}
/**
 */
void Inspector::showProperty(const Property& property) {
  for(auto& iter : property.getMembers()) {
    if(auto m = std::dynamic_pointer_cast<PropertyMember>(iter)) {
      Append(new wxPropertyCategory(m->getName()));
      showProperty(*m->getProperty());
    }
    else if(auto member = Member<int>::As(iter)) {
      append<wxIntProperty>(member);
    }
    else if(auto member = Member<double>::As(iter)) {
      append<wxFloatProperty>(member);
    }
    else if(auto member = Member<bool>::As(iter)) {
      append<wxBoolProperty>(member);
    }
    else if(auto member = Member<wxString>::As(iter)) {
      append<wxStringProperty>(member);
    }
    else if(auto member = Member<wxColour>::As(iter)) {
      append<wxColourProperty>(member);
    }
    else if(auto member = Member<wxFileName>::As(iter)) {
      append<wxFileProperty>(member, member->getValue().GetFullPath());
    }
    else if(auto m = Member<wxFont>::As(iter)) {
      append<wxFontProperty>(m);
    }
    else if(auto m = Member<PenPtr>::As(iter)) {
      appendPaletteChoices(m, createPenChoices());
    }
    else if(auto m = Member<BrushPtr>::As(iter)) {
      appendPaletteChoices(m, createBrushChoices());
    }
    else if(auto m = Member<ColorPtr>::As(iter)) {
      appendPaletteChoices(m, createColorChoices());
    }
    else if(auto m = Member<ColorBasePtr>::As(iter)) {
      appendPaletteChoices(m, createColorBaseChoices());
    }
  }
}
/**
 */
wxPGChoices Inspector::createPenChoices() const {
  wxPGChoices choices;
  if(auto palette = getPaletteComponent()) {
    createPaletteItemChoices(choices, palette->getItems<Pen>());
  }
  choices.Add("Null");
  return choices;
}
/**
 */
wxPGChoices Inspector::createBrushChoices() const {
  wxPGChoices choices;
  if(auto palette = getPaletteComponent()) {
    createPaletteItemChoices(choices, palette->getItems<Brush>());
  }
  choices.Add("Null");
  return choices;
}
/**
 */
wxPGChoices Inspector::createColorChoices() const {
  wxPGChoices choices;
  if(auto palette = getPaletteComponent()) {
    createPaletteItemChoices(choices, palette->getItems<Color>());
  }
  choices.Add("Null");
  return choices;
}
/**
 */
wxPGChoices Inspector::createColorBaseChoices() const {
  wxPGChoices choices;
  if(auto palette = getPaletteComponent()) {
    createPaletteItemChoices(choices, palette->getItems<Color>());
    createPaletteItemChoices(choices, palette->getItems<Gradient>());
  }
  choices.Add("Null");
  return choices;
}
/**
 */
void Inspector::onChanged(wxPropertyGridEvent& event) {
  doChange<WXDRAW_PROPERTY_CLASSES>(event);
}
/**
 */
void Inspector::append(wxPGProperty* property, const MemberBasePtr& member) {
  property->SetClientData(member.get());
  Append(property);
}
/**
 */
void Inspector::onRightClick(wxPropertyGridEvent& event) {
  if(dynamic_cast<wxPropertyCategory*>(event.GetProperty())) {
    auto menu = new Menu(Menu::Type::POPUP_INSPECTOR_COMPONENT);
    menu->Append(Menu::ID_COMPONENT_REMOVE, "Remove");
    menu->AppendSeparator();
    menu->Append(Menu::ID_COMPONENT_UP, "Up");
    menu->Append(Menu::ID_COMPONENT_DOWN, "Down");
    PopupMenu(menu);
  }
}
/**
 */
const PaletteComponentPtr& Inspector::getPaletteComponent() const {
  return mainFrame_->getPaletteComponent();
}
}
