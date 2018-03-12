# cppMicroService

This project is a C++ microservice with connection to the SQLite3 DB and frontend implementation for Windows.

The code is base on micro-serivce on C++ using the C++ REST SDK sample:
[ivanmejiarocha/micro-service](https://github.com/ivanmejiarocha/micro-service)
and windows visual studio 2017 project -version of the sample:
[kadirmalak/micro-service-vs-2017](https://github.com/kadirmalak/micro-service-vs-2017)


 In order to run the .exe (inside IDE or outside) make sure to run it as Administrator.
 When using the frontend make sure that the ip variable in .js files are same as the ip and port microservice is listening. 


METHOD | ADDRESS | INFO
-------|---------|----
GET    | api/service/test |Test rest interface
GET    | api/songs/all |Gets all the data from DB
POST   | api/songs/add |Adds data to the DB
POST   | api/songs/update |Updates data in DB
POST   | api/songs/search |Search data in DB
DELETE | api/songs/delete |Delete data in DB


Example JSON:
```json
{
  "song_id" : 1,
  "song_name" : " You Suffer",
  "artist": "Napalm Death",
  "album" : "Scum",
  "length" : "0:01",
  "year" : "1986",
  "lyrics" : " You Suffer But Why?"
}
```
