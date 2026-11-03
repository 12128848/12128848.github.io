# Pikachu | SQL注入 POST字符型注入
## 一、漏洞简介
登录框POST提交字符型参数，单引号闭合注入。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_login.php
## 三、复现步骤
1. 抓包看到username、password POST参数
2. username输入：`admin' -- `，密码随便填，直接绕过登录
3. 也可以union查询脱库
## 四、Payload
绕过登录：`admin' -- `
脱库：`' union select 1,database() -- `
## 五、漏洞原理
登录SQL直接拼接用户名参数。
## 六、修复方案
参数化查询，不要拼接SQL。
## 七、总结
登录框注入最常用的就是注释绕过登录。