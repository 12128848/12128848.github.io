# SQLi-Labs | Less-48 GET 排序注入 order by 数字型 无报错
## 一、漏洞简介
sort拼入order by数字型，关闭错误回显，时间盲注。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-48/?sort=1
注入类型：GET、order by注入、数字型、时间盲注
## 三、复现步骤
1. ?sort=1' 无报错，数字型。
2. 使用sleep时间盲注，根据响应延时判断。
## 四、Payload
`?sort=1 and if(substr(database(),1,1)='s',sleep(3),1)`
## 五、漏洞原理
`SELECT * FROM users ORDER BY $sort`
关闭错误回显，无法报错注入，只能时间盲注。
## 六、修复方案
1. 排序字段白名单，不接受用户直接输入排序参数。
## 七、总结
Less48排序注入无报错，只能时间盲注。