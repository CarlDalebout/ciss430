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
