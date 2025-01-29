db = db.getSiblingDB('moodle-statistics');

db.users.insertMany([
    {
        "name": "Иван",
        "surname": "Иванов",
        "lastname": "Иванович",
        "email": "ivan@mail.ru",
        "position": "admin",
        "password": "bhewrtfm3klmt3"
    },
    {
        "name": "Петров",
        "surname": "Петр",
        "lastname": "Петрович",
        "email": "petr@mail.ru",
        "position": "regular",
        "password": "bhewrsdfsdfsdwlmt3"
    },
    {
        "name": "Сидоров",
        "surname": "Федор",
        "lastname": "Федорович",
        "email": "fedor@mail.ru",
        "position": "regular",
        "password": "bhsdgdfgergef3klmt3"
    }
])

db.sessions.insertMany([
    {
        "_id": ObjectId("6648756f964c1253e72202db"),
        "browser": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit",
        "page": "http://e.moevm.info",
        "page_html": "<html></html>",
        "title": "kakoy-to title",
        "window": {
            "height": 800,
            "width": 1200
        }
    },
    {
        "_id": ObjectId("6648756f964c1253e72202dc"),
        "browser": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit",
        "page": "http://e.moevm.info",
        "page_html": "<html></html>",
        "title": "kakoy-to title",
        "window": {
            "height": 800,
            "width": 1200
        }
    }
])

db.statistics.insertMany([
    {
        "student_id": 2071,
        "student": "Диана Романенко",
        "session_id": ObjectId("6648756f964c1253e72202db"),
        "email": "diana@mail.ru",
        "course": "Курс молодого бойца",
        "actions": [
            {
                "timestamp": new Date("2024-02-02T14:00:00"),
                "element_type": "button",
                "element_name": "сохранить",
                "action_type": "conversation",
                "event_type": "mousedown", 
                "element_html": `<input id="id_q_6627c493e6c5f" class="form-control" type="text" name="q" placeholder="Поиск" size="13" tabindex="-1">`
               }
        ]
    },
    {
        "student_id": 824,        
        "student": "Беззубов Даниил",
        "email": "daniil@mail.ru",
        "session_id": ObjectId("6648756f964c1253e72202dc"),
        "course": "Курс молодого бойца",
        "actions": [
            {
                "timestamp": new Date("2024-02-02T14:00:00"),
                "element_type": "button",
                "element_name": "сохранить",
                "action_type": "conversation",
                "event_type": "mousedown", 
                "element_html": `<input id="id_q_6627c493e6c5f" class="form-control" type="text" name="q" placeholder="Поиск" size="13" tabindex="-1">`
            },
            {
                "timestamp": new Date("2024-02-02T14:00:00"),
                "element_type": "button",
                "element_name": "следующая страница",
                "action_type": "conversation",
                "event_type": "mousedown", 
                "element_html": `<input id="id_q_6627c493e6c5f" class="form-control" type="text" name="q" placeholder="Поиск" size="13" tabindex="-1">`
            }
        ]
    }
])

