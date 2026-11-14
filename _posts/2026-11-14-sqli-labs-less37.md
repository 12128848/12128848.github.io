# SQLi-Labs | Less-37 POST 宽字节注入 mysql_real_escape_string
## 一、漏洞简介
POST表单注入，uname参数使用mysql_real_escape_string转义，字符集配置错误，GBK宽字节注入。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-37/
注入类型：POST、宽字节注入、GBK
## 三、复现步骤
1. BP抓包POST参数uname、passwd。
2. uname填入%df%27，宽字节逃逸单引号。
3. 联合查询脱库或者绕过登录。
## 四、Payload
uname=%df%27 union select 1,version() --+ & passwd=1
## 五、漏洞原理
mysql_real_escape_string依赖连接字符集，GBK配置不当，宽字节逃逸。
## 六、修复方案
1. 统一UTF-8，预编译查询。
## 七、总结
Less37是POST版本的36，巩固宽字节注入。