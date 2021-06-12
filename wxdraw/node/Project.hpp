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

 public:
  Project();
  ~Project() override = default;
};
}
