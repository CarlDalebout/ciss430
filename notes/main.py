import pymysql

username = input("MySQL Username: ")
password = input("MySQL Password: ")
database = input("MySQL DataBase: ")

conn = pymysql.connect(user=username, passwd=password, db=database)
cursor = conn.cursor()



# create table Person (
# id INT,
# fname VARCHAR(100),
# lname VARCHAR(100),
# fingers INT,
# primary key (id)
# ) engine=innodb;

# create table Email (
# id INT,
# email VARCHAR(100),
# Person_id INT,
# foreign key (Person_id) references Person(id)
# ) engine=innodb;

# insert Person set id=42, fname="John", lname="Doe", fingers=10;
# insert Person set id=43, fname="Tom", lname="smith", fingers=9;

# insert Email set id=001, email="JohnDow@gmail.com", Person_id = 42;
# insert Email set id=002, email="JohnDow@yahoo.com", Person_id = 42;
# insert Email set id=003, email="JohnDow@hotmail.com", Person_id = 42;
# insert Email set id=004, email="TomSmith@hotmail.com", Person_id = 43;

# select * from Person;
# select * from Email;

# select fname, lname, email from Person, Email
# where Person.id = Person_id;