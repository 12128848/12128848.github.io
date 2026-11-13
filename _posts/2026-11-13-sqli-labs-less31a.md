# SQLi-Labs | Less-31a GET 盲注 数字型 HPP绕过
## 一、漏洞简介
HPP绕过WAF，数字型注入，页面无回显，布尔盲注。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-31a/?id=1
注入类型：GET、数字型、HPP绕过、布尔盲注
## 三、复现步骤
1. 单参数payload被拦截，使用?id=1&id=payload。
2. 1=1页面正常，1=2页面空白，布尔盲注。
## 四、Payload
`?id=1&id=1 and substr(database(),1,1)='s' --+`
## 五、漏洞原理
HPP参数污染，WAF和后端解析不一致。
## 六、修复方案
1. 统一参数解析，预编译，强转数字。
## 七、总结
Less31a把HPP绕过和布尔盲注结合。