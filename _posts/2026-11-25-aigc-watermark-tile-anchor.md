---
layout: post
title: "AIGC图像隐形水印实验 - LSB / DCT / Tile锚点校正水印"
date: 2026-11-25
categories: [CTF, watermark, experiment]
tags: [信息隐藏, 图像水印, C语言, 鲁棒水印]
---

# AIGC图像隐形水印实验 Writeup
实验载体：实拍图片（旋风土豆+开花烤肠，512×512 RGB）
开发环境：C99，不依赖OpenCV等第三方图像库
Payload：`test_watermark_2026`，带HMAC校验防篡改

## 0. 实验简介
本实验实现三种图像隐形水印方案，用于AIGC图片溯源：
1. LSB 最低有效位空域隐写
2. DCT 中频频域水印（阈值T=32）
3. Tile投票鲁棒水印（B1角度搜索 + 块重同步 + B3低频编码锚点仿射校正）

迭代路线：基础Tile → B1角度回正 → 块周期重同步 → 稀疏锚点相似变换校正 → m序列抗噪编码锚点 → 低频分块锚点抵抗JPEG强压缩。

## 1. 基础原理
### 1.1 LSB水印
修改RGB像素最低比特承载水印信息，人眼不可感知。
优点：画质极高，PSNR高；缺点：鲁棒性极差，压缩、噪声、裁剪直接破坏水印。

### 1.2 DCT频域水印
图像分块DCT，在中频系数嵌入水印，避开低频（人眼敏感）和高频（极易被压缩丢弃）。
优点：可抵抗轻度JPEG压缩、高斯噪声；缺点：实拍图大面积平滑区域时中频不稳定，旋转、裁剪、强压缩失效。

### 1.3 Tile投票水印
图像切分为多个小块，每一块投票1bit水印，多块统计投票、少数服从多数，天然容错。
原生缺陷：无法抵抗旋转、缩放、复合仿射攻击，因此引入锚点校正链路。

### 1.4 低频编码锚点校正原理
在图片内嵌入4×4稀疏锚点网格；提取端先检测锚点，最小二乘拟合**相似变换（旋转+平移+均匀缩放）**，逆变换校正图像为轴对齐，校正完成后再执行Tile水印提取。
锚点采用4bit低频分块编码，带比特容错，同时抵抗JPEG压缩与椒盐噪声，过滤假阳性匹配。

## 2. 完整源码
### anchor.h
```c
#ifndef ANCHOR_H
#define ANCHOR_H
#include <stdint.h>
#include <stdbool.h>

#define ANCHOR_W 16
#define ANCHOR_H 16
#define GRID_CNT 4
#define SUB_W 8
#define SUB_H 8

typedef struct {
    double x, y;
    int id;
} AnchorPoint;

bool anchor_embed(uint8_t *rgb, int w, int h, AnchorPoint *out_grid);
int anchor_detect(uint8_t *rgb, int w, int h, AnchorPoint *detected, int max_det);
bool affine_estimate(AnchorPoint *src, AnchorPoint *dst, int n, double *affine);
static bool inv_similar(double *A, double *invA);
bool affine_warp(uint8_t *in_rgb, int w, int h, double *affine, uint8_t *out_rgb);

#endif