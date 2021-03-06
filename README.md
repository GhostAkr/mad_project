----------------------
Игра в жанре RPG Arena
----------------------


Общая концепция
======================

Имеется клеточное игровое поле, на котором одновременно находятся игрок и npc.
Игрок может ходить по полю и использовать элементы боевой системы для нанесения урона противнику или получения определенных эффектов.
Противник обладает теми же возможностями.
RPG является пошаговой.
Цель проста: победить npc.


Перемещение
======================
За один ход как игрок, так и npc могут сходить не более чем заранее заданное количество раз.
Каждый ход осуществляется в одном из четырех напрвлений.

[Optional] При добавлении системы сложности можно варьировать данное значение в зависимости от выбранной сложности.


Боевая система
======================
Боевая система представляет собой взаимодействие между игроком и npc путем последовательной активации заранее выбранных способностей.
У любого существа в игре (в том числе и у игрока) имеется общая "колода" способностей.
Способность представляет собой какое-либо действие (например, нанесение урона или получение баффов)
В начале раунда каждому существу случайным образом выдаётся 5 способностей из его колоды для дальнейшего использования.
За каждый ход, помимо описанного выше передвижения, игрок или npc могут выбрать 3 любые способности из имеющихся пяти.
После того, как игрок и npc выбрали способности, происходит битва.
Выбранные способности активируются поочередно (сначала первая у игрока, потом первая у npc, затем вторая у игрока и т.д.).
Когда ход разыгран, игрок и npc из своей колоды случайным образом получают новые способности взамен потраченных.
Раунд продолжается, если игрок или npc остались живы.

[Optional] Боевая система может быть улучшена усложнением взамодействия между способностями.


Внутриигровой магазин
======================
При успешном завершении боя игрок получает монеты, за которые он может улучшить свою колоду во внутриигровом магазине, купив новые способности.

[Optional] На карту добавляется лут в виде монет или случайных способностей

Ссылка на план разработки: https://docs.google.com/document/d/1lFT1iZUg7gPzv1sCSVVgDIq4X3kKmcZeCpvQ6Hj4Dh4/edit?usp=sharing
