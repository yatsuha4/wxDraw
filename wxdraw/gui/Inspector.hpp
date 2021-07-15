#pragma once

#include "wxdraw/command/ChangePropertyCommand.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/property/Member.hpp"

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
  PropertyPtr property_;

 public:
  Inspector(wxWindow* parent, MainFrame* mainFrame);
  ~Inspector() override = default;

  void show(const PropertyPtr& property);
  void clear();

 private:
  void showProperty(const Property& property);

  template<class PropertyType, class MemberType>
  PropertyType* append(const std::shared_ptr<MemberType>& member) {
    return append<PropertyType>(member, member->getValue());
  }

  template<class PropertyType, class... Args>
  PropertyType* append(const MemberBasePtr& member, Args&&... args) {
    auto property = new PropertyType(member->getLabel(), member->getUniqueName(), args...);
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
      T value;
      if(getValue(wxAny(event.GetValue()), value)) {
        //mainFrame_->submitCommand<ChangePropertyCommand<T>>(node_, m->getValue(), value);
      }
      return true;
    }
    return false;
  }

  template<class T1, class T2, class... Rest>
  bool doChange(const wxPropertyGridEvent& event) {
    return doChange<T1>(event) || doChange<T2, Rest...>(event);
  }

  template<class T>
  bool getValue(const wxAny& src, T& dst) const {
    return src.GetAs(&dst);
  }
};
}
