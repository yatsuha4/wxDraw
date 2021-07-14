﻿#pragma once

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
  glm::dmat3 viewMatrix_;
  wxPoint mousePos_;
  wxBrush brush_;

 public:
  Canvas(wxWindow* parent, MainFrame* mainFrame);
  ~Canvas() override = default;

 protected:
  void OnDraw(wxDC& dc) override;

 private:
  void setupBrush(int size, const wxColour& c1, const wxColour& c2);

  void onRightDown(wxMouseEvent& event);
  void onMotion(wxMouseEvent& event);
  void onMouseWheel(wxMouseEvent& event);

  void drawCursor(Renderer& renderer, const NodePtr& node);
};
}
