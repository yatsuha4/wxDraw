#include "wxdraw/component/Component.hpp"
#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/Menu.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Member.hpp"

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
void Inspector::show(const NodePtr& node) {
  clear();
  node_ = node;
  if(node) {
    showProperty(*node);
    for(auto& component : node->getComponents()) {
      Append(new wxPropertyCategory(component->getName()));
      showProperty(*component);
    }
    SetPropertyAttributeAll(wxPG_BOOL_USE_CHECKBOX, true);
    SetPropertyAttributeAll(wxPG_COLOUR_HAS_ALPHA, true);
  }
}
/**
 */
void Inspector::clear() {
  Clear();
  node_ = nullptr;
}
/**
 */
void Inspector::showProperty(Property& property) {
  for(auto& iter : property.getMembers()) {
    if(auto member = Member<int>::As(iter)) {
      append<wxIntProperty>(member);
    }
    else if(auto member = Member<double>::As(iter)) {
      append<wxFloatProperty>(member);
    }
    else if(auto member = Member<bool>::As(iter)) {
      append<wxBoolProperty>(member);
    }
    else if(auto member = Member<std::string>::As(iter)) {
      append<wxStringProperty>(member);
    }
    else if(auto member = Member<wxColour>::As(iter)) {
      append<wxColourProperty>(member);
    }
    else if(auto member = Member<wxFileName>::As(iter)) {
      append<wxFileProperty>(member, member->getLabel(), member->getUniqueName(), 
                             member->getValue().GetFullPath());
    }
    else if(auto child = std::dynamic_pointer_cast<Property>(iter)) {
      showProperty(*child);
    }
  }
}
/**
 */
void Inspector::append(wxPGProperty* property, const MemberBasePtr& member) {
  property->SetClientData(member.get());
  Append(property);
}
/**
 */
void Inspector::onChanged(wxPropertyGridEvent& event) {
  auto property = event.GetProperty();
  auto member = static_cast<MemberBase*>(property->GetClientData());
  doChange<double>(event, member) ||
    doChange<wxColour>(event, member);
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
}
