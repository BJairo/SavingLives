USE NASA_V_DB;

create table PACIENTE(
id_paciente int AUTO_INCREMENT, 
nombre VARCHAR(20),
apellidos VARCHAR(30), 
fecha_nacimiento date,
sexo VARCHAR(10),
contacto INTEGER,
PRIMARY KEY(id_paciente)
);

insert into PACIENTE values
(1, 'Downs', 'Marsha', '1975-03-21', 'Femenino' , '912563256'),
(2,'Antonio','García Pérez','1960-08-15','Masculino','963689521'),
(3,'Carlos','Pérez Ruiz','1958-04-26','Masculino','962485147'),
(4,'Luis','Rodríguez Más','1961-03-30','Masculino','962965478'),
(5,'Jaime','Juangrán Sornes','1968-01-31','Masculino','963684596'),
(6,'Alfonso','Prats Montolla','1969-04-28','Masculino','963547852'),
(7,'José','Navarro Lard','1964-05-15','Masculino','963874569'),
(8,'Elisa','Úbeda Sansón','1962-07-10','Femenino','963547812'),
(9,'Eva','San Martín','1965-08-12','Femenino','962401589'),
(10,'Gerardo','Hernández Luis','1965-01-02','Masculino','963589621'),
(11,'Carlos','Prats Ruiz','1967-05-03','Masculino','963589654'),
(12,'Lourdes','Oliver Peris','1964-06-25','Femenino','963587412'),
(13,'Sergio','Larred Navas','1967-12-25','Masculino','963589621'),
(14,'Joaquín','Árboles Onsins','1969-05-04','Masculino','963758963');


create table DISCAPACIDAD(
id_paciente int AUTO_INCREMENT,
discapacidad VARCHAR(20),
PRIMARY KEY(id_paciente, discapacidad),
FOREIGN KEY(id_paciente) REFERENCES PACIENTE(id_paciente)
);

insert into DISCAPACIDAD values
(1, 'Esclerosis múltiple'),
(2, 'Devilidad visual'),
(3, 'Alzheimer'),
(4, 'Deficiencia auditiva'),
(5, 'Dificultad del habla'),
(6, 'Deficiencia auditiva'),
(7, 'Esclerosis múltiple'),
(8, 'Devilidad visual'),
(9, 'Alzheimer'),
(10, 'Deficiencia auditiva'),
(11, 'Dificultad del habla'),
(12, 'Deficiencia auditiva'),
(13, 'Deficiencia auditiva'),
(14, 'Esclerosis múltiple');

create table S_ACELEROMETRO(
id_acelerometro int AUTO_INCREMENT,
id_paciente int,
x FLOAT(4,2),
y FLOAT(4,2),
z FLOAT(4,2),
num_caidas INTEGER,
timestamp datetime DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY(id_acelerometro),
FOREIGN KEY(id_paciente) REFERENCES PACIENTE(id_paciente)
);

create table S_ULTRASONICA(
id_ultrasonico int AUTO_INCREMENT,
id_paciente int,
distancia FLOAT(4,2),
num_choques INTEGER,
timestamp datetime DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY(id_ultrasonico),
FOREIGN KEY(id_paciente) REFERENCES PACIENTE(id_paciente)
);

