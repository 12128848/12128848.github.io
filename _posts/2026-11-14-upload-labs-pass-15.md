# Upload-Labs | Pass-15 图片马绕过 文件包含配合
## 一、漏洞简介
和Pass-13类似，服务端检查图片内容，需要制作图片马配合文件包含。本关检查方式是getimagesize()，制作正常图片马即可绕过。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-15/
漏洞类型：图片马、文件包含
## 三、复现步骤
1. 制作图片马：copy test.jpg/b + shell.php/a shell.jpg。
2. 上传shell.jpg，getimagesize()检测通过。
3. 通过文件包含漏洞访问upload/shell.jpg。
4. PHP代码被执行，蚁剑连接getshell。
## 四、Payload
图片马：shell.jpg（图片末尾追加一句话）
包含路径：?file=upload/shell.jpg
## 五、漏洞原理
服务端只判断文件是不是合法图片，不检查图片里有没有PHP代码。配合文件包含，图片当PHP脚本执行。
## 六、修复方案
1. 上传目录禁止脚本解析。
2. 文件包含白名单。
3. 图片重渲染。
## 七、总结
和Pass-13原理一致，巩固图片马+文件包含的利用方式。