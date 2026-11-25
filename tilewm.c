#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "anchor.h"

#define TILE_SIZE 32
#define MAGIC "AIGC"
#define MSG_LEN 39

// 嵌入链路：锚点嵌入 → Tile水印嵌入
// 提取链路：锚点检测 → 仿射校正 → B1角度搜索 → 块重同步 → 投票提取 + HMAC校验
// 本文件为Tile水印核心投票逻辑，B1角度遍历搜索、块偏移同步、HMAC校验实现