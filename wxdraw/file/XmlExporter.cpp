#include "wxdraw/file/XmlExporter.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
*/
XmlExporter::XmlExporter(const NodePtr& node)
  : super(node)
{
}
/**
   出力
*/
bool XmlExporter::save(wxOutputStream& output) {
  return document_.Save(output);
}
}
