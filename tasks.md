#### task1
Требуется безопасно и эффективно реализовать монитор с двумя потоками: потоком-поставщиком и потоком-потребителем. Поток-поставщик должен с задержкой в одну секунду инициировать условное событие, о чём должен выводить сообщение на экран. Поток-потребитель должен это условное событие получать, о чём также должен сообщать на экране. В итоге на экране должна появляться серия чередующихся сообщений об отправлении события и его обработке. Сообщения не должны нарушать очерёдность. Ожидание события должно происходить с минимальным потреблением процессорного времени, т. е. быть практически равным нулю. Подразумевается, что условное событие может содержать несериализуемые данные (скажем, передаётся экземпляр класса по указателю).
### task2
Требуется подготовить безопасную реализацию серверного процесса, который совмещает обработку соединений TCP/IP с обработкой сигналов (можно выбрать, скажем, сигнал SIGHUP). Приложение должно:

1. Принимать соединения на некоторый порт, сообщать о новых соединениях на терминал, одно соединение оставлять принятым, остальные закрывать сразу после подключения.
2. При появлении любых данных в соединении выводить сообщение на терминал (для простоты достаточно вывести только количество полученных данных).
3. При получении сигнала выводить сообщение на терминал.

Фактически, работа сводится к правильному вызову функции pselect(), но все действия должны быть выполнены в предельно безопасном виде, исключающем любые race condition.

### task3
Требуется подготовить модуль для загрузки в ядро Linux. Модуль должен:
- сопровождаться Makefile для сборки;
- оформляться в виде файла *.ko;
- загружаться командой insmod и выгружаться командой rmmod;
при загрузке выводить в dmesg строку «Welcome to the Tomsk State University»;
- при выгрузке выводить в dmesg строку «Tomsk State University forever!».

### task4
Модуль, подготовленный на первой части работы, следует дополнить функционалом, который позволял бы при своей загрузке создавать файл tsulab в каталоге /proc. Содержимое этого файла будет определяться индивидуальным заданием (*При каждом чтении выводить сумму чисел ряда Фибоначчи*) для каждого учащегося, которое он будет получать при сдаче первой части работы. 