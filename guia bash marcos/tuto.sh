#Variables: En Bash, las variables se declaran asignando un valor a un nombre. No es necesario especificar el tipo de variable. Por ejemplo:

nombre_variable = valor

#Entrada de usuario: Para obtener entrada del usuario, se utiliza el comando "read". Por ejemplo:

echo "Ingresa tu nombre:"
read nombre
echo "Hola $nombre"

#Condicionales: El comando "if" se utiliza para crear condicionales. Por ejemplo:

if [ $nombre == "John" ]; then
  echo "Bienvenido John"
else
  echo "Bienvenido $nombre"
fi

#Bucles: El comando "for" se utiliza para crear bucles. Por ejemplo:

for num in {1..10}; do
  echo $num
done

#Funciones: El comando "function" se utiliza para crear funciones. Por ejemplo:

function saludar {
  echo "Hola $1"
}

saludar "Mundo"


#Verificar si un archivo existe: Utilizamos el comando "test" o "[ ]" para verificar si un archivo existe. Por ejemplo:

if [ -e /path/to/file ]; then
  echo "El archivo existe"
else
  echo "El archivo no existe"
fi

#Verificar si un archivo es ejecutable: Utilizamos el comando "test" o "[ ]" con la opción "-x" para verificar si un archivo es ejecutable. Por ejemplo:

if [ -x /path/to/file ]; then
  echo "El archivo es ejecutable"
else
  echo "El archivo no es ejecutable"
fi

#Conocer la ruta actual: Utilizamos el comando "pwd" para conocer la ruta actual. Por ejemplo:

echo "La ruta actual es $(pwd)"

#Cambiar la ruta actual: Utilizamos el comando "cd" para cambiar la ruta actual. Por ejemplo:

cd /path/to/directory

#Listar el contenido de un directorio: Utilizamos el comando "ls" para listar el contenido de un directorio. Por ejemplo:

ls -l /path/to/directory

#Crear un directorio: Utilizamos el comando "mkdir" para crear un directorio. Por ejemplo:

mkdir /path/to/new_directory

#Eliminar un archivo o directorio: Utilizamos el comando "rm" para eliminar un archivo o directorio. Por ejemplo:

rm /path/to/file_or_directory

#################################################################
#Programa para probar el student record
#################################################################

#!/bin/bash


#check if file is an executable 
if [ -x "student-record.out" ]; then
    echo "file \"student-record\" is executable"
else
    echo "file \"student-record\" is not an executable"
    echo "Exiting..."
    exit 0
fi

#check if file records.txt is in the current directory
if [ -f "records.txt" ]; then
    echo "File \"records\" exists"
else
    echo "File \"records\" doesn't exist"
    echo "Exiting..."
    exit 0
fi

#store all the entries in a string variable
records=$(cat records.txt)

#loop through records entries and appends it to database file
first=0
for entry in $records; 
do
    if [ $first == 0 ]; then
        expect -c "send \"1\n\"" -c "expect \"#\""
        echo 1 | ./student-record.out -f database -c
        first=1
    else
        ./student-record.out -f database -a
    fi 
        echo "${entry}"
done

#list the student database with -l option

./student_record.out -f database -l

#list the student database with xxd option

xxd database

#read records variable

for entry in $records; 
do
    echo "${entry}" | cut -d ' ' -f 1 | ./student_record.out -f database -q -n
done
