# SQLi-Labs | Less-35 GET 数字型 宽字节无意义关卡
## 一、漏洞简介
GET数字型注入，id没有引号，addslashes转义对数字型无效，宽字节防护形同虚设，直接union注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-35/?id=1
注入类型：GET、数字型SQL注入
## 三、复现步骤
1. ?id=1' 无报错，数字型，没有引号包裹，转义函数不影响。
2. order by判断列数，union联合查询。
## 四、Payload
`?id=-1 union select 1,version(),database() --+`
## 五、漏洞原理
`SELECT * FROM users WHERE id=$id LIMIT 0,1`
id是数字，不存在引号，addslashes转义函数在这里没有防护效果。
## 六、修复方案
1. 强制id转为数字，预编译查询。
## 七、总结
Less35用来理解：addslashes只对字符串引号生效，数字型注入不受它保护。