# SQLi-Labs | Less-33 GET 宽字节注入 addslashes %df%27
## 一、漏洞简介
和Less32原理一致，addslashes转义单引号，GBK宽字节注入，%df%27逃逸。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-33/?id=1
注入类型：GET、宽字节注入、GBK
## 三、复现步骤
1. ?id=1' 被转义成\'。
2. %df%27 吃掉\，逃逸单引号。
3. union联合查询脱库。
## 四、Payload
`?id=-1%df%27 union select 1,version(),database() --+`
## 五、漏洞原理
GBK字符集+addslashes造成宽字节注入。
## 六、修复方案
1. 全站UTF-8，预编译查询。
## 七、总结
Less33和32几乎一样，巩固宽字节注入。