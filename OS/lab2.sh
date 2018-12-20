
trap "aboutsignal" 2

i=0
aboutsignal(){
#let "i=i+1"
i=$(expr $i + 1)
echo " number of interuption is $i" 
if [ $i -eq 1 ]; then 
	if [ "x$item" = "x" ] ; then 
		echo "You did not entered any file yet"
	else 
		mv -f $name_for_new $item; pr $item
	fi;
fi;
if test $i -gt 4 ; then
	exit 1
fi;
}

echo "enter filename" 
read item
if [ -f $item ]; then  
name_for_new="Copy"
cp $item $name_for_new
var=$(cmp -s $item $name_for_new | echo $?) 
sleep 2
echo "copy finished"
sleep 3
if test $var -eq 0 ; then 
	rm -rf $item
fi; 
sleep 5 
else 
	echo "File does not exist"
fi; 


