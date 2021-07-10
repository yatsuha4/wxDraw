#pragma once

#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
/**
   プロジェクト
*/
class Project
  : public Node
{
  using super = Node;

 private:
  wxFileName fileName_;

 public:
  Project();
  ~Project() override = default;

  WXDRAW_ACCESSOR(FileName, fileName_);
};
}
