# kNN_hls
使用Vivado HLS高层次综合的方法在Zedboard评估板上实现kNN算法，并进行优化。

## 文件列表
- `digitrec.cpp`: 算法主文件
- `digitrec-test.cpp`: HLS测试文件
- `host.cpp`: 版上测试文件
- `Makefile`: 版上Makefile

## 使用方法
整体工程使用[xillilinux](http://xillybus.com/xillinux)工程为框架。

工作流程：新建HLS工程->生成ip核->将ip核添加到XillyDEMO工程中->将`host.cpp`等文件传输到版上->版上运行

## 结果
见`嵌入式SoC第三次实验.pdf`文件
