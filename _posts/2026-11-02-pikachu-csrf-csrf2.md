# Pikachu | CSRF 2
## 一、漏洞简介
GET型CSRF，修改信息使用GET请求，可以直接构造钓鱼url。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/csrf/csrf2.php
## 三、复现步骤
1. 抓包发现修改资料是GET传参
2. 构造恶意url发给登录的受害者
`http://127.0.0.1/pikachu/vul/csrf/csrf2.php?username=hacker&sex=男&phonenum=111111`
3. 受害者登录状态访问链接，自动执行修改
## 四、Payload
恶意GET链接
## 五、漏洞原理
GET请求无token校验，浏览器访问链接自动携带cookie。
## 六、修复方案
重要操作尽量POST，增加csrf token、校验referer。
## 七、总结
GET型CSRF更容易利用，直接一条钓鱼链接。