/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-08 21:14:02
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-08 21:15:54
 * @Description  :
*********************************************/
#include "../inc/node_visitor.hpp"

namespace ESI {

NodeVisitor::NodeVisitor(AST * root) : m_root(root) {}
NodeVisitor::~NodeVisitor() {}

} // namespace ESI