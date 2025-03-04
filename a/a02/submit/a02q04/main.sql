create database cms;

drop table course;
drop table person;


CREATE TABLE semester (
  id INT PRIMARY KEY,
  season VARCHAR(100),
  year INT,
  smonth INT,
  sday INT,
  emonth INT,
  eday INT
) ENGINE=InnoDB;

CREATE TABLE course (
  id INT PRIMARY KEY,
  course_name VARCHAR(100),
  course_number INT,
  course_disc VARCHAR(100)
) ENGINE=InnoDB;

create table section(
  id INT PRIMARY Key,
  section_name varchar(100),
) ENGINE=InnoDB;

create table person(
  id INT PRIMARY Key,
  fname varchar(100),
  lname varchar(100)
) engine=innodb;

create table email(
  id INT PRIMARY Key,
  person_id int,
  username varchar(100),
  passkey  varchar(100)
  FOREIGN KEY (person_id) REFERENCES person(id)
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

create table building(
  id INT PRIMARY Key,
  name VARCHAR(100)
) engine=innodb;

create table room(
  id INT PRIMARY Key,
  building_id INT,
  room_number INT
) engine=innodb;

create table class(
  id INT PRIMARY Key
  teaching_info_id INT,
  room_id INT
  meet_days VARCHAR(100),
  stime INT,
  etime INT
) engine=innodb;

create table course_registration(
  id INT PRIMARY Key,
  student_id INT,
  class_id INT
) engine=innodb;

------------------------------------------------------------------------------------

insert into person values 
  (0, "Yihsiang", "Liow"), 
  (1, "John", "Doe"),
  (2, "Tom", "Smith");

insert into email values 
  (0, 0, "yliow", "password"), 
  (1, 1, "jdoe", "secret");

insert into instructor values 
  (0, 0), 
  (1, 1);

insert into student values
  (0, 2)

insert into semester values 
  (0, "Spring", 2017, 1, 15, 5, 15), 
  (1, "Fall", 2017, 8, 15, 12, 15),
  (2, "Sprint", 2018, 1, 15, 5, 15);

insert into course values
  (0, "Ciss", 145, "Python Programming"),
  (1, "Ciss", 240, "Introduction to Programming"),
  (2, "Ciss", 245, "Advanced Programming"),
  (3, "Ciss", 350, "Data Structures and Advanced Algorithms"),
  (4, "Ciss", 430, "Database Systems"),
  (5, "Math", 225, "Discrete Mathematics I"),
  (6, "Math", 325, "Discrete Mathematics II");

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
  (13, 2, 0, 4, 0);

insert into building values
  (0, "Buchanan Hall");

insert into room values
  (0, 0, 103),
  (1, 0, 104),
  (2, 0, 107);

insert into class values
  (0, 0, 1, "MWF", 1300, 1350),
  (1, 0, 2, "Tu", 1300, 1350),
  (2, 1, 0, "MWF", 1100, 1150),
  (3, 2, 0, "MWF", 900, 950);

insert into course_registration values
  (0, 0, 3);


SELECT 
    semester.season,
    semester.year,
    person.fname,
    person.lname,
    course.course_name,
    course.course_number,
    section.section_name,
    course.course_disc
FROM teaching_info ti
JOIN semester ON ti.semester_id = semester.id
JOIN instructor i ON ti.instructor_id = i.id
JOIN person ON i.person_id = person.id
JOIN course ON ti.course_id = course.id
JOIN section ON ti.section_id = section.id;