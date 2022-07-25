# Order management
Project created for small company specialized in thread rolling. Every order is by worker scanned on terminal with java applicaiton.Orders have 
their drawing number and their batch number, than worker selects if he's manufacturing item or controlling it. Also worker can select from different states:
in progress, stopped (if problem occurres), paused (for example he has a break) and done. 

![Screenshot from 2022-07-25 21-22-09](https://user-images.githubusercontent.com/26491801/180859337-43597824-9be7-4c02-a87a-0c0bf8febd90.png)
|:--:|
|Enter screen with Quick selection where worker can with enter change state from in progress to paused and opposite|

![Screenshot from 2022-07-25 21-22-24](https://user-images.githubusercontent.com/26491801/180859347-16aaaa54-9f7f-4514-9845-3edb269f1cf1.png)
|:--:|
|After login user can see overview of orders and controls added by him, and can change their states except of items with state as done, also can choose to add new order or control with scan button. Around applicaiton can be moved only using arrows backspace for going back in scan dialog, ctrl + o to logout|

![Screenshot from 2022-07-25 21-23-05](https://user-images.githubusercontent.com/26491801/180859354-df02747e-60a1-42f3-8f92-dc7e8da94cf1.png)
|:--:|
|Changing state of and item, worker can select state with 1 to 4 number keys and closes the dialog with ctrl + c|

Application on desktop computer within the same network is than for displaying list of orders and their history of states, with their controls. 

![Screenshot from 2022-07-25 21-24-18](https://user-images.githubusercontent.com/26491801/180859376-0db372c1-10f0-4ccb-88e3-4408ca6a022b.png)
![Screenshot from 2022-07-25 21-24-28](https://user-images.githubusercontent.com/26491801/180859390-79a39bea-938f-447e-947a-57915194e248.png)

Project is now unused due to a lot of different reasons, and so it's not really good tested in practice. 

# Set up of the project
To use the application you will need to create own SQL database and put login creditals to database_obj.h in App folder and Database_obj.java in Java folder.
Also you will need to specify url for database in databaseh.cpp and Database.java

You can use DBschema.sql to import the database
