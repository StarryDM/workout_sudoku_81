用了9*9*9的bool记录已经排除的可能,所有的内存都在这,如同只有的那一张纸
先根据初始输入排除
(应该不能边加边整体排除,不记录,没有信息回去)
每次寻找最拥挤的格子填
一个我觉得复杂的递归实现
