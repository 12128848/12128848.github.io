# Upload-Labs | Pass-11 %00截断绕过 GET型
## 一、漏洞简介
服务端做了白名单，只允许jpg/png/gif。但是在拼接上传路径时，用了用户可控的文件名，且PHP版本<5.3.4。利用%00截断，让服务端误以为文件名是jpg，实际写入php。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-11/
漏洞类型：%00截断、文件上传
环境要求：PHP < 5.3.4，magic_quotes_gpc = Off
## 三、复现步骤
1. BP抓包上传，GET参数里有个上传路径dir=upload/。
2. 把filename改成"shell.php%00.jpg"。
3. 服务端白名单检查后缀是.jpg，放行。
4. 拼接路径时%00是字符串结束符，后面的.jpg被截断，实际保存为shell.php。
5. 蚁剑连接shell.php，getshell。
## 四、Payload
filename=shell.php%00.jpg
dir=upload/shell.php%00
## 五、漏洞原理
PHP在<5.3.4版本中，C语言处理字符串时遇到%00（NULL字节）就认为字符串结束。服务端白名单检查看到的是.jpg，但真正拼路径写文件时，%00后面的内容被截断，文件名变成.php。
## 六、修复方案
1. 升级PHP到5.3.4以上版本。
2. 服务端不要把用户输入直接拼接到文件路径。
3. 白名单校验后重新生成随机文件名。
## 七、总结
%00截断是老版本PHP的经典漏洞，需要特定版本环境。现在新版本PHP已经修复。