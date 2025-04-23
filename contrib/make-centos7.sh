#!/bin/bash
# Automated Installation, Centos 7
# V 0.5
# Author  Cosmin Cioranu - cosmin.cioranu@gmail.com
# copyright: Cosmin Cioranu
#

L=`pwd`
LOG=$L'/make.log'
execute(){
    msg=$1
    cmd=$2
    echo "[Installing $msg -> $cmd]" >>$LOG
    echo "[Installing $msg -> $cmd]"
    R=`$cmd` >>$LOG
    if [ $? -eq 0 ]; then
        echo "[Done] $cmd"
        return 0
    else 
        echo "ERROR '$cmd' failed";
        exit -1;
    fi 
}

#cmd='yum -y install epel-release'
#$cmd > make.log
#[ "$?" -eq "0" ] || (echo "ERROR '$cmd' failed"; exit)
#echo "[Done] $cmd"

echo >$LOG
execute 'epel-release' 'yum -y install epel-release'
execute 'prerequisites' 'yum -y install gcc glibc-headers gcc-c++ openssl-devel postfix  libevent-devel gmime-devel mhash-devel check-devel systemd-devel jemalloc-devel'
execute 'unarchive' 'yum -y install tar unzip'
execute 'database' 'yum -y install mariadb-devel postgresql-devel sqlite-devel '


echo "Install sieve" >>$LOG
echo "SIEVE"
LIBSIEVE_DIR=/tmp/libsieve
LIBSIEVE_NAME="libsieve-2.2.7"
LIBSIEVE_FILE=$LIBSIEVE_NAME'.tar.gz'
LIBSIEVE_PATH=$LIBSIEVE_DIR/$LIBSIEVE_FILE
execute '	removing dir' 'rm -rf '$LIBSIEVE_DIR
execute '	making dir' 'mkdir -p '$LIBSIEVE_DIR
cd  $LIBSIEVE_DIR
pwd
execute '	downloading' 'wget -q --no-check-certificate https://sourceforge.net/projects/libsieve/files/libsieve/2.2.7/libsieve-2.2.7.tar.gz/download -O '$LIBSIEVE_PATH
pwd
ls
execute '	unarchive' 'tar xvf '$LIBSIEVE_FILE
cd ${LIBSIEVE_DIR}'/'$LIBSIEVE_NAME'/src'
execute '	configure' './configure'
execute '	make' 'make'
execute '	make install' 'make install'

echo "Install libzdb" >>$LOG
echo "ZDB"
LIBZDB_DIR=/tmp/libzdb
LIBZDB_NAME="libzdb-3.1"
LIBZDB_FILE=$LIBZDB_NAME'.tar.gz'
LIBZDB_PATH=$LIBZDB_DIR/$LIBZDB_FILE
execute '	removing dir' 'rm -rf '$LIBZDB_DIR
execute '	making dir' 'mkdir -p '$LIBZDB_DIR
cd $LIBZDB_DIR
pwd
execute '	downloading' 'wget -q --no-check-certificate http://www.tildeslash.com/libzdb/dist/libzdb-3.1.tar.gz -O '$LIBZDB_PATH
execute '	current directory' 'cd '$LIBZDB_DIR
execute '	unarchive' 'tar xvf '$LIBZDB_FILE
cd ${LIBZDB_DIR}'/'$LIBZDB_NAME
execute '	configure' './configure'
execute '	make' 'make'
execute '	make install' 'make install'


echo "Install dbmail" >>$LOG
echo "DBMAIL"
LIBDBMAIL_DIR=$L
LIBDBMAIL_NAME="dbmail-3.3.0"
cd $LIBDBMAIL_DIR
pwd
execute '	configure' './configure --prefix=/usr --exec-prefix=/usr --sysconfdir=/etc --enable-systemd --with-logdir'
execute '	make' 'make all'
execute '	make install' 'make install'

echo "Cleaning Up" >>$LOG
echo "Cleaning Up"
execute '\tremoving dir' 'rm -rf '$LIBSIEVE_DIR
execute '\tremoving dir' 'rm -rf '$LIBZDB_DIR
cd $L


