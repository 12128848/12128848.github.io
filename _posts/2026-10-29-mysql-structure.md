# CTFHub MySQL结构
## 题目信息
- 平台：CTFHub
- 分类：Web - SQL注入
- 考点：MySQL系统库information_schema查询，获取库、表、字段结构
- 描述：利用SQL注入读取information_schema系统库，查询数据库、数据表、字段的结构信息，为后续读取数据做准备

## 解题思路
MySQL自带information_schema系统库，里面记录了所有数据库、表、列的元数据信息。在注入点使用union select或者盲注方式查询该库，依次爆出所有库名、当前库下的表名、目标表的字段名，拿到结构后再查询flag数据。

## 复现步骤
1. 开启靶机，确认注入点类型（回显/报错/盲注）
2. 查询information_schema.schemata，获取所有数据库名称
3. 查询information_schema.tables，获取当前数据库下所有表名
4. 查询information_schema.columns，获取目标表的所有字段名
5. 根据得到的表名、字段名，构造查询语句读取flag

## 漏洞原理
存在SQL注入漏洞，攻击者可以访问information_schema系统视图，遍历整个数据库结构，摸清库表字段布局，进而定位存放flag的位置。

## 修复建议
1. 使用预编译SQL，杜绝SQL拼接注入
2. 数据库账号权限收紧，禁止访问information_schema的敏感视图
3. 部署WAF拦截对information_schema的查询语句
4. 关闭数据库错误回显，消除注入利用条件