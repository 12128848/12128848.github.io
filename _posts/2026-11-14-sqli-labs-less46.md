# SQLi-Labs | Less-46 GET 排序注入 order by 数字型
## 一、漏洞简介
GET参数sort，用于order by排序，数字型注入，没有where，不能union，使用报错注入、时间盲注。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-46/?sort=1
注入类型：GET、order by排序注入、数字型
## 三、复现步骤
1. ?sort=1 正常排序，sort直接放到order by后。
2. 不能union，使用updatexml报错注入或者sleep时间盲注。
## 四、Payload
报错注入：
`?sort=1 and updatexml(1,concat(0x7e,database(),0x7e),1)`
时间盲注：
`?sort=1 and if(substr(database(),1,1)='s',sleep(3),1)`
## 五、漏洞原理
`SELECT * FROM users ORDER BY $sort`
sort参数直接拼入order by子句，没有引号，无法union，支持报错/时间盲注。
## 六、修复方案
1. sort参数白名单，只允许预设排序字段。
2. 预编译，不要拼接排序参数。
## 七、总结
Less46是order by排序注入，属于注入位置特殊的场景，没有where子句，union不生效。