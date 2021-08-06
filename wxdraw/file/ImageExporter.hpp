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
  wxFileName fileName_;

 public:
  ImageExporter(const NodePtr& node, const wxFileName& fileName);
  ~ImageExporter() override = default;

  bool save() override;
};
}
