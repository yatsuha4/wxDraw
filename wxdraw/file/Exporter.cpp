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
/**
 */
bool Exporter::save(const wxString& fileName) {
  wxFileOutputStream output(fileName);
  return output.IsOk() ? save(output) : false;
}
/**
 */
bool Exporter::save(wxOutputStream& output) {
  return false;
}
}
