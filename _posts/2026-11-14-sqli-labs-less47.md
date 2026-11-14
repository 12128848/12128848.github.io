# SQLi-Labs | Less-47 GET 排序注入 order by 单引号
## 一、漏洞简介
sort参数拼入order by，单引号闭合，order by注入，报错注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-47/?sort=1
注入类型：GET、order by注入、单引号闭合
## 三、复现步骤
1. ?sort=1' 页面报错，确认单引号闭合。
2. 构造updatexml报错注入。
## 四、Payload
`?sort=1' and updatexml(1,concat(0x7e,database(),0x7e),1) --+`
## 五、漏洞原理
`SELECT * FROM users ORDER BY '$sort'`
sort参数带引号拼入order by，支持报错注入。
## 六、修复方案
1. 排序字段白名单，禁止用户可控字段。
## 七、总结
Less47排序注入，带单引号，和46对比理解order by注入差异。