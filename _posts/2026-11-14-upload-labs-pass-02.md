# Upload-Labs | Pass-02 服务端MIME类型校验绕过
## 一、漏洞简介
服务端检查HTTP请求头中的Content-Type字段，只允许image/jpeg、image/png、image/gif。没有校验文件后缀和文件内容，抓包修改Content-Type即可绕过。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-02/
漏洞类型：MIME类型校验绕过、文件上传
## 三、复现步骤
1. 准备shell.php一句话木马。
2. BP抓包上传shell.php，原始Content-Type为application/x-php，被拦截。
3. 修改Content-Type为image/jpeg，放行数据包，文件上传成功。
4. 访问上传路径，蚁剑连接getshell。
## 四、Payload
Content-Type: image/jpeg
一句话木马：<?php @eval($_POST['cmd']);?>
## 五、漏洞原理
服务端只检查$_FILES['file']['type']，也就是浏览器提交的MIME类型。这个字段完全由客户端可控，抓包就能改。没有检查文件后缀和文件内容，防护形同虚设。
## 六、修复方案
1. 不能只依赖Content-Type判断文件类型。
2. 服务端校验文件后缀白名单。
3. 使用getimagesize()等函数校验文件真实内容。
## 七、总结
Content-Type是客户端可控的请求头，不能作为安全校验依据。MIME类型绕过是文件上传最基础的考点。