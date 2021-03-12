/*********************************************
 * @Author       : Daniel_Elendeer
 * @Date         : 2021-03-07 11:28:16
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-12 17:10:07
 * @Description  :
*********************************************/
#ifndef INC_NODE_VISITOR_HPP_
#define INC_NODE_VISITOR_HPP_

#include "AST.hpp"

namespace ESI {

// As a abstract base class
class NodeVisitor {
protected:
    AST * m_root;
    virtual void generic_visit(AST *node) = 0;

public:
    NodeVisitor(AST * root);
    virtual ~NodeVisitor();

    virtual Any visit(AST *node) = 0;
};

} // namespace ESI

#endif