#include "wxdraw/file/Importer.hpp"

namespace wxdraw::file {
/**
 */
NodePtr Importer::load(const wxString& fileName) {
  input_.reset(new wxFileInputStream(fileName));
  return input_ ? onLoad() : nullptr;
}
/**
   コンストラクタ
*/
wxInputStream& Importer::getInput() const {
  wxASSERT(input_);
  return *input_;
}
}
