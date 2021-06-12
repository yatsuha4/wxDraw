#pragma once

namespace wxdraw::gui {
/**
   レンダラー
*/
class Renderer {
 private:
  std::shared_ptr<wxGraphicsContext> context_;

 public:
  Renderer(wxDC& dc);
  Renderer(const Renderer& renderer) = default;
  ~Renderer() = default;

  wxGraphicsContext& getContext() const {
    return *context_;
  }
};
}
