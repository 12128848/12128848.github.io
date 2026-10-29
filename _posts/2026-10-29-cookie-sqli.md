# CTFHub Cookie注入
## 题目信息
- 平台：CTFHub
- 分类：Web - SQL注入
- 考点：Cookie参数带入SQL语句，Cookie位置SQL注入
- 描述：后端读取Cookie中的参数直接拼接到SQL语句，注入点不在URL参数，而在Cookie请求头内

## 解题思路
常规URL参数没有注入点，后端读取Cookie里的字段参与数据库查询。抓包修改Cookie值，构造注入payload，闭合引号后使用union select、报错或者盲注的方式，查询库、表、字段，获取flag。

## 复现步骤
1. 开启靶机，使用抓包工具抓取请求包
2. 修改Cookie内的参数，添加单引号测试，判断注入类型
3. 根据回显情况选择联合查询/报错注入/盲注方式
4. 依次爆出数据库名、表名、字段名
5. 查询flag字段内容，拿到flag

## 漏洞原理
后端直接读取Cookie中的用户可控内容，拼接进SQL语句执行，没有过滤和预编译。开发者只防护了GET/POST参数，忽略了Cookie请求头，造成注入漏洞。

## 修复建议
1. 所有用户可控输入（GET、POST、Cookie、Header）统一使用预编译SQL
2. 不要直接把Cookie内容拼入SQL查询
3. 统一对所有请求参数做安全检测
4. 部署WAF，对Cookie内容进行注入特征检测