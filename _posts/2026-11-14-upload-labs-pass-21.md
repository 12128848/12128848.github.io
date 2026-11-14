# Upload-Labs | Pass-21 文件头校验绕过 MIME+数组
## 一、漏洞简介
服务端检查文件MIME类型和文件头，但是文件后缀取的是用户可控参数，且可以传数组。通过数组参数绕过后缀检查，上传php文件。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-21/
漏洞类型：数组参数绕过、文件上传
## 三、复现步骤
1. BP抓包上传，Content-Type改成image/jpeg。
2. 文件头伪造GIF89a，在php文件开头加GIF89a。
3. 文件名传数组：filename[]=shell.php&filename[]=.jpg
4. 服务端取后缀时处理数组出错，最终保存为shell.php。
5. 蚁剑连接getshell。
## 四、Payload
文件内容开头加：GIF89a
filename[]=shell.php&filename[]=.jpg
Content-Type: image/jpeg
## 五、漏洞原理
服务端对文件名做后缀截取时，没有考虑传数组的情况。数组绕过了后缀校验逻辑，同时MIME和文件头都伪装成图片，最终上传成功php文件。
## 六、修复方案
1. 严格校验文件名参数类型，拒绝数组。
2. 服务端随机生成文件名。
3. 上传目录禁止脚本解析。
## 七、总结
Pass-21是综合绕过，需要同时绕过MIME、文件头、后缀校验。考点是参数类型不严格，数组绕过逻辑。