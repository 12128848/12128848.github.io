# SQLi-Labs | Less-42 POST 堆叠注入 登录框 单引号
## 一、漏洞简介
POST登录表单，passwd参数注入，单引号闭合，支持堆叠注入，分号执行多条SQL。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-42/
注入类型：POST、字符型、单引号闭合、堆叠注入
## 三、复现步骤
1. BP抓包，uname、passwd参数，注入点在passwd。
2. passwd输入1';create table test like users; --+，uname随便填。
3. 堆叠SQL执行建表。
## 四、Payload
uname=1&passwd=1';create table test like users; --+
## 五、漏洞原理
登录校验SQL，passwd直接拼接，multi_query开启，堆叠注入。
## 六、修复方案
1. 预编译查询，关闭multi_query，数据库账号最小权限。
## 七、总结
Less42是POST表单堆叠注入，注入点在密码框。