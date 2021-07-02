#include "wxdraw/command/InsertNode.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Outliner.hpp"
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
  Node::InsertChild(node_, parent_, index_);
  getMainFrame()->getOutliner()->insertNode(node_, parent_, index_);
  return true;
}
/**
 */
bool InsertNode::Undo() {
  parent_->removeChild(node_);
  getMainFrame()->getOutliner()->removeNode(node_);
  return true;
}
}
