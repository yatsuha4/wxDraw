#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/component/Component.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Member.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param parent 親
   @param mainFrame メインフレーム
*/
Inspector::Inspector(wxWindow* parent, MainFrame& mainFrame)
  : super(parent, wxID_ANY), 
    mainFrame_(mainFrame)
{
}
/**
 */
void Inspector::show(const NodePtr& node) {
  clear();
  node_ = node;
  showProperty(node->getProperty());
  for(auto& component : node->getComponents()) {
    Append(new wxPropertyCategory(typeid(*component).name()));
    showProperty(component->getProperty());
  }
  SetPropertyAttributeAll(wxPG_BOOL_USE_CHECKBOX, true);
}
/**
 */
void Inspector::clear() {
  Clear();
  node_ = nullptr;
}
/**
 */
void Inspector::showProperty(const PropertyPtr& property) {
  for(auto& iter : property->getMembers()) {
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
    else if(auto child = std::dynamic_pointer_cast<Property>(iter)) {
      showProperty(child);
    }
  }
}
/**
 */
void Inspector::append(wxPGProperty* property, const MemberBasePtr& member) {
  property->SetClientData(member.get());
  Append(property);
}
}
