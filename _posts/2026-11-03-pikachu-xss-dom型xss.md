# Pikachu | DOM型XSS
## 一、漏洞简介
DOM XSS不经过服务端数据库，完全靠前端JS脚本，修改DOM节点，触发JS，数据包里看不到恶意代码回显。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/xss/xss_dom.php
## 三、复现步骤
1. 观察页面JS，把what参数拼进innerHTML
2. 构造payload：`' onclick=alert(1)//`
3. 拼接到url：`xss_dom.php?what=' onclick=alert(1)//`
4. 点击页面文字，触发弹窗
## 四、Payload
`' onmouseover=alert(1)//`
## 五、漏洞原理
前端JS直接将url参数拼接进DOM，没有过滤，innerHTML会解析html。
## 六、修复方案
使用textContent而不是innerHTML；对DOM输出做编码。
## 七、总结
DOM XSS：在前端JS里触发，服务端日志可能看不到恶意代码。