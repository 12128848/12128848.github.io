# SQLi-Labs | Less-51 GET 排序注入 order by 单引号 堆叠注入
## 一、漏洞简介
sort拼入order by，单引号闭合，multi_query开启，堆叠注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-51/?sort=1
注入类型：GET、order by注入、单引号闭合、堆叠注入
## 三、复现步骤
1. ?sort=1' 报错，单引号闭合。
2. 分号堆叠SQL。
## 四、Payload
`?sort=1';create table test like users; --+`
## 五、漏洞原理
`SELECT * FROM users ORDER BY '$sort'`
multi_query开启，堆叠注入。
## 六、修复方案
1. 排序字段白名单，关闭multi_query。
## 七、总结
Less51单引号order by堆叠注入。