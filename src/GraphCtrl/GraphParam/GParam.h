/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: GParam.h
@Time: 2021/6/11 6:32 下午
@Desc: 
***************************/

#ifndef CGRAPH_GPARAM_H
#define CGRAPH_GPARAM_H

#include <mutex>
#include <vector>

#include "GParamObject.h"

CGRAPH_NAMESPACE_BEGIN

class GParam : public GParamObject {
public:
#if __cplusplus >= 201703L && _CGRAPH_GPARAM_RWLOCK_ENABLE_
    std::shared_mutex _param_shared_lock_;    // 用于参数互斥的锁信息
#else
    std::recursive_mutex _param_shared_lock_;
#endif

    /**
     * 获取key信息
     * @return
     */
    std::string getKey() const;

    /**
     * 上锁
     * @return
     * @notice 推荐使用raii锁
     */
    CVoid lock();

    /**
     * 解锁
     * @return
     */
    CVoid unlock();

    /**
     * 尝试加锁
     * @return
     */
    CBool tryLock();

    /**
     * 添加一条trace信息
     * @param trace trace信息
     * @param repeatable 是否允许重复写入相同的trace信息
     */
    CVoid addTrace(const std::string &trace, CBool repeatable = true);

    /**
     * 删除所有匹配的trace信息
     * @param trace trace信息
     * @return 删除的trace数量
     */
    CSize removeTrace(const std::string &trace);

    /**
     * 清空所有trace信息
     */
    CVoid clearTrace();

    /**
     * 获取当前所有trace信息的有序快照
     * @return 独立的trace数组，保留添加顺序和重复内容
     * @notice 本接口线程安全，返回结果不受后续增删操作影响
     */
    std::vector<std::string> getTraces();

protected:
    /**
     * 每次pipeline执行前，会调用一次setup，可以不实现
     * @return
     */
    virtual CStatus setup();

    /**
     * 每次pipeline执行结束，会调用一次reset
     * @param curStatus 本次pipeline执行的状态
     * @return
     * @notice 为丰富功能和简化操作，v2.4.0 版本中添加了curStatus作为入参，且取消纯虚函数设定。
     */
    virtual CVoid reset(const CStatus& curStatus);


private:
    std::string key_;                                 // 名称信息
    std::vector<std::string> traces_ {};              // 记录 trace 信息
    std::mutex trace_mtx_ {};

    friend class GParamManager;
    friend class GStorage;
};

using GParamPtr = GParam *;

CGRAPH_NAMESPACE_END

#endif //CGRAPH_GPARAM_H
