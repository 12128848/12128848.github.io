# Bugku WEB | 矛盾 Writeup
## 题目信息
题目：矛盾
分类：WEB
考点：PHP弱类型比较、is_numeric()绕过

## 解题思路
源码核心逻辑：
```php
$num=$_GET['num'];
if(!is_numeric($num))
{
    echo $num;
    if($num==1)
        echo 'flag{**********}';
}