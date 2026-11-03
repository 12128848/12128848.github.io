# Pikachu | SQL注入 insert注入
## 一、漏洞简介
插入语句insert into里拼接参数，注入，一般靠报错注入拿数据。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_insert.php
## 三、复现步骤
1. 注册页面，用户名输入payload，触发报错注入
2. Payload：`' and updatexml(1,concat(0x7e,database(),0x7e),1) -- `
3. 提交注册，页面爆出数据库名称
## 四、Payload
updatexml报错注入，extractvalue报错注入
## 五、漏洞原理
insert语句拼接用户输入，没有过滤，支持报错注入。
## 六、修复方案
预编译。
## 七、总结
增删改语句经常用报错注入，不能union的时候优先报错。