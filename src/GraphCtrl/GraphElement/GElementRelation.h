/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: GElementRelation.h
@Time: 2023/5/24 23:15
@Desc: 
***************************/

#ifndef CGRAPH_GELEMENTRELATION_H
#define CGRAPH_GELEMENTRELATION_H

#include <vector>

#include "GElementObject.h"

CGRAPH_NAMESPACE_BEGIN

class GElement;

struct GElementRelation : public CStruct {
public:
    std::vector<GElement *> predecessors_ {};       // 前驱信息
    std::vector<GElement *> successors_ {};         // 后继信息
    std::vector<GElement *> children_ {};           // 包含的信息。仅在group 类型的情况下有值
    GElement* belong_ = nullptr;                    // 从属信息。如果从属于group，则为该group的值；如果从属于pipeline，则为nullptr
};

CGRAPH_NAMESPACE_END

#endif //CGRAPH_GELEMENTRELATION_H
