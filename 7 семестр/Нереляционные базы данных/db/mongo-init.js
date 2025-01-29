db = db.getSiblingDB('plants_market');

db.plants.insertMany([
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c4d"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://i.pinimg.com/originals/d8/44/39/d84439377efd15eeceb6d84c1d6f9c2f.jpg",
    "size": "Маленькие (до 20 см)",
    "price": 500,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "care_complexity": "Для начинающих",
    "description": "Растение для небольших тенистых пространств, легкое в уходе.",
    "type": "Комнатное растение",
    "species": "Фикус",
    "created_at": ISODate("2024-01-31T10:00:00Z"),
    "place": "Москва",
    "sold_at": ISODate("2024-12-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c4e"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://cache3.youla.io/files/images/780_780/5d/dc/5ddc14211bee2b907f2ff783.jpg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1500,
    "light_condition": "Полутеневые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Требуют среднего ухода",
    "description": "Универсальное растение для офиса и дома.",
    "type": "Суккулент",
    "species": "Алоэ",
    "created_at": ISODate("2024-01-02T11:00:00Z"),
    "place": "Санкт-Петербург",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c4f"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://avatars.mds.yandex.net/i?id=5e9be1d6a4f0d162a67a029eb69b1286_l-5495958-images-thumbs&n=13",
    "size": "Большие (более 50 см)",
    "price": 3000,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Эффектное растение для больших помещений.",
    "type": "Пальма",
    "species": "Финиковая пальма",
    "created_at": ISODate("2024-09-29T12:00:00Z"),
    "place": "Казань",
    "sold_at": ISODate("2024-12-01T15:20:31Z")
  },
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c50"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7c"),
    "image": "https://avatars.mds.yandex.net/i?id=68c1188c9f5b93381053c4a9f0ed9c86_l-5235022-images-thumbs&n=13",
    "size": "Маленькие (до 20 см)",
    "price": 800,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для начинающих",
    "description": "Неприхотливое растение, подходит для небольших помещений.",
    "type": "Комнатное растение",
    "species": "Сансевиерия",
    "created_at": ISODate("2024-10-04T13:00:00Z"),
    "place": "Новосибирск",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c51"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7c"),
    "image": "https://avatars.mds.yandex.net/i?id=02ff3c807e963cecee0fc557f14b75de_l-6505870-images-thumbs&n=13",
    "size": "Средние (от 20 до 50 см)",
    "price": 1200,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Требуют среднего ухода",
    "description": "Растение для офиса и дома, легкое в уходе.",
    "type": "Папоротник",
    "species": "Нефролепис",
    "created_at": ISODate("2024-02-11T14:00:00Z"),
    "place": "Екатеринбург",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c52"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c80"),
    "image": "https://yandex-images.clstorage.net/9X9AVN383/ebf5cd36R/md48cSr7oQG1XR2i0SuisLQEDDiOAYN-dk-0VYuR20_bEA0edQnOdtqGLs_9AEyHjorayr19s3RwEjYyrEN2_PzLbXB30tgdtUlMjvgbyoD0UTxNglSLGmZS0GWSITaGEsGlrqzsG48u63ez-E1NspOPQ37t1C7Y_d42HsTm8wHZZnzhHvM4ib1xRAqdqwqs7LFcYLKcW3uiK60kntGKjtIhdZ4gRLOjNqPP38SdNCYbQ7u_2WCedLmK6hoMSg_9JVqE4ZIrwCGJgQhCZSsqqDyhkCR--JfTzstlODrtmqKmoWEuJATjj4pfd0e4lWCCY8-Hv_m01ux9lu76fP6PqT3GLO32i2TRqe1cxuEbtozwObhUUkA3U0ZfcSTqjVoW_lFlhvRoyw8uO0cnXG0MBrNrs8_1eCLwOe6CHuiuKznN5piFYmeIjb3pyD6ZZzp8lAGEKKIE5zu-x2WcAk3aQrKR9XZUdONLRpvrj0Q9BAZLk6dTBchqEE3-Tn44wm-90R40cRLnLCFRcVw2GTMGnLDV0CCqDJtDwrcNuPqVHiZCoZEG9Awf54qnJ7P0ZaTCc_P_U2FALgxlUrqeyNITBc3WhPkKA3CVvW0MIuH3AvCo1QhYRhyr967L-YQeYRpefhVBgrCsi_fK10OH7P18jns7Xz8NtF4QbW6CAmhG20WJlpR1TvtYaTWdYCKBfw4AhPm4HI4Yk0-Wu2EsWvEqwkphzXZsTNcLtocv6_Q5DIJThzufKSzeYKEOMoa4Ipsl1ZaY-Y5_MJkNUdTGCU_6OOT1vEyKxP-XIotNlL41ch5-1cUybORnA6pvG5PQufRSf3enV_WI7iTBZjKGkBaTtYGWGMl2-0RR1UHYBvn_xjikqYBoLlznjw7z_bA66WoSMtn18liUy_8CRzdXXMGcklP3rxP9oC5gLfpGojg2yz0RsqTJJv9Qgb1pAHohq0I0uNGk3D6MB9--172slnlY",
    "size": "Большие (более 50 см)",
    "price": 2700,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Красивое растение для светлых помещений.",
    "type": "Пальма",
    "species": "Кокосовая пальма",
    "created_at": ISODate("2024-08-27T15:00:00Z"),
    "place": "Нижний Новгород",
    "sold_at":ISODate("2024-02-22T10:00:00Z")
  },
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c53"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c80"),
    "image": "https://avatars.mds.yandex.net/i?id=8428ff239edffbd66e53cce304e1bb0b_l-13095119-images-thumbs&n=13",
    "size": "Маленькие (до 20 см)",
    "price": 600,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для начинающих",
    "description": "Легкое в уходе растение для небольших помещений.",
    "type": "Суккулент",
    "species": "Каланхоэ",
    "created_at": ISODate("2024-07-07T16:00:00Z"),
    "place": "Воронеж",
    "sold_at":ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c54"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
    "image": "https://flowry.ru/wp-content/uploads/2022/03/cay-van-nien-thanh-loc-khong-khi.jpg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1400,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "care_complexity": "Требуют среднего ухода",
    "description": "Эффектное растение, отлично очищает воздух.",
    "type": "Комнатное растение",
    "species": "Диффенбахия",
    "created_at": ISODate("2024-03-30T17:00:00Z"),
    "place": "Самара",
    "sold_at":ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c55"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
    "image": "https://avatars.mds.yandex.net/i?id=4a2c5e1bb0e5b6d6b425874ccd928902_l-9065769-images-thumbs&n=13",
    "size": "Большие (более 50 см)",
    "price": 3200,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Эффектное растение, требует яркого освещения.",
    "type": "Пальма",
    "species": "Бамбуковая пальма",
    "created_at": ISODate("2024-03-22T18:00:00Z"),
    "place": "Челябинск",
    "sold_at":ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c56"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
    "image": "https://mirzhvetov.ru/wp-content/uploads/1/8/a/18adf9a04593e2b41da5aa2064dfdac3.jpeg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1300,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Требуют среднего ухода",
    "description": "Подходит для создания уюта и комфорта в интерьере.",
    "type": "Комнатное растение",
    "species": "Плющ",
    "created_at": ISODate("2024-09-11T19:00:00Z"),
    "place": "Ростов-на-Дону",
    "sold_at":ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c01"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://5179935.ru/image/cache/catalog/Gorshechka/Sansevieria%20Hana-1000x1000.jpg",
    "size": "Маленькие (до 20 см)",
    "price": 500,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "care_complexity": "Для начинающих",
    "description": "Идеально подходит для компактных помещений.",
    "type": "Комнатное растение",
    "species": "Сансевиерия",
    "created_at": ISODate("2024-09-12T10:00:00Z"),
    "place": "Москва",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c02"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7b"),
    "image": "https://avatars.mds.yandex.net/get-znatoki/1520758/2a000001786df302fcc14869da3fe6edb91f/w1200",
    "size": "Большие (более 50 см)",
    "price": 2000,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Требует среднего ухода",
    "description": "Подходит для просторных помещений и зимних садов.",
    "type": "Декоративное растение",
    "species": "Фикус Бенджамина",
    "created_at": ISODate("2024-09-13T14:00:00Z"),
    "place": "Санкт-Петербург",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c03"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7c"),
    "image": "https://i.pinimg.com/originals/ed/bf/0b/edbf0b0a08166a5cc01f007341500863.jpg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1500,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Прекрасно дополняет классический интерьер.",
    "type": "Цветущее растение",
    "species": "Орхидея",
    "created_at": ISODate("2024-09-14T16:00:00Z"),
    "place": "Казань",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c04"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7d"),
    "image": "https://avatars.mds.yandex.net/get-marketpic/1584467/pic314d820d4d400e96718e476771931168/orig",
    "size": "Маленькие (до 20 см)",
    "price": 800,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Для начинающих",
    "description": "Идеально подходит для светлых подоконников.",
    "type": "Суккулент",
    "species": "Алоэ вера",
    "created_at": ISODate("2024-09-15T08:30:00Z"),
    "place": "Новосибирск",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c05"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
    "image": "https://dachnik-omsk.ru/upload/medialibrary/e57/tu1vejs2aidi81ya3oxthc56zf6vh4a7/Maranta-Fasinator.jpg",
    "size": "Большие (более 50 см)",
    "price": 2500,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Требует среднего ухода",
    "description": "Добавляет зелени в темных уголках дома.",
    "type": "Декоративное растение",
    "species": "Маранта",
    "created_at": ISODate("2024-09-16T11:45:00Z"),
    "place": "Екатеринбург",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c06"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7f"),
    "image": "https://stocvetov.ru/images/cms/data/flowers/dracena/marginata/marginata5.jpg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1200,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Идеально для декорирования офисных помещений.",
    "type": "Комнатное растение",
    "species": "Драцена",
    "created_at": ISODate("2024-09-17T13:00:00Z"),
    "place": "Воронеж",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c07"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c80"),
    "image": "https://flowwill.ru/wp-content/uploads/6/d/3/6d3c2a38d03753abe46284bfef7763a3.jpeg",
    "size": "Маленькие (до 20 см)",
    "price": 700,
    "light_condition": "Полутеневые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Для начинающих",
    "description": "Отличный выбор для новичков в цветоводстве.",
    "type": "Цветущее растение",
    "species": "Бегония",
    "created_at": ISODate("2024-09-18T15:20:00Z"),
    "place": "Красноярск",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c08"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c81"),
    "image": "https://avatars.mds.yandex.net/get-marketpic/1041839/market_4F9SkkV8wPIFkYLcHklKwA/orig",
    "size": "Большие (более 50 см)",
    "price": 3000,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Эффектное растение для просторных помещений.",
    "type": "Цветущее растение",
    "species": "Гибискус",
    "created_at": ISODate("2024-09-19T17:45:00Z"),
    "place": "Сочи",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c09"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c82"),
    "image": "https://cache3.youla.io/files/images/780_780/5c/f6/5cf62b7d2aecd617a55defc2.jpg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1100,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "care_complexity": "Требует среднего ухода",
    "description": "Необычное растение для любителей оригинальности.",
    "type": "Комнатное растение",
    "species": "Папоротник",
    "created_at": ISODate("2024-09-20T19:30:00Z"),
    "place": "Иркутск",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c10"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
    "image": "https://my-farmer.ru/wp-content/uploads/b/1/f/b1f91746879d3dc2e729cfa489341926.jpg",
    "size": "Маленькие (до 20 см)",
    "price": 400,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для начинающих",
    "description": "Идеально для оживления рабочих зон.",
    "type": "Суккулент",
    "species": "Каланхоэ",
    "created_at": ISODate("2024-09-21T12:00:00Z"),
    "place": "Уфа",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c11"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
    "image": "https://i.etsystatic.com/26466238/r/il/177e61/3474589839/il_1588xN.3474589839_atwb.jpg",
    "size": "Большие (более 50 см)",
    "price": 3200,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Создаёт ощущение тропического уюта.",
    "type": "Экзотическое растение",
    "species": "Монстера",
    "created_at": ISODate("2024-09-22T10:30:00Z"),
    "place": "Краснодар",
    "sold_at": ISODate("2024-10-15T11:11:54Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c12"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
    "image": "https://www.bhg.com/thmb/oDnjlrHprd67aYvinrMfQgVUPtQ=/5332x0/filters:no_upscale():strip_icc()/BHG-spider-plant-c0e0fdd5ec6e4c1588998ce3167f6579.jpg",
    "size": "Маленькие (до 20 см)",
    "price": 600,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для начинающих",
    "description": "Идеально для небольших офисов.",
    "type": "Комнатное растение",
    "species": "Хлорофитум",
    "created_at": ISODate("2024-09-23T14:10:00Z"),
    "place": "Томск",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c13"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
    "image": "https://i.pinimg.com/736x/ee/fb/b5/eefbb5048bb4c4e6c913b1bd44aa8c97.jpg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1800,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "care_complexity": "Требует среднего ухода",
    "description": "Выдерживает прохладные температуры и редкий уход.",
    "type": "Декоративно-лиственное растение",
    "species": "Аглаонема",
    "created_at": ISODate("2024-09-24T17:40:00Z"),
    "place": "Хабаровск",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c14"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://rastenievod.com/wp-content/uploads/2016/08/20.jpg",
    "size": "Большие (более 50 см)",
    "price": 2800,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для начинающих",
    "description": "Создаёт уют в просторных гостиных.",
    "type": "Декоративное растение",
    "species": "Юкка",
    "created_at": ISODate("2024-09-25T11:25:00Z"),
    "place": "Омск",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c15"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://i.pinimg.com/736x/90/42/02/904202dbd44dbb7a68fd4d73fcbd3452.jpg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1000,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Требует среднего ухода",
    "description": "Подходит для создания влажного микроклимата.",
    "type": "Комнатное растение",
    "species": "Спатифиллум",
    "created_at": ISODate("2024-09-26T09:00:00Z"),
    "place": "Саратов",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c16"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://domashniecvety.ru/wp-content/uploads/4/e/7/4e7e7a9272c03254d6dfa0d26eb34231.jpe",
    "size": "Маленькие (до 20 см)",
    "price": 900,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Интересное растение для необычных интерьеров.",
    "type": "Экзотическое растение",
    "species": "Замиокулькас",
    "created_at": ISODate("2024-09-27T15:30:00Z"),
    "place": "Челябинск",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c17"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://selcdn.fedsp.com/eridanus/13/1160/500x500.3c161b73c57712b8.jpeg",
    "size": "Большие (более 50 см)",
    "price": 3500,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Тропическое украшение для больших помещений.",
    "type": "Цветущее растение",
    "species": "Антуриум",
    "created_at": ISODate("2024-09-28T18:50:00Z"),
    "place": "Пермь",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c18"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://static.tildacdn.com/tild3233-3537-4133-b666-363965626333/IKzoftn2SBg.jpg",
    "size": "Маленькие (до 20 см)",
    "price": 750,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для начинающих",
    "description": "Идеально для рабочего стола или подоконника.",
    "type": "Комнатное растение",
    "species": "Суккулент",
    "created_at": ISODate("2024-09-29T14:20:00Z"),
    "place": "Казань",
    "sold_at": ISODate("0001-09-29T20:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c19"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://i.pinimg.com/736x/a1/10/79/a11079d1fce09e7cb945dfebc396574f.jpg",
    "size": "Большие (более 50 см)",
    "price": 2700,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "care_complexity": "Требует среднего ухода",
    "description": "Прекрасный выбор для просторных комнат с низким освещением.",
    "type": "Декоративно-лиственное растение",
    "species": "Сансевиерия",
    "created_at": ISODate("2024-09-30T11:15:00Z"),
    "place": "Самара",
    "sold_at": ISODate("2024-10-01T12:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c20"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "image": "https://mandarin-shop.ru/images/cms/data/cvetushie/kalteya/syurpraiz/2056026.jpg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1500,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Частый полив (ежедневно)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Экзотический вид и красивое цветение.",
    "type": "Цветущее растение",
    "species": "Калатея",
    "created_at": ISODate("2024-10-01T09:45:00Z"),
    "place": "Новосибирск",
    "sold_at": ISODate("2024-11-12T15:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c21"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
    "image": "https://i.pinimg.com/736x/a0/06/68/a00668fb094139a32f6b73581b62709f.jpg",
    "size": "Маленькие (до 20 см)",
    "price": 550,
    "light_condition": "Тенелюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для начинающих",
    "description": "Миниатюрный размер, легко ухаживать.",
    "type": "Декоративное растение",
    "species": "Пеперомия",
    "created_at": ISODate("2024-10-02T08:30:00Z"),
    "place": "Тюмень",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c22"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
    "image": "https://vsegda-pomnim.com/uploads/posts/2024-01/1705312976_vsegda-pomnim-com-p-fikus-bendzhamina-s-krupnimi-listyami-foto-13.jpg",
    "size": "Большие (более 50 см)",
    "price": 4200,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Для опытных цветоводов",
    "description": "Эффектное украшение зимнего сада.",
    "type": "Декоративное растение",
    "species": "Фикус Бенджамина",
    "created_at": ISODate("2024-10-03T16:20:00Z"),
    "place": "Екатеринбург",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c23"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
    "image": "https://mirzhvetov.ru/wp-content/uploads/6/b/d/6bd7ba5d7943e92c6445a93ca617e78b.jpeg",
    "size": "Средние (от 20 до 50 см)",
    "price": 1400,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "care_complexity": "Требует среднего ухода",
    "description": "Необычные листья и долговечность.",
    "type": "Комнатное растение",
    "species": "Филодендрон",
    "created_at": ISODate("2024-10-04T12:50:00Z"),
    "place": "Уфа",
    "sold_at": ISODate("2024-06-07T10:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c24"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
    "image": "https://cdn.nur.kz/images/1120/92f8eac8e0745022.jpeg",
    "size": "Маленькие (до 20 см)",
    "price": 450,
    "light_condition": "Светолюбивые",
    "watering_frequency": "Редкий полив (раз в 2 недели)",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "care_complexity": "Для начинающих",
    "description": "Простое растение для солнечных мест.",
    "type": "Суккулент",
    "species": "Алоэ",
    "created_at": ISODate("2024-10-05T15:10:00Z"),
    "place": "Иркутск",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  },
  {
    "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c25"),
    "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
    "image": "https://avatars.dzeninfra.ru/get-zen_doc/1912454/pub_5da7367f433ecc00b3dabd12_5da73b24aad43600b1f1f430/scale_1200",
    "size": "Большие (более 50 см)",
    "price": 3000,
    "light_condition": "Полутеневые",
    "watering_frequency": "Средний полив (1-2 раза в неделю)",
    "temperature_regime": "Средний режим (15-22°C)",
    "care_complexity": "Требует среднего ухода",
    "description": "Великолепное растение для офиса.",
    "type": "Декоративное растение",
    "species": "Драцена",
    "created_at": ISODate("2024-10-06T11:30:00Z"),
    "place": "Калининград",
    "sold_at": ISODate("0001-01-01T00:00:00Z")
  }
])

db.care_rules.insertMany([
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d10"),
    "species": "Фикус",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7d"),
        "description_addition": "Поддерживайте влажность воздуха, но избегайте сквозняков.",
        "created_at": ISODate("2023-12-12T10:00:00Z")
      },
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7f"),
        "description_addition": "Разместите на светлом месте, но без прямого солнца.",
        "created_at": ISODate("2024-01-05T14:00:00Z")
      }
    ],
    "created_at": ISODate("2023-12-12T10:00:00Z"),
    "updated_at": ISODate("2024-01-05T14:00:00Z"),
    "image": "https://avatars.mds.yandex.net/i?id=5b167f0e52d626daaea97045b9d447f0_l-4577816-images-thumbs&n=13",
    "light_condition": "Тенелюбивые",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "type": "Комнатное растение",
  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d11"),
    "species": "Алоэ",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7c"),
        "description_addition": "Поливайте только после высыхания почвы.",
        "created_at": ISODate("2024-02-10T08:30:00Z")
      }
    ],
    "created_at": ISODate("2024-02-10T08:30:00Z"),
    "updated_at": ISODate("2024-02-10T08:30:00Z"),
    "image": "https://cvety-planety.ru/upload/iblock/776/a4uj1p6m37kghorv2nn4ps1qe774izuy.webp",
    "light_condition": "Полутеневые",
    "temperature_regime": "Средний режим (15-22°C)",
    "type": "Суккулент",
  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d12"),
    "species": "Финиковая пальма",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
        "description_addition": "Не требует частого полива, оптимально раз в месяц.",
        "created_at": ISODate("2024-04-01T09:00:00Z")
      },
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7b"),
        "description_addition": "Подходит для любых условий освещения.",
        "created_at": ISODate("2024-04-15T13:45:00Z")
      }
    ],
    "created_at": ISODate("2024-04-01T09:00:00Z"),
    "updated_at": ISODate("2024-04-15T13:45:00Z"),
    "image": "https://img.inmyroom.ru/inmyroom/resize/620x/jpg:85/uploads/photo/file/77/77e8/jpg_1000_77e814a5-db24-48a0-b39f-d6cb5535b87e.jpg?sign=ac5dcc57b6f51fea31baa4869aa82a98d2c8055d41a650be47cd0045635e485f",
    "light_condition": "Светолюбивые",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "type": "Пальма",

  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d13"),
    "species": "Сансевиерия",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c80"),
        "description_addition": "Регулярно протирайте листья влажной тряпкой.",
        "created_at": ISODate("2024-05-05T16:20:00Z")
      },
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7f"),
        "description_addition": "Держите в тепле, избегайте температур ниже 18°C.",
        "created_at": ISODate("2024-06-01T18:10:00Z")
      }
    ],
    "created_at": ISODate("2024-05-05T16:20:00Z"),
    "updated_at": ISODate("2024-06-01T18:10:00Z"),
    "image": "https://i.pinimg.com/originals/3f/b0/db/3fb0db994ea49b370c06fd8745e03048.jpg",
    "light_condition": "Полутеневые",
    "temperature_regime": "Средний режим (15-22°C)",
    "type": "Комнатное растение",
  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d14"),
    "species": "Нефролепис",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c82"),
        "description_addition": "Поливайте погружением корней в воду.",
        "created_at": ISODate("2024-07-01T09:30:00Z")
      },
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
        "description_addition": "Разместите в помещении с хорошей циркуляцией воздуха.",
        "created_at": ISODate("2024-07-20T17:25:00Z")
      }
    ],
    "created_at": ISODate("2024-07-01T09:30:00Z"),
    "updated_at": ISODate("2024-07-20T17:25:00Z"),
    "image": "https://avatars.mds.yandex.net/i?id=02ff3c807e963cecee0fc557f14b75de_l-6505870-images-thumbs&n=13",
    "light_condition": "Тенелюбивые",
    "temperature_regime": "Средний режим (15-22°C)",
    "type": "Папоротник"
  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d15"),
    "species": "Кокосовая пальма",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "description_addition": "Поливайте после полного высыхания верхнего слоя почвы.",
        "created_at": ISODate("2024-08-01T14:15:00Z")
      }
    ],
    "created_at": ISODate("2024-08-01T14:15:00Z"),
    "updated_at": ISODate("2024-08-01T14:15:00Z"),
    "image": "https://i.pinimg.com/736x/72/51/b4/7251b45263cfcaea655e94aa81ec18e7.jpg",
    "light_condition": "Светолюбивые",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "type": "Пальма"
  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d16"),
    "species": "Каланхоэ",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7b"),
        "description_addition": "Требует умеренного освещения, не любит прямой свет.",
        "created_at": ISODate("2024-09-01T11:30:00Z")
      }
    ],
    "created_at": ISODate("2024-09-01T11:30:00Z"),
    "updated_at": ISODate("2024-09-01T11:30:00Z"),
    "image": "https://avatars.mds.yandex.net/i?id=8428ff239edffbd66e53cce304e1bb0b_l-13095119-images-thumbs&n=13",
    "light_condition": "Полутеневые",
    "temperature_regime": "Средний режим (15-22°C)",
    "type": "Суккулент"
  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d17"),
    "species": "Диффенбахия",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
        "description_addition": "Светолюбивое растение, нуждается в обилии солнечного света.",
        "created_at": ISODate("2024-10-01T08:20:00Z")
      }
    ],
    "created_at": ISODate("2024-10-01T08:20:00Z"),
    "updated_at": ISODate("2024-10-01T08:20:00Z"),
    "image": "https://flowry.ru/wp-content/uploads/2022/03/cay-van-nien-thanh-loc-khong-khi.jpg",
    "light_condition": "Тенелюбивые",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "type": "Комнатное растение"
  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d18"),
    "species": "Бамбуковая пальма",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c81"),
        "description_addition": "Поливайте осторожно, чтобы не замачивать листья.",
        "created_at": ISODate("2024-11-01T09:40:00Z")
      }
    ],
    "created_at": ISODate("2024-11-01T09:40:00Z"),
    "updated_at": ISODate("2024-11-01T09:40:00Z"),
    "image": "https://avatars.mds.yandex.net/i?id=4a2c5e1bb0e5b6d6b425874ccd928902_l-9065769-images-thumbs&n=13",
    "light_condition": "Светолюбивые",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "type": "Пальма"
  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d19"),
    "species": "Плющ",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
        "description_addition": "Поливайте мягкой водой, избегая застоя.",
        "created_at": ISODate("2024-12-01T10:30:00Z")
      }
    ],
    "created_at": ISODate("2024-12-01T10:30:00Z"),
    "updated_at": ISODate("2024-12-01T10:30:00Z"),
    "image": "https://avatars.mds.yandex.net/i?id=8c2f8a972981d9594dbcbee96c16cace_l-6489726-images-thumbs&n=13",
    "light_condition": "Полутеневые",
    "temperature_regime": "Средний режим (15-22°C)",
    "type": "Комнатное растение"
  },
  {
    "_id": ObjectId("5f3e8c1d1a9e3f1b1b2c3d20"),
    "species": "Цикламен",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c82"),
        "description_addition": "Поливайте после полного высыхания верхнего слоя почвы.",
        "created_at": ISODate("2024-12-11T09:27:26Z")
      }
    ],
    "created_at": ISODate("2024-12-11T09:27:26Z"),
    "updated_at": ISODate("2024-12-11T09:27:26Z"),
    "image": "https://krrot.net/wp-content/uploads/2018/04/image001-3.jpg",
    "light_condition": "Тенелюбивые",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "type": "Растение"
  },
  {
    "_id": ObjectId("6759c64e9d01a30bd118cda1"),
    "species": "Тюльпан",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7c"),
        "description_addition": "Поливайте после полного высыхания верхнего слоя почвы.",
        "created_at": ISODate("2024-12-11T09:27:26Z")
      }
    ],
    "created_at": ISODate("2024-12-11T09:27:26Z"),
    "updated_at": ISODate("2024-12-11T09:27:26Z"),
    "image": "http://view-photo.ru/wp-content/uploads/2016/11/tulpani0004.jpg",
    "light_condition": "Тенелюбивые",
    "temperature_regime": "Средний режим (15-22°C)",
    "type": "Растение"
  },
  {
    "_id": ObjectId("6759c64e9d01a30bd118cda2"),
    "species": "Герань",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "description_addition": "Поливайте после полного высыхания верхнего слоя почвы.",
        "created_at": ISODate("2024-12-11T09:27:26Z")
      }
    ],
    "created_at": ISODate("2024-12-11T09:27:26Z"),
    "updated_at": ISODate("2024-12-11T09:27:26Z"),
    "image": "https://i.pinimg.com/originals/ed/0f/22/ed0f22dba6a755b08f4402dafad3020a.jpg",
    "light_condition": "Светолюбивые",
    "temperature_regime": "Теплолюбивые (более 22°C)",
    "type": "Растение"
  },
  {
    "_id": ObjectId("6759c64e9d01a30bd118cda3"),
    "species": "Лаванда",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
        "description_addition": "Поливайте после полного высыхания верхнего слоя почвы.",
        "created_at": "2024-12-11T09:27:26Z"
      }
    ],
    "created_at": ISODate("2024-12-11T09:27:26Z"),
    "updated_at": ISODate("2024-12-11T09:27:26Z"),
    "image": "https://mobileimages.lowes.com/productimages/099bd9ee-f195-45d6-8a7a-62f91b213314/64336031.jpg?size=pdhism",
    "light_condition": "Полутеневые",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "type": "Растение"
  },
  {
    "_id": ObjectId("6759c64e9d01a30bd118cda4"),
    "species": "Роза",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7b"),
        "description_addition": "Поливайте после полного высыхания верхнего слоя почвы.",
        "created_at": ISODate("2024-12-11T09:27:26Z")
      }
    ],
    "created_at": ISODate("2024-12-11T09:27:26Z"),
    "updated_at": ISODate("2024-12-11T09:27:26Z"),
    "image": "https://ogorod.moe-online.ru/media/3/8/2/d4f70aae3b05a44f968ab93436e25410/Oni0dfoG2ZS4PPa0svdn8WgU5jFTYWAGga7UKMl5-thumb_1680.jpg",
    "light_condition": "Светолюбивые",
    "temperature_regime": "Холодостойкие (до 15°C)",
    "type": "Растение"
  },
  {
    "_id": ObjectId("6759c64e9d01a30bd118cda5"),
    "species": "Сциндапсус золотистый",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7b"),
        "description_addition": "Растение предпочитает умеренный полив и рыхлый грунт.",
        "created_at": ISODate("2024-09-15T10:30:00Z")
      }
    ],
    "created_at": ISODate("2024-09-15T10:30:00Z"),
    "updated_at": ISODate("2024-09-15T10:30:00Z"),
    "image": "https://gardengrove.ru/upload/iblock/ae6/stsindapsus_zolotistyy_epipremnum_aureum_podvesnoy_4scauha08_1.jpg",
    "light_condition": "Полутеневые",
    "temperature_regime": "Средний режим (15-22°C)",
    "type": "Лиана"
  },
  {
    "_id": ObjectId("6759c64e9d01a30bd118cda6"),
    "species": "Хризантема",
    "description": [
      {
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c80"),
        "description_addition": "Для обильного цветения поливайте регулярно.",
        "created_at": ISODate("2024-10-01T14:00:00Z")
      }
    ],
    "created_at": ISODate("2024-10-01T14:00:00Z"),
    "updated_at": ISODate("2024-10-01T14:00:00Z"),
    "image": "https://самара-сад.рф/images/cms/data/81.jpg",
    "light_condition": "Светолюбивые",
    "temperature_regime": "Средний режим (15-22°C)",
    "type": "Цветущее"
  }
])

