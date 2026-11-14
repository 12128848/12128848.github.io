# SQLi-Labs | Less-52 GET 排序注入 order by 数字型 堆叠注入 无报错
## 一、漏洞简介
sort拼入order by数字型，关闭错误回显，multi_query开启，堆叠注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-52/?sort=1
注入类型：GET、order by注入、数字型、堆叠注入、无报错
## 三、复现步骤
1. sort参数拼入order by。
2. 分号堆叠建表，去数据库验证。
## 四、Payload
`?sort=1;create table test like users; --+`
## 五、漏洞原理
`SELECT * FROM users ORDER BY $sort`
关闭错误回显，multi_query开启，堆叠SQL正常执行。
## 六、修复方案
1. 排序字段白名单，关闭multi_query，最小权限。
## 七、总结
Less52堆叠注入+order by，无报错。