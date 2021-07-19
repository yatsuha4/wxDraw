#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
   パレット
*/
class Palette
  : public wxWindow
{
  using super = wxWindow;

 private:
  MainFrame* mainFrame_;
  std::vector<PaletteListBase*> lists_;
  PaletteComponentPtr paletteComponent_;

 public:
  Palette(wxWindow* parent, MainFrame* mainFrame);
  ~Palette() override = default;

  WXDRAW_GETTER(MainFrame, mainFrame_);

  void setPaletteComponent(const PaletteComponentPtr& component);
  WXDRAW_GETTER(PaletteComponent, paletteComponent_);

  void setGradient(const GradientPtr& gradient);

  void update();

 private:
  template<class T1, class T2, class... Rest>
  void appendList() {
    appendList<T1>();
    appendList<T2, Rest...>();
  }

  template<class T>
  void appendList() {
    auto list = new T(this, this);
    GetSizer()->Add(list, wxSizerFlags().Expand().Proportion(1));
    lists_.push_back(list);
  }
};
}
