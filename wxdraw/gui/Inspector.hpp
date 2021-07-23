#pragma once

#include "wxdraw/command/EditCommand.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
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
  class ClientData
    : public wxClientData
  {
   private:
    MemberBasePtr member_;

   public:
    ClientData(const MemberBasePtr& member)
      : member_(member)
    {}
    ~ClientData() override = default;

    WXDRAW_GETTER(Member, member_);
  };

 private:
  MainFrame* mainFrame_;
  PropertyPtr property_;

 public:
  Inspector(wxWindow* parent, MainFrame* mainFrame);
  ~Inspector() override = default;

  void show(const PropertyPtr& property);
  void clear();

 private:
  const PaletteComponentPtr& getPaletteComponent() const;
  void showProperty(const Property& property);

  template<class T1, class T2, class... Rest>
  bool appendMember(const MemberBasePtr& member) {
    return appendMember<T1>(member) || appendMember<T2, Rest...>(member);
  }

  template<class T>
  bool appendMember(const MemberBasePtr& member) {
    if(auto m = Member<T>::As(member)) {
      appendMember(m);
      return true;
    }
    return false;
  }

  void appendMember(const Member<int>::Ptr& member) {
    append<wxIntProperty>(member);
  }

  void appendMember(const Member<double>::Ptr& member) {
    append<wxFloatProperty>(member);
  }

  void appendMember(const Member<bool>::Ptr& member) {
    append<wxBoolProperty>(member);
  }

  void appendMember(const Member<wxString>::Ptr& member) {
    append<wxStringProperty>(member);
  }

  void appendMember(const Member<wxColour>::Ptr& member) {
    append<wxColourProperty>(member);
  }

  void appendMember(const Member<wxFileName>::Ptr& member) {
    append<wxFileProperty>(member, member->getValue().GetFullPath());
  }

  void appendMember(const Member<wxFont>::Ptr& member) {
    append<wxFontProperty>(member);
  }

  void appendMember(const Member<Choice>::Ptr& member);

  void appendMember(const Member<PenPtr>::Ptr& member) {
    appendPaletteChoices(member, createPaletteItemChoices<Pen>());
  }

  void appendMember(const Member<BrushPtr>::Ptr& member) {
    appendPaletteChoices(member, createPaletteItemChoices<Brush>());
  }

  void appendMember(const Member<ColorPtr>::Ptr& member) {
    appendPaletteChoices(member, createPaletteItemChoices<Color>());
  }

  void appendMember(const Member<ColorBasePtr>::Ptr& member) {
    appendPaletteChoices(member, createColorBaseChoices());
  }

  void appendMember(const Member<FontPtr>::Ptr& member) {
    appendPaletteChoices(member, createPaletteItemChoices<Font>());
  }

  template<class PropertyType, class T>
  void append(const std::shared_ptr<Member<T>>& member) {
    append<PropertyType>(member, member->getValue());
  }

  template<class T>
  void appendPaletteChoices(const std::shared_ptr<Member<T>>& member, 
                            wxPGChoices choices) {
    appendChoices(member, choices, 
                  getPaletteComponent()->getIndex(member->getValue()));
  }

  template<class T>
  void appendChoices(const std::shared_ptr<Member<T>>& member, 
                     wxPGChoices choices, 
                     size_t index) {
    append<wxEnumProperty>(member, choices, static_cast<int>(index));
  }

  template<class PropertyType, class... Args>
  void append(const MemberBasePtr& member, Args&&... args) {
    auto property = new PropertyType(member->getLabel(), member->getUniqueName(), args...);
    append(property, member);
  }

  void append(wxPGProperty* property, const MemberBasePtr& member);

  wxPGChoices createColorBaseChoices() const;

  template<class T>
  wxPGChoices createPaletteItemChoices() const {
    wxPGChoices choices;
    if(auto palette = getPaletteComponent()) {
      createPaletteItemChoices(choices, palette->getItems<T>());
    }
    choices.Add("Null");
    return choices;
  }

  template<class T>
  void createPaletteItemChoices(wxPGChoices& choices, 
                                const std::vector<std::shared_ptr<T>>& items) const {
    for(auto& item : items) {
      choices.Add(item->getName(), item->getBitmap());
    }
  }

  void onChanged(wxPropertyGridEvent& event);
  void onRightClick(wxPropertyGridEvent& event);

  template<class T>
  bool doChange(const wxPropertyGridEvent& event) {
    if(auto data = static_cast<ClientData*>(event.GetProperty()->GetClientObject())) {
      if(auto member = Member<T>::As(data->getMember())) {
        T value;
        if(getValue(event, value)) {
          mainFrame_->submitCommand<EditCommand<T>>(member, value);
        }
        return true;
      }
    }
    return false;
  }

  template<class T1, class T2, class... Rest>
  bool doChange(const wxPropertyGridEvent& event) {
    return doChange<T1>(event) || doChange<T2, Rest...>(event);
  }

  template<class T>
  bool getValue(const wxPropertyGridEvent& event, T& value) const {
    return wxAny(event.GetValue()).GetAs(&value);
  }

  bool getValue(const wxPropertyGridEvent& event, Choice& choice) const;

  bool getValue(const wxPropertyGridEvent& event, BrushPtr& value) const {
    return getValuePalette(event, value);
  }

  bool getValue(const wxPropertyGridEvent& event, ColorBasePtr& value) const {
    return getValuePalette(event, value);
  }

  bool getValue(const wxPropertyGridEvent& event, ColorPtr& value) const {
    return getValuePalette(event, value);
  }

  bool getValue(const wxPropertyGridEvent& event, PenPtr& value) const {
    return getValuePalette(event, value);
  }

  bool getValue(const wxPropertyGridEvent& event, FontPtr& value) const {
    return getValuePalette(event, value);
  }

  template<class T>
  bool getValuePalette(const wxPropertyGridEvent& event, 
                       std::shared_ptr<T>& value) const {
    if(auto palette = getPaletteComponent()) {
      value = palette->getItem<T>(event.GetValue().GetLong());
      return true;
    }
    return false;
  }
};
}
