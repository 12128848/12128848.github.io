# Pikachu | XSS过滤绕过
## 一、漏洞简介
服务端简单过滤<script>标签，替换为空，可以用多种方式绕过标签过滤。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/xss/xss_filter.php
## 三、复现步骤
1. 直接提交<script>alert(1)</script>被过滤失效
2. 使用绕过payload：`<img src=x onerror=alert(1)>`
3. 提交，成功弹窗
其他备选：`<svg onload=alert(1)>`
## 四、Payload
`<img src=x onerror=alert(document.cookie)>`
## 五、漏洞原理
只黑名单过滤script标签，没有过滤事件标签onerror、onload等。
## 六、修复方案
白名单机制，禁止所有事件属性，完整HTML编码。
## 七、总结
黑名单过滤很容易被绕过，不要只删script。