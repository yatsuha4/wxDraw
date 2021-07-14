#pragma once

#include "wxdraw/file/Exporter.hpp"

namespace wxdraw::file {
/**
   イメージ出力
*/
class ImageExporter
  : public Exporter
{
  using super = Exporter;

 private:
  glm::ivec2 size_;
  glm::dvec2 scale_;
  glm::dvec2 alignment_;

 public:
  ImageExporter(const NodePtr& node, 
                const glm::ivec2& size, 
                const glm::dvec2& scale, 
                const glm::dvec2& alignment);
  ~ImageExporter() override = default;

  bool save(const wxString& fileName) override;
};
}
