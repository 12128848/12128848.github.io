# SQLi-Labs | Less-49 GET 排序注入 order by 单引号 无报错
## 一、漏洞简介
sort拼入order by，单引号闭合，关闭错误回显，时间盲注。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-49/?sort=1
注入类型：GET、order by注入、单引号闭合、时间盲注
## 三、复现步骤
1. ?sort=1' 无报错，单引号闭合。
2. if+sleep时间盲注。
## 四、Payload
`?sort=1' and if(substr(database(),1,1)='s',sleep(3),1) --+`
## 五、漏洞原理
`SELECT * FROM users ORDER BY '$sort'`
关闭错误回显，使用延时注入。
## 六、修复方案
1. 排序字段白名单。
## 七、总结
Less49排序注入单引号+无报错，时间盲注。