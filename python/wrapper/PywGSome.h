/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: PywGSome.h
@Time: 2026/7/4 15:13
@Desc: 
***************************/

#ifndef CGRAPH_PYWGSOME_H
#define CGRAPH_PYWGSOME_H

#include <pybind11/pybind11.h>

#include "CGraph.h"
#include "PyWrapperMacro.h"

class PywGSome : public CGraph::GSome {
public:
    explicit PywGSome(const CGraph::GElementPtrArr& elements = CGraph::GElementPtrArr{}) {
        __addGElements_4py(elements);
    }
    ~PywGSome() override = default;

    CSize getWaitNum() override {
        PYBIND11_OVERLOAD_PURE(CSize, PywGSome, getWaitNum);
    }
};


PYCGRAPH_DECLARE_GGROUP_INTERFACE_CLASS(PywGSome,
    CSize getWaitNum() override {
        PYBIND11_OVERLOAD_PURE(CSize, PywGSomeInterface, getWaitNum);
    });

#endif //CGRAPH_PYWGSOME_H
