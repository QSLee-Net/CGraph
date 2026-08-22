/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: GParam.cpp
@Time: 2023/2/20 22:11
@Desc: 
***************************/

#include "GParam.h"

#include <algorithm>

CGRAPH_NAMESPACE_BEGIN

std::string GParam::getKey() const {
    return key_;
}


CStatus GParam::setup() {
    CGRAPH_EMPTY_FUNCTION
}


CVoid GParam::reset(const CStatus& curStatus) {
    (CVoid)curStatus;
}


CVoid GParam::lock() {
    _param_shared_lock_.lock();
}


CVoid GParam::unlock() {
    _param_shared_lock_.unlock();
}


CBool GParam::tryLock() {
    return _param_shared_lock_.try_lock();
}


CVoid GParam::addTrace(const std::string &trace, const CBool repeatable) {
    CGRAPH_LOCK_GUARD lk(trace_mtx_);
    if (repeatable || traces_.end() == std::find(traces_.begin(), traces_.end(), trace)) {
        traces_.emplace_back(trace);
    }
}


CSize GParam::removeTrace(const std::string &trace) {
    CGRAPH_LOCK_GUARD lk(trace_mtx_);
    const auto curSize = traces_.size();
    traces_.erase(std::remove(traces_.begin(), traces_.end(), trace), traces_.end());
    return curSize - traces_.size();
}


CVoid GParam::clearTrace() {
    std::vector<std::string> traces {};
    CGRAPH_LOCK_GUARD lk(trace_mtx_);
    traces.swap(traces_);
}


std::vector<std::string> GParam::getTraces() {
    CGRAPH_LOCK_GUARD lk(trace_mtx_);
    return traces_;
}

CGRAPH_NAMESPACE_END
