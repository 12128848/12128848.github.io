# SQLi-Labs | Less-36 GET 宽字节注入 mysql_real_escape_string
## 一、漏洞简介
使用mysql_real_escape_string转义，但是PHP连接和数据库字符集不一致，GBK宽字节注入，%df%27逃逸。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-36/?id=1
注入类型：GET、宽字节注入、GBK
## 三、复现步骤
1. 单引号被转义，但是字符集不匹配，宽字节依然可以逃逸。
2. %df%27闭合，union注入。
## 四、Payload
`?id=-1%df%27 union select 1,version(),database() --+`
## 五、漏洞原理
mysql_real_escape_string依赖连接字符集，PHP和数据库字符集不一致，导致防护失效。
## 六、修复方案
1. PHP连接和数据库字符集统一UTF-8。
2. 使用PDO预编译。
## 七、总结
Less36说明：mysql_real_escape_string不是万能，字符集配置错误依然会被宽字节绕过。