# question 
* 每天凌晨2点的时候定时打包 /var/log 下的 dpkg.log,mysql.log,fontconfig.log 三个文件到 /home/shiyanlou/backup/ 目录
* 命名格式为 年-月-日.tar，比如今天是2017年10月23日，那么文件名为2017-10-23.tar，若有重名则覆盖

# answer
* 使用Linux的crontab服务
* crontab -e 写入需要执行任务的命令
* 0 2 * * 1 cp file_name /dir
* ...
* tar -zcvf /dir/file$(date +\%Y-\%m-\%d).tar /dir


# other 
* [how to use crontab](http://www.cnblogs.com/longjshz/p/5779215.html)
