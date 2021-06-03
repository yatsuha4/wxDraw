#include "wxdraw/gui/Inspector.hpp"
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
void Inspector::show(const PropertyPtr& property) {
  clear();
  property_ = property;
  showProperty(property);
}
/**
 */
void Inspector::clear() {
  Clear();
  property_ = nullptr;
}
/**
 */
void Inspector::showProperty(const PropertyPtr& property) {
  for(auto& iter : property->getMembers()) {
    if(auto member = std::dynamic_pointer_cast<Member<int>>(iter)) {
      append(new wxIntProperty(member->getId(), member->getName(), member->getValue()), member);
    }
    else if(auto member = std::dynamic_pointer_cast<Member<double>>(iter)) {
      append(new wxFloatProperty(member->getId(), member->getName(), member->getValue()), member);
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
