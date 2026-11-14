# SQLi-Labs | Less-39 GET 数字型 堆叠注入
## 一、漏洞简介
GET数字型注入，无引号，支持堆叠注入，分号执行多条SQL。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-39/?id=1
注入类型：GET、数字型、堆叠注入
## 三、复现步骤
1. ?id=1' 无报错，数字型。
2. 分号堆叠执行额外SQL。
## 四、Payload
`?id=1;create table test like users; --+`
## 五、漏洞原理
multi_query开启，数字型直接拼接，分号分隔多条SQL。
## 六、修复方案
1. 关闭multi_query，预编译，最小权限账号。
## 七、总结
Less39数字型堆叠注入，不需要引号闭合。