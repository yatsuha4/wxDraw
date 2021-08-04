#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/Menu.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Choice.hpp"
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
void Inspector::show(PropertyPtr property) {
  clear();
  property_ = property;
  if(property) {
    showProperty(*property);
    SetPropertyAttributeAll(wxPG_BOOL_USE_CHECKBOX, true);
    SetPropertyAttributeAll(wxPG_COLOUR_ALLOW_CUSTOM, true);
    SetPropertyAttributeAll(wxPG_COLOUR_HAS_ALPHA, true);
  }
}
/**
 */
void Inspector::update() {
  update(GetRoot());
}
/**
 */
void Inspector::clear() {
  Clear();
  property_ = nullptr;
}
/**
 */
PaletteComponentPtr Inspector::getPaletteComponent() const {
  if(property_) {
    if(auto node = std::dynamic_pointer_cast<Node>(property_->getObject())) {
      return Node::GetParentComponent<PaletteComponent>(node);
    }
    else if(auto item = std::dynamic_pointer_cast<PaletteItem>(property_->getObject())) {
      return item->getPalette();
    }
  }
  return nullptr;
}
/**
 */
void Inspector::showProperty(const Property& property) {
  for(auto& member : property.getMembers()) {
    if(member->isShow()) {
      if(auto m = std::dynamic_pointer_cast<PropertyMember>(member)) {
        Append(new wxPropertyCategory(m->getName()));
        showProperty(*m->getProperty());
      }
      else if(auto prop = appendMember<WXDRAW_PROPERTY_CLASSES>(member)) {
        SetPropertyReadOnly(prop, member->isReadOnly());
      }
      else {
        wxLogFatalError("illegal member");
      }
    }
  }
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
  property->SetClientObject(new ClientData(member));
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
wxPGProperty* Inspector::appendMember(const Member<Choice>::Ptr& member) {
  auto& choice = member->getValue();
  wxPGChoices choices;
  for(auto item = choice.getItems(); *item; item++) {
    choices.Add(*item);
  }
  return appendChoices(member, choices, choice.getIndex());
}
/**
 */
wxPGProperty* Inspector::appendMember(const Member<NodePtr>::Ptr& member) {
  auto node = member->getValue();
  return append<wxStringProperty>(member, node ? node->getName() : "NULL");
}
/**
 */
bool Inspector::getValue(const wxPropertyGridEvent& event, Choice& choice) const {
  choice.setIndex(event.GetValue().GetLong());
  return true;
}
/**
 */
void Inspector::update(wxPGProperty* property) {
  if(auto data = static_cast<ClientData*>(property->GetClientObject())) {
    update<WXDRAW_PROPERTY_CLASSES>(property, data->getMember());
  }
  for(auto i = 0; i < property->GetChildCount(); i++) {
    update(property->Item(i));
  }
}
}
