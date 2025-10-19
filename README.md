Вот фото моего интерфейса

Светлая тема авторизация:
<img width="2560" height="1397" alt="image" src="https://github.com/user-attachments/assets/ad275794-a941-4a19-9a70-30c166656801" />
Темная тема авторизация:
<img width="2560" height="1399" alt="image" src="https://github.com/user-attachments/assets/ca7e2c65-367e-410a-b25d-e959fb3db524" />
Светлая тема вход:
<img width="2560" height="1399" alt="image" src="https://github.com/user-attachments/assets/54f86bf6-b4b8-45ac-b69f-58137d8aaf65" />
Темная тема вход:
<img width="2560" height="1398" alt="image" src="https://github.com/user-attachments/assets/b1852a4d-418d-42f0-b8a2-76a92abdffe6" />
При запуске сразу проверяется UUID машины и сверяется со значением в БД если нету то закрытие.
Далее когда ввел данные запрос отправляется в БД там заносятся данные если это авторизация или проверяются если это вход, также с запросом отправляется UUID машины для проверки и также сверяется.
Метод по которому пользователь идентифицируется это его UUID пк который лежит в БД захешированный используется как авторизация сессиями.
