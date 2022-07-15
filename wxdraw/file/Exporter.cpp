#include "wxdraw/file/Exporter.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
   @param node ノード
*/
Exporter::Exporter(const NodePtr& node)
  : node_(node)
{
}
}
