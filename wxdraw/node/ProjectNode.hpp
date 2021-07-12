#pragma once

#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
/**
   プロジェクト
*/
class ProjectNode
  : public Node
{
  using super = Node;

 public:
  static const char* TYPE;

 private:
  wxFileName fileName_;

 public:
  ProjectNode();
  ~ProjectNode() override = default;

  WXDRAW_ACCESSOR(FileName, fileName_);
};
}
