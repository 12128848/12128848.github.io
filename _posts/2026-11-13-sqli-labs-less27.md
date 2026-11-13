# SQLi-Labs | Less-27 GET 单引号 过滤union select
## 一、漏洞简介
GET单引号字符注入，过滤union、select，大小写混合绕过，页面有回显，联合查询。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-27/?id=1
注入类型：GET、字符型、单引号闭合、union/select黑名单过滤
## 三、复现步骤
1. ?id=1' 报错，单引号闭合。
2. union、select被过滤，大小写混合绕过：UnIoN、SeLeCt。
3. order by确定3列，构造联合查询。
## 四、Payload
`?id=-1' UnIoN SeLeCt 1,version(),database() --+`
## 五、漏洞原理
`SELECT * FROM users WHERE id='$id' LIMIT 0,1`
替换函数只匹配小写union、select，MySQL语句不区分大小写，大小写混合绕过。
## 六、修复方案
1. 正则忽略大小写匹配关键字，或者直接预编译。
2. 白名单控制输入。
## 七、总结
Less27考察大小写绕过union select过滤，是很经典的弱过滤场景。