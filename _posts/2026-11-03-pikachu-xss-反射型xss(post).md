# Pikachu | 反射型XSS（POST）
## 一、漏洞简介
POST方式的反射型XSS，输入通过POST表单提交，不存入数据库，返回页面直接执行JS，无法直接构造URL，需要表单提交。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/xss/xss_reflected_post.php
## 三、复现步骤
1. 页面输入payload：`<script>alert('xss')</script>`
2. 提交表单，页面弹窗，触发XSS
3. 抓包可见是POST提交，参数为message
## 四、Payload
`<script>alert(document.cookie)</script>` 可用于窃取cookie
## 五、漏洞原理
POST接收参数，无过滤直接输出页面。
## 六、修复方案
HTML实体转义，输入过滤。
## 七、总结
POST反射XSS不能直接放链接，一般需要配合钓鱼页面自动提交表单。