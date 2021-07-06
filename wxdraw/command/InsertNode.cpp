#include "wxdraw/command/InsertNode.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::command {
/**
   コンストラクタ
*/
InsertNode::InsertNode(MainFrame* mainFrame, 
                       const NodePtr& node, 
                       const NodePtr& parent, 
                       size_t index)
  : super("InsertNode", mainFrame), 
    node_(node), 
    parent_(parent), 
    index_(index)
{
}
/**
 */
bool InsertNode::Do() {
  getMainFrame()->insertNode(node_, parent_, index_);
  return true;
}
/**
 */
bool InsertNode::Undo() {
  getMainFrame()->removeNode(node_);
  return true;
}
}
