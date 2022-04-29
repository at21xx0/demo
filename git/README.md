# 准备
	git config --global user.name "Your Name"
	git config --global user.email "email@example.com"
	mkdir git-test && cd git-test
	git init

# 把文件添加到仓库
	git add README.md

# commit 一次可以提交很多文件
	git commit -m "write README.md"  


	git add file1.txt
	git add file2.txt file3.txt
	git commit -m "add 3 files.


# 查看状态
	git status

# 文件不同
	git diff
	git diff README.md


# 查看日志
	git log README.md
	// --author=xxx // 指定一个用户
	// 输出在一行
	git log --pretty=oneline README.md 
	git blame <file> // 文件历史修改

# 退回版本
	git reset --hard HEAD^
	// HEAD^是上一个版本，上两个可以 HEAD^^ 100 可以 HEAD~100
# 前进
	git reset --hard a1ccc
	// a1ccc 是 git log 出的 commit id
# 回到未来 (查看 commit id)
	git reflog

# add & commit
	git add命令实际上就是把要提交的所有修改放到暂存区（Stage），然后，执行git commit就可以一次性把暂存区的所有修改提交到分支。

# diff
	git diff HEAD -- readme.txt命令可以查看工作区和版本库里面最新版本的区别：

# back
	git checkout -- <file> // 恢复为最新文件 (切换分支 从另一个提交中取出文件 恢复文件)
	git reset HEAD <file> // 把 git add <file> 撤销
# rm
	git rm <file> // 删除文件 然后commit
# github
	// 创建ssh key (~/.ssh 目录下存在 id_rsa id_rsa.pub 不用创建)
	ssh-keygen -t rsa -C "youremail@example.com"

	// 登陆GitHub，打开“Account settings”，“SSH Keys”页面：然后，点“Add SSH Key”，填上任意Title，在Key文本框里粘贴id_rsa.pub文件的内容：
	git remote add origin git@github.com:user-name/git-test.git
	git push -u origin master // 推送到master(默认)分支  // -u 之后 直接 `git push`
	// 之后直接可以git push ...
# gitee
	git remote add origin https://gitee.com/at21xx0/git-test.git
	// 或
	git remote add origin ssh://git@gitee.com/at21xx0/git-test.git
	// ..
# remote
	git remote add <shortname> ssh://git@xxx.com:22/at21xx0/git-test.git
	//其中 origin 是remote 名称，可以用来
	git remote -v // 列出
	git remote rm <shortname>  // 删除
# clone
	git clone git@xxx.com:xx/xxx.git
	// 成为本地仓库
# branch (分支)
	# 分支好像是同时做两个功能，互不影响，然后合并后做完了两个功能
	git checkout -b dev
	// -b 创建并切换分支
	//相当于 `git branch dev` 和 `git checkout dev`
	git branch //查看当前分支 (*)
	git merge dev 与当前分支合并
	git branch -d dev // 删除分支
	git branch recover_branch_anme <hash> // 恢复分支，到某次commit 找
	// git 新
	git switch -c dev // 创建 切换 分支
	git switch dev // 切换分支
	git push origin dev:dev // 远程分支
	git push origin :dev // 推送一个空分支到远程分支，相当于删除分支
	git push origin --delete dev // 删除分支
# conflict
	git branch <name> // 可能出现冲突
	git status 也可以看到冲突
	// 用git log --graph命令可以看到分支合并图。
	// 可以打开冲突文件
	//git 用 >>>>>>>   <<<<<<<  ====== 标记不同分支内容
	//再提交即可恢复正常(`git add README.md` `git commit -m "conflict fixed")
	// git log 可以看到分支的合并情况
	git log --graph --pretty=oneline --abbrev-commit
	// 通常情况下可以创建一个dev分支，在dev分支下开发
# 分支合并策略
	git merge --ff //默认 删除分支后容易丢失merge分支信息 历史记录乱
	//-–squash // 总结一下分支，不把分支的历史带过来
	//--no-ff // 简洁清晰 (在图表上)
	//git config branch.master.mergeoptions  "--no-ff" 仅针对当前分支有效
	//git config --add merge.ff false 仅针对当前版本库的所有分支有效
	//git config --global --add merge.ff false 仅针对所有版本库的所有分支有效
# stash
	git stash // 保存工作现场(未commit 文件等)
	git stash list // 查看 
	git stash apply // 恢复
	git stash drop // 删除
	git stash pop // 恢复并恢复
	// 充分利用 stash 和 cherry-pick 可以debug
	// 开发新功能，最好新建一个feature 分支
# cherry-pick
	git cherry-pick <hash> // 复制一个特定提交到当前分支
# pull
	// git push origin <本地分支>:<远程分支> 上传远程代码并合并
	// git pull origin <远程分支>:<本地分支> 下载远程代码并合并
	// pull 相当于先 fetch(获取最新) 再 merge
	//`git push` 后，remote 可能更新，会出问题，所以要`git pull`，然后手动合并冲突(像`git merge`中一样)
	git branch --set-upstream branch-name origin/branch-name 建立本地分支和远程分支的关联，使用
# rebase
	rebase操作可以把本地未push的分叉提交历史整理成直线
	rebase的目的是使得我们在查看历史提交的变化时更容易，因为分叉的提交需要三方对比
# tag
	// tag 就是和commit 绑定起来的有意义的名字，如v1.0
	git tag v1.0 // 最新提交
	git tag v0.9 <hash> // hash可以从`git log`里面找
	git tag // 查看标签
	git tag -a v0.1 -m "version 0.1 released" <hash>
	git show <tagname> // 可以看到说明性文字
	git tag -d v1.0 // 删除标签
	git push origin v1.0
	git push origin --tags // 所有标签
	git push origin :refs/tags/v1.0 // 删除标签(要先删除本地标签)
# Pull request
	pull request 是 先 fork某仓库某分支，修复bug或添加功能，然后提交
# c
	git config --global color.ui true // 使git看起来有颜色
# .gitignore
	cat .gitignore
	git add -f .README.md.swp // 强制
	// gitignore 本身需要放在版本库中# config
	git config --global alias.st status // 之后`git st`相当于`git status`
	// 不加global只对本仓库起作用，存放在`.git/config`，否则在`~\gitconfig`
	git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
	// 改 log
# git
	// 创建git
	// debian ubuntu
	sudo apt-get install git
	sudo useradd git
	// 把所有公钥导入到 /home/git/.ssh/authorized_keys
	sudo git init --bare sample.git // 假定/svr/sample.git 在 /srv 目录下输入
	sudo chown -R git:git sample.git
	// 编辑 /etc/passwd 禁止shell登录
	// git:x:1001:1001:,,,:/home/git:/bin/bash
	// 改为
	// git:x:1001:1001:,,,:/home/git:/usr/bin/git-shell
	// git clone git@server:/srv/sample.git // 在另一台
	// 公钥管理用 Gitosis
	// 权限Gitolite
# SourceTree
	https://www.sourcetreeapp.com/






