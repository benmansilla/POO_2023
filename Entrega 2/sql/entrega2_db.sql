drop table if exists benja_usuarios;

create table benja_usuarios(
id int not null auto_increment,
username text,
password text,
name text,
surname text,
email text,
failed_attempts int,
time_when_unblock int,
primary key(id)
)engine=InnoDB, default charset=utf8mb4, collate=utf8mb4_spanish_ci;

insert into benja_usuarios (id, username, password, name, surname, email, failed_attempts, time_when_unblock) values (null, 'benja', 'benman', 'Benjamin', 'Mansilla', 'ben@mansilla.com', 0, 0);
insert into benja_usuarios (id, username, password, name, surname, email, failed_attempts, time_when_unblock) values (null, 'facu', 'faculop', 'Facundo', 'Lopez', 'facu@lopez.com', 0, 0);
insert into benja_usuarios (id, username, password, name, surname, email, failed_attempts, time_when_unblock) values (null, 'agus', 'agusman', 'Agustina', 'Manrique', 'agus@manrique.com', 0, 0);