db.trades.insertMany([
  {
    "_id": ObjectId("672f5ee65d51777333752da1"),
    "offerer": {
      "name": "Алексей",
      "surname": "Иванов",
      "father_name": "Петрович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
      "plant": {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c4d"),
        "species": "Фикус",
        "image": "https://i.pinimg.com/originals/d8/44/39/d84439377efd15eeceb6d84c1d6f9c2f.jpg",
      }
    },
    "accepter": {
      "name": "Дмитрий",
      "surname": "Сидоров",
      "father_name": "Иванович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7c"),
      "plant": {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c50"),
        "species": "Сансевиерия",
        "image": "https://avatars.mds.yandex.net/i?id=68c1188c9f5b93381053c4a9f0ed9c86_l-5235022-images-thumbs&n=13",
      }
    },
    "created_at": ISODate("2024-10-10T10:00:00Z"),
    "updated_at": ISODate("2024-10-11T10:00:00Z"),
    "status": 1,
    "type": "trade",
  },
  {
    "_id": ObjectId("672f5ee65d51777333752da0"),
    "offerer": {
      "name": "Алексей",
      "surname": "Иванов",
      "father_name": "Петрович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
      "plant": {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c4e"),
        "species": "Алоэ",
        "image": "https://cache3.youla.io/files/images/780_780/5d/dc/5ddc14211bee2b907f2ff783.jpg",

      }
    },
    "accepter": {
      "name": "Сергей",
      "surname": "Кузнецов",
      "father_name": "Андреевич",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
      "plant": {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c56"),
        "species": "Плющ",
        "image": "https://mirzhvetov.ru/wp-content/uploads/1/8/a/18adf9a04593e2b41da5aa2064dfdac3.jpeg",

      }
    },
    "created_at": ISODate("2024-02-22T10:00:00Z"),
    "updated_at": ISODate("2024-02-28T10:00:00Z"),
    "status": 1,
    "type": "trade",
  },
  {
    "_id": ObjectId("672f5ee65d51777333752da6"),
    "offerer": {
      "name": "Михаил",
      "surname": "Васильев",
      "father_name": "Павлович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c80"),
      "plant": {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c52"),
        "species": "Каланхоэ",
        "image": "https://yandex-images.clstorage.net/9X9AVN383/ebf5cd36R/md48cSr7oQG1XR2i0SuisLQEDDiOAYN-dk-0VYuR20_bEA0edQnOdtqGLs_9AEyHjorayr19s3RwEjYyrEN2_PzLbXB30tgdtUlMjvgbyoD0UTxNglSLGmZS0GWSITaGEsGlrqzsG48u63ez-E1NspOPQ37t1C7Y_d42HsTm8wHZZnzhHvM4ib1xRAqdqwqs7LFcYLKcW3uiK60kntGKjtIhdZ4gRLOjNqPP38SdNCYbQ7u_2WCedLmK6hoMSg_9JVqE4ZIrwCGJgQhCZSsqqDyhkCR--JfTzstlODrtmqKmoWEuJATjj4pfd0e4lWCCY8-Hv_m01ux9lu76fP6PqT3GLO32i2TRqe1cxuEbtozwObhUUkA3U0ZfcSTqjVoW_lFlhvRoyw8uO0cnXG0MBrNrs8_1eCLwOe6CHuiuKznN5piFYmeIjb3pyD6ZZzp8lAGEKKIE5zu-x2WcAk3aQrKR9XZUdONLRpvrj0Q9BAZLk6dTBchqEE3-Tn44wm-90R40cRLnLCFRcVw2GTMGnLDV0CCqDJtDwrcNuPqVHiZCoZEG9Awf54qnJ7P0ZaTCc_P_U2FALgxlUrqeyNITBc3WhPkKA3CVvW0MIuH3AvCo1QhYRhyr967L-YQeYRpefhVBgrCsi_fK10OH7P18jns7Xz8NtF4QbW6CAmhG20WJlpR1TvtYaTWdYCKBfw4AhPm4HI4Yk0-Wu2EsWvEqwkphzXZsTNcLtocv6_Q5DIJThzufKSzeYKEOMoa4Ipsl1ZaY-Y5_MJkNUdTGCU_6OOT1vEyKxP-XIotNlL41ch5-1cUybORnA6pvG5PQufRSf3enV_WI7iTBZjKGkBaTtYGWGMl2-0RR1UHYBvn_xjikqYBoLlznjw7z_bA66WoSMtn18liUy_8CRzdXXMGcklP3rxP9oC5gLfpGojg2yz0RsqTJJv9Qgb1pAHohq0I0uNGk3D6MB9--172slnlY",

      }
    },
    "accepter": {
      "name": "Алексей",
      "surname": "Иванов",
      "father_name": "Петрович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
      "plant": {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c4f"),
        "species": "Финиковая палма",
        "image": "https://avatars.mds.yandex.net/i?id=5e9be1d6a4f0d162a67a029eb69b1286_l-5495958-images-thumbs&n=13",
      }
    },
    "created_at": ISODate("2024-08-11T10:00:00Z"),
    "updated_at": ISODate("2024-08-28T10:00:00Z"),
    "status": 1,
    "type": "trade",
  },
  {
    "_id": ObjectId("672f5ee65d51777333752da2"),
    "accepter": {
      "name": "Морозов",
      "surname": "Олег",
      "father_name": "Геннадьевич",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
      "plant": {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c24"),
        "species": "Алоэ",
        "image": "https://cdn.nur.kz/images/1120/92f8eac8e0745022.jpeg",

      }
    },
    "offerer": {
      "name": "Алексей",
      "surname": "Иванов",
      "father_name": "Петрович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
      "plant": {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c20"),
        "species": "Калатея",
        "image": "https://mandarin-shop.ru/images/cms/data/cvetushie/kalteya/syurpraiz/2056026.jpg",
      }
    },
    "created_at": ISODate("2024-08-11T10:00:00Z"),
    "updated_at": ISODate("2024-08-28T10:00:00Z"),
    "status": 2,
    "type": "trade",
  },
  {
    "_id": ObjectId("672f5ee65d51777333752da3"),
    "offerer": {
      "name": "Кузнецов",
      "surname": "Сергей",
      "father_name": "Андреевич",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
      "plant": {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c13"),
        "species": "Аглаонема",
        "image": "https://i.pinimg.com/736x/ee/fb/b5/eefbb5048bb4c4e6c913b1bd44aa8c97.jpg",
      }
    },
    "accepter": {
      "name": "Алексей",
      "surname": "Иванов",
      "father_name": "Петрович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
      "plant": {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c19"),
        "species": "Сансевиерия",
        "image": "https://i.pinimg.com/736x/a1/10/79/a11079d1fce09e7cb945dfebc396574f.jpg",
      }
    },
    "created_at": ISODate("2024-08-11T10:00:00Z"),
    "updated_at": ISODate("2024-08-28T10:00:00Z"),
    "status": 3,
    "type": "trade",
  },
  {
    "_id": ObjectId("672f5ee65d51777333752da4"),
    "offerer": {
      "name": "Сидоров",
      "surname": "Дмитрий",
      "father_name": "Иванович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7c"),
      "plant": {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c51"),
        "species": "Нефролепис",
        "image": "https://images.unsplash.com/photo-1529516532344-1a34b1df1f19?crop=entropy&cs=tinysrgb&fit=max&fm=jpg&ixid=MnwzNjUyOXwwfDF8c2VhcmNofDZ8fHBsYW50fGVufDB8fHx8MTY5OTQxNjg5Nw&ixlib=rb-1.2.1&q=80&w=400",
      }
    },
    "accepter": {
      "name": "Алексей",
      "surname": "Иванов",
      "father_name": "Петрович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
      "plant": {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c18"),
        "species": "Суккулент",
        "image": "https://static.tildacdn.com/tild3233-3537-4133-b666-363965626333/IKzoftn2SBg.jpg",
      }
    },
    "created_at": ISODate("2024-08-11T10:00:00Z"),
    "updated_at": ISODate("2024-08-28T10:00:00Z"),
    "status": 2,
    "type": "trade",
  },
  {
    "_id": ObjectId("6759369c55bfccddab5a04c0"),
    "offerer": {
      "name": "Михаил",
      "surname": "Васильев",
      "father_name": "Павлович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c80"),
      "plant": {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c52"),
        "species": "Каланхоэ",
        "image": "https://yandex-images.clstorage.net/9X9AVN383/ebf5cd36R/md48cSr7oQG1XR2i0SuisLQEDDiOAYN-dk-0VYuR20_bEA0edQnOdtqGLs_9AEyHjorayr19s3RwEjYyrEN2_PzLbXB30tgdtUlMjvgbyoD0UTxNglSLGmZS0GWSITaGEsGlrqzsG48u63ez-E1NspOPQ37t1C7Y_d42HsTm8wHZZnzhHvM4ib1xRAqdqwqs7LFcYLKcW3uiK60kntGKjtIhdZ4gRLOjNqPP38SdNCYbQ7u_2WCedLmK6hoMSg_9JVqE4ZIrwCGJgQhCZSsqqDyhkCR--JfTzstlODrtmqKmoWEuJATjj4pfd0e4lWCCY8-Hv_m01ux9lu76fP6PqT3GLO32i2TRqe1cxuEbtozwObhUUkA3U0ZfcSTqjVoW_lFlhvRoyw8uO0cnXG0MBrNrs8_1eCLwOe6CHuiuKznN5piFYmeIjb3pyD6ZZzp8lAGEKKIE5zu-x2WcAk3aQrKR9XZUdONLRpvrj0Q9BAZLk6dTBchqEE3-Tn44wm-90R40cRLnLCFRcVw2GTMGnLDV0CCqDJtDwrcNuPqVHiZCoZEG9Awf54qnJ7P0ZaTCc_P_U2FALgxlUrqeyNITBc3WhPkKA3CVvW0MIuH3AvCo1QhYRhyr967L-YQeYRpefhVBgrCsi_fK10OH7P18jns7Xz8NtF4QbW6CAmhG20WJlpR1TvtYaTWdYCKBfw4AhPm4HI4Yk0-Wu2EsWvEqwkphzXZsTNcLtocv6_Q5DIJThzufKSzeYKEOMoa4Ipsl1ZaY-Y5_MJkNUdTGCU_6OOT1vEyKxP-XIotNlL41ch5-1cUybORnA6pvG5PQufRSf3enV_WI7iTBZjKGkBaTtYGWGMl2-0RR1UHYBvn_xjikqYBoLlznjw7z_bA66WoSMtn18liUy_8CRzdXXMGcklP3rxP9oC5gLfpGojg2yz0RsqTJJv9Qgb1pAHohq0I0uNGk3D6MB9--172slnlY"
      }
    },
    "accepter": {
      "name": "Алексей",
      "surname": "Иванов",
      "father_name": "Петрович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
      "plant": {}
    },
    "created_at": ISODate("2024-02-22T10:00:00Z"),
    "updated_at": ISODate("2024-02-22T10:00:00Z"),
    "status": 2,
    "type": "buy",
  },
  {
    "_id": ObjectId("6759369c55bfccddab5a04c1"),
    "offerer": {
      "name": "Кузнецов",
      "surname": "Сергей",
      "father_name": "Андреевич",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
      "plant": {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c11"),
        "species": "Монстера",
        "image": "https://i.etsystatic.com/26466238/r/il/177e61/3474589839/il_1588xN.3474589839_atwb.jpg"
      }
    },
    "accepter": {
      "name": "Алексей",
      "surname": "Иванов",
      "father_name": "Петрович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
      "plant": {}
    },
    "created_at": ISODate("2024-08-11T10:00:00Z"),
    "updated_at": ISODate("2024-08-11T10:00:00Z"),
    "status": 2,
    "type": "buy",
  },
  {
    "_id": ObjectId("6759369c55bfccddab5a04c2"),
    "offerer": {
      "name": "Морозов",
      "surname": "Олег",
      "father_name": "Геннадьевич",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
      "plant": {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c23"),
        "species": "Филодендрон",
        "image": "https://mirzhvetov.ru/wp-content/uploads/6/b/d/6bd7ba5d7943e92c6445a93ca617e78b.jpeg"
      }
    },
    "accepter": {
      "name": "Алексей",
      "surname": "Иванов",
      "father_name": "Петрович",
      "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
      "plant": {}
    },
    "created_at": ISODate("2024-06-07T10:00:00Z"),
    "updated_at": ISODate("2024-06-07T10:00:00Z"),
    "status": 2,
    "type": "buy",
  }
])

