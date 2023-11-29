# 软件模拟I2C

## 1.引脚

PB6 -- SCL

PB7 -- SDA

### 2.时序延时（标准模式，快速模式，快速模式Plus）

实际使用时，延时时间暂不知道如何设置，即使全都设置为 1 us 也可以成功进行通信，甚至不加延时函数都可以成功通信。以下内容仅供参考。

##### 1）开始信号

SDA 电平下降前，SCL 保持 **4.7 us** 以上的 “高” 电平；

SDA 电平下降后，SCL 保持 **4 us** 以上的 “高” 电平

![](E:\Github\STM32\STM32F103C8T6\I2C\img\image-20231129152119675.png)

tHD;STA 最小值：4 微秒

![](E:\Github\STM32\STM32F103C8T6\I2C\img\image-20231129152629911.png)

tSU;STA 最小值：4.7 微秒

##### 2）停止信号

SDA 电平上升前，SCL 保持 **4 us** 以上的 “高” 电平；

SDA 电平上升后，保持 **4.7 us** 以上的 “高” 电平

![image-20231129153400716](E:\Github\STM32\STM32F103C8T6\I2C\img\image-20231129153400716.png)

tSU;STO 最小值：4 微秒

tBUF 最小值：4.7 微秒

##### 3）其他信号

SCL 脉冲信号上升前，SDA 保持 **0.25 us** 以上的电平；

SCL 脉冲信号下降后，SDA 保持 **5 us** 以上的电平；

SCL 脉冲信号 “低” 电平保持 **4.7 us** 以上；

SCL 脉冲信号 “高” 电平保持 **4 us** 以上

![image-20231129154609720](E:\Github\STM32\STM32F103C8T6\I2C\img\image-20231129154609720.png)

tHD;DAT 最小值：5 微秒

tSU;DAT 最小值：0.25 微秒

![image-20231129155055221](E:\Github\STM32\STM32F103C8T6\I2C\img\image-20231129155055221.png)

tLOW 最小值：4.7 微秒

tHIGH 最小值：4 微秒