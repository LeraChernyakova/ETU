# Сравнение аналогов

## Принцип отбора аналогов
В роли сравнительных аналогов были рассмотрены системы управления данными, использующийся для хранения большого объема данных. Подбор аналогов осуществлялся с использованием Google Scholar и поисковой системы Google. Для поиска аналогов применялись следующие запросы: "системы хранения данных", "системы управления данными", "объектное хранилище", "storage services", "storage system", "object storage".

### MinIO
Объектное хранилище, поддерживающее протокол S3 (Simple Storage Service) [1]. Данная система используется, когда требуется согласованное, производительное и масштабируемое хранилище для данных в неструктурированном формате.

### Ceph
Распределенная система хранения, предлагающая объектное (поддерживает протокол S3), блочное и файловое хранилище [2]. Широко используется для хранения больших объемов данных, требующих высокой доступности и отказоустойчивости.

### OpenStack Swift
Объектное хранилище, поддерживающее протокол S3, является частью платформы OpenStack [3]. Предназначена для работы с большими объемами данных, обеспечивая масштабируемость, отказоустойчивость и высокую доступность. Как и MinIO обычно используется для хранения неструктурированных данных.

### GridFS
Система хранения файлов, встроенная в базу данных MongoDB [4]. Используется для хранения файлов, которые превышают размер стандартных документов MongoDB. GridFS разделяет файлы на части, из-за чего можно читать файл без полной загрузки в память.

### HDFS
Распределенная файловая система, которая используется в экосистеме Apache Hadoop [5]. Используется вместе с остальными продуктами Apache Hadoop, для обработки и хранения больших объемов данных.

## Критерии сравнения аналогов

### Скорость доступа
Критерий оценивает скорость работы с данными. Является ключевым фактором при работе с большими видео данными.

### Управление метаданными
Критерий показывает, как система управления данными хранит дополнительную информацию(метаданные) и какие возможности предоставляет для работы с ними. В системе видеомониторинга метаданные зачастую несут следующую информацию: временные метки, местоположение (камеры), результаты из аналитических систем и другие данные.

### Отказоустойчивость системы
Критерий показывает какими средствами, достигается отказоустойчивость в случае сбоя оборудования или программного обеспечения. Для видеомониторинга важно, чтобы система сохраняла данные, даже если часть оборудования выходит из строя. Наиболее интересные в контексте хранения данных следующие механизмы и подходы для обеспечения отказоустойчивости [6]:
- Репликация - создание копий данных.
- Шардирование - разбиения данных на части (шарды), которые могут храниться на разных узлах системы.
- Автоматическое восстановление - способность системы автоматически обнаруживать повреждения и восстанавливать свои данные без стороннего вмешательства.

## Таблица сравнения аналогов
Таблица 1 -- Сравнение систем управления данными
| Аналог | Скорость доступа | Управление метаданными                                                         | Отказоустойчивость системы                              |
|--------|------------------|--------------------------------------------------------------------------------|---------------------------------------------------------|
| MinIO  | Высокая          | Ограниченное, необходимы сторонние системы                                     | Репликация, поддерживает шардирование                   |
| Ceph   | Высокая          | Поддериживает различные типы метаданных и тегов, метаданные хранятся отдельно  | Репликация, шардирование, автоматическое восстановление |
| Swift  | Средняя          | Ограниченное, необходимы сторонние системы                                     | Репликация, шардирование контейнеров с данными          |
| GridFS | Низкая           | Работает с метаданными через возможности MongoDB                               | Репликация и шардирование на уровне MongoDB             |
| HDFS   | Средняя          | Ограниченное, необходимы сторонние системы                                     | Репликация, шардирование, автоматическое восстановление |

## Выводы по итогам сравнения
По результатам сравнения систем управления данными, представленным в таблице 1, можно сказать, что объектные хранилища имеют скорость доступа выше, чем файловые системы GridFS и HDFS. Говоря про управления метаданными, Ceph демонстрирует наибольшие возможности в сравнении с другими, большинству из них требуются сторонние системы. Все рассмотренные системы управления данными имеют схожие возможности к репликации и шардированию, однако Ceph имеет также возможность автоматического восстановления.

## Выбор метода решения
В системе видеомониторинга Ceph будет использоваться, как решение для хранения видео данных с камер видеонаблюдения, а также для хранения метаданных каждой записи, включая результаты из аналитических систем. Высокая отказоустойчивость Ceph обеспечит надежность всей системы в целом.

## Список использованных источников
1. MinIO, Inc. MinIO | S3 Compatible Storage for AI // Официальный сайт MinIO. - https://min.io/.
2. Red Hat. Ceph.io // Официальный сайт Ceph. - https://ceph.io/en/.
3. Rackspace. Swift Documentation // Официальная документация к Swift - https://docs.openstack.org/swift/latest/.
4. MongoDB. GridFS - MongoDB Manual // Официальная документация к GridFS - https://www.mongodb.com/docs/manual/core/gridfs/.
5. Apache Software Foundation. HDFS User Guide // Руководство пользователя к HDFS - https://hadoop.apache.org/docs/stable/hadoop-project-dist/hadoop-hdfs/HdfsUserGuide.html.
6. Hussein A. A. et al. State of Art Survey for Fault Tolerance Feasibility in Distributed Systems //Asian Journal of Research in Computer Science. – 2021. – Т. 11. – №. 4. – С. 19-34.