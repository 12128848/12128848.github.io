# Pikachu | PHP反序列化1
## 一、漏洞简介
unserialize() 对用户可控字符串反序列化，魔术方法触发，执行代码。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/unserialize/unserialize1.php
## 三、复现步骤
1. 理解PHP类、魔术方法（__wakeup、__destruct等）
2. 写php脚本构造序列化字符串payload
3. 传入参数，unserialize解析，触发魔术方法执行
## 四、Payload
自己构造类生成序列化字符串
## 五、漏洞原理
unserialize解析可控的序列化字符串，自动调用魔术方法，形成POP链。
## 六、修复方案
不要反序列化不可信数据；白名单类过滤。
## 七、总结
反序列化重点：POP链、魔术方法，不一定直接传一句话。