**№7 К занятию “Symmetric cryptography”, 6 баллов**

**Задание:**

- Сделать программу - консольное приложение, используя языки: С/C++, Rust, Python, Go, Node.JS.
- Программа принимает три параметра командной строки, типа:
- ./program --file <filename> --numbilets 20 --parameter 42
    - Параметры: имя файла с ФИО студентов, число билетов, параметр, изменяющий распределение. Программа выдает в консоль строку из файла + номер билета. Номера билетов детерминировано связаны с ФИО и параметром, меняющим распределение. Распределение должно быть максимально равномерным
- Входные данные (параметры командной строки):
    - 1) файл, где каждая строка - это ФИО студента, типа:
        - Иванов Иван Иванович
        - Ярцев Ярослав Ярославович
        - …
        - Петров Петр Петрович
    - 2) число билетов N (билеты нумеруются с 1 до N (включая N))
    - 3) численный параметр, детерминированно меняющий распределение (при его изменении распределение номеров билетов максимально изменяется). При использовании одного и того же параметра, одна и та же строка Фамилия-Имя из файла всегда генерирует один и тот же номер билета
- Выходные данные: вывод в STDOUT строк вида:
    - Иванов Иван Иванович: 21
    - Ярцев Ярослав Ярославович: 12
    - …
    - Петров Петр Петрович: 11

**Как выполнить:**

- github репозиторий с файлами проекта
    - отдельный репозиторий на GitHub c образцом вывода в README.md


### Реализация
В качестве алгоритма симметричного шифрования был выбран **AES 128 ECB**. Реализация находится в `AES128.h`
Ссылки на полезные материалы используемые при реализации:

[AES-128. Детали и реализация на python](https://habr.com/ru/post/212235/)

[Как устроен AES](https://habr.com/ru/post/112733/)

[Кратко с реализацией о AES 128 ECB](https://habr.com/ru/post/451830/)

[Официальная документация](https://csrc.nist.gov/csrc/media/publications/fips/197/final/documents/fips-197.pdf)

[AES (стандарт шифрования)](https://ru.wikipedia.org/wiki/AES_(%D1%81%D1%82%D0%B0%D0%BD%D0%B4%D0%B0%D1%80%D1%82_%D1%88%D0%B8%D1%84%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F))

[Алгоритмы шифрования. Специальный справочник. Автор: Панасенко С.П](https://denis.elib.ru/Documents/Books/PanasenkoSP_Crypto_algoritms_2008.pdf)

NOTE: В папке `test` расположен простой тест на алгоритм.

### Пример
```
Сазонов Артём Михаилович 15
Силиванова Софья Тихоновна 18
Бояринова Антонина Ивановна 14
Дьяченко Степан Евграфович 10
Морошкин Дмитрий Пахомович 4
Морошкин Дмитрий Пахомович 4
Морошкин Дмитрий Пахомович 4
Яценко Ирина Антониновна 14
Серых Арсений Евграфович 0
Голубовский Илья Савелиевич 12
Старков Тимофей Всеволодович 18
Лапухина Антонина Михеевна 2
Михальченко Алла Ивановна 15
Ивашов Леонид Евграфович 17
Кузикин Виталий Панкратиевич 3
Занина Оксана Никитевна 19
Лихачева Наталья Михеевна 9
Гаголин Никита Фролович 6
Грушанина Марина Несторовна 6
Зыкин Дмитрий Архипович 9
Невзоров Степан Олегович 9
Колбягина Галина Брониславовна 10
Малкин Александр Андронович 7
Бакрылова Надежда Мефодиевна 15
Грехов Никита Изяславович 14
Шипулин Валентин Натанович 8
```