# Pikachu | 反射型XSS（GET）
## 一、漏洞简介
反射型XSS，也叫非持久型XSS。用户输入的内容，GET参数直接拼接到页面输出，不做过滤，输入的JS代码立刻执行，不会存入数据库。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/xss/xss_reflected_get.php
## 三、复现步骤
1. 在输入框输入payload：`<script>alert('xss')</script>` 提交
2. 页面直接弹出alert弹窗，漏洞触发
3. 也可以构造URL链接发给别人：
`http://127.0.0.1/pikachu/vul/xss/xss_reflected_get.php?message=<script>alert('xss')</script>&submit=submit`
## 四、Payload
基础payload：`<script>alert('xss')</script>`
绕过备选：`<img src=x onerror=alert(1)>`
## 五、漏洞原理
服务端直接读取GET参数message，未经过滤输出到HTML页面，浏览器解析标签执行JS。
## 六、修复方案
1. 对用户输入做HTML转义，< > & " ' 转义
2. 输入输出过滤，禁止危险标签与事件
## 七、总结
反射型XSS特点：一次性、不带库、靠诱导点击链接触发。