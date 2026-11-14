# Upload-Labs | Pass-06 大小写绕过
## 一、漏洞简介
黑名单没有做大小写转换，.PHP、.Php等大写后缀不匹配黑名单里的.php。Windows下文件后缀不区分大小写，可以绕过。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-06/
漏洞类型：大小写绕过、文件上传
## 三、复现步骤
1. 准备一句话木马，命名为shell.php。
2. 直接上传shell.php被拦截。
3. 改文件名为shell.PHP（大写后缀），上传成功。
4. Windows下.PHP和.php是同一个文件，蚁剑连接getshell。
## 四、Payload
文件名：shell.PHP、shell.PhP、shell.pHp
## 五、漏洞原理
黑名单匹配时直接和.php比较，没有把后缀转成小写再判断。Windows系统文件后缀不区分大小写，.PHP照样能被解析成PHP脚本。
## 六、修复方案
1. 取到后缀后strtolower()转成小写再校验。
2. 使用白名单。
## 七、总结
大小写绕过是最简单的黑名单绕过方式，几乎所有黑名单都要做大小写转换。