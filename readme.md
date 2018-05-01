## 简单的键盘主控程序

### 特点

0. 组合键的支持
1. 似乎没其他特点了, 只是为了弥补只用AHK的缺陷
2. 第一次自己设计PCB~

### 键盘布局

<img src="https://raw.githubusercontent.com/deepkolos/my_keyboard/master/asset/layout.png"/>

### 组合键配置
```
Home  + WASD -> 方向键(中间可穿插Ctrl/Shift/Alt)
Home  + N    -> Win + N
Shift + BS   -> Enter
Esc   + N    -> Fn
Home  + Esc  -> Alt + F4
Home  + Tab  -> Alt + Tab
Home  + R    -> Win + R
Home  + SPC  -> Win + R
Home  + E    -> Win + E
Home  + T    -> Ctrl + Shift + ESC

AHK实现部分
Home  + P    -> 电源模式切换(平衡/省电)
Home  + Z    -> 减少亮度
Home  + X    -> 增加亮度
Home  + C    -> 减少音量
Home  + V    -> 增大音量
End   + M    -> 静音
```
还有一些第二版时候有的组合键, 但是很少用, 所以没加上去, 比如快速把窗口切换到另一个屏幕, 最大化窗口, 鼠标控制等

### 键盘

<img src="https://raw.githubusercontent.com/deepkolos/my_keyboard/master/asset/keyboard.jpg" width="300"/>

### PCB
<img src="https://raw.githubusercontent.com/deepkolos/my_keyboard/master/asset/pcb.jpg"/>

### 主控 Pro Micro

<img src="https://raw.githubusercontent.com/deepkolos/my_keyboard/master/asset/pro micro.png"/>

### 组合键触发规则

待续

### 小记

> 和之前做的触控手势识别类似, 但是简单不少\
> 有些组合键的实现通过tmk那种keymap的切换可能更方便一些, 下次重写主控会试一下~\
> 发现#define在tmk里面被用得超溜~\
> 发现自己其实连简单的数据结构感觉自己掌握了, 但是一上去写代码, 各种边界条件没有注意, 不过好在后面增加了单侧, 很快解决
> 写C++也好, 写JS也好, 关键还是在于逻辑是否清晰, 记得开始上大学的时候学C, 做的题目都是学生当作计算机, 把代码的结果运算写出来, 那时候不屑, 感觉那是计算机做的事, 不是人去做的, 现在打脸了, 在编码的时候这个过程占用的时间是最多的, 需要不断在脑子里推演按下Home, 按下D, 再按下F, 这时候F的行为是? 恢复被阻塞的Home? 还是不恢复? 是否触发F? 还是屏蔽? 这些行为带来的响应的记录的更新, 都是清楚, 不然debug起来十分讲究运气
> 键盘弄完之后, 希望是最近几个月消沉的结束的标志