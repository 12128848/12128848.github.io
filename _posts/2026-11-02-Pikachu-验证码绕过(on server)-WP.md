# Writeup：Pikachu 验证码绕过(on server)
## 题目信息
靶场：Pikachu
漏洞模块：暴力破解 -> 验证码绕过(on server)
地址：http://127.0.0.1:8081/vul/burteforce/bf_server.php

## 解题思路
本关卡验证码在服务端校验，但是后端校验通过后**没有销毁session里保存的验证码**，同一个正确验证码可以反复多次提交。
拿到一次有效的验证码之后固定写在数据包里，只爆破username和password，实现暴力破解。

## 复现步骤
1. 访问页面，表单包含Username、Password、验证码三个输入框。
2. 在页面输入任意账号密码 + **当前页面上正确的验证码**，点击Login，用Burp Suite抓POST包。
3. 把抓到的数据包右键发送到Intruder。
4. Positions设置：点击Clear §，只给username、password添加标记，**vcode（验证码参数保持固定不变，不加标记）**，攻击类型选择Cluster bomb。
5. 配置Payload：
    - Payload Set1（用户名）：admin、pikachu、test
    - Payload Set2（密码）：123456、000000、abc123
6. 点击Start attack启动爆破。
7. 根据响应长度区分结果：成功包响应内包含 `login success`，失败提示 `username or password is not exists`。

> 有效凭据：
> admin / 123456
> pikachu / 000000
> test / abc123

## 漏洞原理
服务端验证验证码后，没有清空`session['vcode']`，验证码不会一次性失效，攻击者捕获一次合法验证码后可以重复复用，继续穷举账号密码，绕过验证码防护。

## 修复建议
1. 验证码校验成功/失败后，立刻销毁session中的验证码，保证验证码一次性使用；
2. 增加登录失败次数限制、IP锁定策略；
3. 增加验证码复杂度，设置较短有效期。

## 学习总结
区分：on server 是后端校验验证码，但验证码可复用；on client 是前端JS校验验证码，抓包可以直接删掉vcode参数绕过。