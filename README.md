# Операционные системы ИДЗ №3
 ### Русанов Андрей БПИ219
 ### Вариант 22
 **Задача об инвентаризации по рядам.** . После нового года в библиотеке университета обнаружилась пропажа каталога. После поиска и наказания виноватых, ректор дал указание восстановить каталог силами студентов. Фонд библиотека представляет собой прямоугольное помещение, в котором находится M рядов по N шка8
фов по K книг в каждом шкафу. Требуется создать приложение, составляющее каталог. В качестве отдельного процесса
задается составление подкаталога одним студентом–процессом для
одного ряда. После этого студент передает информацию процессу–
библиотекарю, который сортирует ее учитывая подкаталоги, переданные другими студентами. Сервер формирует каталог, получая
информацию от студентов — клиентов. Порождение студентов
может быть вручную или с использованием скрипта. *Примечание. Каталог — это список книг, упорядоченный по их
инвентарному номеру или по алфавиту (на выбор разработчика). Каждая строка каталога содержит идентифицирующее значение (номер или название), номер ряда,
номер шкафа, номер книги в шкафу.*

##  4-5 баллов
Необходимо сначала запустить сервер(библиотекаря) , а затем поочередно всех клиентов(студентов)  в разных терминалах.
Программа библиотекаря принимает на вход в качестве аргументов коммандной строки порт, целые числа m, n, k, ( m\*n\*k не должно быть больше 1000), и количество студентов.
```
gcc librarian.c -o librarian
./librarian 8888 2 2 2 1
```
Программа студента принимает на вход в качестве аргументов коммандной строки IP-адрес, порт и номер студента.
```
gcc student .c -o student 
./student 127.0.0.1 8888 1
```
Библиотекарь создаёт массив книг со случайными номерами, затем по очереди передаёт каждый ряд студентам. Студент сортирует переданный ему ряд по возрастанию номеров сортировкой вставками, выводя сообщение каждый раз, когда он находит место для книги. 
Когда ряд отсортирован, студен  передаёт отсортированные значения обратно билиотекарю.

##  6-7 баллов
В решении на 6-7 баллов добавлена программа presenter.c, выводящая информацию, которyю печатают сервер и клиенты. Программа presenter.c принимает на вход в качестве аргументов коммандной строки IP-адрес и порт сервера
```
gcc presenter.c -o presenter
./presenter 127.0.0.1 8888
```