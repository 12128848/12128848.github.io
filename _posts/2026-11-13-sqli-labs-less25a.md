# SQLi-Labs | Less-25a GET 数字型 过滤or and 联合注入
## 一、漏洞简介
GET数字型注入，无引号包裹，过滤and、or，双写绕过，union联合查询。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-25a/?id=1
注入类型：GET、数字型、关键字过滤、联合注入
## 三、复现步骤
1. ?id=1' 无报错，判定数字型。
2. and/or被过滤，使用双写anandd、oor绕过。
3. order by确定3列，union查询。
## 四、Payload
`?id=-1 union select 1,version(),database() --+`
`?id=2 anandd 1=1 --+`
## 五、漏洞原理
`SELECT * FROM users WHERE id=$id LIMIT 0,1`
简单字符串替换and/or为空，双写绕过。
## 六、修复方案
1. 预编译，id强转为数字类型。
2. 整词正则过滤，禁止简单替换。
## 七、总结
Less25a和25逻辑一致，区别是数字型，不需要单引号闭合。