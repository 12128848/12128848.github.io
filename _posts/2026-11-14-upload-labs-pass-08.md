# Upload-Labs | Pass-08 ::$DATA绕过 Windows NTFS特性
## 一、漏洞简介
Windows NTFS文件系统有个特性：如果文件名后面加::$DATA，Windows会把前面的内容当作正常文件保存。利用这个特性绕过黑名单。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-08/
漏洞类型：NTFS数据流绕过、Windows特性
## 三、复现步骤
1. BP抓包上传shell.php。
2. filename改成"shell.php::$DATA"。
3. 黑名单检查不匹配.php，放行。
4. Windows保存时自动去掉::$DATA后缀，实际文件shell.php。
5. 蚁剑连接shell.php，getshell。
## 四、Payload
filename=shell.php::$DATA
## 五、漏洞原理
Windows NTFS支持数据流，文件名加::$DATA后，系统会把文件内容写到主数据流，等价于正常文件。服务端看到的后缀不是.php，但磁盘上实际生成了shell.php。
## 六、修复方案
1. 服务端对文件名做处理，去除::$DATA等特殊后缀再校验。
2. 部署在Linux服务器上不受此影响。
## 七、总结
::$DATA是Windows NTFS特有特性，Linux靶场不受影响。只在Windows环境下有效。