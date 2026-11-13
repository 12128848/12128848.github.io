# SQLi-Labs | Less-24 二次注入 重置密码
## 一、漏洞简介
二次注入，也叫存储型注入。注册账号时，用户名中的单引号被转义存入数据库，登录后在修改密码功能处，直接取出数据库内原始用户名拼接SQL，触发注入。注入payload写在注册用户名中。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-24/
注入类型：二次注入、存储型注入、单引号闭合、update注入
## 三、复现步骤
1. 注册新用户，用户名填写 `admin'#`，密码随便设置。
2. 使用刚注册的 `admin'#` 账号登录。
3. 进入修改密码页面，修改密码，此时后端取出数据库中用户名admin'#拼入update语句，#注释掉后面条件，实现修改admin用户密码。
4. 用新密码登录admin账号。
## 四、Payload
注册用户名：`admin'#`
修改密码后，admin账号密码被覆盖。
## 五、漏洞原理
注册时输入 `admin'#`，转义后存入数据库的是admin'#；修改密码SQL：
`UPDATE users SET password='$pass' WHERE username='$username'`
取出username=admin'#，SQL变成：
`UPDATE users SET password='$pass' WHERE username='admin'#' AND password='$oldpass'`
#注释掉后面验证语句，直接修改admin的密码。
## 六、修复方案
1. 从数据库取出数据后，再次做转义或者使用预编译。
2. 不能认为入库转义就安全，二次使用时依然存在风险。
3. 权限校验采用用户ID，而不是用户名。
## 七、总结
Less24是经典二次注入，注入点不在提交瞬间，而是数据二次被取出拼接SQL的时候，属于容易忽略的存储注入场景。