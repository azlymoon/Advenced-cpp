# Лабораторные работы по курсам C/C++

Это репозиторий с заданиями по курсам:
* Программирование на языке Си,
* *Программирование на языке Си-плюс-плюс (когда начнётся).*

Тут будут выкладываться условия задаваемых работ. Сами работы надо будет сдавать в своих приватных
репозиториях (преподаватели имеют туда доступ). Каждая работа появляется в виде отдельной папки
и выполняется в ней же (**не меняйте эту структуру, пожалуйста!**).

## Содержание
1. [Контакты преподавателей](#контакты-преподавателей)
1. [Общие требования к работам](#общие-требования-к-работам)
   1. [Структура решения](#структура-решения)
   1. [Требования к Makefile](#требования-к-makefile)
   1. [Требования к CMakeLists.txt](#требования-к-cmakeliststxt)
   1. [Требования к коду](#требования-к-коду)
   1. [Требования к _Merge Requests_](#требования-к-merge-requests)
1. [Как пользоваться своим репозиторием?](#как-пользоваться-своим-репозиторием)
   1. [Начальная настройка](#начальная-настройка)
   1. [Как начать делать задание](#как-начать-делать-задание)
   1. [Как проверить работу на открытых тестах](#как-проверить-работу-на-открытых-тестах)
   1. [Как отправить работу на проверку](#как-отправить-работу-на-проверку)


## Контакты преподавателей
| Преподаватель      | Ник на GitLab |
|--------------------|---------------|
| Иван Голубев       | rshaniiazov   |
| Ростислав Шаниязов | igolubev      |

## Общие требования к работам

### Структура решения

* Каждое решение содержится в вашем репозитории в отдельной папке в соответствии с условием.
* Решение должно содержать файлы для одной из систем сборки:
  * `Makefile` для `make`,
  * `CMakeLists.txt` для `cmake`.
* Все файлы решения (и исходные, и артефакты) должны находиться в правильных местах внутри папки
  решения:
  * Исходные файлы C/C++ которые непосредственно компилируются должны быть в подпапке `src/`.
  * Заголовочные файлы C/C++ должны быть в подпапке `include/`.
  * Все объектные файлы, возникающие по ходу сборки, должны быть в папке `obj/` _(неактуально для
    CMake)_.
  * Исполняемые собранные программы должны быть в самой папке с решением.
* Если не сказано иного, решение должно собирать приложение, которое называется так же, как и папка.
* В репозитории, включая историю, не должны храниться любые артефакты сборки и тестирования,
  включая:
  * папку `obj/` и папку сборки CMake (CLion вам будет создавать что-то вида `cmake-build*/`),
  * объектные файлы,
  * исполняемые программы,
  * файлы от запуска тестов.

  *Рекомендуется использование `.gitignore`*.
* Допускается, чтобы используемая система сборки собирала дополнительное приложение `test`, которое
  может использоваться вами же для тестирования вашего решения. В некоторых заданиях эта часть будет
  обязательной (или даже основной).
  * Тесты должны отрабатывать без вмешательства пользователя (никаких проверок глазами или
    интерактивных действий),
  * Тесты должны помогать отличить корректную реализацию от некорректной (если тест выполняется
    абсолютно всегда или никогда, он неинформативен).
  * Тесты должны быть детерминированны (если от перезапуска они то проходят, то нет,
    они малополезны).
  * Если тесты написаны, решение должно их проходить.

Конкретное задание может уточнять требования.

#### Пример:

В репозитории, при использовании `make`:
```
ваш-репозиторий/
├╼ README.md          # этот файл!
├╼ lab-00_example/    # папка с заданием, пример
│  ├╼ .gitignore
│  ├╼ include/
│  │  ╰╼ sample.h
│  ├╼ Makefile
│  ├╼ README.md       # условие задания
│  ╰╼ src/
│     ├╼ main.c
│     ├╼ sample.c
│     ╰╼ test.c
╰╼ …
```

В репозитории после запуска `make`, `make all` или `make lab-00_example test`:
```
ваш-репозиторий/
├╼ …
├╼ lab-00_example/
│  ├╼ .gitignore
│  ├╼ include/
│  │  ╰╼ sample.h
│  ├╼ lab-00_example  # ваша основная собранная программа
│  ├╼ Makefile
│  ├╼ obj/
│  │  ├╼ main.o
│  │  ├╼ sample.o
│  │  ╰╼ test.o
│  ├╼ README.md
│  ├╼ src/
│  │  ├╼ main.c
│  │  ├╼ sample.c
│  │  ╰╼ test.c
│  ╰╼ test           # ваша собранная программа с тестами
╰╼ …
```
После выполнения `make clean` дерево файлов должно вернуться в состояние до сборки.

### Требования к _Makefile_

При использовании системы сборки `make`:

* Каждая из `make`, `make all` и `make НАЗВАНИЕ-ПРИЛОЖЕНИЯ` должны собрать программы из задания.
* `make clean` должен удалять все артефакты сборки, включая созданные папки. Она должна успешно
отрабатывать даже если репозиторий уже чист.
* Правила должны быть корректными:
  * Повторные запросы на сборку конечных или промежуточных файлов без изменений не должно
    приводить к каким-либо действиям.
  * Если же изменения требуют пересборки, должны выполняться лишь необходимые действия.
    * В частности это означает что вы должны правильно прописывать зависимости на заголовочные
      файлы.
    * В частности, зависимости на папки должна быть лишь на существование, а не на время
  модификации.
* Компилятор должен быть прописан только как `gcc` или `$(CC)` для C и `g++` или `$(CXX)` для C++,
  никаких полных путей.
* Компилятору всегда указывайте флаги `-Wall -Wextra -Werror`, включающие множество предупреждений
как ошибки.
* Не включайте в отправленном решении в флагах сборки санитайзеры.

### Требования к _CMakeLists.txt_

При использовании системы сборки `cmake`:

* Вам доступна версия CMake 3.16. Указывайте её в `cmake_minimum_required`. _CLion по умолчанию
  использует свою версию, которая может быть новее._
* В директиве `project` указывайте используемый язык явно: `project(lab-00_example C)`.
* Вся суть CMake в том, чтобы абстрагироваться от конкретного компилятора. Не завязывайтесь на
  ваш компилятор.
  * В том числе CMake из коробки умеет в виды сборки, и из коробки есть *Debug* для отладки и
    *Release* с оптимизациями. Не вмешивайтесь в выбор оптимизации глобально.

### Требования к коду

* Для языка Си используются довольно распространённые расширения `.c`/`.h`, для языка C++ давайте
  использовать `.cpp`/`.hpp`.
* Если файл реализации (`.c`/`.cpp`) что-то предоставляет другим единицам трансляции, это должно
  иметь объявление в соответствующем ему заголовочном файле (`.h`/`.hpp`). Файл реализации должен
  подключать свой заголовок.
* Всё, что файл реализации не предоставляет другим единицам трансляции, не должно быть видно в
  других единицах трансляции. Не включайте в заголовочные файлы то, чему там не место. *Дальше по
  курсу мы научимся делать ещё кое-что со словом `static`.*
* Заголовочный файл должен быть защищён он повторного подключения стандартными *include guards*
  или нестандартной (но доступной буквально везде) `#pragma once`.
* Не пользуйтесь относительными путями к папке `include`, вместо этого есть флаги компилятора.
* Программа к своему завершению должна освобождать все взятые ей ресурсы *(кроме аварийных ситуаций,
  где разрешено заданием)*.
* Программа не должна содержать *неопределённого поведения* (из самого частого: выходов за пределы
  массивов и обращение к невалидным указателям или ссылкам).
* Код должен соблюдать базовые требования к стилю:
  * Правильные и консистентные по решению отступы,
  * Пробелы и расположения управляющих конструкций должны соответствовать популярным стилям.

### Требования к _Merge Requests_

* Называйте ветки ровно названием папки с лабораторной. Название вашей ветки, например, должно называться как: `lab-00_example`.
* Называйте *Merge Request* в виде
  ```
  C/C++: ${Фамилия} ${Имя} ${НомерГруппы}, ${Название папки с заданием}
  ```
* *Merge Request* должен содержать только изменения в папке с соответствующей ему лабораторной.
  **Нельзя**, чтобы в нём же всплывали изменения из других заданий или прочих папок.
* Назначайте вашего преподавателя в _Reviewer_. **Не в _Assignee_.**
* В момент проверки целью _Merge Request_ должна быть ваша ветка _master_, которая уже содержит
  актуальное условие задания за счёт коммитов преподавателей из общего репозитория.
  * Самим копировать и коммитить эти файлы нельзя.
  * Чаще всего на момент практики условие опубликовано в финальном виде, но в редких случаях мы
    можем сообщить об обновлении. В такой ситуации преподаватель может помочь поправить ваши ветки.
  * Если всё правильно, то на вкладке _Changes_ должно быть отображено, как вы меняете файлы с кодом
    только в папке этого задания.
* Вам **запрещено** менять файлы с описанием задания, скрипты для проверок и предоставленные тесты.
  Остальные файлы, если предоставлены (чаще всего это скелет для решения), в вашем распоряжении.
* _Merge Request_ должен иметь:
  * Ни одну из меток, если вы ещё его не отправляете на проверку,
  * Метку *ожидает проверки* (ставится вами), чтобы преподаватель его проверил,
  * Метку *ожидает исправлений* (ставится преподавателем), когда от вас ждут исправлений и/или
    ответов,
  * Метку *принято* (ставится преподавателем), когда к заданию больше нет вопросов.

## Как пользоваться своим репозиторием?

> Дальнейшие слова ожидают, что Git вы знаете на базовом уровне. Если нет — просите помощи у вашего
> преподавателя.
>
> Из терминала делать необязательно, если ваша среда разработки умеет в Git, в её интерфейсе можно
> выполнить все те же действия.

### Начальная настройка

1. Сделайте локальную копию своего приватного репозитория. Ссылку можно найти нажав кнопку *Clone*.
   ```sh
   git clone git clone https://git.miem.hse.ru/cpp_2022/students/SURNAME.git
   
   # или если вы настроили SSH-ключ:
   git clone git@git.miem.hse.ru:cpp_2022/students/SURNAME.git
   ```
   Можно указать ещё одним аргументом где именно делать репозиторий вместо `./my-labs-repo`:
   ```sh
   git clone … my-labs-repo
   ```
1. Перейдите в этот репозиторий:
   ```sh
   cd SURNAME
   # или, если указали
   cd my-labs-repo
   ```
1. Сейчас ваш репозиторий на GitLab.com добавлен как удалённый *origin*. Добавим к нему репозиторий
   с условиями как *upstream*:
   ```sh
   git remote add upstream https://git.miem.hse.ru/cpp_2022/public/labs.git
   ```
   Путь, при необходимости, можно найти под кнопкой *Clone* репозитория с условиями.
1. Можно пользоваться!

### Как начать делать задание:

1. Находясь в вашем репозитории, убедитесь что у вас нет не сохранённых, но нужных вам изменений,
   и что вы на ветке по умолчанию *master*:
   ```sh
   git status
   git switch master
   ```
1. Обновите локальную копию репозитория *upstream*:
   ```sh
   git fetch upstream
   ```
1. Включите в свой *master* изменения из *upstream/master*:
   ```sh
   git merge upstream/master --allow-unrelated-histories
   ```
   Может появиться редактор для сообщения (но если вы действовали точно по инструкции не появится),
   можно не меняя ничего сохранить и выйти (в Vim достаточно нажать по очереди: `:`, `w`, `q`,
   `Enter`).
1. Отправьте обновлённый `master` на ваш GitLab:
   ```
   git push
   ```
1. Создайте новую ветку для нового задания, название ветки на ваше усмотрение, но желательно
   включает название лабораторной:
   ```sh
   git switch -c lab-01_makefile
   ```
1. Сразу отправим её, в неизменном виде, на сервер:
   ```sh
   git push -u origin lab-01_makefile # тут надо повторить название
   ```
1. Всё, в этой ветке можно делать свою работу! Или во многих ветках, как вам удобнее, но на
   проверку отправьте лишь одну.

### Как проверить работу на открытых тестах:

Просто запустите скрипт `./run-tests ИМЯ-ПАПКИ` в корне репозитория. Кстати, именно он же
используется и для закрытых тестов:
```sh
pwd # убедились что в корне репозитория
./run-tests lab-01_makefile
```
Все промежуточные выводы (ввод и вывод на каждом тесте, ошибки от Valgrind и прочее) будут сохранены
в папку `output/`

### Как отправить работу на проверку:

1. Убедитесь, что у вас отправлены все изменения в ветке с работой:
   ```sh
   git status
   git push # если не всё отправлено
   ```
2. Откройте сайт с вашим репозиторием. Если приглашения создать *Merge Request* не увидите, то
   переключитесь на ветку с решением.
3. Создайте *Merge Request* в основную ветку *master*. Назовите его, пожалуйста, как просят выше,
   и укажите в *Reviewer* вашего преподавателя. Когда он готов к проверке, выставьте метку
   *ожидает проверки*.

Созданный *Merge Request* преподаватель может прийти и проверить. Если добавить в начало названия
`Draft: ` и не назначить проверяющего или не выставить метку, такой *Merge Request* можно создать
заранее (не забудьте к моменту сдачи поправить!), чтобы задать вопросы или посмотреть на результат
автоматической проверки.

Автоматическая проверка, если включена, производится на каждую отправку в правильно названной ветке.
Там можно увидеть результат компиляции вашего задания, запуска на предоставленных тестах и на
нераскрытых тестах.

Всё обсуждение по проверке и другим вопросам по коду задания будет идти в созданном
*Merge Request*-е.

Мы не планируем вливать эти *Merge Request*-ы в основную ветку *master*, но если вы уверены в себе, то
после окончания проверки можете это сделать.

[emkn-C]: https://emkn.ru/courses/2022-autumn/2.108-c/
