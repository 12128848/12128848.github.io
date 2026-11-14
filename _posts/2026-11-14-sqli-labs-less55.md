# SQLi-Labs | Less-55 挑战关卡 数字型 14次机会
## 一、漏洞简介
GET数字型注入，页面有回显，每个session最多14次查询机会，联合注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-55/?id=1
注入类型：GET、数字型、联合注入、次数限制
## 三、复现步骤
1. ?id=1' 无报错，数字型。
2. order by 3，union联合查询，控制次数拿到flag。
## 四、Payload
`?id=-1 union select 1,version(),database() --+`
## 五、漏洞原理
`SELECT * FROM users WHERE id=$id LIMIT 0,1`
服务端计数，限制14次查询。
## 六、修复方案
1. 预编译，限流。
## 七、总结
Less55数字型次数限制挑战，和54思路一致，只是闭合类型不同。