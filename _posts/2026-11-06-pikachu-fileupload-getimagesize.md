# Pikachu | 文件上传 getimagesize 校验
## 一、漏洞简介
使用getimagesize判断是不是图片，检测文件头，但是可以制作图片马绕过。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/upload/upload_suffix.php
## 三、复现步骤
1. 制作图片马：cmd `copy 1.jpg /b + shell.php /a shell.jpg`
2. 上传图片马，getimagesize检测是图片通过
3. 配合文件包含漏洞，包含这个jpg图片马，解析php代码
## 四、Payload
图片马内嵌入php一句话
## 五、漏洞原理
getimagesize只校验文件头是不是图片，不检查文件后面内容；图片马本身合法图片头。
## 六、修复方案
上传目录禁止php解析；重命名随机文件名；严格后缀校验。
## 七、总结
图片马本身不能直接解析php，必须搭配文件包含漏洞才能执行代码。