# Writeup：Pikachu 验证码绕过(on server)
## 题目信息
靶场：Pikachu
漏洞模块：暴力破解 -> 验证码绕过(on server)
地址：http://127.0.0.1:8081/vul/burteforce/bf_server.php

## 解题思路
验证码校验逻辑在服务端PHP中，但是后端校验验证码之后，**没有销毁Session中保存的验证码**，同一个合法验证码可以重复多次提交。我们捕获一次有效的验证码，在数据包中将验证码固定不变，只爆破用户名和密码，实现暴力破解。

## 复现步骤
1. 配置Burp Suite代理，开启Proxy拦截。页面填写任意账号密码，同时填入页面上显示的正确验证码，点击Login，捕获POST数据包。
原始数据包：
POST /vul/burteforce/bf_server.php HTTP/1.1
Host: 127.0.0.1:8081
Content-Type: application/x-www-form-urlencoded

username=test&password=123&vcode=nyzm8e
2. 不删除vcode参数，保留这个正确验证码，右键将数据包发送到Intruder模块。
3. Positions选项卡：Clear §，只给username、password的值添加§标记，**vcode的值不添加标记，保持固定**，攻击类型选择Cluster bomb（集束炸弹）。
4. Payload配置：
    - Payload Set1（用户名）：admin、pikachu、test
    - Payload Set2（密码）：123456、000000、abc123
5. 启动爆破，对比响应长度，响应包中包含 login success 的请求即为成功。

> 有效账号密码：
> admin / 123456
> pikachu / 000000
> test / abc123

## 漏洞原理
验证码由服务端生成并校验，但是校验完成后没有清空Session里存储的验证码，验证码不会一次性失效。攻击者拿到一个合法验证码后可以反复复用，继续穷举账号密码，验证码防护失效。

## 修复建议
1. 无论验证码校验成功或者失败，服务端都要立刻销毁Session内的验证码，保证验证码只能使用一次；
2. 设置验证码较短有效期；
3. 添加登录失败次数限制、IP限流锁定策略。

## 学习总结
区分两个验证码关卡：
- on server：后端校验验证码、验证码可复用 → 数据包保留并固定vcode爆破
- on client：前端JS校验验证码，后端不校验 → 抓包直接删除vcode参数绕过