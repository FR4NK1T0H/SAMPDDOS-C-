for (( i=0; i<100000; i++ ))
do
echo "84.$(($RANDOM%255)).$(($RANDOM%255)).$(($RANDOM%255))" >> $1.txt
echo "181.$(($RANDOM%255)).$(($RANDOM%255)).$(($RANDOM%255))" >> $1.txt
echo "186.$(($RANDOM%255)).$(($RANDOM%255)).$(($RANDOM%255))" >> $1.txt
echo "201.$(($RANDOM%255)).$(($RANDOM%255)).$(($RANDOM%255))" >> $1.txt
echo "186.$(($RANDOM%255)).$(($RANDOM%255)).$(($RANDOM%255))" >> $1.txt
echo "190.$(($RANDOM%255)).$(($RANDOM%255)).$(($RANDOM%255))" >> $1.txt
done
