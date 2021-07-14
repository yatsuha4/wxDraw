#pragma once

#include "wxdraw/command/ChangePropertyCommand.hpp"
#include "wxdraw/gui/MainFrame.hpp"

namespace wxdraw::gui {
/**
   インスペクタ
*/
class Inspector
  : public wxPropertyGrid
{
  using super = wxPropertyGrid;

 private:
  MainFrame* mainFrame_;
  NodePtr node_;

 public:
  Inspector(wxWindow* parent, MainFrame* mainFrame);
  ~Inspector() override = default;

  void show(const NodePtr& node);
  void clear();

 private:
  void showProperty(Property& property);

  template<class PropertyType, class MemberType>
  PropertyType* append(const std::shared_ptr<MemberType>& member) {
    return append<PropertyType>(member, 
                                member->getLabel(), 
                                member->getUniqueName(), 
                                member->getValue());
  }

  template<class PropertyType, class... Args>
  PropertyType* append(const MemberBasePtr& member, Args... args) {
    auto property = new PropertyType(args...);
    append(property, member);
    return property;
  }

  void append(wxPGProperty* property, const MemberBasePtr& member);

  void onChanged(wxPropertyGridEvent& event);

  void onRightClick(wxPropertyGridEvent& event);

  template<class T>
  bool doChange(const wxPropertyGridEvent& event) {
    auto member = static_cast<MemberBase*>(event.GetProperty()->GetClientData());
    if(auto m = dynamic_cast<Member<T>*>(member)) {
      mainFrame_->submitCommand<ChangePropertyCommand<T>>(node_, m->getValue(), 
                                                          wxAny(event.GetValue()).As<T>());
      return true;
    }
    return false;
  }

  template<class T1, class T2, class... Rest>
  bool doChange(const wxPropertyGridEvent& event) {
    return doChange<T1>(event) || doChange<T2, Rest...>(event);
  }
};
}
