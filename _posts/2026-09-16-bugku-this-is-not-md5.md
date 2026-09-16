# Bugku CTF - 这不是md5
## 题目信息
题目：这不是md5
分类：Crypto
密文：666c61677b616537333538376261353662616566357d

## 解题思路
题目名称存在误导，密文长度32位，很容易让人第一时间想到MD5哈希。MD5是不可逆哈希算法，不能解密。观察密文由0-9，a-f字符构成，判断是十六进制Hex编码。Hex编码规则为每2个十六进制字符对应1个ASCII字符，直接解码就能拿到flag。

## 解题过程
1. 密文分组，两个字符一组：
66 6c 61 67 7b 61 65 37 33 35 38 37 62 61 35 36 62 61 65 66 35 7d
2. 将每组十六进制字符转换为ASCII字符，依次转换。
3. 解码得到flag：flag{ae73587ba56baef5}

## EXP
```python
import binascii
cipher = "666c61677b616537333538376261353662616566357d"
result = binascii.unhexlify(cipher).decode()
print(result)