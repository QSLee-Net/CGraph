"""
@Author: Chunel
@Contact: chunel@foxmail.com
@File: T23-GSome.py
@Time: 2026/7/4 21:58
@Desc: 
"""

from pycgraph import GPipeline

from MyGNode.MyNode1 import MyNode1
from MyGNode.MyNode2 import MyNode2
from MyGSome.MySome import MyGSome


def tutorial_some():
    pipeline = GPipeline()
    a, c, d = MyNode1(), MyNode1(), MyNode2()
    b_some = MyGSome(
        [MyNode1("nodeB1"), MyNode2("nodeB2"), MyNode2("nodeB3")]
    )

    pipeline.registerGElement(a, set(), "nodeA")
    pipeline.registerGElement(b_some, {a}, "someB")
    pipeline.registerGElement(c, {b_some}, "nodeC")
    pipeline.registerGElement(d, {c}, "nodeD")

    pipeline.process()


if __name__ == '__main__':
    tutorial_some()
