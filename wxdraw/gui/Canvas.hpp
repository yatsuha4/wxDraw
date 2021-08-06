#pragma once

#include "wxdraw/container/Transform.hpp"

namespace wxdraw::gui {
/**
   キャンバス
*/
class Canvas
  : public wxScrolledCanvas
{
  using super = wxScrolledCanvas;

 private:
  MainFrame* mainFrame_;
  glm::dvec2 offset_;
  double zoom_;
  Transform viewTransform_;
  wxPoint mousePos_;
  NodePtr viewNode_;

  static wxBrush BackgroundBrush;

 public:
  Canvas(wxWindow* parent, MainFrame* mainFrame);
  ~Canvas() override = default;

  static const wxBrush& GetBackgroundBrush();

 protected:
  void OnDraw(wxDC& dc) override;

 private:
  void onLeftDown(wxMouseEvent& event);
  void onMotion(wxMouseEvent& event);
  void onMouseWheel(wxMouseEvent& event);
  void onRightDown(wxMouseEvent& event);

  void drawCursor(Renderer& renderer, const NodePtr& node);

  NodePtr getNode(const NodePtr& node, 
                  const Transform& parent, 
                  const glm::dvec2& pos) const;
  Transform getTransform(const NodePtr& node) const;
};
}
