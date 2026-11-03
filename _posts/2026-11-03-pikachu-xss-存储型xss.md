# Pikachu | 存储型XSS
## 一、漏洞简介
持久型XSS，输入内容存入后端数据库，任何人访问页面都会加载并执行JS，危害比反射型大很多。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/xss/xss_stored.php
## 三、复现步骤
1. 在留言框输入payload：`<script>alert('storage xss')</script>`
2. 提交留言，数据存入数据库
3. 刷新页面，每次打开页面都会自动弹窗
## 四、Payload
`<script>window.location='http://xxx'</script>` 跳转钓鱼网站
## 五、漏洞原理
用户输入保存进数据库，读取展示时没有过滤，JS直接渲染执行。
## 六、修复方案
存储前、输出前都做HTML转义。
## 七、总结
存储型XSS是高危，一次植入，所有访问者中招。