db.users.insertMany([
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
    "photo": "https://irinakhrustaleva.com/upload/medialibrary/8e4/8e4f38234003be08e5b867312de42d3e.jpg",
    "surname": "Иванов",
    "name": "Алексей",
    "father_name": "Петрович",
    "phone_number": "+79210001111",
    "email": "ivanov.alexey@example.com",
    "password": "password123",
    "created_at": ISODate("2023-12-15T09:30:00Z"),
    "updated_at": ISODate("2024-01-02T12:45:00Z"),
    "plants": [
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c4d"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://i.pinimg.com/originals/d8/44/39/d84439377efd15eeceb6d84c1d6f9c2f.jpg",
        "size": "Маленькие (до 20 см)",
        "price": 500,
        "light_condition": "Тенелюбивые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Холодостойкие (до 15°C)",
        "care_complexity": "Для начинающих",
        "description": "Растение для небольших тенистых пространств, легкое в уходе.",
        "type": "Комнатное растение",
        "species": "Фикус",
        "created_at": ISODate("2024-01-31T10:00:00Z"),
        "place": "Москва",
        "sold_at":ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c4e"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://cache3.youla.io/files/images/780_780/5d/dc/5ddc14211bee2b907f2ff783.jpg",
        "size": "Средние (от 20 до 50 см)",
        "price": 1500,
        "light_condition": "Полутеневые",
        "watering_frequency": "Частый полив (ежедневно)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Требуют среднего ухода",
        "description": "Универсальное растение для офиса и дома.",
        "type": "Суккулент",
        "species": "Алоэ",
        "created_at": ISODate("2024-01-02T11:00:00Z"),
        "place": "Санкт-Петербург",
        "sold_at":ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c4f"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://avatars.mds.yandex.net/i?id=5e9be1d6a4f0d162a67a029eb69b1286_l-5495958-images-thumbs&n=13",
        "size": "Большие (более 50 см)",
        "price": 3000,
        "light_condition": "Светолюбивые",
        "watering_frequency": "Редкий полив (раз в 2 недели)",
        "temperature_regime": "Теплолюбивые (более 22°C)",
        "care_complexity": "Для опытных цветоводов",
        "description": "Эффектное растение для больших помещений.",
        "type": "Пальма",
        "species": "Финиковая пальма",
        "created_at": ISODate("2024-09-29T12:00:00Z"),
        "place": "Казань",
        "sold_at": ISODate("2024-12-01T15:20:31Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c14"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://rastenievod.com/wp-content/uploads/2016/08/20.jpg",
        "size": "Большие (более 50 см)",
        "price": 2800,
        "light_condition": "Светолюбивые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Для начинающих",
        "description": "Создаёт уют в просторных гостиных.",
        "type": "Декоративное растение",
        "species": "Юкка",
        "created_at": ISODate("2024-09-25T11:25:00Z"),
        "place": "Омск",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c15"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://i.pinimg.com/736x/90/42/02/904202dbd44dbb7a68fd4d73fcbd3452.jpg",
        "size": "Средние (от 20 до 50 см)",
        "price": 1000,
        "light_condition": "Тенелюбивые",
        "watering_frequency": "Частый полив (ежедневно)",
        "temperature_regime": "Теплолюбивые (более 22°C)",
        "care_complexity": "Требует среднего ухода",
        "description": "Подходит для создания влажного микроклимата.",
        "type": "Комнатное растение",
        "species": "Спатифиллум",
        "created_at": ISODate("2024-09-26T09:00:00Z"),
        "place": "Саратов",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c16"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://domashniecvety.ru/wp-content/uploads/4/e/7/4e7e7a9272c03254d6dfa0d26eb34231.jpe",
        "size": "Маленькие (до 20 см)",
        "price": 900,
        "light_condition": "Полутеневые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Холодостойкие (до 15°C)",
        "care_complexity": "Для опытных цветоводов",
        "description": "Интересное растение для необычных интерьеров.",
        "type": "Экзотическое растение",
        "species": "Замиокулькас",
        "created_at": ISODate("2024-09-27T15:30:00Z"),
        "place": "Челябинск",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c17"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://selcdn.fedsp.com/eridanus/13/1160/500x500.3c161b73c57712b8.jpeg",
        "size": "Большие (более 50 см)",
        "price": 3500,
        "light_condition": "Светолюбивые",
        "watering_frequency": "Частый полив (ежедневно)",
        "temperature_regime": "Теплолюбивые (более 22°C)",
        "care_complexity": "Для опытных цветоводов",
        "description": "Тропическое украшение для больших помещений.",
        "type": "Цветущее растение",
        "species": "Антуриум",
        "created_at": ISODate("2024-09-28T18:50:00Z"),
        "place": "Пермь",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c18"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://static.tildacdn.com/tild3233-3537-4133-b666-363965626333/IKzoftn2SBg.jpg",
        "size": "Маленькие (до 20 см)",
        "price": 750,
        "light_condition": "Полутеневые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Для начинающих",
        "description": "Идеально для рабочего стола или подоконника.",
        "type": "Комнатное растение",
        "species": "Суккулент",
        "created_at": ISODate("2024-09-29T14:20:00Z"),
        "place": "Казань",
        "sold_at": ISODate("0001-09-29T20:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c19"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://i.pinimg.com/736x/a1/10/79/a11079d1fce09e7cb945dfebc396574f.jpg",
        "size": "Большие (более 50 см)",
        "price": 2700,
        "light_condition": "Тенелюбивые",
        "watering_frequency": "Редкий полив (раз в 2 недели)",
        "temperature_regime": "Холодостойкие (до 15°C)",
        "care_complexity": "Требует среднего ухода",
        "description": "Прекрасный выбор для просторных комнат с низким освещением.",
        "type": "Декоративно-лиственное растение",
        "species": "Сансевиерия",
        "created_at": ISODate("2024-09-30T11:15:00Z"),
        "place": "Самара",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c20"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7a"),
        "image": "https://mandarin-shop.ru/images/cms/data/cvetushie/kalteya/syurpraiz/2056026.jpg",
        "size": "Средние (от 20 до 50 см)",
        "price": 1500,
        "light_condition": "Светолюбивые",
        "watering_frequency": "Частый полив (ежедневно)",
        "temperature_regime": "Теплолюбивые (более 22°C)",
        "care_complexity": "Для опытных цветоводов",
        "description": "Экзотический вид и красивое цветение.",
        "type": "Цветущее растение",
        "species": "Калатея",
        "created_at": ISODate("2024-10-01T09:45:00Z"),
        "place": "Новосибирск",
        "sold_at": ISODate("2024-11-12T15:00:00Z")
      },
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c52"),
        "image": "https://yandex-images.clstorage.net/9X9AVN383/ebf5cd36R/md48cSr7oQG1XR2i0SuisLQEDDiOAYN-dk-0VYuR20_bEA0edQnOdtqGLs_9AEyHjorayr19s3RwEjYyrEN2_PzLbXB30tgdtUlMjvgbyoD0UTxNglSLGmZS0GWSITaGEsGlrqzsG48u63ez-E1NspOPQ37t1C7Y_d42HsTm8wHZZnzhHvM4ib1xRAqdqwqs7LFcYLKcW3uiK60kntGKjtIhdZ4gRLOjNqPP38SdNCYbQ7u_2WCedLmK6hoMSg_9JVqE4ZIrwCGJgQhCZSsqqDyhkCR--JfTzstlODrtmqKmoWEuJATjj4pfd0e4lWCCY8-Hv_m01ux9lu76fP6PqT3GLO32i2TRqe1cxuEbtozwObhUUkA3U0ZfcSTqjVoW_lFlhvRoyw8uO0cnXG0MBrNrs8_1eCLwOe6CHuiuKznN5piFYmeIjb3pyD6ZZzp8lAGEKKIE5zu-x2WcAk3aQrKR9XZUdONLRpvrj0Q9BAZLk6dTBchqEE3-Tn44wm-90R40cRLnLCFRcVw2GTMGnLDV0CCqDJtDwrcNuPqVHiZCoZEG9Awf54qnJ7P0ZaTCc_P_U2FALgxlUrqeyNITBc3WhPkKA3CVvW0MIuH3AvCo1QhYRhyr967L-YQeYRpefhVBgrCsi_fK10OH7P18jns7Xz8NtF4QbW6CAmhG20WJlpR1TvtYaTWdYCKBfw4AhPm4HI4Yk0-Wu2EsWvEqwkphzXZsTNcLtocv6_Q5DIJThzufKSzeYKEOMoa4Ipsl1ZaY-Y5_MJkNUdTGCU_6OOT1vEyKxP-XIotNlL41ch5-1cUybORnA6pvG5PQufRSf3enV_WI7iTBZjKGkBaTtYGWGMl2-0RR1UHYBvn_xjikqYBoLlznjw7z_bA66WoSMtn18liUy_8CRzdXXMGcklP3rxP9oC5gLfpGojg2yz0RsqTJJv9Qgb1pAHohq0I0uNGk3D6MB9--172slnlY",
        "size": "Большие (более 50 см)",
        "price": 2700,
        "light_condition": "Светолюбивые",
        "watering_frequency": "Редкий полив (раз в 2 недели)",
        "temperature_regime": "Теплолюбивые (более 22°C)",
        "care_complexity": "Для опытных цветоводов",
        "description": "Красивое растение для светлых помещений.",
        "type": "Пальма",
        "species": "Кокосовая пальма",
        "created_at": ISODate("2024-08-27T15:00:00Z"),
        "place": "Нижний Новгород",
        "sold_at": ISODate("2024-02-22T10:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c11"),
        "image": "https://i.etsystatic.com/26466238/r/il/177e61/3474589839/il_1588xN.3474589839_atwb.jpg",
        "size": "Большие (более 50 см)",
        "price": 3200,
        "light_condition": "Светолюбивые",
        "watering_frequency": "Частый полив (ежедневно)",
        "temperature_regime": "Теплолюбивые (более 22°C)",
        "care_complexity": "Для опытных цветоводов",
        "description": "Создаёт ощущение тропического уюта.",
        "type": "Экзотическое растение",
        "species": "Монстера",
        "created_at": ISODate("2024-09-22T10:30:00Z"),
        "place": "Краснодар",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c23"),
        "image": "https://mirzhvetov.ru/wp-content/uploads/6/b/d/6bd7ba5d7943e92c6445a93ca617e78b.jpeg",
        "size": "Средние (от 20 до 50 см)",
        "price": 1400,
        "light_condition": "Полутеневые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Холодостойкие (до 15°C)",
        "care_complexity": "Требует среднего ухода",
        "description": "Необычные листья и долговечность.",
        "type": "Комнатное растение",
        "species": "Филодендрон",
        "created_at": ISODate("2024-10-04T12:50:00Z"),
        "place": "Уфа",
        "sold_at": ISODate("2024-06-07T10:00:00Z")
      }
    ],
    "trades": [
      ObjectId("672f5ee65d51777333752da1"),
      ObjectId("672f5ee65d51777333752da0"),
      ObjectId("672f5ee65d51777333752da6"),
      ObjectId("672f5ee65d51777333752da2"),
      ObjectId("672f5ee65d51777333752da3"),
      ObjectId("672f5ee65d51777333752da4"),
      ObjectId("6759369c55bfccddab5a04c0"),
      ObjectId("6759369c55bfccddab5a04c1"),
      ObjectId("6759369c55bfccddab5a04c2")
    ],
    "role": 1
  },
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7b"),
    "photo": "https://ruskino.ru/media/photo/15619/381c2BUxDPtyGTCuNluxp8yzZ35.jpg",
    "surname": "Петров",
    "name": "Виктор",
    "father_name": "Алексеевич",
    "phone_number": "+79210002222",
    "email": "petrov.viktor@example.com",
    "password": "securePass321",
    "created_at": ISODate("2024-01-10T10:15:00Z"),
    "updated_at": ISODate("2024-01-15T11:20:00Z"),
    "role": 1
  },
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7c"),
    "photo": "https://photo.7ya.ru/ph/2013/8/9/1376061617350.jpg",
    "surname": "Сидоров",
    "name": "Дмитрий",
    "father_name": "Иванович",
    "phone_number": "+79210003333",
    "email": "sidorov.dmitry@example.com",
    "password": "pass1234",
    "created_at": ISODate("2024-02-01T08:00:00Z"),
    "updated_at": ISODate("2024-02-10T15:30:00Z"),
    "plants": [
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c50"),
        "image": "https://avatars.mds.yandex.net/i?id=68c1188c9f5b93381053c4a9f0ed9c86_l-5235022-images-thumbs&n=13",
        "size": "Маленькие (до 20 см)",
        "price": 800,
        "light_condition": "Полутеневые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Для начинающих",
        "description": "Неприхотливое растение, подходит для небольших помещений.",
        "type": "Комнатное растение",
        "species": "Сансевиерия",
        "created_at": ISODate("2024-10-04T13:00:00Z"),
        "place": "Новосибирск",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c51"),
        "image": "https://images.unsplash.com/photo-1529516532344-1a34b1df1f19?crop=entropy&cs=tinysrgb&fit=max&fm=jpg&ixid=MnwzNjUyOXwwfDF8c2VhcmNofDZ8fHBsYW50fGVufDB8fHx8MTY5OTQxNjg5Nw&ixlib=rb-1.2.1&q=80&w=400",
        "size": "Средние (от 20 до 50 см)",
        "price": 1200,
        "light_condition": "Тенелюбивые",
        "watering_frequency": "Частый полив (ежедневно)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Требуют среднего ухода",
        "description": "Растение для офиса и дома, легкое в уходе.",
        "type": "Папоротник",
        "species": "Нефролепис",
        "created_at": ISODate("2024-02-11T14:00:00Z"),
        "place": "Екатеринбург",
        "sold_at": ISODate("0001-09-29T20:00:00Z")
      }
    ],
    "trades": [
      ObjectId("672f5ee65d51777333752da1"),
      ObjectId("672f5ee65d51777333752da4")
    ],
    "role": 2
  },
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7d"),
    "photo": "https://games-of-thrones.ru/sites/default/files/pictures/all/gosling/18.jpg",
    "surname": "Алексеев",
    "name": "Николай",
    "father_name": "Фёдорович",
    "phone_number": "+79210004444",
    "email": "alekseev.nikolay@example.com",
    "password": "pass5678",
    "created_at": ISODate("2024-03-05T14:00:00Z"),
    "updated_at": ISODate("2024-03-15T16:45:00Z"),
    "role": 2
  },
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
    "photo": "https://static.alltime.ru/obj/article/image-blog/Brutalnyy_stil_dlya_muzhchin/Brutalnyy_stil_dlya_muzhchin_1.jpg",
    "surname": "Кузнецов",
    "name": "Сергей",
    "father_name": "Андреевич",
    "phone_number": "+79210005555",
    "email": "kuznetsov.sergey@example.com",
    "password": "MyStrongPass!",
    "created_at": ISODate("2024-04-01T07:45:00Z"),
    "updated_at": ISODate("2024-04-10T13:50:00Z"),
    "plants": [
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c56"),
        "image": "https://mirzhvetov.ru/wp-content/uploads/1/8/a/18adf9a04593e2b41da5aa2064dfdac3.jpeg",
        "size": "Средние (от 20 до 50 см)",
        "price": 1300,
        "light_condition": "Полутеневые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Требуют среднего ухода",
        "description": "Подходит для создания уюта и комфорта в интерьере.",
        "type": "Комнатное растение",
        "species": "Плющ",
        "created_at": ISODate("2024-09-11T19:00:00Z"),
        "place": "Ростов-на-Дону",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c12"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
        "image": "https://www.bhg.com/thmb/oDnjlrHprd67aYvinrMfQgVUPtQ=/5332x0/filters:no_upscale():strip_icc()/BHG-spider-plant-c0e0fdd5ec6e4c1588998ce3167f6579.jpg",
        "size": "Маленькие (до 20 см)",
        "price": 600,
        "light_condition": "Тенелюбивые",
        "watering_frequency": "Редкий полив (раз в 2 недели)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Для начинающих",
        "description": "Идеально для небольших офисов.",
        "type": "Комнатное растение",
        "species": "Хлорофитум",
        "created_at": ISODate("2024-09-23T14:10:00Z"),
        "place": "Томск",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c13"),
        "user_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7e"),
        "image": "https://i.pinimg.com/736x/ee/fb/b5/eefbb5048bb4c4e6c913b1bd44aa8c97.jpg",
        "size": "Средние (от 20 до 50 см)",
        "price": 1800,
        "light_condition": "Полутеневые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Холодостойкие (до 15°C)",
        "care_complexity": "Требует среднего ухода",
        "description": "Выдерживает прохладные температуры и редкий уход.",
        "type": "Декоративно-лиственное растение",
        "species": "Аглаонема",
        "created_at": ISODate("2024-09-24T17:40:00Z"),
        "place": "Хабаровск",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      }
    ],
    "trades": [
      ObjectId("672f5ee65d51777333752da0"),
      ObjectId("672f5ee65d51777333752da3"),
      ObjectId("6759369c55bfccddab5a04c1")
    ],
    "role": 2
  },
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c7f"),
    "photo": "https://iv1.lisimg.com/image/11627519/740full-eldar-lebedev.jpg",
    "surname": "Новиков",
    "name": "Андрей",
    "father_name": "Викторович",
    "phone_number": "+79210006666",
    "email": "novikov.andrey@example.com",
    "password": "andrey2024",
    "created_at": ISODate("2024-05-15T09:10:00Z"),
    "updated_at": ISODate("2024-05-20T10:30:00Z"),
    "role": 2
  },
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c80"),
    "photo": "https://i.pinimg.com/originals/e3/7e/0e/e37e0e25686c2139b281a57a5b4906f2.jpg",
    "surname": "Васильев",
    "name": "Михаил",
    "father_name": "Павлович",
    "phone_number": "+79210007777",
    "email": "vasilyev.mikhail@example.com",
    "password": "securePass2024",
    "created_at": ISODate("2024-06-01T11:15:00Z"),
    "updated_at": ISODate("2024-06-10T15:25:00Z"),
    "plants": [
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c53"),
        "image": "https://images.unsplash.com/photo-1517683059670-9cb6f6b43a59?crop=entropy&cs=tinysrgb&fit=max&fm=jpg&ixid=MnwzNjUyOXwwfDF8c2VhcmNofDh8fHBsYW50fGVufDB8fHx8MTY5OTQxNjg5Nw&ixlib=rb-1.2.1&q=80&w=400",
        "size": "Маленькие (до 20 см)",
        "price": 600,
        "light_condition": "Полутеневые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Для начинающих",
        "description": "Легкое в уходе растение для небольших помещений.",
        "type": "Суккулент",
        "species": "Каланхоэ",
        "created_at": ISODate("2024-07-07T16:00:00Z"),
        "place": "Воронеж",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      }
    ],
    "trades": [
      ObjectId("672f5ee65d51777333752da6"),
      ObjectId("6759369c55bfccddab5a04c0")
    ],
    "role": 2
  },
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c81"),
    "photo": "https://example.com/photo8.jpg",
    "surname": "Макаров",
    "name": "Юрий",
    "father_name": "Сергеевич",
    "phone_number": "+79210008888",
    "email": "makarov.yuriy@example.com",
    "password": "uniquePass098",
    "created_at": ISODate("2024-07-10T08:20:00Z"),
    "updated_at": ISODate("2024-07-15T12:35:00Z"),
    "role": 2
  },
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c82"),
    "photo": "https://coolsen.ru/wp-content/uploads/2021/10/078-20211027_232810.jpg",
    "surname": "Захаров",
    "name": "Игорь",
    "father_name": "Александрович",
    "phone_number": "+79210009999",
    "email": "zakharov.igor@example.com",
    "password": "mypassword_2024",
    "created_at": ISODate("2024-08-15T14:40:00Z"),
    "updated_at": ISODate("2024-08-25T16:55:00Z"),
    "role": 2
  },
  {
    "_id": ObjectId("5f2d8c1d1d8e2f1a1a2b3c83"),
    "photo": "https://images.mubicdn.net/images/cast_member/55232/cache-358535-1532856063/image-w856.jpg",
    "surname": "Морозов",
    "name": "Олег",
    "father_name": "Геннадьевич",
    "phone_number": "+79210001010",
    "email": "morozov.oleg@example.com",
    "password": "oleg_secure123",
    "created_at": ISODate("2024-09-05T18:05:00Z"),
    "updated_at": ISODate("2024-09-15T20:30:00Z"),
    "plants": [
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c54"),
        "image": "https://images.unsplash.com/photo-1526744226395-7d63a3c6a5bb?crop=entropy&cs=tinysrgb&fit=max&fm=jpg&ixid=MnwzNjUyOXwwfDF8c2VhcmNofDl8fHBsYW50fGVufDB8fHx8MTY5OTQxNjg5Nw&ixlib=rb-1.2.1&q=80&w=400",
        "size": "Средние (от 20 до 50 см)",
        "price": 1400,
        "light_condition": "Тенелюбивые",
        "watering_frequency": "Частый полив (ежедневно)",
        "temperature_regime": "Холодостойкие (до 15°C)",
        "care_complexity": "Требуют среднего ухода",
        "description": "Эффектное растение, отлично очищает воздух.",
        "type": "Комнатное растение",
        "species": "Диффенбахия",
        "created_at": ISODate("2024-03-30T17:00:00Z"),
        "place": "Самара",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f1d7c1d1d8e2f1a1a2b3c55"),
        "image": "https://images.unsplash.com/photo-1511546395754-38b13532eabc?crop=entropy&cs=tinysrgb&fit=max&fm=jpg&ixid=MnwzNjUyOXwwfDF8c2VhcmNofDEwfHxwbGFudHxlbnwwfHx8fDE2OTk0MTY4OTc&ixlib=rb-1.2.1&q=80&w=400",
        "size": "Большие (более 50 см)",
        "price": 3200,
        "light_condition": "Светолюбивые",
        "watering_frequency": "Редкий полив (раз в 2 недели)",
        "temperature_regime": "Теплолюбивые (более 22°C)",
        "care_complexity": "Для опытных цветоводов",
        "description": "Эффектное растение, требует яркого освещения.",
        "type": "Пальма",
        "species": "Бамбуковая пальма",
        "created_at": ISODate("2024-03-22T18:00:00Z"),
        "place": "Челябинск",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c21"),
        "image": "https://i.pinimg.com/736x/a0/06/68/a00668fb094139a32f6b73581b62709f.jpg",
        "size": "Маленькие (до 20 см)",
        "price": 550,
        "light_condition": "Тенелюбивые",
        "watering_frequency": "Редкий полив (раз в 2 недели)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Для начинающих",
        "description": "Миниатюрный размер, легко ухаживать.",
        "type": "Декоративное растение",
        "species": "Пеперомия",
        "created_at": ISODate("2024-10-02T08:30:00Z"),
        "place": "Тюмень",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c22"),
        "image": "https://vsegda-pomnim.com/uploads/posts/2024-01/1705312976_vsegda-pomnim-com-p-fikus-bendzhamina-s-krupnimi-listyami-foto-13.jpg",
        "size": "Большие (более 50 см)",
        "price": 4200,
        "light_condition": "Светолюбивые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Для опытных цветоводов",
        "description": "Эффектное украшение зимнего сада.",
        "type": "Декоративное растение",
        "species": "Фикус Бенджамина",
        "created_at": ISODate("2024-10-03T16:20:00Z"),
        "place": "Екатеринбург",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c24"),
        "image": "https://cdn.nur.kz/images/1120/92f8eac8e0745022.jpeg",
        "size": "Маленькие (до 20 см)",
        "price": 450,
        "light_condition": "Светолюбивые",
        "watering_frequency": "Редкий полив (раз в 2 недели)",
        "temperature_regime": "Теплолюбивые (более 22°C)",
        "care_complexity": "Для начинающих",
        "description": "Простое растение для солнечных мест.",
        "type": "Суккулент",
        "species": "Алоэ",
        "created_at": ISODate("2024-10-05T15:10:00Z"),
        "place": "Иркутск",
        "sold_at": ISODate("2024-11-12T15:00:00Z")
      },
      {
        "_id": ObjectId("5f2d7c1d1d8e2f1a1a2b3c25"),
        "image": "https://avatars.dzeninfra.ru/get-zen_doc/1912454/pub_5da7367f433ecc00b3dabd12_5da73b24aad43600b1f1f430/scale_1200",
        "size": "Большие (более 50 см)",
        "price": 3000,
        "light_condition": "Полутеневые",
        "watering_frequency": "Средний полив (1-2 раза в неделю)",
        "temperature_regime": "Средний режим (15-22°C)",
        "care_complexity": "Требует среднего ухода",
        "description": "Великолепное растение для офиса.",
        "type": "Декоративное растение",
        "species": "Драцена",
        "created_at": ISODate("2024-10-06T11:30:00Z"),
        "place": "Калининград",
        "sold_at": ISODate("0001-01-01T00:00:00Z")
      }
    ],
    "trades": [
      ObjectId("672f5ee65d51777333752da2")
    ],
    "role": 2
  }
])