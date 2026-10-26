# 备份文件下载 - bak
## 题目信息
- 平台：CTFHub
- 分类：Web / 信息泄露
- Flag：`ctfhub{3e3bdb7dca6905e71dfff091}`

## 考点
php备份文件泄露，.bak备份后缀猜测

## 解题思路
页面提示flag在index.php源码中，直接访问index.php会被PHP引擎解析，无法查看源代码。尝试访问常见备份后缀index.php.bak，下载源码备份文件读取flag。

## 复现步骤
1. 访问靶机地址，页面提示 `Flag in index.php source code.`
2. 猜测PHP文件的备份后缀 `.bak`，拼接访问 `/index.php.bak`
3. 浏览器自动下载index.php.bak备份文件
4. 使用记事本打开备份文件，读取源码内的flag
5. 提交flag完成解题

## 原理
开发编辑代码时编辑器自动生成.bak备份文件，该备份文件放在web目录下可以直接被下载，造成php源码泄露。

## 修复建议
1. 禁止编辑器备份文件存放在网站web根目录
2. 上线前扫描站点，清理 .bak、.swp、.~ 这类备份临时文件
3. 配置Web服务器拦截这类备份文件的访问