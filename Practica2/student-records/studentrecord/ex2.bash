#!/bin/bash

if [ ! -x "./student-records" ]; then
  echo "Error: no se encuentra el programa student-records o no tiene permisos de ejecución."
  exit 1
fi

if [ ! -f records.txt ]; then
  echo "Error: records.txt is not found or is not a regular file"
  exit 1
fi


records=$(cat records.txt | tr '\n' ' ')


./student-records -f database -c $(cat records.txt) >> /dev/null
check_database

rm database
opt="-c"
for r in $(cat records.txt)
do
	./student-records -f database $opt $r >> /dev/null
	opt="-a"
done

if ! student-records -l; then
  exit 1
fi

xxd database

done
