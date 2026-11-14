# SQLi-Labs | Less-40 GET 单引号括号 ') 堆叠注入
## 一、漏洞简介
GET注入，闭合符号 `')`，支持堆叠注入，分号执行多条SQL。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-40/?id=1
注入类型：GET、字符型、')闭合、堆叠注入
## 三、复现步骤
1. ?id=1') 报错，确认闭合。
2. 分号结束SQL，堆叠执行其他语句。
## 四、Payload
`?id=1');create table test like users; --+`
## 五、漏洞原理
multi_query开启，参数直接拼接，支持堆叠。
## 六、修复方案
1. 关闭multi_query，预编译，最小权限。
## 七、总结
Less40堆叠注入，闭合是')，语法上要匹配括号。