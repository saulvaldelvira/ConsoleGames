action=UNKNOWN
unknown=UNKNOWN
while [ "$action" = "$unknown" ];
do
    echo "***Options***"
    echo "1)Build Release"
    echo "2)Build Debug"
    echo "3)Build All"
    echo "4)Clean"

    read -p "Option: " option
    

    if [ "$option" = "1" ];
    then
        action="release"
    elif [ "$option" = "2" ];
    then
        action="debug"
    elif [ $option = "3" ];
    then
        action="all"
    elif [ $option = "4" ];
    then
        cd src
        make clean
        cd ..
        exit 0
    else
        echo "Invalid Option"
    fi
done

cd src

for dir in $(ls -d */)
do
    echo working on $dir
    make SET=$dir $action
    echo
done

cd ..