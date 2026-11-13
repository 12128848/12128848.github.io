# SQLi-Labs | Less-29 GET 基于WAF 数字型注入 伪静态
## 一、漏洞简介
WAF防护，前端传入id，服务端对参数做过滤，但是可以使用Hpp（HTTP参数污染）绕过，数字型注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-29/?id=1
注入类型：GET、数字型、HPP参数污染绕过WAF
## 三、复现步骤
1. 单参数?id=1'会被WAF拦截。
2. 构造两个id参数：?id=1&id=1'，WAF取第一个id，后端数据库取第二个id，绕过WAF。
3. 数字型，order by、union联合查询。
## 四、Payload
`?id=1&id=-1 union select 1,version(),database() --+`
## 五、漏洞原理
WAF和后端PHP对同名参数解析策略不一致，WAF读取第一个id，后端读取最后一个id，造成参数污染绕过。
## 六、修复方案
1. WAF和后端保持一致参数解析逻辑。
2. 预编译，id强制转为数字。
3. 拒绝重复参数。
## 七、总结
Less29学习HPP参数污染绕过WAF，属于WAF绕过基础思路。