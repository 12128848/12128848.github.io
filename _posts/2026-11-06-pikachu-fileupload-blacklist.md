# Pikachu | 文件上传 黑名单绕过
## 一、漏洞简介
服务端黑名单禁止php、asp等后缀，但是漏了php3、php5、phtml等可解析后缀。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/upload/upload_black.php
## 三、复现步骤
1. 上传shell.phtml，黑名单没有拦截
2. Apache默认配置下phtml会交给php解析
## 四、Payload
文件名 shell.phtml，内容一句话木马
## 五、漏洞原理
黑名单是不全的，存在大量可解析后缀漏检。
## 六、修复方案
优先使用白名单：只允许 jpg、png、gif
## 七、总结
黑名单绕过多，白名单才稳妥。