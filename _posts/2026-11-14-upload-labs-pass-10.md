# Upload-Labs | Pass-10 双写后缀绕过
## 一、漏洞简介
服务端把字符串中的php替换为空，如果是简单str_replace，双写phpphp可以绕过。替换掉中间的php后，剩下的拼起来还是php。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-10/
漏洞类型：双写绕过、文件上传
## 三、复现步骤
1. BP抓包上传，filename改成"shell.pphphp"。
2. 服务端把php替换为空，pphphp去掉中间php → php。
3. 实际保存为shell.php，蚁剑连接getshell。
## 四、Payload
filename=shell.pphphp
原理：phphpphp → 删掉中间php → php
## 五、漏洞原理
服务端使用str_replace('php', '', $filename)做黑名单过滤。这种替换会把字符串里所有php都删掉，但双写后，删掉中间的php，剩下的两边拼起来还是php。属于简单替换的逻辑缺陷。
## 六、修复方案
1. 使用正则匹配后缀，不要简单字符串替换。
2. 白名单校验。
## 七、总结
双写绕过是str_replace黑名单的经典缺陷。pphphp、ppaaspp等都是同理。