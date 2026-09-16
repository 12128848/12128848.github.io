# Bugku CTF - 贝斯家族
## 题目信息
题目：贝斯家族
分类：Crypto
密文：@iH<,{bdR2H;i6*Tm,Wx2izpx2!

## 解题思路
题目名字“贝斯”谐音Base，代表Base系列编码。Base64、Base32无法解码该密文，观察字符集包含`@ < , { * !`等特殊符号，判断为Base91编码。使用Base91算法解密，即可得到flag。

## 解题过程
1. 观察密文，存在大量特殊符号，排除Base64、Base32。
2. 尝试Base91解码，输入密文`@iH<,{bdR2H;i6*Tm,Wx2izpx2!`。
3. 解码得到flag：`flag{base91_1s_funny}`

## EXP
```python
import base91
cipher = "@iH<,{bdR2H;i6*Tm,Wx2izpx2!"
result = base91.decode(cipher).decode()
print(result)