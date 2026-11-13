# SQLi-Labs | Less-31 GET 基于WAF 双引号括号 ") HPP绕过
## 一、漏洞简介
HPP参数污染绕过WAF，参数被 `("$id")` 包裹，闭合符号 `")`。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-31/?id=1
注入类型：GET、字符型、")闭合、HPP绕过
## 三、复现步骤
1. 单参数带payload被WAF拦截。
2. 双参数：?id=1&id=1") 绕过WAF。
3. union联合查询脱库。
## 四、Payload
`?id=1&id=-1") union select 1,version(),database() --+`
## 五、漏洞原理
WAF读第一个id，后端读取最后一个id，参数污染绕过。
## 六、修复方案
1. 统一参数解析，拒绝重复参数。
2. 预编译查询。
## 七、总结
Less31闭合为 `")`，HPP绕过WAF，巩固前面的闭合知识。