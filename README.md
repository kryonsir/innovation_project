# innovation_project
密码学创新创业课程project
## project1:实现naive的生日碰撞
1. hash值使用c++标准库中的unordered_map数据结构存储，由于unoredered_map只能单向索引，第一次找到匹配之后记录经过的循环数，再跑一次程序，在上次记录下来的循环数中打印出hash值，验证一下。程序中给出的是第二次跑程序的状态。跑的结果在文件夹中以图片形式保存，在代码注释中也有保存。
2. 最终碰撞了48bits，开优化后需要100s左右

## project2:实现rho方法的生日碰撞
1. 使用自己实现sm3，性能方面与从openssl中分离出来的sm3相差不大
2. 根据参考文献实现，文献是projec2文件夹下的
3. 最终只有24bits的可以在合理时间内爆破出来，可能有什么gg方（在随机消息值得选取？）存在问题
4. 碰撞了24bits，24s左右


## project3：实现sm3的长度扩展攻击
1. 修改自己实现的sm3以方便进行长度扩展攻击，具体操作是sm3_hash函数增加了一个初始向量IV参数。
2. 同时要注意修改手动攻击组的最后几个字节，因为这几个字节按照填充规则是前面有效消息的bit长度，需要手动控制攻击组的长度与对照组的长度一致。

## project4：手动实现sm3算法
1. 在实现过程中尽量使用inline和宏定dd
2. 进行100000次sm3_hash运算花费0.012s 对比openssl中分离出来的sm3计算100000次用时0.085s。总体实现效果还是不错的。

## project5:根据RFC6962实现sm3的merkle tree
1. computeMerkleRoot 函数接受一个消息列表作为输入，并根据 RFC6962 的规则计算 Merkle 树的根。sm3_hash 函数是一个占位函数，你需要在其中实现你自己的 SM3 哈希函数。
2. 在 main 函数中，创建了一个测试数据集 messages，然后调用 computeMerkleRoot 函数计算 Merkle 树的根。最后，将 Merkle 根以十六进制形式打印出来。



