# SQLi-Labs | Less-17 POST 重置密码 update注入
## 一、漏洞简介
密码重置页面，用户名参数先做查询校验，密码参数直接拼入update修改语句，密码参数存在注入，属于update报错注入。必须输入一个已经存在的用户名，注入payload写在密码框。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-17/
注入类型：POST、字符型、单引号闭合、update报错注入
## 三、复现步骤
1. 打开页面，抓包，POST参数 uname、passwd。
2. 先填入存在用户名admin，密码位置输入测试payload `1'`，提交，页面SQL报错，确认单引号闭合。
3. 构造updatexml报错注入payload放在passwd参数，uname保持admin。
4. 提交，通过报错带出数据库信息，依次获取库、表、字段、数据。
## 四、Payload
查询库名：
`uname=admin&passwd=1' and updatexml(1,concat(0x7e,database(),0x7e),1) --+`
查询users表账号密码：
`uname=admin&passwd=1' and updatexml(1,concat(0x7e,(select group_concat(username,0x7e,password) from users),0x7e),1) --+`
## 五、漏洞原理
后端先查询用户名是否存在，用户名存在后执行修改密码SQL：
`UPDATE users SET password='$passwd' WHERE username='$uname'`
passwd参数可控直接拼接，没有过滤，支持报错注入。
## 六、修复方案
1. 密码修改SQL使用预编译绑定参数。
2. 关闭数据库详细错误回显。
3. 对密码输入做过滤，禁止特殊字符与SQL函数。
## 七、总结
Less17重点：注入点在密码参数，不是用户名，且用户名必须真实存在才会执行update语句，属于update更新语句注入，只能用报错注入。