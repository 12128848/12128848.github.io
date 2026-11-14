# SQLi-Labs | Less-44 POST 堆叠注入 单引号 无报错
## 一、漏洞简介
POST登录passwd注入，单引号闭合，无SQL报错回显，堆叠注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-44/
注入类型：POST、字符型、单引号闭合、堆叠注入
## 三、复现步骤
1. BP抓包，passwd注入。
2. 堆叠建表，去数据库验证是否执行成功。
## 四、Payload
uname=1&passwd=1';create table test like users; --+
## 五、漏洞原理
multi_query开启，关闭错误回显，堆叠SQL正常执行。
## 六、修复方案
1. 预编译，关闭multi_query，最小权限账号。
## 七、总结
Less44堆叠注入，无报错，只能通过数据库变化验证。