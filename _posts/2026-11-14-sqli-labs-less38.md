# SQLi-Labs | Less-38 GET 堆叠注入 ; 分号
## 一、漏洞简介
GET单引号字符注入，支持堆叠注入，使用分号;分隔多条SQL语句，可以执行多条SQL，比如新建表、插入数据。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-38/?id=1
注入类型：GET、字符型、单引号闭合、堆叠注入
## 三、复现步骤
1. ?id=1' 报错，确认单引号闭合。
2. 分号;结束当前SQL，写入第二条SQL语句。
3. 堆叠注入执行额外SQL，例如创建表、插入数据。
## 四、Payload
`?id=1';create table test like users; --+`
`?id=1';insert into test values(99,'test','123456'); --+`
## 五、漏洞原理
PHP的mysql_multi_query支持多条SQL以分号分隔执行，参数直接拼接，导致堆叠注入。
## 六、修复方案
1. 禁止multi_query，使用预编译。
2. 权限最小化，数据库账号不允许建表删表。
## 七、总结
Less38经典堆叠注入，重点理解分号分隔多条SQL，union是一条语句，堆叠是多条独立SQL。