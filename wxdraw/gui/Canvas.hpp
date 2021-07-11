#pragma once

namespace wxdraw::gui {
/**
   キャンバス
*/
class Canvas
  : public wxScrolledCanvas
{
  using super = wxScrolledCanvas;

 public:
  MainFrame* mainFrame_;
  glm::dvec2 offset_;
  double zoom_;

 public:
  Canvas(wxWindow* parent, MainFrame* mainFrame);
  ~Canvas() override = default;

 protected:
  void OnDraw(wxDC& dc) override;
};
}
