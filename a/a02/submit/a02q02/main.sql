create database cms;

drop table course;
drop table person;

create table semester(
  id int,
  season varchar(100),
  year    int, 
  smonth  int,
  sday    int,
  emonth  int,
  eday    int
);

create table course(
  id int,
  course_id varchar(100),
  course_name varchar(100),
  primary key (id) 
); engine=innodb;

create table section(
  id int,
  section_name varchar(100),
  primary key(id) references course(id)
); engine=innodb;

create table person(
  id int,
  fname varchar(100),
  lname varchar(100)
  primary key (id)
); engine=innodb;

create table email(
  id int,
  person_id int,
  username varchar(100),
  passkey  varchar(100)
  primary key (id) references person(id)
); engine=innodb;

create table instructor(
  id int
  person_id int
  primary key (id) references person(id)
); engine=innodb;

create table student(
  id int,
  person_id int
  primary key (id) references person(id)
); engine=innodb;

create table teaching_info(
  id int,
  semester_id int,
  instructor_id int,
  course_id int,
  section_id int
  primary key (id) references semester(id), instructor(id), course(id), section(id)
); engine=innodb;

------------------------------------------------------------------------------------

insert into person values 
  (0, "Yihsiang", "Liow"), 
  (1, "John", "Doe");

insert into email values 
  (0, 0, "yliow", "password"), 
  (1, 1, "jdoe", "secret");

insert into instructor values (0, 0), (1, 1);

insert into semester values 
  (0, "Spring", 2017, 1, 15, 5, 15), 
  (1, "Fall", 2017, 8, 15, 12, 15),
  (2, "Sprint", 2018, 1, 15, 5, 15);

insert into course values
  (0, "Ciss145", "Python Programming"),
  (1, "Ciss240", "Introduction to Programming"),
  (2, "Ciss245", "Advanced Programming"),
  (3, "Ciss350", "Data Structures and Advanced Algorithms"),
  (4, "Ciss430", "Database Systems"),
  (5, "Math225", "Discrete Mathematics I"),
  (6, "Math325", "Discrete Mathematics II");

insert into section values
  (0, "A"),
  (1, "B"),
  (2, "C");

insert into teaching_info values
  (0,  0, 0, 1, 0),
  (1,  0, 0, 3, 0),
  (2,  0, 0, 4, 0),
  (3,  0, 1, 0, 1),
  (4,  0, 1, 1, 1),
  (5,  1, 0, 2, 2),
  (6,  1, 0, 3, 2),
  (7,  1, 0, 6, 2),
  (8,  1, 1, 1, 0),
  (9,  1, 1, 3, 0),
  (10, 1, 1, 5, 0), 
  (11, 2, 0, 2, 0),
  (12, 2, 0, 3, 0),
  (13, 2, 0, 4, 0) 