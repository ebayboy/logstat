
TODO:
- 增加异常处理try catch finally
- 集成日志模块

#### 处理流程：
- 接收sub信息
- 读取redis数据
- 计算
    + 中缀表达式转后缀表达式（最小堆或二叉树实现）、计算
- 输出
- 多线程架构

- compute 数学表达式解析计算
  - ExpParse解决策略
  - stat策略计算 ExpParse + MathFunction
  - risk策略计算 ExpParse + MathExpCal
  - 多线程框架 (threadpool)
  - 延迟任务
    + SUM/AVG(ip, total, 5)  map + funccall 
        + start_end();  sep: ,
        + val ip_total_5m
    + EQ|GE|LE|GT|LT (ip_total_5m/all_total_5m,0.1)   sep:
        + 参数解析: ip_total_5m, all_total_5m, 0.1(LAST)
        + start_end (); sep: ,  sep2 + / - *
        + var: ip_total_5m, all_total_5m
        + 获取变量的value
        + 计算ret = ip_total_5m/all_total_5m => 输入数据到参数中
        + 计算 GT => ret > 0.1
    + and (vector<int> rules)

- output
    + 输出结果到redis

WillDo:
- noexcept shared_ptr

Done:
#### libs:
- cpp redis
- cpp json lib
- add libevent

- json to struct

#### 处理流程：
- 接收sub信息
- 读取redis数据
- 计算
- 输出
- 多线程架构
