# SQLi-Labs | Less-28 GET 单引号括号 ') 过滤union select 空格
## 一、漏洞简介
GET注入，闭合 `')`，过滤union、select、空格，大小写绕过+括号代替空格。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-28/?id=1
注入类型：GET、字符型、')闭合、union/select/空格过滤
## 三、复现步骤
1. ?id=1') 报错，闭合确认。
2. union、select、空格被过滤，大小写混合+括号代替空格。
3. 末尾使用 `and('1')=('1` 闭合，不使用注释。
## 四、Payload
`?id=-1')UnIoN(SeLeCt(1),version(),database())and('1')=('1`
## 五、漏洞原理
`SELECT * FROM users WHERE id=('$id') LIMIT 0,1`
多重黑名单过滤，但是没有阻止大小写变形和括号语法。
## 六、修复方案
1. 预编译，黑名单层层绕过成本很低。
2. 输入白名单。
## 七、总结
Less28综合考察：括号闭合、空格绕过、关键字大小写绕过。