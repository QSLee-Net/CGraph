"""
@Author: Chunel
@Contact: chunel@foxmail.com
@File: MyCondition
@Time: 2025/2/25 23:37
@Desc: 
"""

from PyCGraph import GCondition

class MyCondition(GCondition):
    index = 0
    def choose(self):
        self.index += 1
        return self.index % self.getRange()
