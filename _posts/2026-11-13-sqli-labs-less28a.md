# SQLi-Labs | Less-28a GET 单引号括号 ') 过滤union select 简化版
## 一、漏洞简介
GET注入，闭合 `')`，过滤union、select，大小写绕过，相比28空格限制宽松一点。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-28a/?id=1
注入类型：GET、字符型、')闭合、union/select过滤
## 三、复现步骤
1. ?id=1') 报错，确认闭合。
2. union、select小写被过滤，大小写混合绕过。
3. 联合查询脱库。
## 四、Payload
`?id=-1') UnIoN SeLeCt 1,version(),database() --+`
## 五、漏洞原理
`SELECT * FROM users WHERE id=('$id') LIMIT 0,1`
简单字符串替换小写union、select。
## 六、修复方案
1. 预编译，正则忽略大小写匹配关键字。
## 七、总结
Less28a是28简化版本，空格不做限制，只过滤union select。