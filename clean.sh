for i in `find .`
do
    if [ -d $i ];then
        cd $i 
        if [ -e Makefile ];then
            echo "----------- cd $i -------------"
            make clean
        fi
        cd - > /dev/null
    fi
done
find . -name gcm.cache | xargs rm -f
