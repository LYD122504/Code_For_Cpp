**快速排序**（英语：Quicksort），又称**分区交换排序**（partition-exchange sort），是一种排序算法。在平均状况下，排序![{\displaystyle n}](https://wikimedia.org/api/rest_v1/media/math/render/svg/a601995d55609f2d9f5e233e36fbe9ea26011b3b)个项目要 ![{\displaystyle \ O(n\log n)}](https://wikimedia.org/api/rest_v1/media/math/render/svg/52de01bd6666792cf18fce11c058ae3e67694f02)次比较。在最坏状况下则需要![{\displaystyle O(n^{2})}](https://wikimedia.org/api/rest_v1/media/math/render/svg/6cd9594a16cb898b8f2a2dff9227a385ec183392)次比较，但这种状况并不常见。事实上，快速排序![{\displaystyle \Theta (n\log n)}](https://wikimedia.org/api/rest_v1/media/math/render/svg/1b8781cea4259c3bd43204e02d08b9b9ce8fe0ff)通常明显比其他算法更快，因为它的内部循环可以在大部分的架构上很有效率地达成。

快速排序使用分治法策略来把一个序列分为较小和较大的2个子序列，然后递归地排序两个子序列。

步骤为：

1. 挑选基准值：从数列中挑出一个元素，称为“基准”（pivot），
2. 分割：重新排序数列，所有比基准值小的元素摆放在基准前面，所有比基准值大的元素摆在基准后面（与基准值相等的数可以到任何一边）。在这个分割结束之后，对基准值的排序就已经完成，
3. 递归排序子序列：递归地将小于基准值元素的子序列和大于基准值元素的子序列排序。

递归到最底部的判断条件是数列的大小是零或一，此时该数列显然已经有序。

选取基准值有数种具体方法，此选取方法对排序的时间性能有决定性影响。