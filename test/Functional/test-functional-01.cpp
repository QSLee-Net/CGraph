/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: test-functional-01.cpp
@Time: 2023/12/27 23:16
@Desc: 
***************************/

#include "../_Materials/TestInclude.h"

using namespace CGraph;

void test_functional_01() {
    GPipelinePtr pipeline = GPipelineFactory::create();
    CStatus status;
    const int runTimes = 500000;

    GElementPtr a, b, c, d, e, f, g, h, i, j = nullptr;
    status += pipeline->registerGElement<TestAdd1GNode>(&a, {});
    status += pipeline->registerGElement<TestAdd1GNode>(&b, {});
    status += pipeline->registerGElement<TestAdd1GNode>(&c, {a});
    status += pipeline->registerGElement<TestAdd1GNode>(&d, {b});
    status += pipeline->registerGElement<TestAdd1GNode>(&e, {b, c});
    status += pipeline->registerGElement<TestAdd1GNode>(&f, {c});
    status += pipeline->registerGElement<TestAdd1GNode>(&g, {d, e, f});
    status += pipeline->registerGElement<TestAdd1GNode>(&h, {f});
    status += pipeline->registerGElement<TestAdd1GNode>(&i, {g, h});
    status += pipeline->registerGElement<TestAdd1GNode>(&j, {h});

    {
        UTimeCounter counter("test_functional_01");
        {
            UTimeCounter ic("test_functional_init_01", CGRAPH_PRIMARY_THREAD_EMPTY_INTERVAL);
            status += pipeline->init();
        }

        for (auto x = 0; x < runTimes; x++) {
            UTimeCounter rc("test_functional_run_01", CGRAPH_PRIMARY_THREAD_EMPTY_INTERVAL);
            status += pipeline->run();
            if (rc.getSpan() >= CGRAPH_PRIMARY_THREAD_EMPTY_INTERVAL) {
                std::cout << "  [timeout] test_functional_01 times = " << x << " span = " << rc.getSpan() << std::endl;
                break;
            }
        }

        {
            UTimeCounter dc("test_functional_destroy_01", CGRAPH_PRIMARY_THREAD_EMPTY_INTERVAL);
            status += pipeline->destroy();
        }
    }

    if (status.isErr()) {
        std::cout << status.getInfo() << std::endl;
    }

    if (g_test_node_cnt != runTimes * 10) {
        std::cout << "test_functional_01: g_test_node_cnt is not right : " << g_test_node_cnt << std::endl;
    }

    GPipelineFactory::remove(pipeline);
}


int main() {
    test_functional_01();
    return 0;
}
