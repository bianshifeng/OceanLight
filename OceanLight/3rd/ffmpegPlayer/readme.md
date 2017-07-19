# ffplay 功能原理图

1、创建一个VideoState结构体对象，其实这个对象就是一个PlayWorker抽象类，
该类完成了一个播放器的运行环境，AvIOContext，AvCodeContext环境的所有内容


