#include "wxdraw/command/RemoveNodeCommand.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::command {
/**
   コンストラクタ
*/
RemoveNodeCommand::RemoveNodeCommand(MainFrame* mainFrame, const NodePtr& node)
  : super("RemoveNode", mainFrame), 
    node_(node), 
    parent_(node->getParent()), 
    index_(0)
{
}
/**
 */
bool RemoveNodeCommand::Do() {
  getMainFrame()->removeNode(node_);
  return true;
}
/**
 */
bool RemoveNodeCommand::Undo() {
  getMainFrame()->insertNode(node_, parent_, index_);
  return true;
}
}

    
