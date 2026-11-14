# Upload-Labs | Pass-07 空格绕过
## 一、漏洞简介
黑名单没有trim()去空格，文件名末尾加空格绕过。Windows自动忽略末尾空格，保存后变成.php。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-07/
漏洞类型：空格绕过、Windows特性
## 三、复现步骤
1. 准备shell.php，BP抓包上传。
2. 把filename改成"shell.php "（末尾加一个空格）。
3. 服务端黑名单检查.php空格不匹配，放行。
4. Windows保存时去掉末尾空格，实际文件shell.php，蚁剑连接。
## 四、Payload
filename=shell.php （末尾带空格）
## 五、漏洞原理
服务端直接拿原始文件名做黑名单匹配，没有trim()去除首尾空格。Windows文件系统自动忽略末尾空格，最终文件名还是.php。
## 六、修复方案
1. 对文件名trim()去除空格后再校验。
2. 使用白名单。
## 七、总结
和Pass-05末尾点绕过原理类似，都是Windows文件系统特性。服务端要先规范化文件名再校验。