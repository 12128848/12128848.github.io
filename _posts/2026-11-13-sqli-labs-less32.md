# SQLi-Labs | Less-32 GET 宽字节注入 %df%27
## 一、漏洞简介
GET注入，单引号被转义 \'，使用GBK编码宽字节注入，%df%27 吃掉转义符\，成功闭合单引号。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-32/?id=1
注入类型：GET、宽字节注入、GBK、单引号
## 三、复现步骤
1. ?id=1' 变成 \'，单引号被转义。
2. 构造 %df%27，GBK解析：%df%5c 组成一个汉字，剩下%27单引号逃逸。
3. order by判断列数，union联合查询。
## 四、Payload
`?id=-1%df%27 union select 1,version(),database() --+`
## 五、漏洞原理
后端数据库连接字符集GBK，addslashes转义单引号，%df和转义符%5c拼成一个GBK汉字，单引号逃逸出来。
## 六、修复方案
1. 统一使用UTF-8字符集，不要GBK。
2. 使用预编译，不要依赖addslashes防护。
## 七、总结
Less32经典宽字节注入，GBK编码漏洞，是转义绕过的重点关卡。