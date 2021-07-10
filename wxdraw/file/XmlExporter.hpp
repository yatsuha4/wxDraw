#pragma once

#include "wxdraw/file/Exporter.hpp"

namespace wxdraw::file {
/**
   XML出力
*/
class XmlExporter
  : public Exporter
{
  using super = Exporter;

 private:
  wxXmlDocument document_;

 public:
  XmlExporter(const NodePtr& node);
  ~XmlExporter() override = default;

  bool save(wxOutputStream& output) override;
};
}
