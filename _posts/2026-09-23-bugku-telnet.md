---
title: Bugku CTF | MISC telnet
date: 2026-09-23 15:34:00 +0800
categories: [CTF, MISC]
tags: [Bugku, 流量分析, wireshark, telnet]
---

# Bugku MISC：telnet
> 题目来源：Bugku CTF
> 考点：Wireshark流量包分析，telnet明文传输

## 题目描述
下载流量抓包文件，分析telnet流量获取flag。

## 解题思路
Telnet协议传输数据是明文，没有加密。打开pcap流量包，找到telnet数据流，追踪TCP流，直接看到传输的flag。

### 详细步骤
1. 下载题目给的pcap流量文件。
2. 使用Wireshark打开流量包。
3. 过滤协议：`telnet`。
4. 选中telnet数据包，右键 → 追踪 → TCP流。
5. 在弹出的流窗口里直接读取flag。

## Flag
`flag{df60fa0512d447889858e879e74ab289}`

## 知识点总结
Telnet是老旧远程登录协议，所有数据明文传输，安全性很差。现在基本被SSH替代。流量分析题型里看到telnet，直接追踪TCP流即可拿到明文内容。