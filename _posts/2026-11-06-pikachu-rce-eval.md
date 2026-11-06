# Pikachu | RCE eval 代码执行
## 一、漏洞简介
eval函数可以把字符串当成PHP代码执行，用户可控输入直接放入eval，造成代码执行漏洞。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/rce/rce_eval.php
## 三、复现步骤
1. 页面提示输入phpinfo();
2. 输入 payload：`phpinfo();`，页面打印php信息
3. 拓展payload：`system('whoami');` 执行系统命令
## 四、Payload
`system('ls');`
`system('ipconfig');`
## 五、漏洞原理
`eval($_GET['txt']);` 用户输入直接作为PHP代码解析执行。
## 六、修复方案
禁止使用eval处理用户可控输入；过滤危险函数。
## 七、总结
eval属于代码执行，和系统命令执行（system）有区别，eval执行PHP代码。