Вот фото моего интерфейса

Светлая тема авторизация:
<img width="2560" height="1399" alt="image" src="https://github.com/user-attachments/assets/bad31da8-97fe-4fb6-8da6-0e6dfa29681b" />
Темная тема авторизация:
<img width="2559" height="1398" alt="image" src="https://github.com/user-attachments/assets/c2679ba4-5f59-49ef-a58b-ee8322a30c9b" />
Светлая тема вход:
<img width="2560" height="1398" alt="image" src="https://github.com/user-attachments/assets/30cf95c9-4dea-4139-97fb-3787e6318072" />
Темная тема вход:
<img width="2560" height="1400" alt="image" src="https://github.com/user-attachments/assets/ee56a187-17d3-4f9b-9125-767836f3e4a0" />

Далее когда ввел данные запрос отправляется в БД там заносятся данные если это авторизация или проверяются если это вход.
Метод по которому пользователь идентифицируется это ключ его UUID пк который лежит в БД захешированный.
При открытии приложения он сверяется и если нету в базе то сразу выход из приложения.
