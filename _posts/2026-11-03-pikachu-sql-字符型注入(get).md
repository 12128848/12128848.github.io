# Pikachu | SQL注入 字符型（GET）
## 一、漏洞简介
参数被单引号包裹，需要用单引号闭合SQL语句，再注入。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_str.php
## 三、复现步骤
1. 输入kobe正常查询；输入kobe' 页面报错，证明单引号闭合
2. 闭合语句：`kobe' and 1=1 -- `
3. order by判断列数，联合查询脱库
Payload：`kobe' union select 1,version() -- `
## 四、Payload
`kobe' union select 1,database() -- `
## 五、漏洞原理
SQL语句：`select * from user where username='$name'`，变量直接拼接。
## 六、修复方案
预编译，参数绑定。
## 七、总结
字符型注入核心：用单引号闭合前面的引号，注释掉后面多余语句。