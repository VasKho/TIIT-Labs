read -p "Enter text " tekst
for I in  {1..10..1}
do
   touch text$I.txt
   echo text$I>text$I.txt
done
for I in {1..10..1}
do
   if [[ `cat text$I.txt` = $tekst ]]
   then
      rm -i  text$I.txt
   fi
done
