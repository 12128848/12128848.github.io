# Upload-Labs | Pass-12 %00截断绕过 POST型
## 一、漏洞简介
和Pass-11原理一样，%00截断，区别是上传路径dir是POST传参。POST方式的%00需要用二进制0x00，不能直接写%00。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-12/
漏洞类型：%00截断、POST型文件上传
环境要求：PHP < 5.3.4
## 三、复现步骤
1. BP抓包，POST参数dir=upload/。
2. 把dir改成"upload/shell.php[0x00]"，在BP里把%00转成NULL字节。
3. filename保持shell.jpg，白名单放行。
4. 拼接路径时%00截断，实际保存为upload/shell.php。
5. 蚁剑连接getshell。
## 四、Payload
dir=upload/shell.php 后面加NULL字节（0x00）
filename=shell.jpg
## 五、漏洞原理
和Pass-11相同，都是老版本PHP的NULL字节截断。区别是截断点在POST参数dir里，不是filename里。POST数据需要BP手动改hex为00。
## 六、修复方案
1. 升级PHP版本。
2. 不要让用户可控参数参与文件路径拼接。
## 七、总结
POST型%00截断和GET型原理一致，只是参数位置不同。需要用BP的Hex视图修改字节。