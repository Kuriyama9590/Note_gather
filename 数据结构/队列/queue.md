# 队列

## 定义
- **队列**：先进先出（FIFO）

## 性质
- **循环队列**：
    - 队首指针为front，队尾指针为rear
    - 队空：front == rear 
    - 队满：(rear + 1) % n == front
    - 队长度：(rear - front + n) % n
